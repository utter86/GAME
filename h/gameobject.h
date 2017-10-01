#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "window.h"
#include "enums.h"
#include "error.h"

class GameObject
{
public:
  RET_NUMS init(int id, SDL_Rect* viewPort = NULL);

  bool mouseMove();

  RET_NUMS render(Window* window);

  void close();

  //Getters
  int getID();
  SDL_Rect* getRect();

  //Setters
  void setTexture(TEXTURE_ID ID, int start, int stop, SDL_Rect dstRect, double angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
  void setText(std::string text, int x, int y, int size);
  void setPos(int x, int y);
  void setSize(int w, int h);
  void setRect(SDL_Rect rect);
  void setBorder(SDL_Color* color = NULL);
  void setViewport(SDL_Rect* viewPort);
  void fitRect(bool texture = false);

private:
  int _id;
  bool _border;

  //Texture stuff
  TEXTURE_ID _textId;
  int _start; int _stop;
  SDL_Rect _textureDestRect;
  double _angle;
  SDL_RendererFlip _flip;
  int _textureX;
  int _textureY;

  //Text stuff
  std::string _text;
  int _textX;
  int _textY;
  int _textSize;

  SDL_Color _borderColor;

  SDL_Rect _objectRect;
  int _objX; int _objY;
  SDL_Rect* _viewPort;

  Error _error;
};

#endif //GAMEOBJECT_H
