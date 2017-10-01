#include "error.h"

void Error::error(std::string freeText, std::string sdlText)
{
	std::cout << freeText << "\n" << sdlText << "\n";
	exit(-1);
}

void Error::pause(std::string string)
{
	char tmpChar;
	std::cout << string;
	std::cin.get(tmpChar);
}

void Error::print(std::string string)
{
	std::cout << string;
}

void Error::printRect(SDL_Rect* rect)
{
	std::cout << "X: " << rect->x << " Y: " << rect->y << " W: " << rect->w << " H: " << rect->h << "\n";
}
