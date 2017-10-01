#include "texture.h"

//Setters
RET_NUMS Texture::setSDLTexture(TEXTURE_ID id, SDL_Texture* texture)
{
  _texture = texture;
  _id = id;
  return RET_SUCCESS;
}
RET_NUMS Texture::addRect(SDL_Rect rect, int rectNum)
{
  _srcRect[rectNum] = rect;
  return RET_SUCCESS;
}

//Getters
SDL_Texture* Texture::getSDLTexture()
{
  return _texture;
}
SDL_Rect* Texture::getRect(int rectNum)
{
  return &_srcRect[rectNum];
}
int Texture::getID()
{
  return _id;
}
