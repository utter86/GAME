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
        if(_events.key.keysym.sym == SDLK_F12)
        {
          return RET_FAILED;
        }
        keyUp(_events.key.keysym.sym);
      break;
      case SDL_MOUSEBUTTONUP:
        click(_events.button.button);
      break;
      case SDL_MOUSEMOTION:
        mouseMove();
      break;
    }
  }
  return retNum;
}

RET_NUMS SceneHandler::mouseMove()
{
  switch(_activeScene)
  {
    case TEXTURE_EDITOR:
      _textureEditor.mouseMove();
    break;
    default:
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::keyUp(int key)
{
  switch(_activeScene)
  {
    case TEXTURE_EDITOR:
      _textureEditor.keyUp(key);
    break;
    default:
    break;
  }
  return RET_SUCCESS;
}
RET_NUMS SceneHandler::click(int button)
{
  switch(_activeScene)
  {
    case TEXTURE_EDITOR:
      _textureEditor.click(button);
    break;
    default:
    break;
  }
  return RET_SUCCESS;
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
