#include "textureeditor.h"

RET_NUMS TextureEditor::init(Window* window)
{
  _window = window;
  _rectNum = 1;
  _text.init();
  setScene();
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::render()
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  _window->render(BACK, 0,0, nullptr, nullptr);
  _window->drawBorder(_window->getRect(), &color);

  _window->render(IN_FILE, 0,0, _inFileRect, NULL);

  _menu.render(_window);
  _rectListMenu.render(_window);

  bool isDone = false;
  int counter = 0;

  //Draw all rects in texture red;
  while(!isDone)
  {
    SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);

    if(tmpRect != NULL)
    {
      SDL_Rect drawRect = *tmpRect;
      drawRect.x += _inFileRect->x;
      drawRect.y += _inFileRect->y;
      _window->drawBorder(&drawRect, &color);
      counter++;
    }
    else
    {
      isDone = true;
    }
  }

  //Draw active rect green
  SDL_Color activeColor = {0, 255, 0, 255};
  if(_activeRect != NULL)
  {
    SDL_Rect tmpRect = *_activeRect;
    tmpRect.x += _inFileRect->x;
    tmpRect.y += _inFileRect->y;
    _window->drawBorder(&tmpRect, &activeColor);
  }
  //Render lables
  SDL_Color* tmpColor = new SDL_Color;
  *tmpColor = {255, 0, 0, 255};
  _window->setColorMod(ALPHA, tmpColor);
  delete tmpColor;
  tmpColor = NULL;
  _window->renderText("F1 Add Rect.", 0,50, SMALL);
  _window->renderText("F2 Make grid.", 0, 80, SMALL);
  _window->renderText("F3 Save file.", 0,65, SMALL);
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::doEvents(SDL_Event* event)
{
  switch(event->type)
  {
    case SDL_KEYUP:
      return keyUp(event->key.keysym.sym);
    break;
    case SDL_MOUSEBUTTONUP:
      return click(event->button.button);
    break;
    default:
      mouseMove();
    break;
  }
  switch(_text.update(event))
  {
    case RET_SUCCESS:

    break;
    case RET_FULL:

    break;
    default:

    break;
  }
  return RET_SUCCESS;
}

