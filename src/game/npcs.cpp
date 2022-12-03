#include <memory>
#include <cstdlib>
#include <string>

#include "primitives.h"
#include "identifier.h"
#include "information.h"
#include "AT.h"

#include "gameobjects.h"
#include "game.h"


namespace Game {

  GameObjects::bG9 createBG9(
    std::string window, int layer, Box sizeInTiles, std::string fileName, Box tileSize, std::shared_ptr<FK::AT::Information> group, Vec2 spriteOffset = {0,0}){
    
    // Box spriteSize = {tileSize.width/3, tileSize.height/3};

    // + spriteOffset + (tileSize*tilePos)

    // FK::Bounds area;
    // area.box =
    std::shared_ptr<FK::AT::SpriteInformation> menuInformation = std::make_shared<FK::AT::SpriteInformation>();
    menuInformation->fileName = fileName;
    menuInformation->area.box = tileSize;
    // Box hMenuSize = sizeInTiles;

    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> menuBackground;
    // SDLA::Box tileSize = (SDLA::Box) {bgInformation->area.box.width, bgInformation->area.box.height};

    for(int y = 0; y < sizeInTiles.height; y++){
      for(int x = 0; x < sizeInTiles.width; x++){
        std::shared_ptr<FK::AT::SpriteInformation> menuElement = std::make_shared<FK::AT::SpriteInformation>(menuInformation);
        menuElement->fileName = fileName;
        menuElement->area.box.width = tileSize.width;
        menuElement->area.box.height = tileSize.height;
        menuElement->offset.y = tileSize.height * y;

        if(y == 0){
          menuElement->area.pos.y = spriteOffset.y + 0;
        } else if (y == sizeInTiles.height - 1){
          menuElement->area.pos.y = spriteOffset.y + tileSize.height * 2;
        } else {
          menuElement->area.pos.y = spriteOffset.y + tileSize.height;
        }

        menuElement->offset.x = tileSize.width * x;

        if(x == 0){
          menuElement->area.pos.x = spriteOffset.x + 0;
        } else if (x == sizeInTiles.width - 1){
          menuElement->area.pos.x = spriteOffset.x + tileSize.width * 2;
        } else {
          menuElement->area.pos.x = spriteOffset.x + tileSize.width;
        }

        menuBackground.push_back(menuElement);
      }
    }
    GameObjects::bG9 bg9 = GameObjects::bG9();
    bg9.fullSize = {tileSize.width * sizeInTiles.width, tileSize.height * sizeInTiles.height};
    bg9.spriteGroup = FK::AT::addSpriteGroup(window, layer, group, menuBackground);
    return bg9;

    // return Menus::createBG9(window, layer, hMenuSize, menuBackground, group);
  }

