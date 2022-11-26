#ifndef _gameobjects_h
#define _gameobjects_h

#include <memory>
#include <vector>
#include "rendering.h"
#include "identifier.h"

namespace Menus{
  std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> createBG9(std::string window, int layer, SDLA::Box sizeInBlocks, SDLA::Rendering::SpriteInfo* bgInfo, bool ignoreCamera);
}

namespace Npcs{
  class Npc {
    public:
      Npc(std::string window){
        id = SDLA::Identifier::newID();
        this->myWindow = window;
      }
      ~Npc(){}
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> sprites = 
        std::vector<std::shared_ptr<SDLA::Rendering::Sprite>>();
      std::vector<std::shared_ptr<SDLA::Rendering::Text>> texts = 
        std::vector<std::shared_ptr<SDLA::Rendering::Text>>();
      SDLA::ID id;
      std::string myWindow;
  };
}

namespace Actions{
  class Pairings{
    public:
    inline static std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> character;
    inline static int head;
    inline static int body;
    inline static int shield;
  };
  void setHead(int number);
  void setBody(int number);
  void setShield(int number);
}

#endif