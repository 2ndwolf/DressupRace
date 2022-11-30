#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include <string>
#include "rendering.h"
#include "gameobjects.h"
#include "primitives.h"

namespace Game{
  class HeadsMenu : public GameObjects::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::string window, int layer, SDLA::Vec2 position);
    ~HeadsMenu(){}
  };

  class BodiesMenu: public GameObjects::Npc {
    public:
    BodiesMenu();
    BodiesMenu(std::string window, int layer, SDLA::Vec2 position);
    ~BodiesMenu(){}
  };

  class ShieldsMenu: public GameObjects::Npc {
    public:
    ShieldsMenu();
    ShieldsMenu(std::string window, int layer, SDLA::Vec2 position);
    ~ShieldsMenu(){}
  };

  class Character: public GameObjects::Npc {
    public:
    Character();
    Character(std::string window, int layer, SDLA::Vec2 position);

  };

  class RandoChar: public GameObjects::Npc {
    public:
    RandoChar();
    RandoChar(std::string window, int layer, SDLA::Vec2 position);
    void update();
    void refresh();

    int headNumber;
    int bodyNumber;
    int shieldNumber;
  };

  class Tally : public GameObjects::Npc{
    public:
    inline static int pts = 0;

    std::shared_ptr<SDLA::Rendering::Text> scoreTXT;

    SDLA::Rendering::SpriteInfo* info = new SDLA::Rendering::SpriteInfo();

    Tally(std::string window, int layer, SDLA::Vec2 position);
    void initPoints(std::string window);
    void displayPoints();
  };
}

#endif