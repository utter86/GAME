#include "textinput.h"

void TextInput::init()
{
  _numeric = false;
  _active = false;
}
RET_NUMS TextInput::update(SDL_Event* event)
{
  RET_NUMS retNum = RET_FAILED;
  if(_active)
  {
    std::string tmpString = _text;
    switch(event->type)
    {
      case SDL_TEXTINPUT:
        if(tmpString.length() > 30)
        {
          return RET_FULL;
        }
        strcat(_text, event->text.text);
        retNum = RET_SUCCESS;
      break;
      case SDL_KEYUP:
        switch(event->key.keysym.sym)
        {
          case SDLK_BACKSPACE:
            tmpString = tmpString.substr(0, tmpString.length() - 1);
            strcpy(_text, tmpString.c_str());
          break;
          case SDLK_RETURN:
            retNum = RET_DONE;
          break;
        }
      break;
    }
    if(_destText != NULL)
    {
      *_destText = _text;
    }
  }
  return retNum;
}
void TextInput::start(std::string* dest, bool numeric)
{
  if(dest != NULL)
  {
    _destText = dest;
  }
  if(numeric)
  {
    _numeric = true;
  }
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
bool TextInput::active()
{
    return _active;
}
std::string TextInput::getText()
{
  std::string tmpString = _text;
  return tmpString;
}