RET_NUMS TextureEditor::mouseMove()
{
  int tmpInt = _menu.mouseMove();
  SDL_Color color = {255,0,0,255};
  _menu.setTextColor(-1, &color);
  color = {0,255,0,255};
  _menu.setTextColor(tmpInt, &color);
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::keyUp(int key)
{
    RET_NUMS retNum = RET_SUCCESS;
  switch(key)
  {
    case SDLK_F1:
      addRect();
      getInFileRects();
    break;
    case SDLK_F2:
      _text.start();
    break;
    case SDLK_F5:

    break;
    case SDLK_F4:
      makeGrid();
    break;
    case SDLK_F8:
      saveFile();
    break;
    case SDLK_F7:
      loadFile();
    break;
    case SDLK_RETURN:
      _text.stop();
    break;
  }
  return retNum;
}
RET_NUMS TextureEditor::click(int button)
{
  switch(button)
  {
    case SDL_BUTTON_LEFT:
      switch(_menu.mouseMove())
      {
        case CLOSE:
          exit(99);
        break;
        case LOAD_IMAGE:
          if(_inFileRect == NULL)
          {
            SDL_Rect tmpRect = *_window->getRect();
            _inFileRect = new SDL_Rect;
            _window->loadPNG(IN_FILE, "./data/in/in.png");
            *_inFileRect = *_window->getRect(IN_FILE, 0);
            _inFileRect->x = tmpRect.w / 2 - _inFileRect->w / 2;
            _inFileRect->y = tmpRect.h / 2 - _inFileRect->h / 2;
            getInFileRects();
          }
        break;
      }
    break;
    case SDL_BUTTON_RIGHT:

    break;
  }
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::setScene()
{
  RET_NUMS retNum = RET_FAILED;

  SDL_Color color = {255,0,0,255};
  SDL_Color bgColor = {0,0,0,255};

  //Menu menu
  _menu.init(MENU);
  //Load image button
  Button* buttonPtr = new Button;
  buttonPtr->init(LOAD_IMAGE);
  buttonPtr->setText("LOAD IMAGE", 0, 0, XSMALL);
  buttonPtr->setBorder(&color);
  buttonPtr->setBGColor(&bgColor);
  _menu.addButton(buttonPtr);
  //Close button
  buttonPtr = NULL;
  buttonPtr = new Button;
  buttonPtr->init(CLOSE);
  buttonPtr->setText("CLOSE", -1, -1, XLARGE);
  buttonPtr->setBorder(&color);
  _menu.addButton(buttonPtr);
  //Set menu!
  _menu.setBorder(&color);
  color = {0,0,0,255};
  _menu.setBGColor(&color);
  _menu.makeMenu();
  _menu.setPos( 0, 0);
  _menu.active = true;

  //Rect List menu
  _rectListMenu.init(RECT_LIST);
  _rectListMenu.active = false;
  return retNum;
}

void TextureEditor::getInFileRects()
{
  int counter = 0;
  _rectListMenu.clearMenu();
  _rectListMenu.init(RECT_LIST);
  SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);
  while(tmpRect != NULL)
  {
    Button* buttonPtr =  new Button;
    buttonPtr->init(counter);
    std::string tmpString = "Rect: ";
    tmpString.append(std::to_string(counter));
    tmpString.append(", X: ");
    tmpString.append(std::to_string(tmpRect->x));
    tmpString.append(", Y: ");
    tmpString.append(std::to_string(tmpRect->y));
    tmpString.append(", W: ");
    tmpString.append(std::to_string(tmpRect->w));
    tmpString.append(", H: ");
    tmpString.append(std::to_string(tmpRect->h));
    buttonPtr->setText(tmpString, -1, -1, XSMALL);
    _rectListMenu.addButton(buttonPtr);
    counter++;
    tmpRect = _window->getRect(IN_FILE, counter);
  }
  _rectListMenu.makeMenu();
  tmpRect = _window->getRect();
  int wW = tmpRect->w;
  tmpRect = _rectListMenu.getRect();
  _rectListMenu.setPos(wW - tmpRect->w - 5,0);
  _rectListMenu.active = true;
}
void TextureEditor::addRect()
{
  if(_inFileRect != NULL)
  {

    SDL_Rect* tmpRect = new SDL_Rect;
    *tmpRect = {0,0,50,50};
    _window->addTextureRect(IN_FILE, _rectNum, tmpRect);
    _activeRect = tmpRect;
    _rectNum++;
  }
  else
  {
    std::cout << "NOPE\n";
  }

}
void TextureEditor::makeGrid()
{
  int rows = 0;
  int lines = 0;
  int tmpW = 0;
  int tmpH = 0;
  int tmpX = 0;
  int tmpY = 0;
  int counter = 1;
  std::cout << "Rows: ";
  std::cin >> rows;
  std::cout << "Lines: ";
  std::cin >> lines;
  tmpW = _inFileRect->w / rows;
  tmpH = _inFileRect->h / lines;
  for(int y; y < lines; y++)
  {
    for(int x; x < rows; x++)
    {
      SDL_Rect* tmpRect = new SDL_Rect;
      *tmpRect = {tmpX, tmpY, tmpW, tmpH};
      _window->addTextureRect(IN_FILE, counter, tmpRect);
      tmpX += tmpW;
      counter++;
    }
    tmpY += tmpH;
  }
  getInFileRects();
}

void TextureEditor::saveFile()
{
  SDL_RWops* file = SDL_RWFromFile("./data/out/out.rect", "wb");
  int rectSize = sizeof(SDL_Rect);
  int counter = 0;
  if(file != NULL)
  {
    SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);
    while(tmpRect != NULL)
    {
      SDL_RWwrite(file, tmpRect, rectSize, 1);
      counter++;
      tmpRect = _window->getRect(IN_FILE, counter);
    }
  }
  SDL_RWclose(file);

  file = SDL_RWFromFile("./data/out/out.texture", "wb");
  SDL_Texture* tmpTexture = _window->getSDLTexture(IN_FILE);
  int textSize = sizeof(tmpTexture);
  if(file != NULL)
  {
    SDL_RWwrite(file, tmpTexture, textSize, 1);
  }
  SDL_RWclose(file);

  file = SDL_RWFromFile("./data/out/out", "wb");
  int idPtr = IN_FILE;
  int intSize = sizeof(int);
  if(file != NULL)
  {
    SDL_RWwrite(file, &idPtr, intSize, 1);
  }
  SDL_RWclose(file);
}
void TextureEditor::loadFile()
{
  SDL_RWops* rectFile = SDL_RWFromFile("./data/out/out.rect", "rb");
  int fileSize = SDL_RWsize(rectFile);
  int rectSize = sizeof(SDL_Rect);
  int current = 1;
  int loaded = 0;
  SDL_Rect* rectPtr = (SDL_Rect*)malloc(fileSize);
  while(loaded < fileSize && current != 0)
  {
    current = SDL_RWread(rectFile, rectPtr, rectSize, 1);
    _error.printRect(rectPtr);
    rectPtr += current;
    loaded += rectSize;
  }
  SDL_RWclose(rectFile);

  SDL_RWops* textFile = SDL_RWFromFile("./data/out/out.text", "rb");
  fileSize = SDL_RWsize(textFile);
  SDL_Texture* tmpTexture = (SDL_Texture*)malloc(fileSize);
  SDL_RWread(textFile, tmpTexture, fileSize, 1);
  SDL_RWclose(textFile);
}
