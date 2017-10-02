#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"

class TextureEditor
{
public:
  RET_NUMS init();
  RET_NUMS render(Window* window);

  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);

  RET_NUMS setScene();

  void saveFile();
  void loadFile();

private:
  Error _error;

  Menu _menu;
  enum BUTTONS
  {
    ALL_BUTTONS = 100, LOAD_IMAGE, CLOSE,
  };
  enum MENUS
  {
    MENU = 1,
  };
};

#endif //TEXTUREEDITOR_H
