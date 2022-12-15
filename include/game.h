#ifndef _npcs_h
#define _npcs_h

#include <memory>
#include <string>
#include "_MTR.h"
#include "gameobjects.h"
// #include "rendering.h"

// #include "image.h"
// #include "gameobjects.h"
// #include "primitives.h"
// #include "renderable.h"
// #include "renderables.h"

namespace Game{
  class HeadsMenu : public GameObjects::Npc {
    public:
    HeadsMenu();
    HeadsMenu(std::vector<std::string> window, int layer, Vec2 position);
    ~HeadsMenu(){}
  };

  // class BodiesMenu: public GameObjects::Npc {
  //   public:
  //   BodiesMenu();
  //   BodiesMenu(std::string window, int layer, Vec2 position);
  //   ~BodiesMenu(){}
  // };

  // class ShieldsMenu: public GameObjects::Npc {
  //   public:
  //   ShieldsMenu();
  //   ShieldsMenu(std::string window, int layer, Vec2 position);
  //   ~ShieldsMenu(){}
  // };

  class Character: public GameObjects::Npc {
    public:
    Character();
    Character(std::vector<std::string> windows, int layer, Vec2 position);

  };

  // class RandoChar: public GameObjects::Npc {
  //   public:
  //   RandoChar();
  //   RandoChar(std::string window, int layer, Vec2 position);
  //   void update();
  //   void refresh();

  //   int headNumber;
  //   int bodyNumber;
  //   int shieldNumber;

  //   MTR::RND::Image head  ;
  //   MTR::RND::Image body  ;
  //   MTR::RND::Image shield;
    
  //   int initX;
  // };

  // class Tally : public GameObjects::Npc{
  //   public:
  //   inline static int pts = 0;

  //   std::shared_ptr<FK::AT::Text> scoreTXT;

  //   FK::AT::SpriteInformation* information = new FK::AT::SpriteInformation(std::make_shared<FK::AT::Information>());

  //   Tally(std::string window, int layer, Vec2 position);
  //   void initPoints(std::string window);
  //   void displayPoints();
  // };
}

#endif