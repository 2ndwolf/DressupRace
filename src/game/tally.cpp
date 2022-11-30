#include <string>
#include <memory>

#include "rendering.h"
#include "game.h"
// #include "tally.h"

namespace Game {
  Tally::Tally(std::string window, int layer, SDLA::Vec2 position) : Npc(window, layer){
    SDLA::Rendering::Text::loadText(window, 1, 
      SDLA::Rendering::TextInfo().create(
        new SDLA::Rendering::Info((SDLA::Vec2) position),
        "Score: " + std::to_string(Tally::pts),
        "assets/Minecraft.ttf",
        12,
        (SDL_Color) {255,255,255}
    ), true);


  }

  void Tally::displayPoints(){

    // scoreTXT->updateText("Score: " + std::to_string(Tally::pts));
  }
}