#include "texturefolder.h"

RET_NUMS TextureFolder::addTexture(TEXTURE_ID id, SDL_Texture* texture)
{
  Texture tmpTexture;
  if(getTexture(id) != NULL)
  {
    _error.print("Texture not added to folder. ID not unique.\n");
    return RET_FAILED;
  }
  tmpTexture.setSDLTexture(id, texture);
  _textureVector.push_back(tmpTexture);
  return RET_SUCCESS;
}
RET_NUMS TextureFolder::addRect(TEXTURE_ID id, int rectNum, SDL_Rect* rect)
{
  Texture* tmpTexture = getTexture(id);
  if(tmpTexture != NULL)
  {
    tmpTexture->addRect(rect, rectNum);
    return RET_SUCCESS;
  }
  return RET_FAILED;
}

//Getters
SDL_Texture* TextureFolder::getSDLTexture(TEXTURE_ID id)
{
  Texture* tmpTexture = getTexture(id);
  if(tmpTexture != NULL)
  {
    SDL_Texture* sdlTexture = tmpTexture->getSDLTexture();
    return sdlTexture;
  }
  return NULL;
}
SDL_Rect* TextureFolder::getRect(TEXTURE_ID id, int rectNum)
{
  Texture* tmpTexture = getTexture(id);
  if(tmpTexture != NULL)
  {
    return tmpTexture->getRect(rectNum);
  }
  return NULL;
}

//Private
Texture* TextureFolder::getTexture(TEXTURE_ID id)
{
  for(std::vector<Texture>::iterator it = _textureVector.begin(); it != _textureVector.end(); it++)
  {
    if(it->getID() == id)
    {
      return &(*it);
    }
  }
  return NULL;
}
