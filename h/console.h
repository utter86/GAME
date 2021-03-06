#ifndef CONSOLE_H
#define CONSOLE_H

#include <algorithm>
#include <map>
#include <functional>
#include "window.h"
#include "textinput.h"
#include "errno.h"
#include "menu.h"

class Console
{
public:
  void init(int x, int y, int w, int h);
  void addTextLog(std::string text);
  void createCommands();
  RET_NUMS doEvents(SDL_Event* event);
  void input();
  void executeCommand(std::string command);
  void render(Window* window);
  void close();

  //Setters
  void setConsoleColor(SDL_Color* color);
  bool active;
private:

  SDL_Rect* _consoleRect;
  SDL_Color* _consoleColor;
  SDL_Color* _consoleTextColor;
  SDL_Color* _consoleTextBackColor;
  int _consoleTextSize;
  int _itemNum;

  std::map<std::string, std::function<void()> > _commands;

  TextInput _text;
  GameObject _inputLine;
  Menu _consoleLog;
  Error _error;
};
#endif // CONSOLE_H
