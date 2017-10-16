#include "scenehandler.h"

//Public
RET_NUMS SceneHandler::init(Window* window)
{
  _window = window;
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
      _mainMenu.init();
    break;
    case TEXTURE_EDITOR:
      _textureEditor.init(_window);
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::doEvents()
{
  RET_NUMS retNum = RET_SUCCESS;
  while(SDL_PollEvent(&_events))
  {
    if(_events.type == SDL_KEYUP && _events.key.keysym.sym == SDLK_F12)
    {
      exit(99);
    }
    switch(_activeScene)
    {
      case TEXTURE_EDITOR:
        _textureEditor.doEvents(&_events);
      break;
      default:
        std::cout << "BLÄ\n";
      break;
    }
  }
  return retNum;
}

void SceneHandler::render(Window* window)
{
  switch(_activeScene)
  {
    case MAIN_MENU:
      _mainMenu.render(window);
    break;
    case TEXTURE_EDITOR:
      _textureEditor.render();
    break;
  }
}
