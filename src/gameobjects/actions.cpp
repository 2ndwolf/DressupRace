#include <SDL.h>

#include "rendering.h"
#include "gameobjects.h"
#include "npcs.h"

namespace Actions{
  void setHead(int number){
    Pairings::head = number;
    SDLA::Rendering::Sprite::changeSurface(Pairings::character->sprites[1], "assets/head" + std::to_string(number) + ".png");
  }
  void setBody(int number){
    Pairings::body = number;
    SDLA::Rendering::Sprite::changeSurface(Pairings::character->sprites[0], "assets/body" + std::to_string(number) + ".png");
  }
  void setShield(int number){
    Pairings::shield = number;
    SDLA::Rendering::Sprite::changeSurface(Pairings::character->sprites[2], "assets/shield" + std::to_string(number) + ".png");
  }
}