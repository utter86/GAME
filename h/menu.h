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
  RET_NUMS makeMenu(bool xAxis = false, char alignment = 'l');

  void close();

  //Getters
  Button* getButton(int id);
  //Setters
  RET_NUMS setPos(int x, int y);
  RET_NUMS setBorder(SDL_Color* color = NULL);


  bool active;

private:
  int _id;
  bool _border;
  SDL_Color _borderColor;
  SDL_Rect* _menuRect = new SDL_Rect;

  std::vector<Button*> _buttonVector;

  Error _error;
};

#endif //MENU_H
