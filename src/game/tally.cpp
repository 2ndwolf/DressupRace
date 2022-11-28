#include <string>
#include <memory>

#include "rendering.h"
#include "tally.h"

namespace Tally {
  void Points::initPoints(std::string window){
    info->offset = {16,480};
    SDLA::Rendering::TextInfo* textInfo = new SDLA::Rendering::TextInfo();
    textInfo->textureText = "Score: " + std::to_string(Points::pts);
    textInfo->fontName = "assets/Minecraft.ttf";
    textInfo->size = 12;
    textInfo->textColor = (SDL_Color) {255,255,255};
    Points::scoreTXT = SDLA::Rendering::Text::loadText(window, 2, textInfo, true);

  }

  void Points::displayPoints(){

    // scoreTXT->updateText("Score: " + std::to_string(Points::pts));
  }
}