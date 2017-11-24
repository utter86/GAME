#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>

class Error
{
public:
	void error(std::string freeText, std::string sdlText);
	void pause(std::string string = "Press return to contiune...\n");
	void print(std::string text);
	void printRect(SDL_Rect* rect);
	void log(std::string logInput);
	void printLog();

	std::vector<std::string>* getLog();
private:
    std::vector<std::string> _log;
};

#endif // ERROR_H
