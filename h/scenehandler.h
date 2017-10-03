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
  RET_NUMS init(Window* window);
  RET_NUMS update(Window* window);

private:
  RET_NUMS initScene(SCENE scene);
  RET_NUMS doEvents();

  RET_NUMS mouseMove();
  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);

  void render(Window* window);


  Window* _window;

  SCENE _activeScene;

  MainMenu _mainMenu;
  TextureEditor _textureEditor;
  SDL_Event _events;
};

#endif //SCENEHANDLER_H
