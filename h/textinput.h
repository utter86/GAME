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
  void start(std::string* dest = NULL, bool numeric = false);
  void stop();
  bool active();

  //Getters
  std::string getText();
private:
  bool _active;
  int _txtSize;
  char* _text;
  std::string* _destText = NULL;

  int _X;
  int _Y;

  bool _numeric;

  SDL_Event _events;
};
#endif // TEXTINPUT_H
