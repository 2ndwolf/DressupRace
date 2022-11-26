#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include "rendering.h"
#include "gameobjects.h"

namespace Npcs{
  class HeadsMenu : public Npcs::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::shared_ptr<SDLA::Rendering::Window> window);
    ~HeadsMenu(){}
  };

  class BodiesMenu: public Npcs::Npc {
    public:
    BodiesMenu();
    BodiesMenu(std::shared_ptr<SDLA::Rendering::Window> window);
    ~BodiesMenu(){}
  };

  class ShieldsMenu: public Npcs::Npc {
    public:
    ShieldsMenu();
    ShieldsMenu(std::shared_ptr<SDLA::Rendering::Window> window);
    ~ShieldsMenu(){}
  };

  class Character: public Npcs::Npc {
    public:
    Character();
    Character(std::shared_ptr<SDLA::Rendering::Window> window);

  };

  class RandoChar: public Npcs::Npc {
    public:
    RandoChar();
    RandoChar(std::shared_ptr<SDLA::Rendering::Window> window);
    void update();
    void refresh(std::shared_ptr<SDLA::Rendering::Window> window);

    int headNumber;
    int bodyNumber;
    int shieldNumber;
  };
}

#endif