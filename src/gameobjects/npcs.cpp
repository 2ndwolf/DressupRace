#include <memory>
#include <cstdlib>
#include <string>

#include "gameobjects.h"
#include "npcs.h"
#include "rendering.h"
#include "primitives.h"
#include "identifier.h"
#include "button.h"

namespace Npcs {
  HeadsMenu::HeadsMenu(std::string window) : Npc::Npc(window){

    SDLA::Rendering::SpriteInfo* hMenuBackground = new SDLA::Rendering::SpriteInfo();
    hMenuBackground->fileName = "assets/menubg.png";
    hMenuBackground->area.box.width = 16;
    hMenuBackground->area.box.height = 16;
    hMenuBackground->offset.x = 10;
    hMenuBackground->offset.y = 10;
    SDLA::Box hMenuSize = (SDLA::Box) {30,9};

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> bg9 = Menus::createBG9(window, 1, hMenuSize, hMenuBackground, true);
      sprites.insert(sprites.end(), bg9.begin(), bg9.end());
    }

    SDLA::Box headGridSize = {11,3};
    std::vector<SDLA::Rendering::SpriteInfo*> heads;
    SDLA::Rendering::SpriteInfo* headGrid = new SDLA::Rendering::SpriteInfo();
    headGrid->offset.x = 32;
    headGrid->offset.y = 26;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < headGridSize.height; y++){
      for(int x = 0; x < headGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
        head->fileName = "assets/head" + std::to_string(i) + ".png";
        head->offset = {x * (32 + spacing), y * (32 + spacing)};
        head->area.box.width = 32;
        head->area.box.height = 32;
        head->area.pos.x = 0;
        head->area.pos.y = 64;
        heads.push_back(head);


        if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(SDLA::Bounds{head->offset+headGrid->offset,head->area.box});
        button->action = Actions::setHead;
        button->parameter = i;
        Button::buttons[window].push_back(button);

        i++;
      }
    }

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, 1, headGrid, heads, true);
      sprites.insert(sprites.end(), imgG.begin(), imgG.end());
    }
  }

  BodiesMenu::BodiesMenu(std::string window) : Npc::Npc(window){

    SDLA::Rendering::SpriteInfo* bMenuBackground = new SDLA::Rendering::SpriteInfo();
    bMenuBackground->fileName = "assets/menubg.png";
    bMenuBackground->area.box.width = 16;
    bMenuBackground->area.box.height = 16;
    bMenuBackground->offset.x = 500 - (10+7*16);
    bMenuBackground->offset.y = 10 + 10 * 16;
    SDLA::Box bMenuSize = (SDLA::Box) {7,11};

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> bg9 = Menus::createBG9(window, 0, bMenuSize, bMenuBackground, true);
      sprites.insert(sprites.end(), bg9.begin(), bg9.end());
    }

    SDLA::Box bodyGridSize = {2,4};
    std::vector<SDLA::Rendering::SpriteInfo*> bodies;
    SDLA::Rendering::SpriteInfo* bodyGrid = new SDLA::Rendering::SpriteInfo();
    bodyGrid->offset.x = 500 - (10+6*16);
    bodyGrid->offset.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < bodyGridSize.height; y++){
      for(int x = 0; x < bodyGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
        body->fileName = "assets/body" + std::to_string(i) + ".png";
        body->offset = {x * (32 + spacing), y * (32 + spacing)};
        body->area.box.width = 32;
        body->area.box.height = 32;
        body->area.pos.x = 64;
        body->area.pos.y = 0;
        bodies.push_back(body);

        if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(SDLA::Bounds{body->offset+bodyGrid->offset,body->area.box});
        button->action = Actions::setBody;
        button->parameter = i;
        Button::buttons[window].push_back(button);

        i++;
      }
    }
    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, 1, bodyGrid, bodies, true);
      sprites.insert(sprites.end(), imgG.begin(), imgG.end());
    }
  }

  ShieldsMenu::ShieldsMenu(std::string window) : Npc::Npc(window){

    SDLA::Rendering::SpriteInfo* sMenuBackground = new SDLA::Rendering::SpriteInfo();
    sMenuBackground->fileName = "assets/menubg.png";
    sMenuBackground->area.box.width = 16;
    sMenuBackground->area.box.height = 16;
    sMenuBackground->offset.x = 10;
    sMenuBackground->offset.y = 10 + 10 * 16;
    SDLA::Box sMenuSize = (SDLA::Box) {7,11};

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> bg9 = Menus::createBG9(window, 0, sMenuSize, sMenuBackground, true);
      sprites.insert(sprites.end(), bg9.begin(), bg9.end());
    }

    SDLA::Box shieldGridSize = {2,4};
    std::vector<SDLA::Rendering::SpriteInfo*> shields;
    SDLA::Rendering::SpriteInfo* shieldGrid = new SDLA::Rendering::SpriteInfo();
    shieldGrid->offset.x = 32;
    shieldGrid->offset.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < shieldGridSize.height; y++){
      for(int x = 0; x < shieldGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();
        shield->fileName = "assets/shield" + std::to_string(i) + ".png";
        shield->offset = {x * (32 + spacing), y * (32 + spacing)};
        shield->area.box.width = 16;
        shield->area.box.height = 20;
        shield->area.pos.x = 14;
        shield->area.pos.y = 0;
        shields.push_back(shield);

        if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(SDLA::Bounds{shield->offset+shieldGrid->offset,shield->area.box});
        button->action = Actions::setShield;
        button->parameter = i;
        Button::buttons[window].push_back(button);

        i++;
      }
    }

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, 1, shieldGrid, shields, true);
      sprites.insert(sprites.end(), imgG.begin(), imgG.end());
    }

  }

  Character::Character(std::string window) : Npc::Npc(window){
    SDLA::Rendering::SpriteInfo* characterGroup = new SDLA::Rendering::SpriteInfo();
    characterGroup->offset = {250,250};

    SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();

    head->fileName = "assets/head440.png";
    head->offset = {0, 0};
    head->area.box.width = 32;
    head->area.box.height = 32;
    head->area.pos.x = 0;
    head->area.pos.y = 64;

    body->fileName = "assets/body0.png";
    body->offset = {0, 16};
    body->area.box.width = 32;
    body->area.box.height = 32;
    body->area.pos.x = 64;
    body->area.pos.y = 0;

    shield->fileName = "assets/shield2.png";
    shield->offset = {-3, 20};
    shield->area.box.width = 16;
    shield->area.box.height = 20;
    shield->area.pos.x = 14;
    shield->area.pos.y = 0;

    std::vector<SDLA::Rendering::SpriteInfo*> character = {body, head, shield};

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, 1, characterGroup, character, true);
      sprites.insert(sprites.end(), imgG.begin(), imgG.end());
    }

    Actions::Pairings::character = sprites;
  }

  RandoChar::RandoChar(std::string window) : Npc::Npc(window){
    myWindow = window;
    refresh();
  }

  void RandoChar::update(){
    sprites[0]->ownerGroup->info->offset.x -= 1;
    if(sprites[0]->ownerGroup->info->offset.x < -64){
      refresh();
    }

  }

  void RandoChar::refresh(){
    SDLA::Rendering::SpriteInfo* characterGroup = new SDLA::Rendering::SpriteInfo();
    characterGroup->offset = {550,400};

    headNumber = rand() % 33;
    bodyNumber = rand() % 8;
    shieldNumber = rand() % 8;

    SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();

    head->fileName = "assets/head" + std::to_string(headNumber) + ".png";
    head->offset = {0, 0};
    head->area.box.width = 32;
    head->area.box.height = 32;
    head->area.pos.x = 0;
    head->area.pos.y = 64;

    body->fileName = "assets/body" + std::to_string(bodyNumber) + ".png";
    body->offset = {0, 16};
    body->area.box.width = 32;
    body->area.box.height = 32;
    body->area.pos.x = 64;
    body->area.pos.y = 0;

    shield->fileName = "assets/shield" + std::to_string(shieldNumber) + ".png";
    shield->offset = {-3, 20};
    shield->area.box.width = 16;
    shield->area.box.height = 20;
    shield->area.pos.x = 14;
    shield->area.pos.y = 0;

    std::vector<SDLA::Rendering::SpriteInfo*> character = {body, head, shield};

    if(sprites.size() != 0){
      sprites[0]->ownerGroup->pendingErase = true;
    } else {
      sprites = std::vector<std::shared_ptr<SDLA::Rendering::Sprite>>();
    }
    sprites = {SDLA::Rendering::Sprite::addImageGroup(myWindow, 0, characterGroup, character, true)};

  }

}