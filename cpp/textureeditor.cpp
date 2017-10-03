#include "textureeditor.h"

RET_NUMS TextureEditor::init(Window* window)
{
  _window = window;
  _inFileRect = {10,10,500,500};
  setScene();
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::render()
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  SDL_Rect tmpRect = {x - 25, y-25, 50, 50};

  _window->render(BACK, 0,0, nullptr, nullptr);
  _window->drawBorder(_window->getRect(), &color);

  _window->render(TEST, 1, 4, &tmpRect, NULL);
  _window->drawBorder(&tmpRect, &color);


  _window->render(IN_FILE, 0, 0, &_inFileRect, NULL);
  _menu.render(_window);
  _rectListMenu.render(_window);

  _window->render();

  return RET_SUCCESS;
}

RET_NUMS TextureEditor::mouseMove()
{
  int tmpInt = _menu.mouseMove();
  SDL_Color color = {255,0,0,255};
  _menu.setTextColor(-1, &color);
  color = {0,255,0,255};
  _menu.setTextColor(tmpInt, &color);
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::keyUp(int key)
{
  switch(key)
  {
    case SDLK_F1:

    break;
  }
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::click(int button)
{
  switch(button)
  {
    case SDL_BUTTON_LEFT:
      switch(_menu.mouseMove())
      {
        case CLOSE:
          exit(99);
        break;
        case LOAD_IMAGE:
          _window->loadPNG(IN_FILE, "./data/in/in.png");
          SDL_Rect tmpRect = *_window->getRect();
          _inFileRect = *_window->getRect(IN_FILE, 0);
          _inFileRect.x = tmpRect.w / 2 - _inFileRect.w / 2;
          _inFileRect.y = tmpRect.h / 2 - _inFileRect.h / 2;
          getInFileRects();
        break;
      }
    break;
    case SDL_BUTTON_RIGHT:

    break;
  }
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::setScene()
{
  RET_NUMS retNum = RET_FAILED;
  SDL_Color color = {255,0,0,255};
  SDL_Color bgColor = {0,0,0,255};
  _menu.init(MENU);
  Button* buttonPtr = new Button;
  buttonPtr->init(LOAD_IMAGE);
  buttonPtr->setText("LOAD IMAGE", 0, 0, XSMALL);
  buttonPtr->setBorder(&color);
  buttonPtr->setBGColor(&bgColor);

  Button* buttonPtr1 = new Button;
  buttonPtr1->init(CLOSE);
  buttonPtr1->setText("CLOSE", -1, -1, XLARGE);
  buttonPtr1->setBorder(&color);

  _menu.addButton(buttonPtr);
  _menu.addButton(buttonPtr1);
  _menu.setBorder(&color);
  color = {0,0,0,255};
  _menu.setBGColor(&color);
  _menu.makeMenu();
  _menu.setPos( 0, 0);
  _menu.active = true;

  return retNum;
}

void TextureEditor::getInFileRects()
{
  bool isDone = false;
  int counter = 0;
  SDL_Rect* tmpRect = new SDL_Rect;
  _rectListMenu.close();
  _rectListMenu.init(RECT_LIST);
  _rectListMenu.active = true;
  while(!isDone)
  {
    tmpRect = _window->getRect(IN_FILE, counter);
    if(tmpRect->x >-1)
    {
      std::cout << "HEJ\n";
      Button* buttonPtr = new Button;

      std::string tmpString = "Rect: ";
      tmpString.append(std::to_string(counter));
      tmpString.append("X: ");
      tmpString.append(std::to_string(tmpRect->x));
      tmpString.append("Y: ");
      tmpString.append(std::to_string(tmpRect->y));
      tmpString.append("W: ");
      tmpString.append(std::to_string(tmpRect->w));
      tmpString.append("H: ");
      tmpString.append(std::to_string(tmpRect->h));
      buttonPtr->init(counter);
      buttonPtr->setText(tmpString,-1,-1, LARGE);
    }
    else
    {
      isDone = true;
    }
    counter ++;
  }
  //delete tmpRect;
  //tmpRect = NULL;
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
