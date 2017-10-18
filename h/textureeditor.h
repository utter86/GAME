#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"
#include "textinput.h"

class TextureEditor
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS render();
  RET_NUMS doEvents(SDL_Event* event);
  RET_NUMS mouseMove();
  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);

  RET_NUMS setScene();

  void getInFileRects();
  void addRect();
  void makeGrid();

  void saveFile();
  void loadFile();

private:
  //Window
  Window* _window;

  SDL_Rect* _inFileRect = NULL;
  SDL_Rect* _activeRect = NULL;

  int _rectNum;
  Menu _rectListMenu;
  Menu _menu;

  TextInput _text;

  Error _error;
  enum BUTTONS
  {
    LOAD_IMAGE = 100, CLOSE,
  };
  enum MENUS
  {
    MENU = 1, RECT_LIST,
  };
};

#endif //TEXTUREEDITOR_H
