#include "textinput.h"

void TextInput::init()
{
  _active = false;
}
RET_NUMS TextInput::update(SDL_Event* event)
{
  RET_NUMS retNum = RET_FAILED;
  if(_active)
  {
    switch(event->type)
    {
      case SDL_TEXTINPUT:
        std::string tmpString = _text;
        if(tmpString.length() > 30)
        {
          return RET_FULL;
        }
        strcat(_text, event->text.text);
        retNum = RET_SUCCESS;
      break;
    }
  }
  return retNum;
}
void TextInput::start()
{
  _active = true;
  SDL_StartTextInput();
  _text = new char [32];
  strcpy(_text, "");
}
void TextInput::stop()
{
  SDL_StopTextInput();
  _active = false;
  delete _text;
  _text = NULL;
}

std::string TextInput::getText()
{
  std::string tmpString = _text;
  return tmpString;
}
