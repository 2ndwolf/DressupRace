#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "rendering.h"
#include "primitives.h"
#include "input.h"
#include "gameobjects.h"
#include "npcs.h"
#include "preferences.h"

#include "audio.h"
#include "button.h"
#include "tally.h"

// std::map<SDLA::ID, std::vector<std::shared_ptr<SDLA::Button>>> buttons;

int main() {

  Preferences::parseIni("assets/uPref.ini");
  Input::initKeyBinds(Preferences::uPreferences::uPrefs.keys);
  Audio::init();

  SDL_Event event;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
    printf("error initializing SDL: %s\n", SDL_GetError()); 
    return 1;
  }

  if (TTF_Init() == -1){
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    return 1;
  }

  // SDLA::Rendering::loadSurface("assets/head440.png", true);
  // SDLA::Rendering::loadSurface("assets/head439.png", true);
  // SDLA::Rendering::loadSurface("assets/body0.png", true);
  // SDLA::Rendering::loadSurface("assets/hat0.png", true);
  // SDLA::Rendering::loadSurface("assets/gen_specialchest.png", true);

/*
  SDLA::Rendering::SpriteInfo* groupInfo = new SDLA::Rendering::SpriteInfo();
  groupInfo->angle = 32;
  groupInfo->pos.worldPos.x = 256;
  groupInfo->pos.worldPos.y = 256;

  // groupInfo->rotCenter = new (SDLA::Vec2) {16,20};
  SDLA::Rendering::SpriteInfo* headInfo = new SDLA::Rendering::SpriteInfo();
  headInfo->fileName = "assets/head440.png";
  headInfo->area.box.width = 32;
  headInfo->area.box.height = 32;
  headInfo->area.pos.x = 0;
  headInfo->area.pos.y = 64;
  headInfo->pos.offset.x = 0;
  headInfo->pos.offset.y = 0;
  SDLA::Rendering::SpriteInfo* bodyInfo = new SDLA::Rendering::SpriteInfo();
  bodyInfo->fileName = "assets/body0.png";
  bodyInfo->area.box.width = 32;
  bodyInfo->area.box.height = 32;
  bodyInfo->area.pos.x = 64;
  bodyInfo->area.pos.y = 0;
  bodyInfo->pos.offset.x = 0;
  bodyInfo->pos.offset.y = 16;


*/

  // std::vector<SDLA::Rendering::SpriteInfo*> bbb = {groupInfo, bodyInfo, headInfo};
  




  SDLA::Rendering rendering = SDLA::Rendering();
  std::string win = rendering.newWindow(3, (SDLA::Box) {500,500});

  // SDLA::Rendering::Sprite::addImage(win, 0, new SDLA::Rendering::SpriteInfo());
  SDLA::Rendering::Sprite::addImage(win, 2, new SDLA::Rendering::SpriteInfo(), true);
  SDLA::Rendering::SpriteInfo* sI = new SDLA::Rendering::SpriteInfo();
  sI->offset = {16, 16};
  SDLA::Rendering::Sprite::addImage(win, 0, sI, true);
  SDLA::Rendering::SpriteInfo* sI2 = new SDLA::Rendering::SpriteInfo();
  sI2->offset = {32, 32};
  SDLA::Rendering::Sprite::addImage(win, 2, sI2, true);

  Npcs::HeadsMenu{win};
  Npcs::BodiesMenu{win};
  Npcs::ShieldsMenu{win};
  Npcs::Character{win};
  Npcs::RandoChar zeCat = Npcs::RandoChar{win};

      // SDLA::Rendering::Renderable::setWorkingWindow(win);

      // SDL_SetRenderDrawColor(win->getContext(), 128, 0, 128, 255);

      // Menus::createBG9(win, 0, bMenuSize, bMenuBackground);
      // Menus::createBG9(win, 0, sMenuSize, sMenuBackground);




  // int ms = SDL_GetTicks();
  // int i = 0;

  int close = 0;

  while(!close){

    close = Input::pollEvents(); // get/store window focus for events (so they happen on the right window)
    zeCat.update();

    if(Input::keyDown("VALIDATE")){
      if(Actions::Pairings::body == zeCat.bodyNumber &&
        Actions::Pairings::head == zeCat.headNumber &&
        Actions::Pairings::shield == zeCat.shieldNumber){
        Audio::play("assets/BasicMeow.wav");
        Tally::Points::pts += 10;
      } else {

      }
      zeCat.refresh();
    }

    if(Input::Mouse::clicks[SDL_BUTTON_LEFT] == Input::KeyStates::DOWN){
    //         SDLA::Rendering::SpriteInfo* textInfo = new SDLA::Rendering::SpriteInfo();
    // textInfo->pos.worldPos = {0,400};
    // SDLA::Rendering::Text::loadText(SDLA::Rendering::Renderable::win,2,textInfo,std::to_string(SDLA::Button::buttons[currentWindow].size()),"assets/Minecraft.ttf",12, (SDL_Color) {255,255,255});
      for(std::shared_ptr<Button> b : Button::buttons[SDLA::Rendering::getCurrentWindow()]){
        if(Input::Mouse::mousePos.x > b->bounds.pos.x && Input::Mouse::mousePos.y > b->bounds.pos.y &&
           Input::Mouse::mousePos.x < b->bounds.pos.x + b->bounds.box.height && Input::Mouse::mousePos.y < b->bounds.pos.y + b->bounds.box.width){
           b->action(b->parameter);
        }
      }
    }

    if(event.type == SDL_QUIT)
      break;
    SDL_Delay(16); 
  };


  SDL_Quit();
  rendering.~Rendering();

  return 0;
}