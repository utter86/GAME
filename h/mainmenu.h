#ifndef MAINMENU_H
#define MAINMENU_H

#include "window.h"
#include "enums.h"
#include "error.h"

class MainMenu
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS render();

private:
  Error _error;
  Window* _window = NULL;
};

#endif //MAINMENU_H
