#include <memory>
#include "rendering.h"
#include "gameobjects.h"

namespace Menus{

  std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> createBG9(std::string window, int layer, SDLA::Box sizeInBlocks, SDLA::Rendering::SpriteInfo* bgInfo, SDLA::Rendering::Info* groupInfo){
    std::vector<std::shared_ptr<SDLA::Rendering::SpriteInfo>> menuBackground;
    SDLA::Box tileSize = (SDLA::Box) {bgInfo->area.box.width, bgInfo->area.box.height};

    for(int y = 0; y < sizeInBlocks.height; y++){
      for(int x = 0; x < sizeInBlocks.width; x++){
        std::shared_ptr<SDLA::Rendering::SpriteInfo> menuElement = std::make_shared<SDLA::Rendering::SpriteInfo>();
        menuElement->fileName = bgInfo->fileName;
        menuElement->area.box.width = tileSize.width;
        menuElement->area.box.height = tileSize.height;
        menuElement->offset.y = tileSize.height * y;

        if(y == 0){
          menuElement->area.pos.y = bgInfo->area.pos.y + 0;
        } else if (y == sizeInBlocks.height - 1){
          menuElement->area.pos.y = bgInfo->area.pos.y + tileSize.height * 2;
        } else {
          menuElement->area.pos.y = bgInfo->area.pos.y + tileSize.height;
        }

        menuElement->offset.x = tileSize.width * x;

        if(x == 0){
          menuElement->area.pos.x = bgInfo->area.pos.x + 0;
        } else if (x == sizeInBlocks.width - 1){
          menuElement->area.pos.x = bgInfo->area.pos.x + tileSize.width * 2;
        } else {
          menuElement->area.pos.x = bgInfo->area.pos.x + tileSize.width;
        }

        menuBackground.push_back(menuElement);
      }
    }

    return SDLA::Rendering::Sprite::addImageGroup(window, layer, groupInfo, menuBackground);
  }
}