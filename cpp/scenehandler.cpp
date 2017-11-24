#include "scenehandler.h"

//Public
RET_NUMS SceneHandler::init(Window* window, Error* error)
{
  _error = error;
  _window = window;

  SDL_Rect tmpRect = *window->getRect();
  _console.init(0, 0, tmpRect.w, tmpRect.h / 2);
  initScene(TEXTURE_EDITOR);
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::update(Window* window)
{
  RET_NUMS retNum = doEvents();
  render(window);
  return retNum;
}
//Private
RET_NUMS SceneHandler::initScene(SCENE scene)
{
  _activeScene = scene;
  switch(_activeScene)
  {
    case MAIN_MENU:
      //_mainMenu.init();
    break;
    case TEXTURE_EDITOR:
      _textureEditor.init(_window);
    break;
    case COMBAT:
      _combat.init(_window);
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::doEvents()
{
  RET_NUMS retNum = RET_SUCCESS;
  while(SDL_PollEvent(&_events))
  {
    //Global keys for forced quit and console!
    if(_events.type == SDL_KEYUP && _events.key.keysym.sym == SDLK_F12)
    {
      exit(99);
    }
    else if(_events.type == SDL_KEYUP && _events.key.keysym.sym == SDLK_TAB)
    {
      if(_console.active)
      {
        std::cout << "CONOSOLE OFF!\n";
        _console.active = false;
      }
      else
      {
        std::cout << "CONOSOLE ON!\n";
        _console.active = true;
      }
    }
    //if console is active
    if(_console.active)
    {
      _console.doEvents(&_events);
    }
    else
    {
      //Scene updates
      switch(_activeScene)
      {
        case TEXTURE_EDITOR:
          retNum = _textureEditor.doEvents(&_events);
        break;
        case COMBAT:
          retNum = _combat.doEvents(&_events);
        break;
        default:
          std::cout << "BLÄ\n";
        break;
      }
    }
  }
  return retNum;
}
void SceneHandler::render(Window* window)
{
  switch(_activeScene)
  {
    case MAIN_MENU:
      //_mainMenu.render(window);
    break;
    case TEXTURE_EDITOR:
      _textureEditor.render();
    break;
    case COMBAT:
      _combat.render();
    break;
  }

  if(_console.active)
  {
    _console.render(window);
  }
  _window->render();
}
