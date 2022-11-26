#ifndef _tally_h
#define _tally_h

#include "rendering.h"

namespace Tally {
  class Points{
    public:
    inline static int pts = 0;

    std::shared_ptr<SDLA::Rendering::Text> scoreTXT;

    SDLA::Rendering::SpriteInfo* info = new SDLA::Rendering::SpriteInfo();

    void initPoints(std::string window);
    void displayPoints();
  };
}

#endif