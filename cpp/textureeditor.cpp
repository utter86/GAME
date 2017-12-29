#include "textureeditor.h"

RET_NUMS TextureEditor::init(Window* window)
{
  _window = window;
  _rectNum = 1;
  _text.init();
  setScene();
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::render()
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  SDL_Color color = {255, 0, 0, 255};
  _window->render(BACK, 0,0, nullptr, nullptr);
  _window->drawBorder(_window->getRect(), &color);

  _window->render(IN_FILE, 0,0, _inFileRect, NULL);

  bool isDone = false;
  int counter = 0;

  //Draw all rects in texture red;
  while(!isDone)
  {
    SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);

    if(tmpRect != NULL)
    {
      SDL_Rect drawRect = *tmpRect;
      drawRect.x += _inFileRect->x;
      drawRect.y += _inFileRect->y;
      _window->drawBorder(&drawRect, &color);
      counter++;
    }
    else
    {
      isDone = true;
    }
  }
  //Draw active rect green
  SDL_Color activeColor = {0, 255, 0, 255};
  if(_activeRect != NULL)
  {
    SDL_Rect tmpRect = *_activeRect;
    tmpRect.x += _inFileRect->x;
    tmpRect.y += _inFileRect->y;
    _window->drawBorder(&tmpRect, &activeColor);
  }

  for(std::vector<Menu>::iterator it = _menus.begin(); it != _menus.end(); it++)
  {
    (*it).render(_window);
  }
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::doEvents(SDL_Event* event)
{
  if(_text.active())
  {
    textUpdate(event);
  }
  else
  {
    switch(event->type)
    {
    case SDL_KEYUP:
      return keyUp(event->key.keysym.sym);
    break;
    case SDL_MOUSEBUTTONUP:
      return click(event->button.button);
    break;
    default:
      mouseMove();
    break;
    }
  }
  return RET_SUCCESS;
}
RET_NUMS TextureEditor::mouseMove()
{
  RET_NUMS retNum = RET_FAILED;
  SDL_Color color = {255,0,0,255};

  int tmpID;
  int tmpInt;
  for(std::vector<Menu>::iterator it = _menus.begin(); it != _menus.end(); it++)
  {
    (*it).setTextColor(-1, &color);
  }

  for(std::vector<Menu>::iterator it = _menus.begin(); it != _menus.end(); it++)
  {
    tmpID = (*it).getID();
    tmpInt = (*it).mouseMove();
    switch(tmpID)
    {
      case TOP_MENU:
        color = {0,255,0,255};
        (*it).setTextColor(tmpInt, &color);
      break;
    }
  }
  return retNum;
}
RET_NUMS TextureEditor::keyUp(int key)
{
  RET_NUMS retNum = RET_SUCCESS;
  switch(key)
  {
    case SDLK_F1:
      addRect();
    break;
    case SDLK_F2:

    break;
    case SDLK_F3:

    break;
    case SDLK_F4:

    break;
    case SDLK_F8:

    break;
    case SDLK_F7:

    break;
    case SDLK_RETURN:
      _text.stop();
    break;
  }
  return retNum;
}
RET_NUMS TextureEditor::click(int button)
{
  RET_NUMS retNum = RET_SUCCESS;
  if(topMenuClick() == RET_FAILED)
  {
    return RET_FAILED;
  }
  addRectClick();
  return retNum;
}
RET_NUMS TextureEditor::topMenuClick()
{
  RET_NUMS retNum = RET_SUCCESS;
  Menu* tmpMenu = getMenu(TOP_MENU);
  if(tmpMenu != NULL)
  {
    switch(tmpMenu->mouseMove())
    {
      case CLOSE:
        retNum = RET_FAILED;
      break;

      case LOAD_IMAGE:
        if(_inFileRect == NULL)
        {
          SDL_Rect tmpRect = *_window->getRect();
          _inFileRect = new SDL_Rect;
          _window->loadPNG(IN_FILE, "./data/in/in.png");
          *_inFileRect = *_window->getRect(IN_FILE, 0);
          _inFileRect->x = tmpRect.w / 2 - _inFileRect->w / 2;
          _inFileRect->y = tmpRect.h / 2 - _inFileRect->h / 2;
          getInFileRects();
        }
        retNum = RET_SUCCESS;
      break;

      case RET_SUCCESS:
        retNum = RET_SUCCESS;
      break;
    }
  }
  return retNum;
}
RET_NUMS TextureEditor::addRectClick()
{
  RET_NUMS retNum = RET_SUCCESS;
  Menu* tmpMenu = getMenu(ADD_RECT);
  switch(tmpMenu->mouseMove())
  {
    case OK:

    break;
    case CANCEL:
      tmpMenu->active = false;
    break;
  }
  return retNum;
}

