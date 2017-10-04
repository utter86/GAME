#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <vector>

#include "enums.h"
#include "texture.h"
#include "error.h"

class TextureFolder
{
public:
  RET_NUMS addTexture(TEXTURE_ID id, SDL_Texture* texture);
  RET_NUMS addRect(TEXTURE_ID id, int rectNum, SDL_Rect* rect);


  //Getters
  SDL_Texture* getSDLTexture(TEXTURE_ID id);
  SDL_Rect* getRect(TEXTURE_ID id, int recNum);

private:
  Texture* getTexture(TEXTURE_ID id);

  std::vector<Texture> _textureVector;

  Error _error;
};

#endif // TEXTUREFOLDER_H
