#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include "window.h"
#include "enums.h"
#include "error.h"
#include "gameobject.h"

class TextureEditor
{
public:
  RET_NUMS init();
  RET_NUMS render(Window* window);

  void saveFile();
  void loadFile();

  GameObject _testObject;

  SDL_Rect _testView;

private:
  Error _error;
};

#endif //TEXTUREEDITOR_H
