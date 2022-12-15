#define NONONO
#ifndef NONONO


#include <SDL.h>

#include "gameobjects.h"

namespace Actions{
  void setHead(int number){
    Pairings::head = number;
    Pairings::character->sprites[1]->changeSurface("assets/head" + std::to_string(number) + ".png");
  }
  void setBody(int number){
    Pairings::body = number;
    Pairings::character->sprites[0]->changeSurface("assets/body" + std::to_string(number) + ".png");
  }
  void setShield(int number){
    Pairings::shield = number;
    Pairings::character->sprites[2]->changeSurface("assets/shield" + std::to_string(number) + ".png");
  }
}
#endif