#ifndef _gameobjects_h
#define _gameobjects_h

#include <memory>
#include <vector>
#include "rendering.h"
#include "identifier.h"

namespace Menus{
  std::shared_ptr<SDLA::Rendering::SpriteGroup> createBG9(std::shared_ptr<SDLA::Rendering::Window> window, int layer, SDLA::Box sizeInBlocks, SDLA::Rendering::SpriteInfo* bgInfo);
}

namespace Npcs{
  class Npc {
    public:
      Npc(){
        id = SDLA::Identifier::newID();
      }
      ~Npc(){}
      std::vector<std::vector<std::shared_ptr<SDLA::Rendering::SpriteGroup>>> images = 
        std::vector<std::vector<std::shared_ptr<SDLA::Rendering::SpriteGroup>>>(1,std::vector<std::shared_ptr<SDLA::Rendering::SpriteGroup>>(0));
      SDLA::ID id;
      std::shared_ptr<SDLA::Rendering::Window> myWindow;
  };
}

namespace Actions{
  class Pairings{
    public:
    inline static std::shared_ptr<SDLA::Rendering::SpriteGroup> character;
    inline static int head;
    inline static int body;
    inline static int shield;
  };
  void setHead(int number);
  void setBody(int number);
  void setShield(int number);
}

#endif