RET_NUMS TextureEditor::textUpdate(SDL_Event* event)
{
  _text.update(event);
  return RET_FAILED;
}

RET_NUMS TextureEditor::setScene()
{
  RET_NUMS retNum = RET_FAILED;
  setMainMenu();
  setAddRectMenu();
  return retNum;
}
RET_NUMS TextureEditor::setMainMenu()
{
  SDL_Color color = {255,0,0,255};
  SDL_Color bgColor = {0,0,0,255};

  Menu tmpMenu;
  Button* buttonPtr;

  SDL_Rect tmpRect;

  int totW = 0; int totH = 0;

  //Menu TOP MENU
  tmpMenu.init(TOP_MENU);
  for(int i = LOAD_IMAGE; i <= CLOSE; i++)
  {
    buttonPtr = new Button;
    switch(i)
    {
      case LOAD_IMAGE:
        buttonPtr->init(LOAD_IMAGE, 0);
        buttonPtr->setText("LOAD IMAGE", 0, 0, XSMALL);
      break;
      case CLOSE:
        buttonPtr->init(CLOSE, 1);
        buttonPtr->setText("CLOSE", -1, -1, XLARGE);
      break;
    }
    buttonPtr->setBorder(&color);
    buttonPtr->setBGColor(&bgColor);

    tmpRect = *buttonPtr->getRect();
    totW = std::max(totW, tmpRect.w);
    totH += tmpRect.h;
    tmpMenu.addButton(buttonPtr);
  }
  //Set menu!
  tmpMenu.makeMenu();
  tmpMenu.setSize(totW + 4, totH + 5);
  tmpMenu.setBorder(&color);
  tmpMenu.setBGColor(&bgColor);
  tmpMenu.setPos(5, 5);
  tmpMenu.active = true;

  _menus.push_back(tmpMenu);

  return RET_SUCCESS;
}
RET_NUMS TextureEditor::setAddRectMenu()
{
  Button* buttonPtr = NULL;
  Menu tmpMenu;

  int newX = 0; int newY = 4;

  SDL_Rect windowRect = *_window->getRect();
  SDL_Rect menuRect;
  SDL_Rect buttRect;

  SDL_Color* colorPtr = new SDL_Color;
  *colorPtr = {255, 0, 0, 255};

  //Set Menu
  tmpMenu.init(ADD_RECT);
  tmpMenu.setSize(windowRect.w / 7, windowRect.h / 6);
  menuRect = *tmpMenu.getRect();
  tmpMenu.setPos(windowRect.w / 2 - menuRect.w / 2, windowRect.h / 2 - menuRect.h / 2);
  tmpMenu.setBorder(colorPtr);
  *colorPtr = {0, 0, 0, 255};
  tmpMenu.setBGColor(colorPtr);
  tmpMenu.active = false;

  //Add dimensions lbls
  buttonPtr = new Button;
  buttonPtr->init(LBL_X, 0);
  buttonPtr->setText("X: 9999", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  newX = menuRect.w / 2 - buttRect.w / 2;
  buttonPtr->setPos(newX, newY);
  newY += buttRect.h;
  tmpMenu.addButton(buttonPtr);

  buttonPtr = new Button;
  buttonPtr->init(LBL_Y, 1);
  buttonPtr->setText("Y: 9999", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  buttonPtr->setPos(newX, newY);
  newY += buttRect.h;
  tmpMenu.addButton(buttonPtr);

  buttonPtr = new Button;
  buttonPtr->init(LBL_W, 2);
  buttonPtr->setText("W: 9999", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  buttonPtr->setPos(newX, newY);
  newY += buttRect.h;
  tmpMenu.addButton(buttonPtr);

  buttonPtr = new Button;
  buttonPtr->init(LBL_H, 3);
  buttonPtr->setText("H: 9999", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  buttonPtr->setPos(newX, newY);
  newY += buttRect.h;
  tmpMenu.addButton(buttonPtr);

  //Add buttons
  *colorPtr = {255, 0, 0, 255};
  buttonPtr = new Button;
  buttonPtr->init(CANCEL, 5);
  buttonPtr->setText("CANCEL", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  newX = menuRect.w/2 + 2;
  newY = menuRect.h - buttRect.h - 4;
  buttonPtr->setPos(newX, newY);
  buttonPtr->setBorder(colorPtr);
  tmpMenu.addButton(buttonPtr);

  buttonPtr = new Button;
  buttonPtr->init(OK, 4);
  buttonPtr->setText(" OKAY ", -1, -1, LARGE);
  buttRect = *buttonPtr->getRect();
  newX = menuRect.w/2 - buttRect.w;
  buttonPtr->setPos(newX, newY);
  buttonPtr->setBorder(colorPtr);
  tmpMenu.addButton(buttonPtr);

  _menus.push_back(tmpMenu);
  return RET_SUCCESS;
}

void TextureEditor::getInFileRects()
{
  /*
  int counter = 0;
  _rectListMenu.clearMenu();
  _rectListMenu.init(RECT_LIST);
  SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);
  while(tmpRect != NULL)
  {
    Button* buttonPtr =  new Button;
    buttonPtr->init(counter);
    std::string tmpString = "Rect: ";
    tmpString.append(std::to_string(counter));
    tmpString.append(", X: ");
    tmpString.append(std::to_string(tmpRect->x));
    tmpString.append(", Y: ");
    tmpString.append(std::to_string(tmpRect->y));
    tmpString.append(", W: ");
    tmpString.append(std::to_string(tmpRect->w));
    tmpString.append(", H: ");
    tmpString.append(std::to_string(tmpRect->h));
    buttonPtr->setText(tmpString, -1, -1, XSMALL);
    _rectListMenu.addButton(buttonPtr);
    counter++;
    tmpRect = _window->getRect(IN_FILE, counter);
  }
  _rectListMenu.makeMenu();
  tmpRect = _window->getRect();
  int wW = tmpRect->w;
  tmpRect = _rectListMenu.getRect();
  _rectListMenu.setPos(wW - tmpRect->w - 5,0);
  _rectListMenu.active = true;
  */
}
void TextureEditor::addRect()
{
  Menu* tmpMenu = getMenu(ADD_RECT);
  if(tmpMenu != NULL)
  {
    tmpMenu->active = true;
    tmpMenu->setFocus(0);
    _text.start();
  }
}
void TextureEditor::makeGrid()
{

}
Menu* TextureEditor::getMenu(MENUS ID)
{
  Menu* retMenu = NULL;
  for(std::vector<Menu>::iterator it = _menus.begin(); it != _menus.end(); it++)
  {
    if((*it).getID() == ID)
    {
      retMenu = &(*it);
    }
  }
  return retMenu;
}
void TextureEditor::saveFile()
{
  SDL_RWops* file = SDL_RWFromFile("./data/out/out.rect", "wb");
  int rectSize = sizeof(SDL_Rect);
  int counter = 0;
  if(file != NULL)
  {
    SDL_Rect* tmpRect = _window->getRect(IN_FILE, counter);
    while(tmpRect != NULL)
    {
      SDL_RWwrite(file, tmpRect, rectSize, 1);
      counter++;
      tmpRect = _window->getRect(IN_FILE, counter);
    }
  }
  SDL_RWclose(file);

  file = SDL_RWFromFile("./data/out/out.texture", "wb");
  SDL_Texture* tmpTexture = _window->getSDLTexture(IN_FILE);
  int textSize = sizeof(tmpTexture);
  if(file != NULL)
  {
    SDL_RWwrite(file, tmpTexture, textSize, 1);
  }
  SDL_RWclose(file);

  file = SDL_RWFromFile("./data/out/out", "wb");
  int idPtr = IN_FILE;
  int intSize = sizeof(int);
  if(file != NULL)
  {
    SDL_RWwrite(file, &idPtr, intSize, 1);
  }
  SDL_RWclose(file);
}
void TextureEditor::loadFile()
{
  SDL_RWops* rectFile = SDL_RWFromFile("./data/out/out.rect", "rb");
  int fileSize = SDL_RWsize(rectFile);
  int rectSize = sizeof(SDL_Rect);
  int current = 1;
  int loaded = 0;
  SDL_Rect* rectPtr = (SDL_Rect*)malloc(fileSize);
  while(loaded < fileSize && current != 0)
  {
    current = SDL_RWread(rectFile, rectPtr, rectSize, 1);
    _error.printRect(rectPtr);
    rectPtr += current;
    loaded += rectSize;
  }
  SDL_RWclose(rectFile);

  SDL_RWops* textFile = SDL_RWFromFile("./data/out/out.text", "rb");
  fileSize = SDL_RWsize(textFile);
  SDL_Texture* tmpTexture = (SDL_Texture*)malloc(fileSize);
  SDL_RWread(textFile, tmpTexture, fileSize, 1);
  SDL_RWclose(textFile);
}
