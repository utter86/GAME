#ifndef MAINMENU_H
#define MAINMENU_H

#include "window.h"
#include "enums.h"
#include "error.h"

class MainMenu
{
public:
  RET_NUMS init();
  RET_NUMS render(Window* window);

private:
  Error _error;
};

#endif //MAINMENU_H
