#include <SDL.h>

#include "rendering.h"
#include "gameobjects.h"
#include "input.h"
#include "npcs.h"

namespace Actions{
  void setHead(int number){
    Pairings::head = number;
    Pairings::character[1]->changeSurface("assets/head" + std::to_string(number) + ".png");
  }
  void setBody(int number){
    Pairings::body = number;
    Pairings::character[0]->changeSurface("assets/body" + std::to_string(number) + ".png");
  }
  void setShield(int number){
    Pairings::shield = number;
    Pairings::character[2]->changeSurface("assets/shield" + std::to_string(number) + ".png");
  }
}