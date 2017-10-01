#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include "window.h"
#include "enums.h"
#include "error.h"

class TextureEditor
{
public:
  RET_NUMS init();
  RET_NUMS render(Window* window);

  void saveFile();
  void loadFile();

private:
  Error _error;
};

#endif //TEXTUREEDITOR_H
