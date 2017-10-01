#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "enums.h"
#include "window.h"
#include "scenehandler.h"
#include "error.h"


class Game
{

public:
  RET_NUMS init(std::string file);
  RET_NUMS update();
  void close();
private:

  //Window
  Window _window;

  //Scene handler
  SceneHandler _sceneHandeler;

  //Error
  Error _error;

};

#endif //GAME_H
