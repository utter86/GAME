#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#include "enums.h"

class Texture
{
public:
  //Setters
  RET_NUMS setSDLTexture(TEXTURE_ID id, SDL_Texture* texture);
  RET_NUMS addRect(SDL_Rect rect, int rectNum);

  //Getters
  SDL_Texture* getSDLTexture();
  SDL_Rect* getRect(int rectNum);
  int getID();

private:
  TEXTURE_ID _id;
  SDL_Texture* _texture;
  SDL_Rect _srcRect[99];

};

#endif //TEXTURE_H
