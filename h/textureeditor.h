#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"

class TextureEditor
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS render();

  RET_NUMS mouseMove();
  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);

  RET_NUMS setScene();

  void saveFile();
  void loadFile();

private:
  //Window
  Window* _window;
  SDL_Rect _inFileRect;

  Menu _rectMenu;
  Menu _menu;
  Error _error;


  enum BUTTONS
  {
    LOAD_IMAGE = 100, CLOSE,
  };
  enum MENUS
  {
    MENU = 1,
  };
};

#endif //TEXTUREEDITOR_H
