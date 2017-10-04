#include "texture.h"

//Setters
RET_NUMS Texture::setSDLTexture(TEXTURE_ID id, SDL_Texture* texture)
{
  _texture = texture;
  _id = id;
  return RET_SUCCESS;
}
RET_NUMS Texture::addRect(SDL_Rect* rect, int rectNum)
{
  Rect tmpRect = {rectNum, rect};
  _rectVect.push_back(tmpRect);
  return RET_SUCCESS;
}

//Getters
SDL_Texture* Texture::getSDLTexture()
{
  return _texture;
}
SDL_Rect* Texture::getRect(int rectNum)
{
  for(std::vector<Rect>::iterator it = _rectVect.begin(); it != _rectVect.end(); it++)
  {
    if(rectNum == it->id)
    {
      return it->rect;
    }
  }
  return NULL;
}
int Texture::getID()
{
  return _id;
}
