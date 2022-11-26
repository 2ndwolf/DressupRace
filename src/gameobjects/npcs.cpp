#include <memory>
#include <cstdlib>

#include "gameobjects.h"
#include "npcs.h"
#include "rendering.h"
#include "primitives.h"
#include "identifier.h"
#include "button.h"

namespace Npcs {
  HeadsMenu::HeadsMenu(std::shared_ptr<SDLA::Rendering::Window> window) : Npc::Npc(){
    SDLA::ID winID = SDLA::Rendering::Window::getWindowID(window);
    // id = SDLA::Identifier::newID();

    SDLA::Rendering::SpriteInfo* hMenuBackground = new SDLA::Rendering::SpriteInfo();
    hMenuBackground->fileName = "assets/menubg.png";
    hMenuBackground->area.box.width = 16;
    hMenuBackground->area.box.height = 16;
    hMenuBackground->pos.worldPos.x = 10;
    hMenuBackground->pos.worldPos.y = 10;
    SDLA::Box hMenuSize = (SDLA::Box) {30,9};

    images[0].push_back(Menus::createBG9(window, 0, hMenuSize, hMenuBackground));

    SDLA::Box headGridSize = {11,3};
    std::vector<SDLA::Rendering::SpriteInfo*> heads;
    SDLA::Rendering::SpriteInfo* headGrid = new SDLA::Rendering::SpriteInfo();
    headGrid->pos.worldPos.x = 32;
    headGrid->pos.worldPos.y = 26;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < headGridSize.height; y++){
      for(int x = 0; x < headGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
        head->fileName = "assets/head" + std::to_string(i) + ".png";
        // head->fileName = "assets/head440.png";
        head->pos.offset = {x * (32 + spacing), y * (32 + spacing)};
        head->area.box.width = 32;
        head->area.box.height = 32;
        head->area.pos.x = 0;
        head->area.pos.y = 64;
        heads.push_back(head);


        if(SDLA::Button::buttons[winID].empty()) SDLA::Button::buttons.insert({winID,std::vector<std::shared_ptr<SDLA::Button>>()});
        std::shared_ptr<SDLA::Button> button = std::make_shared<SDLA::Button>(SDLA::Bounds{head->pos.offset+headGrid->pos.worldPos,head->area.box});
        button->action = Actions::setHead;
        button->parameter = i;
        SDLA::Button::buttons[winID].push_back(button);

        i++;
      }
    }

