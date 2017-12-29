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
  _inputLine.init(0, 0);
  _inputLine.setBGColor(_consoleTextBackColor);

  createCommands();

  //Text input
  _text.init();
  _text.start();
  active = false;
}
void Console::addTextLog(std::string text)
{
  Button* buttonPtr = new Button;
  buttonPtr->init(_itemNum, _itemNum);
  _itemNum++;
  buttonPtr->setText(text, 0, 0, _consoleTextSize, _consoleTextColor);
  _consoleLog.addButton(buttonPtr);
  _consoleLog.makeMenu();
  SDL_Rect* tmpRect = _consoleLog.getRect();
  _consoleLog.setPos(_consoleRect->x, _consoleRect->h - tmpRect->h - (_consoleTextSize * 1.5));
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
void Console::createCommands()
{
  _commands["EXIT"] = [this]
  {
    _error.log("EXIT 909");
    exit(909);
  };
  _commands["PRINT LOG"] = [this]
  {
    _error.log("LOG PRINTED!");
    _error.printLog();
  };
  _commands["UNKNOWN"] = [this]
  {
    _error.log("UNKNOWN COMMAND!");
    addTextLog("UNKNOWN COMMAND!");
  };
}
void Console::input()
{
  addTextLog(_text.getText());
  executeCommand(_text.getText());
  _text.stop();
  _text.start();
}
void Console::executeCommand(std::string command)
{
  std::transform(command.begin(), command.end(), command.begin(), toupper);
  if(_commands.find(command) != _commands.end())
  {
    _commands[command]();
  }
  else
  {
    _commands["UNKNOWN"]();
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
