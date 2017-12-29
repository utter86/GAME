#include "combat.h"

RET_NUMS Combat::init(Window* window)
{
  _window = window;
  _direction = OBJ_NONE;
  _activeColor = new SDL_Color;
  _inActiveColor = new SDL_Color;
  *_activeColor = {0, 255, 0, 255};
  *_inActiveColor = {255, 0, 0, 255};
  initStick();
  setScene();
  return RET_SUCCESS;
}
RET_NUMS Combat::initStick()
{
  for(int i = 0; i < SDL_NumJoysticks(); i++)
  {
    if(!SDL_IsGameController(i))
    {
      _error.error("Controller not suported!\n", SDL_GetError());
    }
    else
    {
      _controller = SDL_GameControllerOpen(i);
      if(_controller == NULL)
      {
        _error.error("UNable to open controller\n", SDL_GetError());
      }
    }
  }
  _button = OBJ_NONE;
  return RET_SUCCESS;
}

RET_NUMS Combat::render()
{
  renderDir();
  return RET_SUCCESS;
}
RET_NUMS Combat::renderDir()
{
  for(std::vector<GameObject>::iterator it = _gameObjects.begin(); it != _gameObjects.end(); it++)
  {
    if(it->getID() == _direction)
    {
      _window->setColorMod(ARROW, _activeColor);
    }
    else if(it->getID() == _button)
    {
      _window->setColorMod(BUTTON, _activeColor);
    }
    else
    {
      _window->setColorMod(ARROW, _inActiveColor);
      _window->setColorMod(BUTTON, _inActiveColor);
    }
    (it)->render(_window);
  }
  return RET_SUCCESS;
}

