#include "console.h"

void Console::init(int x, int y, int w, int h)
{
  //Coloors
  _consoleRect = new SDL_Rect;
  *_consoleRect = {x, y, w, h};

  _consoleColor = new SDL_Color;
  *_consoleColor = {0,0,0,150};

  _consoleTextColor = new SDL_Color;
  *_consoleTextColor = {255,255,255,255};

  _consoleTextBackColor = new SDL_Color;
  *_consoleTextBackColor = {0,0,0,0};

  _consoleTextSize = SMALL;
  //Console log
  _consoleLog.init(0);
  _consoleLog.active = true;
  _itemNum = 0;
  _inputLine.init(0);
  _inputLine.setBGColor(_consoleTextBackColor);
  //Text input
  _text.init();
  _text.start();
  active = false;
}

RET_NUMS Console::doEvents(SDL_Event* event)
{
  switch(event->type)
  {
    case SDL_KEYUP:
      switch(event->key.keysym.sym)
      {
        case SDLK_RETURN:
          input();
        break;
      }
    break;
  }
  _text.update(event);
  std::string tmpString = _text.getText();
  tmpString.append(":");
  _inputLine.setText(tmpString, 0,0, _consoleTextSize, _consoleTextColor);
  return RET_SUCCESS;
}
void Console::input()
{
  Button* buttonPtr = new Button;
  buttonPtr->init(_itemNum);
  _itemNum++;
  buttonPtr->setText(_text.getText(), 0, 0, _consoleTextSize, _consoleTextColor);
  _consoleLog.addButton(buttonPtr);
  _consoleLog.makeMenu();
  SDL_Rect* tmpRect = _consoleLog.getRect();
  _consoleLog.setPos(_consoleRect->x, _consoleRect->h - tmpRect->h - (_consoleTextSize * 1.5));
  executeCommand(findCommand(_text.getText()));
  _text.stop();
  _text.start();
}
CONSOLE_COMMAND Console::findCommand(std::string command)
{
  CONSOLE_COMMAND retCmd = UNKNOW;
  std::string tmpString = command;
  for(std::string::size_type i = 0; i < tmpString.length(); i++)
  {

  }
  if( tmpString == "EXIT")
  {
    retCmd = EXIT;
  }
  return retCmd;
}
void Console::executeCommand(CONSOLE_COMMAND command)
{
  switch(command)
  {
    case EXIT:
      exit(8989);
    break;
    default:
      Button* buttonPtr = new Button;
      buttonPtr->init(_itemNum);
      _itemNum++;
      buttonPtr->setText("UNKNOWN COMMAND", 0, 0, _consoleTextSize, _consoleTextColor);
      _consoleLog.addButton(buttonPtr);
      _consoleLog.makeMenu();
      SDL_Rect* tmpRect = _consoleLog.getRect();
      _consoleLog.setPos(_consoleRect->x, _consoleRect->h - tmpRect->h - (_consoleTextSize * 1.5));
    break;
  }
}
void Console::render(Window* window)
{
  window->fillRect(_consoleRect, _consoleColor);
  window->drawBorder(_consoleRect, _consoleTextColor, nullptr);

  _inputLine.setSize(_consoleRect->w, _consoleTextSize * 1.5);
  _inputLine.setPos(0, _consoleRect->h - _consoleTextSize * 1.5);
  _inputLine.render(window);

  _consoleLog.render(window);
}
void Console::close()
{
  delete _consoleRect;
  delete _consoleColor;
}
void Console::setConsoleColor(SDL_Color* color)
{
  *_consoleColor = *color;
}

