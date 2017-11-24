#include "enums.h"
#include "game.h"
#include "error.h"

int main(int argv, char** args)
{
  RET_NUMS tmpNum = RET_FAILED;

  bool isDone = false;
  Error error;
  Game newGame;

  std::cout << "\n";

  newGame.init("./data/settings/window", &error);

  while(!isDone)
  {
    tmpNum = newGame.update();
    if(tmpNum == RET_FAILED)
    {
      isDone = true;
      newGame.close();
    }
  }
  return 0;
}
