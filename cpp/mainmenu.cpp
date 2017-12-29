#include "mainmenu.h"

RET_NUMS MainMenu::init(Window* window)
{
  _window = window;
  return RET_SUCCESS;
}

RET_NUMS MainMenu::render()
{
  if(_window != NULL)
  {
    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_Color color = {255, 0, 0, 255};
    SDL_Rect tmpRect = {x - 25, y-25, 50, 50};

    _window->render(BACK, 0,0, NULL, NULL);
    _window->drawBorder(_window->getRect(), &color);

    _window->render(TEST, 1, 4, &tmpRect, NULL);
    _window->drawBorder(&tmpRect, &color);

    _window->render();
  }
  return RET_SUCCESS;
}
