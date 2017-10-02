#ifndef MENU_H
#define MENU_H

#include "window.h"
#include "enums.h"
#include "error.h"
#include "gameobject.h"

class Menu
{
public:
  RET_NUMS init(int id);
  RET_NUMS render(Window* window);

  RET_NUMS addButton(Button* button);

  void close();
private:
  int _id;
  SDL_Rect* _menuRect = new SDL_Rect;
  std::vector<Button*> _buttonVector;
  Error _error;
};

#endif //MENU_H
