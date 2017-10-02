#include "textureeditor.h"
RET_NUMS TextureEditor::init()
{
  setScene();
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::render(Window* window)
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  SDL_Rect tmpRect = {x - 25, y-25, 50, 50};

  window->render(BACK, 0,0, nullptr, nullptr);
  window->drawBorder(window->getRect(), &color);

  window->render(TEST, 1, 4, &tmpRect, NULL);
  window->drawBorder(&tmpRect, &color);

  _menu.render(window);

  window->render();

  return RET_SUCCESS;
}


RET_NUMS TextureEditor::setScene()
{
  RET_NUMS retNum = RET_FAILED;
  SDL_Color color = {255,0,0,255};
  _menu.init(MENU);
  Button* buttonPtr = new Button;
  buttonPtr->init(LOAD_IMAGE);
  buttonPtr->setText("LOAD IMAGE!", 0, 0, XSMALL);
  buttonPtr->setBorder(&color);

  Button* buttonPtr1 = new Button;
  buttonPtr1->init(CLOSE);
  buttonPtr1->setText("CLOSE!", 0, 0, XLARGE);
  buttonPtr1->setBorder(&color);

  _menu.addButton(buttonPtr);
  _menu.addButton(buttonPtr1);
  _menu.makeMenu(false, 'l');
  _menu.setPos( 50, 50);
  return retNum;
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
