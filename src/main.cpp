#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#define MTR_ALL
#include "_MTR.h"
#include "gameobjects.h"
#include "game.h"


int main() {
  MTR_Init();

  std::string win = SDLA::render->newWindow(3, (SDLA::Box) {500,500});

  Game::HeadsMenu headsMENU = Game::HeadsMenu{win, 1};
    SDLA::Rendering::TextInfo* textInfo = new SDLA::Rendering::TextInfo();
    textInfo->info = new SDLA::Rendering::SpriteInfo();
    textInfo->info->offset = {0,400};
    textInfo->textureText = std::to_string(headsMENU.sprites[1].size());
    textInfo->fontName = "assets/Minecraft.ttf";
    textInfo->size = 12;
    textInfo->textColor = (SDL_Color) {255,255,255};
    SDLA::Rendering::Text::loadText(win, 1, textInfo, true);
    std::vector<std::shared_ptr<SDLA::Rendering::Sprite>> dgfsd = headsMENU.sprites[0];
    SDLA::Rendering::setGroupAsRotationCenter(headsMENU.sprites[1][0]->ownerGroup);

  Game::BodiesMenu{win, 1};
  Game::ShieldsMenu{win, 1};
  Game::Character{win, 1};
  Game::RandoChar zeCat = Game::RandoChar{win, 1};

  // int ms = SDL_GetTicks();
  // int i = 0;

  int close = 0;

  while(!close){

    close = Input::pollEvents(); // get/store window focus for events (so they happen on the right window)
    zeCat.update();

      // SDLA::Rendering::mutex.lock();
    // while(->writeBufferBusy){}
              // SDLA::Rendering::getDrawWindow(headsMENU.sprites[1][0]->myWindow)->mutex.lock();
              // for(std::shared_ptr<SDLA::Rendering::Sprite> s : headsMENU.sprites[1]){
                // headsMENU.sprites[1][0]->ownerGroup->angle += 1;
                // s->info->angle += 1;
                // SDL_Delay(16);
              // }
              // SDLA::Rendering::getDrawWindow(headsMENU.sprites[1][0]->myWindow)->mutex.unlock();
    // SDLA::Rendering::getCurrentWindow()->writeBufferBusy = false;

      // SDLA::Rendering::mutex.unlock();
    // headsMENU.sprites[1][0]->ownerGroup->info->angle+=1;

    if(Input::keyDown("VALIDATE")){
      if(Actions::Pairings::body == zeCat.bodyNumber &&
        Actions::Pairings::head == zeCat.headNumber &&
        Actions::Pairings::shield == zeCat.shieldNumber){
        Audio::play("assets/BasicMeow.wav");
        Game::Tally::pts += 10;
      } else {
        Audio::play("assets/BasicMeow.wav");

      }
      zeCat.refresh();
    }

    if(Input::Mouse::clicks[SDL_BUTTON_LEFT] == Input::KeyStates::DOWN){
      GameObjects::Button::searchClick();
    }
    
    SDL_Delay(16); 
  };


  return MTR_Close();
}