#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H

#include <SDL2/SDL.h>

#include "enums.h"
#include "window.h"
#include "mainmenu.h"
#include "textureeditor.h"

class SceneHandler
{
public:
  RET_NUMS init();
  RET_NUMS update(Window* window);

private:
  RET_NUMS initScene(SCENE scene);
  RET_NUMS doEvents();
  void render(Window* window);

  SCENE _activeScene;

  MainMenu _mainMenu;
  TextureEditor _textureEditor;
  SDL_Event _events;
};

#endif //SCENEHANDLER_H
