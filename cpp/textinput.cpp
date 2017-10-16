#include "textinput.h"

void TextInput::init(int x, int y, int txtSize, SDL_Color* txtColor, SDL_Color* backColor, SDL_Color* areaColor)
{
  _X = x;
  _Y = y;
  _txtSize = txtSize;
  _txtColor = txtColor;
  _backColor = backColor;
  _areaColor = areaColor;
  _active = false;
}
void TextInput::update(SDL_Event* event)
{
  if(_active)
  {
    switch(event->type)
    {
      case SDL_TEXTINPUT:
        strcat(_text, event->text.text);
        std::cout << _text << "\n";
      break;
    }
  }
}
void TextInput::start()
{
  _active = true;
  SDL_StartTextInput();
  _text = new char;
  strcpy(_text, "");
}
void TextInput::stop()
{
  SDL_StopTextInput();
  _active = false;
  delete _text;
  _text = NULL;
}
void TextInput::setTextColor(SDL_Color* color)
{
  _txtColor = color;
}
void TextInput::setBackColor(SDL_Color* color)
{
  _backColor= color;
}
void TextInput::setAreaColor(SDL_Color* color)
{
  _areaColor = color;
}
void TextInput::setPos(int x, int y)
{
  _X = x;
  _Y = y;
}
