#include "window.h"


RET_NUMS Window::init(WindowSettings settings)
{
  //Init SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    _error.error("FAILED TO INIT SDL!", SDL_GetError());
  }
  //Init Png loading
  int initFlag = IMG_INIT_PNG;
  int initted = IMG_Init(initFlag);
  if((initted&initFlag) != initFlag)
  {
    _error.error("Failed to initialize SDL_image", IMG_GetError());
  }

  //Create window
  _window = SDL_CreateWindow("-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings.w, settings.h, SDL_WINDOW_ALLOW_HIGHDPI | settings.windowMode);
  if(_window == NULL)
  {
    _error.error("FAILED TO CREATE WINDOW!", SDL_GetError());
  }

  //Create renderer
  if(settings.vsync == SDL_RENDERER_PRESENTVSYNC)
  {
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }
  else
  {
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  }
  if(_renderer == NULL)
  {
    _error.error("FAILED TO CREATE RENDERER!", SDL_GetError());
  }
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

  _windowRect = {0, 0, settings.w, settings.h};
  _frames = 3;
  _speed = 10;
  _frame = 0;
  _acctualFrame = 0;

  loadMedia();
  return RET_SUCCESS;
}

RET_NUMS Window::loadMedia()
{
  loadFileOld(TEST, "./data/texture/test.text");
  loadFileOld(ALPHA, "./data/texture/alpha2.text");
  loadFileOld(BACK, "./data/texture/bg.text");
  return RET_SUCCESS;
}
void Window::loadFileOld(TEXTURE_ID id, std::string file)
{
  int rectNum = 0; int rectX; int rectY; int rectW; int rectH;
  //String to work with
  std::string::size_type pos1;
  std::string::size_type pos2;
  std::string valStr;
  //Load texture file
  std::string line;
  std::ifstream textureFile;
  textureFile.open (file);
  while(getline(textureFile,line))
  {
    if(line.find("TEXTURE:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = "./data/texture/";
      valStr.append(line.substr(pos1 + 1, pos2 - pos1 - 1));
      _textureFolder.addTexture(id, createTexture(valStr));
    }
    else if(line.find("RECT:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = line.substr(pos1 + 1, pos2 - pos1 -1);
      rectNum = atoi(valStr.c_str());
    }
    else if(line.find("X:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = line.substr(pos1 + 1, pos2 - pos1 -1);
      rectX = atoi(valStr.c_str());
    }
    else if(line.find("Y:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = line.substr(pos1 + 1, pos2 - pos1 -1);
      rectY = atoi(valStr.c_str());
    }
    else if(line.find("W:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = line.substr(pos1 + 1, pos2 - pos1 -1);
      rectW = atoi(valStr.c_str());
    }
    else if(line.find("H:") != std::string::npos)
    {
      pos1 = line.find(":");
      pos2 = line.find(";");
      valStr = line.substr(pos1 + 1, pos2 - pos1 -1);
      rectH = atoi(valStr.c_str());
      SDL_Rect* tmpRect = new SDL_Rect;
      *tmpRect = {rectX, rectY, rectW, rectH};
      _textureFolder.addRect(id, rectNum, tmpRect);
    }
  }
  textureFile.close();
}
void Window::loadPNG(TEXTURE_ID id, std::string file)
{
  //Add Texture
  SDL_Surface* tmpSurface = NULL;
  SDL_Texture* tmpTexture = NULL;

  //Load the file
  tmpSurface = IMG_Load(file.c_str());
  if (tmpSurface == NULL)
  {
    _error.error("Failed to load image", IMG_GetError());
  }
  else
  {
    //Set color key
    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

    //Creat the texture
    tmpTexture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
    if(tmpTexture == NULL)
    {
      _error.error("Failed to creat Texture from surface", SDL_GetError());
      exit(-1);
    }
    else
    {
      SDL_SetTextureBlendMode(tmpTexture, SDL_BLENDMODE_BLEND);
    }
  }
  SDL_Rect* tmpRect = new SDL_Rect;
  SDL_GetClipRect(tmpSurface, tmpRect);
  _textureFolder.addTexture(id, tmpTexture);
  _textureFolder.addRect(id, 0, tmpRect);
}
void Window::addTextureRect(TEXTURE_ID id, int rectNum, SDL_Rect* rect)
{
  _textureFolder.addRect(id, rectNum, rect);
}
SDL_Texture* Window::createTexture(std::string file)
{
  //Add Texture
  SDL_Surface* tmpSurface = NULL;
  SDL_Texture* tmpTexture = NULL;

  //Load the file
  tmpSurface = IMG_Load(file.c_str());
  if (tmpSurface == NULL)
  {
    _error.error("Failed to load image", IMG_GetError());
  }
  else
  {
    //Set color key
    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

    //Creat the texture
    tmpTexture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
    if(tmpTexture == NULL)
    {
      _error.error("Failed to creat Texture from surface", SDL_GetError());
      exit(-1);
    }
    else
    {
      SDL_SetTextureBlendMode(tmpTexture, SDL_BLENDMODE_BLEND);
    }
  }
  return tmpTexture;
}

RET_NUMS Window::render(TEXTURE_ID id, int start, int stop, SDL_Rect* dstRect, SDL_Rect* viewPort, double angle, SDL_RendererFlip flip)
{
  if(id == NONE)
  {
    _acctualFrame = _frame / _speed;
    if(_acctualFrame > _frames)
    {
      _frame = 0;
    }
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
    _frame++;
  }
  else
  {
    int rectNum = _acctualFrame + start;

    if(rectNum > stop)
    {
      rectNum = start;
    }

    SDL_Texture* tmpTexture = _textureFolder.getSDLTexture(id);
    SDL_Rect* srcRect = _textureFolder.getRect(id, rectNum);
    if(viewPort == NULL)
    {
      SDL_RenderSetViewport(_renderer, NULL);
    }
    else
    {
      SDL_RenderSetViewport(_renderer, viewPort);
    }
    SDL_RenderCopyEx(_renderer, tmpTexture, srcRect, dstRect, angle, NULL, flip);
  }
  return RET_SUCCESS;
}
void Window::drawBorder(SDL_Rect* rect, SDL_Color* color, SDL_Rect* viewPort)
{
  int x1 = rect->x;
  int y1 = rect->y;
  int x2 = rect->x + rect->w - 1;
  int y2 = rect->y + rect->h - 1;

  SDL_RenderSetViewport(_renderer, viewPort);
  SDL_SetRenderDrawColor(_renderer, color->r, color->g, color->b, color->a);
  SDL_RenderDrawLine(_renderer, x1, y1, x2, y1);
  SDL_RenderDrawLine(_renderer, x2, y1, x2, y2);
  SDL_RenderDrawLine(_renderer, x2, y2, x1, y2);
  SDL_RenderDrawLine(_renderer, x1, y2, x1, y1);
}
void Window::renderText(std::string text, int x, int y, int size, SDL_Color* color, SDL_Rect* viewPort)
{
  char tmpChar;
  int alphaPos;
  SDL_Rect dstRect = {x, y, size, int(size * 1.5)};
  setColorMod(ALPHA, color);
  for(std::string::iterator it = text.begin(); it != text.end(); it++)
  {
    tmpChar = std::toupper(*it);
    alphaPos = getAlphaPos(tmpChar);
    render(ALPHA, alphaPos, alphaPos, &dstRect, viewPort);
    dstRect.x += dstRect.w;
  }
}
void Window::fillRect(SDL_Rect* rect, SDL_Color* color)
{
  SDL_SetRenderDrawColor(_renderer, color->r, color->g, color->b, color->a);
  SDL_RenderFillRect(_renderer, rect);
}

void Window::close()
{
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
}

//Getters
SDL_Renderer* Window::getRenderer()
{
  return _renderer;
}
SDL_Texture* Window::getSDLTexture(TEXTURE_ID id)
{
  return _textureFolder.getSDLTexture(id);
}
SDL_Rect* Window::getRect(TEXTURE_ID id, int rectNum)
{
  if(id != NONE)
  {
    return _textureFolder.getRect(id, rectNum);
  }
  else
  {
    return &_windowRect;
  }
}
int Window::getAlphaPos(char tmpChar)
{
  int retInt;
  switch(tmpChar)
  {
    case '0':
      retInt =  1;
    break;
    case '1':
      retInt =  2;
    break;
    case '2':
      retInt =  3;
    break;
    case '3':
      retInt =  4;
    break;
    case '4':
      retInt =  5;
    break;
    case '5':
      retInt =  6;
    break;
    case '6':
      retInt =  7;
    break;
    case '7':
      retInt =  8;
    break;
    case '8':
      retInt =  9;
    break;
    case '9':
      retInt =  10;
    break;
    case '+':
      retInt =  11;
    break;
    case '-':
      retInt =  12;
    break;
    case '*':
      retInt =  13;
    break;
    case '/':
      retInt =  14;
    break;
    case '=':
      retInt =  15;
    break;
    case 'A':
      retInt =  16;
    break;
    case 'B':
      retInt =  17;
    break;
    case 'C':
      retInt =  18;
    break;
    case 'D':
      retInt =  19;
    break;
    case 'E':
      retInt =  20;
    break;
    case 'F':
      retInt =  21;
    break;
    case 'G':
      retInt =  22;
    break;
    case 'H':
      retInt =  23;
    break;
    case 'I':
      retInt =  24;
    break;
    case 'J':
      retInt =  25;
    break;
    case 'K':
      retInt =  26;
    break;
    case 'L':
      retInt =  27;
    break;
    case 'M':
      retInt =  28;
    break;
    case 'N':
      retInt =  29;
    break;
    case 'O':
      retInt =  30;
    break;
    case 'P':
      retInt =  31;
    break;
    case 'Q':
      retInt =  32;
    break;
    case 'R':
      retInt =  33;
    break;
    case 'S':
      retInt =  34;
    break;
    case 'T':
      retInt =  35;
    break;
    case 'U':
      retInt =  36;
    break;
    case 'V':
      retInt =  37;
    break;
    case 'W':
      retInt =  38;
    break;
    case 'X':
      retInt =  39;
    break;
    case 'Y':
      retInt =  40;
    break;
    case 'Z':
      retInt =  41;
    break;
    case '.':
      retInt =  42;
    break;
    case ':':
      retInt =  43;
    break;
    case ',':
      retInt =  44;
    break;
    case ';':
      retInt =  45;
    break;
    case '?':
      retInt =  46;
    break;
    case '!':
      retInt =  47;
    break;
    case '%':
      retInt =  48;
    break;
    case '&':
      retInt =  49;
    break;
    case '_':
      retInt =  50;
    break;
    case '(':
      retInt =  51;
    break;
    case ')':
      retInt =  52;
    break;
    case '<':
      retInt =  53;
    break;
    case '>':
      retInt =  54;
    break;
    case ' ':
      retInt =  55;
    break;

  }

  return retInt;
}

//Setters
RET_NUMS Window::setRenderer(SDL_Renderer* renderer)
{
  _renderer = renderer;
  return RET_SUCCESS;
}
RET_NUMS Window::setColorMod(TEXTURE_ID id, SDL_Color* color)
{
  if(color != NULL)
  {
    SDL_SetTextureColorMod(_textureFolder.getSDLTexture(id), color->r, color->g, color->b);
    return RET_SUCCESS;
  }
  return RET_FAILED;
}