    images[0].push_back(SDLA::Rendering::Sprite::addImageGroup(window, 1, headGrid, heads));
  }

  BodiesMenu::BodiesMenu(std::shared_ptr<SDLA::Rendering::Window> window) : Npc::Npc(){
    SDLA::ID winID = SDLA::Rendering::Window::getWindowID(window);

    SDLA::Rendering::SpriteInfo* bMenuBackground = new SDLA::Rendering::SpriteInfo();
    bMenuBackground->fileName = "assets/menubg.png";
    bMenuBackground->area.box.width = 16;
    bMenuBackground->area.box.height = 16;
    bMenuBackground->pos.worldPos.x = 500 - (10+7*16);
    bMenuBackground->pos.worldPos.y = 10 + 10 * 16;
    SDLA::Box bMenuSize = (SDLA::Box) {7,11};

    id = SDLA::Identifier::newID();
    images[0].push_back(Menus::createBG9(window, 0, bMenuSize, bMenuBackground));

    SDLA::Box bodyGridSize = {2,4};
    std::vector<SDLA::Rendering::SpriteInfo*> bodies;
    SDLA::Rendering::SpriteInfo* bodyGrid = new SDLA::Rendering::SpriteInfo();
    bodyGrid->pos.worldPos.x = 500 - (10+6*16);
    bodyGrid->pos.worldPos.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < bodyGridSize.height; y++){
      for(int x = 0; x < bodyGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
        body->fileName = "assets/body" + std::to_string(i) + ".png";
        body->pos.offset = {x * (32 + spacing), y * (32 + spacing)};
        body->area.box.width = 32;
        body->area.box.height = 32;
        body->area.pos.x = 64;
        body->area.pos.y = 0;
        bodies.push_back(body);

        if(SDLA::Button::buttons[winID].empty()) SDLA::Button::buttons.insert({winID,std::vector<std::shared_ptr<SDLA::Button>>()});
        std::shared_ptr<SDLA::Button> button = std::make_shared<SDLA::Button>(SDLA::Bounds{body->pos.offset+bodyGrid->pos.worldPos,body->area.box});
        button->action = Actions::setBody;
        button->parameter = i;
        SDLA::Button::buttons[winID].push_back(button);

        i++;
      }
    }
    images[0].push_back(SDLA::Rendering::Sprite::addImageGroup(window, 1, bodyGrid, bodies));
  }

  ShieldsMenu::ShieldsMenu(std::shared_ptr<SDLA::Rendering::Window> window) : Npc::Npc(){
    SDLA::ID winID = SDLA::Rendering::Window::getWindowID(window);

    SDLA::Rendering::SpriteInfo* sMenuBackground = new SDLA::Rendering::SpriteInfo();
    sMenuBackground->fileName = "assets/menubg.png";
    sMenuBackground->area.box.width = 16;
    sMenuBackground->area.box.height = 16;
    sMenuBackground->pos.worldPos.x = 10;
    sMenuBackground->pos.worldPos.y = 10 + 10 * 16;
    SDLA::Box sMenuSize = (SDLA::Box) {7,11};

    images[0].push_back(Menus::createBG9(window, 0, sMenuSize, sMenuBackground));

    SDLA::Box shieldGridSize = {2,4};
    std::vector<SDLA::Rendering::SpriteInfo*> shields;
    SDLA::Rendering::SpriteInfo* shieldGrid = new SDLA::Rendering::SpriteInfo();
    shieldGrid->pos.worldPos.x = 32;
    shieldGrid->pos.worldPos.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    for(int y = 0; y < shieldGridSize.height; y++){
      for(int x = 0; x < shieldGridSize.width; x++){
        SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();
        shield->fileName = "assets/shield" + std::to_string(i) + ".png";
        shield->pos.offset = {x * (32 + spacing), y * (32 + spacing)};
        shield->area.box.width = 16;
        shield->area.box.height = 20;
        shield->area.pos.x = 14;
        shield->area.pos.y = 0;
        shields.push_back(shield);

        if(SDLA::Button::buttons[winID].empty()) SDLA::Button::buttons.insert({winID,std::vector<std::shared_ptr<SDLA::Button>>()});
        std::shared_ptr<SDLA::Button> button = std::make_shared<SDLA::Button>(SDLA::Bounds{shield->pos.offset+shieldGrid->pos.worldPos,shield->area.box});
        button->action = Actions::setShield;
        button->parameter = i;
        SDLA::Button::buttons[winID].push_back(button);

        i++;
      }
    }

    images[0].push_back(SDLA::Rendering::Sprite::addImageGroup(window, 1, shieldGrid, shields));

  }

  Character::Character(std::shared_ptr<SDLA::Rendering::Window> window) : Npc::Npc(){
    SDLA::Rendering::SpriteInfo* characterGroup = new SDLA::Rendering::SpriteInfo();
    characterGroup->pos.worldPos = {250,250};

    SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();

    head->fileName = "assets/head440.png";
    head->pos.offset = {0, 0};
    head->area.box.width = 32;
    head->area.box.height = 32;
    head->area.pos.x = 0;
    head->area.pos.y = 64;

    body->fileName = "assets/body0.png";
    body->pos.offset = {0, 16};
    body->area.box.width = 32;
    body->area.box.height = 32;
    body->area.pos.x = 64;
    body->area.pos.y = 0;

    shield->fileName = "assets/shield2.png";
    shield->pos.offset = {-3, 20};
    shield->area.box.width = 16;
    shield->area.box.height = 20;
    shield->area.pos.x = 14;
    shield->area.pos.y = 0;

    std::vector<SDLA::Rendering::SpriteInfo*> character = {body, head, shield};

    images[0].push_back(SDLA::Rendering::Sprite::addImageGroup(window, 0, characterGroup, character));
    Actions::Pairings::character = images[0][0];
  }

  RandoChar::RandoChar(std::shared_ptr<SDLA::Rendering::Window> window) : Npc::Npc(){
    myWindow = window;
    refresh(window);
  }

  void RandoChar::update(){
    images[0][0]->info->pos.worldPos.x -= 1;
    if(images[0][0]->info->pos.worldPos.x < -64){
      refresh(myWindow);
    }

  }

  void RandoChar::refresh(std::shared_ptr<SDLA::Rendering::Window> window){
    SDLA::Rendering::SpriteInfo* characterGroup = new SDLA::Rendering::SpriteInfo();
    characterGroup->pos.worldPos = {550,400};

    headNumber = rand() % 33;
    bodyNumber = rand() % 8;
    shieldNumber = rand() % 8;

    SDLA::Rendering::SpriteInfo* head = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* body = new SDLA::Rendering::SpriteInfo();
    SDLA::Rendering::SpriteInfo* shield = new SDLA::Rendering::SpriteInfo();

    head->fileName = "assets/head" + std::to_string(headNumber) + ".png";
    head->pos.offset = {0, 0};
    head->area.box.width = 32;
    head->area.box.height = 32;
    head->area.pos.x = 0;
    head->area.pos.y = 64;

    body->fileName = "assets/body" + std::to_string(bodyNumber) + ".png";
    body->pos.offset = {0, 16};
    body->area.box.width = 32;
    body->area.box.height = 32;
    body->area.pos.x = 64;
    body->area.pos.y = 0;

    shield->fileName = "assets/shield" + std::to_string(shieldNumber) + ".png";
    shield->pos.offset = {-3, 20};
    shield->area.box.width = 16;
    shield->area.box.height = 20;
    shield->area.pos.x = 14;
    shield->area.pos.y = 0;

    std::vector<SDLA::Rendering::SpriteInfo*> character = {body, head, shield};

    if(images[0].size() != 0){
      images[0][0]->pendingErase = true;
    } else {
      images[0] = std::vector<std::shared_ptr<SDLA::Rendering::SpriteGroup>>();
    }
    images[0] = {SDLA::Rendering::Sprite::addImageGroup(window, 0, characterGroup, character)};

  }

}