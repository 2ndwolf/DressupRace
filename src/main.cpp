#include <iostream>
#include <cmath>
#define SDL_MAIN_HANDLED
#include <SDL_main.h>
#include <SDL.h>

#define TSR_ALL
#include "_TSR.h"
#include "gameobjects.h"
#include "game.h"
#include "information.h"

// #include "window.h"
// #include "TSRPrimitives.h"
// #include "input.h"
// #include "audio.h"
// #include "AT.h"
Vec2 rotatePoint(Vec2 rotCenter, float angle, Vec2 point){
  float s = std::sin((angle/180)*3.14);
  float c = std::cos((angle/180)*3.14);

  point = point - rotCenter;

  int xnew = point.x * c - point.y * s;
  int ynew = point.x * s + point.y * c;

  point.x = xnew + rotCenter.x;
  point.y = ynew + rotCenter.y;

  return point;
}

int main(int argc, char *argv[]) { 
  if(FK_Init()!=0) return 1;

  FK::ORE::Renderable::loadSurface("assets/gen_specialchest.png");


  std::string win = FK::Window::newWindow(3, (Box) {500,500}, "Abstraction", true);

  // FK::AT::addSprite(win, 1, std::make_shared<FK::AT::SpriteInformation>(std::make_shared<FK::AT::Information>(win)), true);
  // Game::HeadsMenu headsMENU = Game::HeadsMenu{win, 1, {10, 179}};
  
  // Game::BodiesMenu{win, 1, {500 - (10+7*16), 10 + 10 * 16}};
  // Game::ShieldsMenu{win, 1, {10, 10 + 10 * 16}};

      // Game::Character zeMe = Game::Character{win, 1, {250,450}};
  // Game::RandoChar zeCat = Game::RandoChar{win, 1, {550,400}};

  // std::string win2 = FK::Window::newWindow(3, (Box) {500,500}, "CATSROCK");
  // Game::HeadsMenu bab = Game::HeadsMenu{win2, 1, {0,0}};
  // Game::BodiesMenu{win2, 1, {0,0}};
  // Game::ShieldsMenu{win2, 1, {0,0}};
  // Game::Character{win2, 1, {0,0}};
  // Game::RandoChar zeCat2 = Game::RandoChar{win2, 1, {0,0}};

  // int ms = SDL_GetTicks();
  // int i = 0;

  int close = 0;
  int angle = 0;
  int angle2 = 0;

  // Vec2 origin = zeMe.spriteGroups[0]->bounds.pos;


  // FK::AT::setGroupAsRotationCenter(zeMe.spriteGroups[0]);

  while(!close){

    close = FK::ORE::pollEvents(); // get/store window focus for events (so they happen on the right window)
    // zeCat.update();
    // zeCat2.update() ;


      // SDLA::Rendering::mutex.lock();
    // while(->writeBufferBusy){}
              // SDLA::Rendering::getDrawWindow(headsMENU.sprites[1][0]->myWindow)->mutex.lock();
              // for(std::shared_ptr<SDLA::Rendering::Sprite> s : headsMENU.sprites[1]){
    // angle+=1;
    // angle2-=1;
    // zeMe.spriteGroups[0]->bounds.pos = rotatePoint({250,250}, angle, origin);
    // zeMe.spriteGroups[0]->angle = angle2;

                // s->information->angle += 1;
                // SDL_Delay(16);
              // }
              // SDLA::Rendering::getDrawWindow(headsMENU.sprites[1][0]->myWindow)->mutex.unlock();
    // SDLA::Rendering::getCurrentWindow()->writeBufferBusy = false;

      // SDLA::Rendering::mutex.unlock();
    // headsMENU.sprites[1][0]->ownerGroup->information->angle+=1;

    if(FK::AT::keyDown("VALIDATE")){
    //   if(Actions::Pairings::body == zeCat.bodyNumber &&
    //     Actions::Pairings::head == zeCat.headNumber &&
    //     Actions::Pairings::shield == zeCat.shieldNumber){
    //     FK::AT::play("assets/BasicMeow.wav");
    //     Game::Tally::pts += 10;
    //   } else {
  return FK_Close();
        

      }
    //   zeCat.refresh();
      // zeCat2.refresh();
    // }

    // if(FK::Mouse::clicks[SDL_BUTTON_LEFT] == FK::ENUM::KeyStates::DOWN){
    //   GameObjects::Button::searchClick();
    // }
    
    SDL_Delay(1000); 
        // FK::AT::play("assets/BasicMeow.wav");
  }; 

  return close;

}

