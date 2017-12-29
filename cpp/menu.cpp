#include "menu.h"

RET_NUMS Menu::init(int id)
{
  _buttonVector.clear();
  _id = id;
  _border = false;
  active = false;
  _borderColor = {0,0,0,0};
  _bgColor = {0,0,0,0};
  return RET_SUCCESS;
}
int Menu::mouseMove()
{
  int retInt = RET_FAILED;
  int x, y;
  SDL_GetMouseState(&x, &y);
  if(x > _menuRect->x && x < _menuRect->x + _menuRect->w &&
    y > _menuRect->y && y < _menuRect->y + _menuRect->h)
  {
    retInt = RET_SUCCESS;
    for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
    {
      if((*it)->mouseMove())
      {
        retInt = (*it)->getID();
      }
    }
  }
  return retInt;
}
RET_NUMS Menu::render(Window* window)
{
  if(active)
  {
    window->fillRect(_menuRect, &_bgColor);
    for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
    {
      (*it)->render(window);
    }
    window->drawBorder(_menuRect, &_borderColor);
  }

  return RET_SUCCESS;
}

RET_NUMS Menu::addButton(Button* button)
{
  RET_NUMS retNum = RET_FAILED;
  if(button != NULL)
  {
    if(getButtonFromFocusNum(button->getFocusNum()) != NULL)
    {
      _error.error("Focus Num taken!", SDL_GetError());
    }
    else
    {
      button->setViewport(_menuRect);
      _buttonVector.push_back(button);
    }
  }
  return retNum;
}
RET_NUMS Menu::makeMenu(bool xAxis)
{
  SDL_Rect* tmpRect = new SDL_Rect;
  int newX = 2, newY = 2, newW = 0, newH = 0;

  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    tmpRect = (*it)->getRect();
    newW = std::max(tmpRect->w, newW);
    newH = std::max(tmpRect->h, newH);
    (*it)->setPos(newX, newY);
    if(!xAxis)
    {
      newY += tmpRect->h + 1;
    }
    else
    {
      newX += tmpRect->w  + 1;
    }
  }

  tmpRect = NULL;
  delete tmpRect;
  return RET_SUCCESS;
}
RET_NUMS Menu::setFocus(int num)
{
  RET_NUMS retNum = RET_SUCCESS;
  _focusNum = num;
  return retNum;
}

void Menu::clearMenu()
{
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    (*it)->close();
    delete (*it);
  }
  _buttonVector.clear();
}
void Menu::close()
{
  delete(_menuRect);
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    (*it)->close();
    delete &(*it);
  }
}

//Getters
Button* Menu::getButton(int id)
{
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    if((*it)->getID() == id)
    {
      return (*it);
    }
  }
  return NULL;
}
Button* Menu::getButtonFromFocusNum(int num)
{
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    if((*it)->getFocusNum() == num)
    {
      return (*it);
    }
  }
  return NULL;
}
SDL_Rect* Menu::getRect()
{
  return _menuRect;
}
int Menu::getID()
{
  return _id;
}
//setters
RET_NUMS Menu::setPos(int x, int y)
{
  _menuRect->x = x;
  _menuRect->y = y;
  return RET_SUCCESS;
}
RET_NUMS Menu::setSize(int w, int h)
{
  _menuRect->w = w;
  _menuRect->h = h;
  return RET_SUCCESS;
}
RET_NUMS Menu::setBorder(SDL_Color* color)
{
  if(color != NULL)
  {
    _border = true;
    _borderColor = *color;
    return RET_SUCCESS;
  }
  return RET_FAILED;
}
RET_NUMS Menu::setBGColor(SDL_Color* color)
{
  if(color != NULL)
  {
    _bgColor = *color;
  }
  return RET_FAILED;
}
RET_NUMS Menu::setTextColor(int id, SDL_Color* color)
{
    for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
    {
      if(id == -1)
      {
        (*it)->setTextColor(color);
      }
      else
      {
        if((*it)->getID() == id)
        {
          (*it)->setTextColor(color);
          return RET_SUCCESS;
        }
      }
    }
  return RET_FAILED;
}
