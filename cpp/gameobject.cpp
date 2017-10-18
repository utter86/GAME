#include "gameobject.h"


RET_NUMS GameObject::init(int id)
{
  close();
  _id = id;
  _objectRect = {0, 0, 0, 0};
  _objX = 0;
  _objY = 0;
  _border = false;
  _borderColor = {255, 0, 0, 255};
  _bgColor = {0, 0, 0, 0};
  _textColor = {255,0,0,255};
  return RET_SUCCESS;
}

bool GameObject::mouseMove()
{
  bool retBool = false;
  int x; int y;
  SDL_GetMouseState(&x, &y);
  if(x > _objectRect.x && x < _objectRect.x + _objectRect.w &&
  y > _objectRect.y && y < _objectRect.y + _objectRect.h)
  {
    retBool = true;
  }
  return retBool;
}

RET_NUMS GameObject::render(Window* window)
{
  if(_viewPort != NULL)
  {
    _objectRect.x = _viewPort->x + _objX;
    _objectRect.y = _viewPort->y + _objY;
  }
  else
  {
    _objectRect.x = _objX;
    _objectRect.y = _objY;
  }
  window->fillRect(&_objectRect, &_bgColor);
  if(_textId != NONE)
  {
    window->render(_textId, _start, _stop, &_textureDestRect, &_objectRect);
  }
  if(_text.length() > 0)
  {
    if(_textX == -1)
    {
      int textW = _textSize * _text.length();
      _textX = _objectRect.w / 2 - textW / 2;
    }
    if(_textY == -1)
    {
      int textH = _textSize * 1.5;
      _textY = _objectRect.h / 2 - textH / 2;
    }
    window->renderText(_text, _textX, _textY, _textSize, &_textColor, &_objectRect);
  }
  if(_border)
  {
    SDL_Rect tmpRect = {0, 0, _objectRect.w, _objectRect.h};
    window->drawBorder(&tmpRect, &_borderColor, &_objectRect);
  }
  return RET_SUCCESS;
}

void GameObject::close()
{
  _id = -1;
  _border = false;
  _textId = NONE;
  _start = 0;
  _stop = 0;
  _textureDestRect = {0,0,0,0};
  _angle = 0.0f;
  _flip = SDL_FLIP_NONE;
  _text = "";
  _textX = 0;
  _textY = 0;
  _objectRect = {0,0,0,0};
  _viewPort = NULL;
}

//Getters
int GameObject::getID()
{
  return _id;
}
SDL_Rect* GameObject::getRect()
{
  return &_objectRect;
}

//Setters
void GameObject::setTexture(TEXTURE_ID ID, int start, int stop, SDL_Rect dstRect, double angle, SDL_RendererFlip flip)
{
  _textId = ID;
  _start = start;
  _stop = stop;
  _textureX = dstRect.x;
  _textureY = dstRect.y;
  _textureDestRect = dstRect;
}
void GameObject::setText(std::string text, int x, int y, int size, SDL_Color* color)
{
  _text = text;
  _textX = x;
  _textY = y;
  _textSize = size;
  if(color != NULL)
  {
    _textColor = *color;
  }
  if(_textId  == NONE)
  {
    fitRect();
  }
}
void GameObject::setBGColor(SDL_Color* color)
{
  _bgColor = *color;
}
void GameObject::setTextColor(SDL_Color* color)
{
  _textColor = *color;
}
void GameObject::setPos(int x, int y)
{
  _objX = x;
  _objY = y;
}
void GameObject::setSize(int w, int h)
{
  _objectRect.w = w;
  _objectRect.h = h;
}
void GameObject::setRect(SDL_Rect rect)
{
  _objectRect = rect;
}
void GameObject::setBorder(SDL_Color* color)
{
  if(color == NULL)
  {
    _border = false;
  }
  else
  {
    _border = true;
    _borderColor = *color;
  }
}
void GameObject::setViewport(SDL_Rect* viewPort)
{
  _viewPort = viewPort;
}
void GameObject::fitRect(bool texture)
{
  if(texture)
  {
    _objectRect.w = _textureDestRect.x + _textureDestRect.w;
    _objectRect.h = _textureDestRect.y + _textureDestRect.h;
  }
  else
  {
    _objectRect.w = _text.length() * _textSize;
    _objectRect.h = _textSize * 1.5;
  }
}