  HeadsMenu::HeadsMenu(std::string window, int layer, Vec2 position) : Npc::Npc(window, layer){

    // group->offset = position;
    GameObjects::bG9 background = createBG9(window, layer, {30,9}, "assets/menubg.png", {16,16},  std::make_shared<FK::AT::Information>(position));
    spriteGroups.push_back(background.spriteGroup);


    Box gridSize = {11,3};
    int spacing = 8;

    std::shared_ptr<FK::AT::SpriteGroup> innerGroup = std::make_shared<FK::AT::SpriteGroup>(std::make_shared<FK::AT::Information>(Vec2{
      (background.fullSize.width -  (gridSize.width  * 32 + spacing * (gridSize.width  - 1))) / 2 + background.spriteGroup->offset.x,
      (background.fullSize.height - (gridSize.height * 32 + spacing * (gridSize.height - 1))) / 2 + background.spriteGroup->offset.y,
    }));

    // innerGroup->superGroup = background.spriteGroup->superGroup = std::make_shared<FK::AT::SuperGroup>();

    int i = 0;
    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        std::shared_ptr<FK::AT::SpriteInformation> image = std::make_shared<FK::AT::SpriteInformation>();
        image->ownerGroup = innerGroup;
        image->fileName = "assets/head" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 32;
        image->area.box.height = 32;
        image->area.pos.x = 0;
        image->area.pos.y = 64;
        images.push_back(image);


        // if(GameObjects::Button::buttons[window].empty()) GameObjects::Button::buttons.insert({window,std::vector<std::shared_ptr<GameObjects::Button>>()});
        std::shared_ptr<GameObjects::Button> button = std::make_shared<GameObjects::Button>(image, window, layer);
        button->action = Actions::setHead;
        button->parameter = i;
        GameObjects::Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::shared_ptr<FK::AT::SpriteGroup> imgG = FK::AT::addSpriteGroup(window, layer, innerGroup, images);
      spriteGroups.push_back(imgG);
    }
  }

  BodiesMenu::BodiesMenu(std::string window, int layer, Vec2 position) : Npc::Npc(window, layer){

    // group->offset = position;
    GameObjects::bG9 background = createBG9(window, layer, {7,11},"assets/menubg.png", {16,16},  std::make_shared<FK::AT::Information>(position));
    spriteGroups.push_back(background.spriteGroup);

    Box gridSize = {2,4};
    int spacing = 8;

    std::shared_ptr<FK::AT::SpriteGroup> innerGroup = std::make_shared<FK::AT::SpriteGroup>(std::make_shared<FK::AT::Information>(Vec2{
      (background.fullSize.width -  (gridSize.width  * 32 + spacing * (gridSize.width  - 1))) / 2 + background.spriteGroup->offset.x,
      (background.fullSize.height - (gridSize.height * 32 + spacing * (gridSize.height - 1))) / 2 + background.spriteGroup->offset.y,
    }));

    int i = 0;
    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        std::shared_ptr<FK::AT::SpriteInformation> image = std::make_shared<FK::AT::SpriteInformation>();
        image->ownerGroup = innerGroup;
        image->fileName = "assets/body" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 32;
        image->area.box.height = 32;
        image->area.pos.x = 64;
        image->area.pos.y = 0;
        images.push_back(image);


        // if(GameObjects::Button::buttons[window].empty()) GameObjects::Button::buttons.insert({window,std::vector<std::shared_ptr<GameObjects::Button>>()});
        std::shared_ptr<GameObjects::Button> button = std::make_shared<GameObjects::Button>(image, window, layer);
        button->action = Actions::setBody;
        button->parameter = i;
        GameObjects::Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::shared_ptr<FK::AT::SpriteGroup> imgG = FK::AT::addSpriteGroup(window, layer, innerGroup, images);
      spriteGroups.push_back(imgG);
    }
  }

  ShieldsMenu::ShieldsMenu(std::string window, int layer, Vec2 position) : Npc::Npc(window, layer){

    GameObjects::bG9 background = createBG9(window, layer, {7,11},"assets/menubg.png", {16,16},  std::make_shared<FK::AT::Information>(position));
    spriteGroups.push_back(background.spriteGroup);

    Box gridSize = {2,4};
    int spacing = 8;

    std::shared_ptr<FK::AT::SpriteGroup> innerGroup = std::make_shared<FK::AT::SpriteGroup>(std::make_shared<FK::AT::Information>(Vec2{
      (background.fullSize.width -  (gridSize.width  * 32 + spacing * (gridSize.width  - 1))) / 2 + background.spriteGroup->offset.x,
      (background.fullSize.height - (gridSize.height * 32 + spacing * (gridSize.height - 1))) / 2 + background.spriteGroup->offset.y,
    }));

    int i = 0;
    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> images;
    for(int y = 0; y < gridSize.height; y++){
      for(int x = 0; x < gridSize.width; x++){
        std::shared_ptr<FK::AT::SpriteInformation> image = std::make_shared<FK::AT::SpriteInformation>();
        image->ownerGroup = innerGroup;
        image->fileName = "assets/shield" + std::to_string(i) + ".png";
        image->offset = {x * (32 + spacing), y * (32 + spacing)};
        image->area.box.width = 16;
        image->area.box.height = 30;
        image->area.pos.x = 14;
        image->area.pos.y = 0;
        images.push_back(image);


        // if(GameObjects::Button::buttons[window].empty()) GameObjects::Button::buttons.insert({window,std::vector<std::shared_ptr<GameObjects::Button>>()});
        std::shared_ptr<GameObjects::Button> button = std::make_shared<GameObjects::Button>(image, window, layer);
        button->action = Actions::setShield;
        button->parameter = i;
        GameObjects::Button::buttons[window][layer].push_back(button);

        i++;
      }
    }

    {
      std::shared_ptr<FK::AT::SpriteGroup> imgG = FK::AT::addSpriteGroup(window, layer, innerGroup, images);
      spriteGroups.push_back(imgG);
    }
    
  }

  Character::Character(std::string window, int layer, Vec2 position) : Npc::Npc(window, layer){

    // group->offset = position;

    std::shared_ptr<FK::AT::SpriteInformation> head = std::make_shared<FK::AT::SpriteInformation>();
    std::shared_ptr<FK::AT::SpriteInformation> body = std::make_shared<FK::AT::SpriteInformation>();
    std::shared_ptr<FK::AT::SpriteInformation> shield = std::make_shared<FK::AT::SpriteInformation>();

    head->fileName = "assets/head0.png";
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

    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> character = {body, head, shield};

    {
      std::shared_ptr<FK::AT::SpriteGroup> imgG = FK::AT::addSpriteGroup(window, layer, std::make_shared<FK::AT::SpriteGroup>(std::make_shared<FK::AT::Information>(position)), character);
      spriteGroups.push_back(imgG);
    }

    Actions::Pairings::character = spriteGroups[0];
  }

  RandoChar::RandoChar(std::string window, int layer, Vec2 position) : Npc::Npc(window, layer){

    // FK::AT::SpriteGroup* characterGroup = new FK::AT::SpriteGroup();
    // group->offset = position;
    initX = position.x;

    headNumber = rand() % 33;
    bodyNumber = rand() % 8;
    shieldNumber = rand() % 8;

    std::shared_ptr<FK::AT::SpriteInformation> headInformation   = std::make_shared<FK::AT::SpriteInformation>();
    std::shared_ptr<FK::AT::SpriteInformation> bodyInformation   = std::make_shared<FK::AT::SpriteInformation>();
    std::shared_ptr<FK::AT::SpriteInformation> shieldInformation = std::make_shared<FK::AT::SpriteInformation>();

    headInformation->fileName = "assets/head" + std::to_string(headNumber) + ".png";
    headInformation->offset = {0, 0};
    headInformation->area.box.width = 32;
    headInformation->area.box.height = 32;
    headInformation->area.pos.x = 0;
    headInformation->area.pos.y = 64;

    bodyInformation->fileName = "assets/body" + std::to_string(bodyNumber) + ".png";
    bodyInformation->offset = {0, 16};
    bodyInformation->area.box.width = 32;
    bodyInformation->area.box.height = 32;
    bodyInformation->area.pos.x = 64;
    bodyInformation->area.pos.y = 0;

    shieldInformation->fileName = "assets/shield" + std::to_string(shieldNumber) + ".png";
    shieldInformation->offset = {-3, 20};
    shieldInformation->area.box.width = 16;
    shieldInformation->area.box.height = 20;
    shieldInformation->area.pos.x = 14;
    shieldInformation->area.pos.y = 0;

    std::vector<std::shared_ptr<FK::AT::SpriteInformation>> character = {bodyInformation, headInformation, shieldInformation};

    spriteGroups.push_back(FK::AT::addSpriteGroup(myWindow, layer, std::make_shared<FK::AT::Information>(position), character));
    // spriteGroups[0] = ;
    body = spriteGroups[0]->sprites[0];
    head = spriteGroups[0]->sprites[1];
    shield = spriteGroups[0]->sprites[2];
  }

  void RandoChar::update(){
    spriteGroups[0]->offset.x -= 1;
    if(spriteGroups[0]->offset.x < -64){
      refresh();
    }
  }

  void RandoChar::refresh(){
    // FK::AT::SpriteGroup* characterGroup = new FK::AT::SpriteGroup();
    // characterGroup->offset = ;

    spriteGroups[0]->offset.x = initX;

    headNumber = rand() % 33;
    bodyNumber = rand() % 8;
    shieldNumber = rand() % 8;

    head->changeSurface("assets/head" + std::to_string(headNumber) + ".png");
    body->changeSurface("assets/body" + std::to_string(bodyNumber) + ".png");
    shield->changeSurface("assets/shield" + std::to_string(shieldNumber) + ".png");
  }

}