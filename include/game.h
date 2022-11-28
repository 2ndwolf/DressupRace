#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include <string>
#include "rendering.h"
#include "gameobjects.h"

namespace Game{
  class HeadsMenu : public GameObjects::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::string window, int layer);
    ~HeadsMenu(){}
  };

  class BodiesMenu: public GameObjects::Npc {
    public:
    BodiesMenu();
    BodiesMenu(std::string window, int layer);
    ~BodiesMenu(){}
  };

  class ShieldsMenu: public GameObjects::Npc {
    public:
    ShieldsMenu();
    ShieldsMenu(std::string window, int layer);
    ~ShieldsMenu(){}
  };

  class Character: public GameObjects::Npc {
    public:
    Character();
    Character(std::string window, int layer);

  };

  class RandoChar: public GameObjects::Npc {
    public:
    RandoChar();
    RandoChar(std::string window, int layer);
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

    Tally(std::string window, int layer);
    void initPoints(std::string window);
    void displayPoints();
  };
}

#endif