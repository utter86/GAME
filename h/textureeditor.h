#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include <vector>

#include "window.h"
#include "enums.h"
#include "error.h"
#include "menu.h"
#include "textinput.h"

enum MENUS
{
  TOP_MENU = 1000, ADD_RECT,
};

enum MAINE_MENU_BUTTONS
{
  LOAD_IMAGE = 2000, CLOSE,
};

enum ADD_RECT_BUTTONS
{
  LBL_X = 3000, LBL_Y, LBL_W, LBL_H, OK, CANCEL,
};

class TextureEditor
{
public:
  RET_NUMS init(Window* window);
  RET_NUMS render();
  RET_NUMS doEvents(SDL_Event* event);

  RET_NUMS mouseMove();

  RET_NUMS keyUp(int key);
  RET_NUMS click(int button);
  RET_NUMS topMenuClick();
  RET_NUMS addRectClick();

  RET_NUMS textUpdate(SDL_Event* event);

  RET_NUMS setScene();
  RET_NUMS setMainMenu();
  RET_NUMS setAddRectMenu();

  void getInFileRects();
  void addRect();
  void makeGrid();
  Menu* getMenu(MENUS ID);

  void saveFile();
  void loadFile();

private:
  //Window
  Window* _window;

  SDL_Rect* _inFileRect = NULL;
  SDL_Rect* _activeRect = NULL;

  int _rectNum;

  TextInput _text;

  std::vector<Menu> _menus;

  Error _error;


};

#endif //TEXTUREEDITOR_H
