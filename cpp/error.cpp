#include "error.h"

void Error::error(std::string freeText, std::string sdlText)
{
	std::cout << freeText << "\n" << sdlText << "\n";
	log(freeText);
	log(sdlText);
	exit(-1);
}
void Error::pause(std::string string)
{
	char tmpChar;
	std::cout << string;
	std::cin.get(tmpChar);
}
void Error::print(std::string text)
{
	std::cout << text;
}
void Error::printRect(SDL_Rect* rect)
{
	std::cout << "X: " << rect->x << " Y: " << rect->y << " W: " << rect->w << " H: " << rect->h << "\n";
}
void Error::log(std::string logInput)
{
    std::ofstream logFile;
    _log.push_back(logInput);
    logFile.open("./data/log/log");
    for(std::vector<std::string>::iterator it = _log.begin(); it != _log.end(); it++)
    {
        logFile << (*it) << '\n';
    }
    logFile.close();
}
void Error::printLog()
{
    for(std::vector<std::string>::iterator it = _log.begin(); it != _log.end(); it++)
    {
        std::cout << (*it) << '\n';
    }
}
std::vector<std::string>* Error::getLog()
{
    return &_log;
}
