#include "menu.h"

RET_NUMS Menu::init(int id)
{
  _id = id;
  _border = false;
  *_menuRect = {0, 0, 0, 0};
  active = false;
  _borderColor = {0,0,0,0};
  return RET_SUCCESS;
}

RET_NUMS Menu::render(Window* window)
{
  SDL_Color color = {0, 255, 255, 255};
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    (*it)->render(window);
  }
  window->drawBorder(_menuRect, &color);
  return RET_SUCCESS;
}

RET_NUMS Menu::addButton(Button* button)
{
  RET_NUMS retNum = RET_FAILED;
  if(button != NULL)
  {
    if(getButton(button->getID()) == NULL)
    {
      button->setViewport(_menuRect);
      _buttonVector.push_back(button);
      retNum = RET_SUCCESS;
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
      newH = newY;
      newW += 2;
    }
    else
    {
      newX += tmpRect->w  + 1;
      newW = newX;
      newH += 2;
    }
  }

  _menuRect->w = newW;
  _menuRect->h = newH + 2;

  tmpRect = NULL;
  delete tmpRect;
  return RET_SUCCESS;
}

void Menu::close()
{
  free(_menuRect);
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
//setters
RET_NUMS Menu::setPos(int x, int y)
{
  _menuRect->x = x;
  _menuRect->y = y;
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
