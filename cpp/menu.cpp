#include "menu.h"

RET_NUMS Menu::init(int id)
{
  _id = id;
  return RET_SUCCESS;
}

RET_NUMS Menu::render(Window* window)
{
  return RET_SUCCESS;
}

RET_NUMS Menu::addButton(Button* button)
{
  RET_NUMS retNum = RET_FAILED;
  if(button != NULL)
  {
    _buttonVector.push_back(button);
    retNum = RET_SUCCESS;
  }
  return retNum;
}

void Menu::close()
{
  free(_menuRect);
  for(std::vector<Button*>::iterator it = _buttonVector.begin(); it != _buttonVector.end(); it++)
  {
    (*it)->close();
    free(&(*it));
  }
}
