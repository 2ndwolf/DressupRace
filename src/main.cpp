#include <iostream>

// #define SDL_MAIN_HANDLED
#include <SDL_main.h>
#include <SDL.h>

#define MTR_ALL
#include "_MTR.h"
#include "gameobjects.h"
#include "game.h"


int WinMain(int argc, char *argv[]) {
  if(MTR_Init()!=0)return 1;

  std::string win = SDLA::Rendering::newWindow(3, (SDLA::Box) {500,500});


  Game::HeadsMenu headsMENU = Game::HeadsMenu{win, 1, {10, 10}};
  
  Game::BodiesMenu{win, 1, {500 - (10+7*16), 10 + 10 * 16}};
  Game::ShieldsMenu{win, 1, {10, 10 + 10 * 16}};

  Game::Character{win, 1, {250,250}};
  Game::RandoChar zeCat = Game::RandoChar{win, 1, {550,400}};

  std::string win2 = SDLA::Rendering::newWindow(3, (SDLA::Box) {500,500}, "CATSROCK");
  Game::HeadsMenu bab = Game::HeadsMenu{win2, 1, {0,0}};
  Game::BodiesMenu{win2, 1, {0,0}};
  Game::ShieldsMenu{win2, 1, {0,0}};
  Game::Character{win2, 1, {0,0}};
  Game::RandoChar zeCat2 = Game::RandoChar{win2, 1, {0,0}};

  // int ms = SDL_GetTicks();
  // int i = 0;

  int close = 0;

  while(!close){

    close = Input::pollEvents(); // get/store window focus for events (so they happen on the right window)
    zeCat.update();
    zeCat2.update();


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
        // Audio::play("assets/BasicMeow.wav");

      }
      zeCat.refresh();
      zeCat2.refresh();
    }

    if(Input::Mouse::clicks[SDL_BUTTON_LEFT] == Input::KeyStates::DOWN){
      GameObjects::Button::searchClick();
    }
    
    SDL_Delay(16); 
  };


  return MTR_Close();
}