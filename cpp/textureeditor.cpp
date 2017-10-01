#include "textureeditor.h"
RET_NUMS TextureEditor::init()
{
  SDL_Rect tmpRect = {0, 0, 50,50};
  SDL_Color tmpColor = {0, 255, 255, 255};
  _testView = {250,250, 700, 300};
  _testObject.init(0);
  _testObject.setTexture(ALPHA, 11, 11, tmpRect);
  _testObject.fitRect(true);
  _testObject.setPos(100, 100);
  _testObject.setBorder(&tmpColor);
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::render(Window* window)
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  SDL_Rect tmpRect = {x - 25, y-25, 50, 50};

  window->render(BACK, 0,0, NULL, NULL);
  window->drawBorder(window->getRect(), &color);

  _testView = {250, 250, 700, 300};
  _testObject.setViewport(&_testView);
  _testObject.render(window);
  window->drawBorder(&_testView, &color, NULL);

  window->render(TEST, 1, 4, &tmpRect, NULL);
  window->drawBorder(&tmpRect, &color);
  window->render();

  return RET_SUCCESS;
}

void TextureEditor::saveFile()
{
  SDL_Rect tmpRect = {0, 0, 184, 184};
  SDL_RWops* file = SDL_RWFromFile("./data/texture/test", "wb");
  int rectSize = sizeof(tmpRect);
  if(file != NULL)
  {
    SDL_RWwrite(file, &tmpRect, rectSize, 1);
    tmpRect = {0, 0, 92, 92};
    SDL_RWwrite(file, &tmpRect, rectSize, 1);
    tmpRect = {92, 0, 92, 92};
    SDL_RWwrite(file, &tmpRect, rectSize, 1);
    tmpRect = {0, 92, 92, 92};
    SDL_RWwrite(file, &tmpRect, rectSize, 1);
    tmpRect = {92, 92, 92, 92};
    SDL_RWwrite(file, &tmpRect, rectSize, 1);
  }
  SDL_RWclose(file);
}
void TextureEditor::loadFile()
{

  SDL_RWops* file = SDL_RWFromFile("./data/texture/test", "rb");
  int fileSize = SDL_RWsize(file);
  int rectSize = sizeof(SDL_Rect);
  int current = 1;
  int loaded = 0;
  SDL_Rect* rectPtr = (SDL_Rect*)malloc(fileSize);
  while(loaded < fileSize && current != 0)
  {
    current = SDL_RWread(file, rectPtr, rectSize, 1);
    _error.printRect(rectPtr);
    rectPtr += current;
    loaded += rectSize;
  }
  SDL_RWclose(file);
}
