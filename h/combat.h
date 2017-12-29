#ifndef COMBAT_H
#define COMBAT_H

#include <vector>

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"
#include "textinput.h"


enum OBJECT
{
  OBJ_ARROWUP = 1000, OBJ_ARROWUR, OBJ_ARROWUL, OBJ_ARROWDOWN,
  OBJ_ARROWDR, OBJ_ARROWDL, OBJ_ARROWLEFT, OBJ_ARROWRIGHT,
  OBJ_ONE, OBJ_TWO, OBJ_THREE, OBJ_FOUR, OBJ_NONE,
};

class Combat
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS initStick();

  RET_NUMS render();
  RET_NUMS renderDir();

  RET_NUMS doEvents(SDL_Event* event);
  int mouseMove();
  RET_NUMS keyDown(int key);
  RET_NUMS controllerButtonDown(int button);
  RET_NUMS controllerButtonUp(int button);
  RET_NUMS click(int button);

  RET_NUMS setScene();

  RET_NUMS moveLeft();
  RET_NUMS moveRight();
  RET_NUMS moveUp();
  RET_NUMS moveDown();

  RET_NUMS buttonDownOne();
  RET_NUMS buttonDownTwo();
  RET_NUMS buttonDownThree();
  RET_NUMS buttonDownFour();

  OBJECT _direction;
  OBJECT _button;

  SDL_Color* _activeColor = NULL;
  SDL_Color* _inActiveColor = NULL;

  std::vector<GameObject> _gameObjects;

  Error _error;

  SDL_GameController* _controller = NULL;

private:
  Window* _window;
};
#endif // define
