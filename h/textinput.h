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
  void init(int x, int y, int txtSize, SDL_Color* txtColor = NULL, SDL_Color* backColor = NULL, SDL_Color* areaColor = NULL);
  void update(SDL_Event* event);
  void start();
  void stop();

  //Setters
  void setTextColor(SDL_Color* color);
  void setBackColor(SDL_Color* color);
  void setAreaColor(SDL_Color* color);
  void setPos(int x, int y);

private:
  bool _active;
  int _X, _Y, _txtSize;
  SDL_Color* _txtColor = NULL;
  SDL_Color* _backColor = NULL;
  SDL_Color* _areaColor = NULL;
  char* _text;

  SDL_Event _events;
};
#endif // TEXTINPUT_H
