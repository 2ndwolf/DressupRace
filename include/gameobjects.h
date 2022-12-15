#ifndef _gameobjects_h
#define _gameobjects_h

#include <functional>
#include <memory>
#include <vector>
#include <string>

// #include "_MTR.h"
#include "spriteGroup.h"

namespace Menus{
  // std::vector<std::shared_ptr<FK::AT::Sprite>> createBG9(
  //   std::string window, int layer, FK::Box sizeInTiles, std::string fileName, FK::Box tileSize, std::shared_ptr<FK::AT::Information> group);
}

namespace GameObjects{
  class Npc {
    public:
      std::vector<std::string> windows;
      int layer;
      std::vector<MTR::RND::SpriteGroup*>  spriteGroups   = std::vector<MTR::RND::SpriteGroup*>();

      Npc(std::vector<std::string> pwindows, int player = 0, Vec2 position = {0,0}):
      windows(pwindows), layer(player)
      {
        spriteGroups.push_back(new MTR::RND::SpriteGroup{pwindows});
        spriteGroups[0]->bounds.pos.x = position.x;
        spriteGroups[0]->bounds.pos.y = position.y;
      };
      // ~Npc(){}
      // std::vector<std::vector<std::shared_ptr<FK::AT::Text>>>   texts   = std::vector<std::vector<std::shared_ptr<FK::AT::Text>>>(); 
      // FK::ID id;

      // std::shared_ptr<FK::AT::SpriteGroup> group = std::make_shared<FK::AT::SpriteGroup>();


      std::function<bool(int)> update;
      bool hasWorkerThread = false;

      inline void createWorkerThread(){
        hasWorkerThread = true;
      };
  };

  class BG9 : public Npc{
    public:
    Box fullSize = {0,0};

    BG9(std::vector<std::string> pwindows, int player = 0, Vec2 position = {0,0}):
      Npc(pwindows, player, position)
    {};

    MTR::RND::SpriteGroup* build(std::string fileName, Box sizeInTiles, Box tileSize = {16,16}, int groupIndex = 0, Vec2 srcPathing = {0,0});

  };

  // class Button : Npc{
  //   public:
  //   Button(MTR::RND::SpriteInformation sprite, std::string window, int layer) : Npc (window, layer) : MTR::Window::getWindow(window) {
  //     this->sprite = sprite;
  //     if(buttons[window].empty()){
  //       buttons[window] = std::vector<std::vector<std::shared_ptr<Button>>>(FK::Window::getWindow(window)->getLayerCount());
  //     }
  //   };
  //   // Button(std::shared_ptr<FK::AT::SpriteInformation> information, std::string window, int layer) : Npc (window, layer) {
  //   //   this->information = information;
  //   //   if(buttons[window].empty()){
  //   //     buttons[window] = std::vector<std::vector<std::shared_ptr<Button>>>(FK::Window::getWindow(window)->getLayerCount());
  //   //   }
  //   // };
  //   std::shared_ptr<FK::AT::SpriteInformation> spriteInformation;

  //   std::function<void(int)> action;

  //   int parameter;
  //   // Window -> Layer -> Button
  //   inline static std::map<std::string, std::vector<std::vector<std::shared_ptr<Button>>>> buttons;

  //   static bool searchClick(){
  //     for(std::vector<std::shared_ptr<Button>> bV : buttons[FK::Window::getCurrentWindowName()]){
  //       for(std::shared_ptr<Button> b : bV){
  //         if(b->clickInBounds()) {b->action(b->parameter); return true;}
  //       }
  //     }
  //     return false;
  //   };

  //   // change information->area to getSDLRECT().h/w
  //   bool clickInBounds(){
  //     FK::AT::SpriteInformation& information = *spriteInformation;
  //     if(information.hidden | information.ownerGroup->hidden) return false;

  //     Vec2 myOffset = FK::Window::getWindow(myWindow)->getBuffer()[layer].offset + information.offset;
  //     if(information.ownerGroup != nullptr){
  //       myOffset = myOffset + information.ownerGroup->offset;
  //       std::shared_ptr<FK::AT::SuperGroup> superGroup = information.ownerGroup->superGroup;
  //       while(superGroup != nullptr) {
  //         if(superGroup->hidden) return false;
  //         myOffset = myOffset + superGroup->offset + (information.ignoreCamera ? (Vec2){0,0} : information.ownerGroup->worldPos - FK::Window::getWindow(sprite->myWindow)->camPos);
  //         superGroup = superGroup->parentGroup;
  //       }
  //     }

  //     if( FK::Mouse::position.x > myOffset.x &&
  //         FK::Mouse::position.y > myOffset.y &&
  //         FK::Mouse::position.x < myOffset.x + information.area.box.width &&
  //         FK::Mouse::position.y < myOffset.y + information.area.box.height) return true;
  //     return false;
  //   };
  // };

  // class bG9{
  //   public:
  //   std::shared_ptr<FK::AT::SpriteGroup> spriteGroup = std::shared_ptr<FK::AT::SpriteGroup>();
  //   
  // };
}


// namespace Actions{
//   class Pairings{
//     public:
//     inline static MTR::RND::SpriteGroup character;
//     inline static int head;
//     inline static int body;
//     inline static int shield;
//   };
//   void setHead(int number);
//   void setBody(int number);
//   void setShield(int number);
// }

#endif