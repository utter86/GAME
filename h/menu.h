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
  int mouseMove();
  RET_NUMS render(Window* window);

  RET_NUMS addButton(Button* button);
  RET_NUMS makeMenu(bool xAxis = false);

  void clearMenu();
  void close();

  //Getters
  Button* getButton(int id);
  SDL_Rect* getRect();
  int getID();

  //Setters
  RET_NUMS setPos(int x, int y);
  RET_NUMS setSize(int w, int h);
  RET_NUMS setBorder(SDL_Color* color = NULL);
  RET_NUMS setBGColor(SDL_Color* color);
  RET_NUMS setTextColor(int id, SDL_Color* color);

  bool active;

private:
  int _id;
  bool _border;
  SDL_Color _borderColor;
  SDL_Color _bgColor;
  SDL_Rect* _menuRect = new SDL_Rect;

  std::vector<Button*> _buttonVector;

  Error _error;
};

#endif //MENU_H
