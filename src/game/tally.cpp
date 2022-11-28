#include <string>
#include <memory>

#include "rendering.h"
#include "game.h"
// #include "tally.h"

namespace Game {
  Tally::Tally(std::string window, int layer) : Npc(window, layer){
    info->offset = {16,480};
    SDLA::Rendering::TextInfo* textInfo = new SDLA::Rendering::TextInfo();
    textInfo->textureText = "Score: " + std::to_string(Tally::pts);
    textInfo->fontName = "assets/Minecraft.ttf";
    textInfo->size = 12;
    textInfo->textColor = (SDL_Color) {255,255,255};
    Tally::scoreTXT = SDLA::Rendering::Text::loadText(window, 2, textInfo, true);

  }

  void Tally::displayPoints(){

    // scoreTXT->updateText("Score: " + std::to_string(Tally::pts));
  }
}