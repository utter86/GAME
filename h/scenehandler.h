#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H

#include <SDL2/SDL.h>

#include "enums.h"
#include "window.h"
#include "mainmenu.h"
#include "textureeditor.h"
#include "combat.h"
#include "console.h"

class SceneHandler
{
public:
  RET_NUMS init(Window* window, Error* error);
  RET_NUMS update(Window* window);

private:
  RET_NUMS initScene(SCENE scene);
  RET_NUMS doEvents();

  void render(Window* window);

  Window* _window;
  Error* _error = NULL;

  SCENE _activeScene;
  Console _console;

  MainMenu _mainMenu;
  TextureEditor _textureEditor;
  Combat _combat;

  SDL_Event _events;
};

#endif //SCENEHANDLER_H
