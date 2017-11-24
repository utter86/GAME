#ifndef COMBAT_H
#define COMBAT_H

#include <vector>

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"
#include "textinput.h"

class Combat
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS render();
  RET_NUMS doEvents(SDL_Event* event);
  int mouseMove();
  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);

private:
  Window* _window;
};
#endif // define
