#include <memory>
#include <cstdlib>
#include <string>

#include "gameobjects.h"
#include "npcs.h"
#include "rendering.h"
#include "primitives.h"
#include "identifier.h"

namespace GameObjects {

  std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> createBG9(std::string window, int layer, std::string fileName, SDLA::Box tileSize, SDLA::Box sizeInTiles, SDLA::Rendering::SpriteGroup* group){
    SDLA::Rendering::SpriteInfo* menuBackground = new SDLA::Rendering::SpriteInfo();
    menuBackground->fileName = fileName;
    menuBackground->area.box = tileSize;
    SDLA::Box hMenuSize = sizeInTiles;


    return Menus::createBG9(window, layer, hMenuSize, menuBackground, group);
  }

  HeadsMenu::HeadsMenu(std::string window, int layer) : Npc::Npc(window, layer){

    SDLA::Rendering::SpriteGroup* menuGroup = new SDLA::Rendering::SpriteGroup();
    menuGroup->offset.x = 10;
    menuGroup->offset.y = 10;

    sprites.push_back(createBG9(window, layer, "assets/menubg.png", {16,16}, {30,9}, menuGroup));

    SDLA::Box gridSize = {11,3};
    SDLA::Rendering::SpriteGroup* grid = new SDLA::Rendering::SpriteGroup();
    grid->offset.x = 32;
    grid->offset.y = 26;
    int spacing = 8;
    int i = 0;
    std::vector<SDLA::Rendering::SpriteInfo*> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        SDLA::Rendering::SpriteInfo* image = new SDLA::Rendering::SpriteInfo();
        image->ownerGroup = std::shared_ptr<SDLA::Rendering::SpriteGroup>(grid);
        image->fileName = "assets/head" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 32;
        image->area.box.height = 32;
        image->area.pos.x = 0;
        image->area.pos.y = 64;
        images.push_back(image);


        // if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(image, window, layer);
        button->action = Actions::setHead;
        button->parameter = i;
        Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, layer, grid, images);
      sprites.push_back(imgG);
    }
  }

  BodiesMenu::BodiesMenu(std::string window, int layer) : Npc::Npc(window, layer){

    SDLA::Rendering::SpriteGroup* menuGroup = new SDLA::Rendering::SpriteGroup();
    menuGroup->offset.x = 500 - (10+7*16);
    menuGroup->offset.y = 10 + 10 * 16;

    sprites.push_back(createBG9(window, layer, "assets/menubg.png", {16,16}, {7,11}, menuGroup));

    SDLA::Box gridSize = {2,4};
    SDLA::Rendering::SpriteGroup* grid = new SDLA::Rendering::SpriteGroup();
    grid->offset.x = 500 - (10+6*16);
    grid->offset.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    std::vector<SDLA::Rendering::SpriteInfo*> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        SDLA::Rendering::SpriteInfo* image = new SDLA::Rendering::SpriteInfo();
        image->ownerGroup = std::shared_ptr<SDLA::Rendering::SpriteGroup>(grid);
        image->fileName = "assets/body" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 32;
        image->area.box.height = 32;
        image->area.pos.x = 64;
        image->area.pos.y = 0;
        images.push_back(image);


        // if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(image, window, layer);
        button->action = Actions::setBody;
        button->parameter = i;
        Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, layer, grid, images);
      sprites.push_back(imgG);
    }
  }

  ShieldsMenu::ShieldsMenu(std::string window, int layer) : Npc::Npc(window, layer){

    SDLA::Rendering::SpriteGroup* menuGroup = new SDLA::Rendering::SpriteGroup();
    menuGroup->offset.x = 10;
    menuGroup->offset.y = 10 + 10 * 16;

    sprites.push_back(createBG9(window, layer, "assets/menubg.png", {16,16}, {7,11}, menuGroup));

    SDLA::Box gridSize = {2,4};
    SDLA::Rendering::SpriteGroup* grid = new SDLA::Rendering::SpriteGroup();
    grid->offset.x = 32;
    grid->offset.y = 10 + 11 * 16;
    int spacing = 8;
    int i = 0;
    std::vector<SDLA::Rendering::SpriteInfo*> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        SDLA::Rendering::SpriteInfo* image = new SDLA::Rendering::SpriteInfo();
        image->ownerGroup = std::shared_ptr<SDLA::Rendering::SpriteGroup>(grid);
        image->fileName = "assets/shield" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 16;
        image->area.box.height = 30;
        image->area.pos.x = 14;
        image->area.pos.y = 0;
        images.push_back(image);


        // if(Button::buttons[window].empty()) Button::buttons.insert({window,std::vector<std::shared_ptr<Button>>()});
        std::shared_ptr<Button> button = std::make_shared<Button>(image, window, layer);
        button->action = Actions::setShield;
        button->parameter = i;
        Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, layer, grid, images);
      sprites.push_back(imgG);
    }

  }

  Character::Character(std::string window, int layer) : Npc::Npc(window, layer){
    SDLA::Rendering::SpriteGroup* characterGroup = new SDLA::Rendering::SpriteGroup();
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
      std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> imgG = SDLA::Rendering::Sprite::addImageGroup(window, layer, characterGroup, character);
      sprites.push_back(imgG);
    }

    Actions::Pairings::character = sprites[0];
  }

  RandoChar::RandoChar(std::string window, int layer) : Npc::Npc(window, layer){
    refresh();
  }

  void RandoChar::update(){
    sprites[0][0]->ownerGroup->offset.x -= 1;
    if(sprites[0][0]->ownerGroup->offset.x < -64){
      refresh();
    }
  }

  void RandoChar::refresh(){
    SDLA::Rendering::SpriteGroup* characterGroup = new SDLA::Rendering::SpriteGroup();
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
    //   SDLA::Rendering::TextInfo* textInfo = new SDLA::Rendering::TextInfo();
    // textInfo->info = new SDLA::Rendering::SpriteInfo();
    // textInfo->info->offset = {0,400};
    // textInfo->textureText = std::to_string(sprites.size());
    // textInfo->fontName = "assets/Minecraft.ttf";
    // textInfo->size = 12;
    // textInfo->textColor = (SDL_Color) {255,255,255};
    // SDLA::Rendering::Text::loadText(myWindow, 1, textInfo, true);

    if(sprites.size() != 0){
      sprites[0][0]->ownerGroup->pendingErase = true;
    } else {

      sprites.push_back(std::vector<std::shared_ptr<SDLA::Rendering::Sprite>>());
    }
    sprites[0] = SDLA::Rendering::Sprite::addImageGroup(myWindow, layer, characterGroup, character);

  }

}