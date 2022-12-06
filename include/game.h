#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include <string>
// #include "rendering.h"

#include "information.h"
#include "gameobjects.h"
#include "TSRPrimitives.h"
#include "renderable.h"
// #include "renderables.h"

namespace Game{
  class HeadsMenu : public GameObjects::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::string window, int layer, Vec2 position);
    ~HeadsMenu(){}
  };

  class BodiesMenu: public GameObjects::Npc {
    public:
    BodiesMenu();
    BodiesMenu(std::string window, int layer, Vec2 position);
    ~BodiesMenu(){}
  };

  class ShieldsMenu: public GameObjects::Npc {
    public:
    ShieldsMenu();
    ShieldsMenu(std::string window, int layer, Vec2 position);
    ~ShieldsMenu(){}
  };

  class Character: public GameObjects::Npc {
    public:
    Character();
    Character(std::string window, int layer, Vec2 position);

  };

  class RandoChar: public GameObjects::Npc {
    public:
    RandoChar();
    RandoChar(std::string window, int layer, Vec2 position);
    void update();
    void refresh();

    int headNumber;
    int bodyNumber;
    int shieldNumber;

    std::shared_ptr<FK::ORE::Renderable> head  ;
    std::shared_ptr<FK::ORE::Renderable> body  ;
    std::shared_ptr<FK::ORE::Renderable> shield;
    
    int initX;
  };

  class Tally : public GameObjects::Npc{
    public:
    inline static int pts = 0;

    std::shared_ptr<FK::AT::Text> scoreTXT;

    FK::AT::SpriteInformation* information = new FK::AT::SpriteInformation(std::make_shared<FK::AT::Information>());

    Tally(std::string window, int layer, Vec2 position);
    void initPoints(std::string window);
    void displayPoints();
  };
}

#endif