#include "scenehandler.h"

//Public
RET_NUMS SceneHandler::init()
{
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
      _textureEditor.init();
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::doEvents()
{
  RET_NUMS retNum = RET_SUCCESS;
  while(SDL_PollEvent(&_events))
  {
    switch(_events.type)
    {
      case SDL_KEYUP:
        switch(_events.key.keysym.sym)
        {
          case SDLK_F12:
            return RET_FAILED;
          break;
          case SDLK_F1:

          break;
          case SDLK_F2:

          break;
        }
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
      _textureEditor.render(window);
    break;
  }
}
