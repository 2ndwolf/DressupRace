#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include "rendering.h"
#include "gameobjects.h"

namespace Npcs{
  class HeadsMenu : public Npcs::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::string window);
    ~HeadsMenu(){}
  };

  class BodiesMenu: public Npcs::Npc {
    public:
    BodiesMenu();
    BodiesMenu(std::string window);
    ~BodiesMenu(){}
  };

  class ShieldsMenu: public Npcs::Npc {
    public:
    ShieldsMenu();
    ShieldsMenu(std::string window);
    ~ShieldsMenu(){}
  };

  class Character: public Npcs::Npc {
    public:
    Character();
    Character(std::string window);

  };

  class RandoChar: public Npcs::Npc {
    public:
    RandoChar();
    RandoChar(std::string window);
    void update();
    void refresh();

    int headNumber;
    int bodyNumber;
    int shieldNumber;
  };
}

#endif