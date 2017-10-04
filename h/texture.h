#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include "enums.h"

struct Rect
{
  int id;
  SDL_Rect rect;
};
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
  std::vector<Rect> _rectVect;

};

#endif //TEXTURE_H
