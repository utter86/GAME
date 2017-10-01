#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

class Error
{
public:
	void error(std::string freeText, std::string sdlText);
	void pause(std::string string = "Press return to contiune...\n");
	void print(std::string string);
	void printRect(SDL_Rect* rect);
private:
};

#endif // ERROR_H
