#include "mainmenu.h"

RET_NUMS MainMenu::init()
{
  return RET_SUCCESS;
}

RET_NUMS MainMenu::render(Window* window)
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  SDL_Rect tmpRect = {x - 25, y-25, 50, 50};

  window->render(BACK, 0,0, NULL, NULL);
  window->drawBorder(window->getRect(), &color);

  window->render(TEST, 1, 4, &tmpRect, NULL);
  window->drawBorder(&tmpRect, &color);

  window->render();

  return RET_SUCCESS;
}