RET_NUMS Combat::doEvents(SDL_Event* event)
{
  switch(event->type)
  {
    case SDL_CONTROLLERAXISMOTION:
      //ANALOG STICKS and triggers
    break;
    case SDL_CONTROLLERBUTTONUP:
      return controllerButtonUp(event->cbutton.button);
    break;
    case SDL_CONTROLLERBUTTONDOWN:
      return controllerButtonDown(event->cbutton.button);
    break;
    case SDL_KEYDOWN:
      return keyDown(event->key.keysym.sym);
    break;
  }
  return RET_SUCCESS;
}
int Combat::mouseMove()
{
  return 0;
}
RET_NUMS Combat::keyDown(int key)
{
  switch(key)
  {
    case SDLK_UP:
      return moveUp();
    break;
    case SDLK_DOWN:
      return moveDown();
    break;
    case SDLK_LEFT:
      return moveLeft();
    break;
    case SDLK_RIGHT:
      return moveRight();
    break;
    default:
      std::cout << "NONE!\n";
      return RET_SUCCESS;
    break;
  }
  return RET_FAILED;
}
RET_NUMS Combat::controllerButtonDown(int button)
{
  switch(button)
  {
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      moveUp();
    break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      moveDown();
    break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      moveLeft();
    break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      moveRight();
    break;
    case SDL_CONTROLLER_BUTTON_A:
      buttonDownThree();
    break;
    case SDL_CONTROLLER_BUTTON_B:
      buttonDownFour();
    break;
    case SDL_CONTROLLER_BUTTON_X:
      buttonDownOne();
    break;
    case SDL_CONTROLLER_BUTTON_Y:
      buttonDownTwo();
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS Combat::controllerButtonUp(int button)
{
  if(SDL_GameControllerGetButton(_controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)
  {
    _direction = OBJ_ARROWUP;
  }
  else if(SDL_GameControllerGetButton(_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)
  {
    _direction = OBJ_ARROWDOWN;
  }
  else if(SDL_GameControllerGetButton(_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1)
  {
    _direction = OBJ_ARROWLEFT;
  }
  else if(SDL_GameControllerGetButton(_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1)
  {
    _direction = OBJ_ARROWRIGHT;
  }
  else
  {
    _direction = OBJ_NONE;
  }
  _button = OBJ_NONE;
  return RET_SUCCESS;
}
RET_NUMS Combat::click(int button)
{
  return RET_FAILED;
}

RET_NUMS Combat::setScene()
{
  GameObject tmpObj;
  SDL_Rect tmpRect = {0, 4, 50, 50};
  tmpObj.init(OBJ_ARROWUP, 0);
  tmpObj.setTexture(ARROW, 4, 4, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(50, 0);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWUR, 1);
  tmpObj.setTexture(ARROW, 5, 5, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(100, 0);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWRIGHT, 2);
  tmpObj.setTexture(ARROW, 1, 1, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(100, 50);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWDR, 3);
  tmpObj.setTexture(ARROW, 6, 6, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(100, 100);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWDOWN, 4);
  tmpObj.setTexture(ARROW, 2, 2, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(50, 100);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWDL, 5);
  tmpObj.setTexture(ARROW, 7, 7, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(0, 100);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWUL, 6);
  tmpObj.setTexture(ARROW, 8, 8, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(0, 0);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_ARROWLEFT, 7);
  tmpObj.setTexture(ARROW, 3, 3, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(0, 50);
  _gameObjects.push_back(tmpObj);

  tmpRect = {0, 0, 50, 50};
  tmpObj.init(OBJ_ONE, 8);
  tmpObj.setTexture(BUTTON, 0, 0, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(200, 50);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_TWO, 9);
  tmpObj.setTexture(BUTTON, 0, 0, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(255, 50);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_THREE, 10);
  tmpObj.setTexture(BUTTON, 0, 0, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(200, 105);
  _gameObjects.push_back(tmpObj);

  tmpObj.init(OBJ_FOUR, 11);
  tmpObj.setTexture(BUTTON, 0, 0, tmpRect);
  tmpObj.setSize(50, 50);
  tmpObj.setPos(255, 105);
  _gameObjects.push_back(tmpObj);

  return RET_SUCCESS;
}

RET_NUMS Combat::moveLeft()
{
  switch(_direction)
  {
    case OBJ_ARROWUP:
      _direction = OBJ_ARROWUL;
    break;
    case OBJ_ARROWDOWN:
      _direction = OBJ_ARROWDL;
    break;
    default:
      _direction = OBJ_ARROWLEFT;
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS Combat::moveRight()
{
  switch(_direction)
  {
    case OBJ_ARROWUP:
      _direction = OBJ_ARROWUR;
    break;
    case OBJ_ARROWDOWN:
      _direction = OBJ_ARROWDR;
    break;
    default:
      _direction = OBJ_ARROWRIGHT;
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS Combat::moveUp()
{
  switch(_direction)
  {
    case OBJ_ARROWLEFT:
      _direction = OBJ_ARROWUL;
    break;
    case OBJ_ARROWRIGHT:
      _direction = OBJ_ARROWUR;
    break;
    default:
      _direction = OBJ_ARROWUP;
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS Combat::moveDown()
{
  switch(_direction)
  {
    case OBJ_ARROWLEFT:
      _direction = OBJ_ARROWDL;
    break;
    case OBJ_ARROWRIGHT:
      _direction = OBJ_ARROWDR;
    break;
    default:
      _direction = OBJ_ARROWDOWN;
    break;
  }
  return RET_SUCCESS;
}

RET_NUMS Combat::buttonDownOne()
{
  _button = OBJ_ONE;
  return RET_SUCCESS;
}
RET_NUMS Combat::buttonDownTwo()
{
  _button = OBJ_TWO;
  return RET_SUCCESS;
}
RET_NUMS Combat::buttonDownThree()
{
  _button = OBJ_THREE;
  return RET_SUCCESS;
}
RET_NUMS Combat::buttonDownFour()
{
  _button = OBJ_FOUR;
  return RET_SUCCESS;
}
