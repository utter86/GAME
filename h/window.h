#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#include "enums.h"
#include "error.h"
#include "texturefolder.h"

struct WindowSettings
{
  int w;
  int h;
  int windowMode;
  int vsync;
};

class Window
{
public:
  RET_NUMS init(WindowSettings settings);

  RET_NUMS loadMedia();
  void loadFileOld(TEXTURE_ID id, std::string file);
  void loadPNG(TEXTURE_ID id, std::string file);
  SDL_Texture* createTexture(std::string file);

  RET_NUMS render(TEXTURE_ID id = NONE, int start = 0, int stop = 0, SDL_Rect* dstRect = NULL, SDL_Rect* viewPort = NULL, double angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
  void drawBorder(SDL_Rect* rect, SDL_Color* color, SDL_Rect* viewPort = NULL);
  void renderText(std::string text, int x, int y, int size, SDL_Color* color = NULL, SDL_Rect* viewPort = NULL);
  void fillRect(SDL_Rect* rect, SDL_Color* color);

  void close();

  //Getters
  SDL_Renderer* getRenderer();
  SDL_Texture* getSDLTexture(TEXTURE_ID id);
  SDL_Rect* getRect(TEXTURE_ID id = NONE, int rectNum = 0);
  int getAlphaPos(char tmpChar);
  //Setters
  RET_NUMS setRenderer(SDL_Renderer* renderer);
  RET_NUMS setColorMod(TEXTURE_ID id, SDL_Color* color);
private:

  //Window
  SDL_Window* _window;
  SDL_Rect _windowRect;

  int _frames;
  int _speed;
  int _frame;
  int _acctualFrame;

  //renderer
  SDL_Renderer* _renderer;

  //Texture folder
  TextureFolder _textureFolder;

  //Error
  Error _error;
};

#endif //WINDOW_H
