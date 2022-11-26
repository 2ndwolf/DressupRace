#include <string>
#include <memory>

#include "rendering.h"
#include "tally.h"

namespace Tally {
  void Points::initPoints(std::shared_ptr<SDLA::Rendering::Window> win){
    info->pos.worldPos = {16,480};
    SDLA::Rendering::TextInfo* textInfo = new SDLA::Rendering::TextInfo();
    textInfo->textureText = "Score: " + std::to_string(Points::pts);
    textInfo->fontName = "assets/Minecraft.ttf";
    textInfo->size = 12;
    textInfo->textColor = (SDL_Color) {255,255,255};
    Points::scoreTXT = SDLA::Rendering::Text::loadText(win, 2, info, textInfo);

  }

  void Points::displayPoints(){

    scoreTXT->updateText("Score: " + std::to_string(Points::pts));
  }
}