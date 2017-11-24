#include "game.h"

RET_NUMS Game::init(std::string file, Error* error)
{
  _error = error;
  WindowSettings windowSettings;
  SDL_RWops* settingsFile = SDL_RWFromFile(file.c_str(), "rb");
  //if file dose not exist make it
  if(settingsFile == NULL)
  {
    windowSettings = {1280, 720, SDL_WINDOW_BORDERLESS, SDL_RENDERER_PRESENTVSYNC};
    settingsFile = SDL_RWFromFile(file.c_str(), "wb");
    size_t outSize = sizeof(windowSettings);
    SDL_RWwrite(settingsFile, &windowSettings, outSize, outSize);
    SDL_RWclose(settingsFile);
  }
  else
  {
    size_t inSize = SDL_RWsize(settingsFile);
    WindowSettings* settings = (WindowSettings*)malloc(inSize + 1);
    SDL_RWread(settingsFile, settings, inSize, 1);
    SDL_RWclose(settingsFile);
    windowSettings = *settings;
  }

  _window.init(windowSettings, _error);
  _sceneHandeler.init(&_window, _error);
  return RET_SUCCESS;
}
RET_NUMS Game::update()
{
  RET_NUMS retNum = RET_FAILED;
  retNum = _sceneHandeler.update(&_window);
  return retNum;
}
void Game::close()
{
  _window.close();
}
