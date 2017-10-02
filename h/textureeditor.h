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


  RET_NUMS setScene();

  void saveFile();
  void loadFile();
private:
  Error _error;
  enum BUTTONS
  {
    ALL_BUTTONS = 100, LOAD_IMAGE,
  };
};

#endif //TEXTUREEDITOR_H
