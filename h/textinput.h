#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <cstring>

#include "enums.h"

class TextInput
{
public:
  void init();
  RET_NUMS update(SDL_Event* event);
  void start();
  void stop();

  //Getters
  std::string getText();
private:
  bool _active;
  int _txtSize;
  char* _text;

  SDL_Event _events;
};
#endif // TEXTINPUT_H
