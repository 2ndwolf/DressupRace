#ifndef _gameobjects_h
#define _gameobjects_h

#include <functional>
#include <memory>
#include <vector>
#include "rendering.h"
#include "identifier.h"
#include "input.h"

namespace Menus{
  std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> createBG9(std::string window, int layer, SDLA::Box sizeInBlocks, SDLA::Rendering::SpriteInfo* bgInfo, SDLA::Rendering::SpriteGroup* groupInfo);
}

namespace GameObjects{
  class Npc {
    public:
      Npc(std::string window, int layer){
        id = SDLA::Identifier::newID();
        this->myWindow = window;
        this->layer = SDLA::Rendering::getWindow(window)->clampLayerIndex(layer);
      };
      // ~Npc(){}
      std::vector<std::vector<std::shared_ptr<SDLA::Rendering::Sprite>>> sprites = std::vector<std::vector<std::shared_ptr<SDLA::Rendering::Sprite>>>(); 
      std::vector<std::vector<std::shared_ptr<SDLA::Rendering::Text>>>   texts   = std::vector<std::vector<std::shared_ptr<SDLA::Rendering::Text>>>(); 
      SDLA::ID id;
      std::string myWindow;
      int layer;
  };

  class Button : Npc{
    public:
    Button(SDLA::Rendering::SpriteInfo* info, std::string window, int layer) : Npc (window, layer) {
      this->info = std::shared_ptr<SDLA::Rendering::SpriteInfo>(info);
      if(buttons[window].empty()){
        buttons[window] = std::vector<std::vector<std::shared_ptr<Button>>>(SDLA::Rendering::getWindow(window)->getLayerCount());
      }
    };
    Button(std::shared_ptr<SDLA::Rendering::SpriteInfo> info, std::string window, int layer) : Npc (window, layer) {
      this->info = info;
      if(buttons[window].empty()){
        buttons[window] = std::vector<std::vector<std::shared_ptr<Button>>>(SDLA::Rendering::getWindow(window)->getLayerCount());
      }
    };
    std::shared_ptr<SDLA::Rendering::SpriteInfo> info;

    std::function<void(int)> action;

    int parameter;
    // Window -> Layer -> Button
    inline static std::map<std::string, std::vector<std::vector<std::shared_ptr<Button>>>> buttons;

    static bool searchClick(){
      for(std::vector<std::shared_ptr<Button>> bV : buttons[SDLA::Rendering::getCurrentWindowName()]){
        for(std::shared_ptr<Button> b : bV){
          if(b->clickInBounds()) {b->action(b->parameter); return true;}
        }
      }
      return false;
    };

    // change info->area to getSDLRECT().h/w
    bool clickInBounds(){
      if(info->hidden | info->ownerGroup->hidden) return false;

      SDLA::Vec2 myOffset = SDLA::Rendering::getWindow(myWindow)->getBuffer()[layer]->offset + info->offset;
      if(info->ownerGroup != nullptr){
        myOffset = myOffset + info->ownerGroup->offset;
        std::shared_ptr<SDLA::Rendering::SuperGroup> superGroup = info->ownerGroup->superGroup;
        while(superGroup != nullptr) {
          if(superGroup->hidden) return false;
          myOffset = myOffset + superGroup->offset + (info->ignoreCamera ? (SDLA::Vec2){0,0} : superGroup->worldPos);
          superGroup = superGroup->parentGroup;
        }
      }

      if( Input::Mouse::mousePos.x > myOffset.x &&
          Input::Mouse::mousePos.y > myOffset.y &&
          Input::Mouse::mousePos.x < myOffset.x + info->area.box.width &&
          Input::Mouse::mousePos.y < myOffset.y + info->area.box.height) return true;
      return false;
    };
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