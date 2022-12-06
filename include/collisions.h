#define RESOLUTION 64

int pathing = 1;

#include <array>

std::array<bool, RESOLUTION * RESOLUTION> past;
std::array<bool, RESOLUTION * RESOLUTION> future;
std::array<bool, RESOLUTION * RESOLUTION> read;
std::array<bool, RESOLUTION * RESOLUTION> noMove;
std::array<bool, RESOLUTION * RESOLUTION> emptyArr; // array with a border of true
// std::array<bool, RESOLUTION * RESOLUTION> upLeft;
// std::array<bool, RESOLUTION * RESOLUTION> downLeft;
// std::array<bool, RESOLUTION * RESOLUTION> downRight;
// std::array<bool, RESOLUTION * RESOLUTION> upRight;

// Write 50 blocks to past
struct Vec2{
  int x = 0,y = 0;
};
struct Box{
  int width = RESOLUTION / 32, height = RESOLUTION / 32;
};

enum Directions{
  UPLEFT,
  UPRIGHT,
  DOWNRIGHT,
  DOWNLEFT,
  LENGTH
};

class FunnySquare{
  Vec2 pos;
  Box box;
  int direction;
  std::array<bool,2> doneAXIS;
  bool done;

  void checkCollisions(int maxLoops){
  int loops = 0;
  bool allDone = false;
  Vec2 futurePos;
  Vec2 compPos;
  future = emptyArr;
  while(!allDone && loops <= maxLoops){
    allDone = true;
    // noMove = emptyArr;
    for(int i = 0; i < funnySquares.size(); i++){
      if(!done){
        doneAXIS[0] = doneAXIS[1] = false;
        if(direction == 0 /* Directions::UPLEFT */ || direction == 3 /* Directions::DOWNLEFT */) {
          futurePos.x = pos.x >> 2;
          for(int j = 0; j < box.width; j+=pathing){
            compPos.x = pos.x >> 2 * j;
            // future[futurePos.x] = true;
            // doneAXIS[0] = true;
            // doneAXIS[0] =  doneAXIS[0] &! /* blocked ->*/(past[futurePos.x] &! (past[futurePos.x] ^ true));
            if(!doneAXIS[0]) break;
          }
        } else {
          futurePos.x = pos.x << 2;
          for(int j = 0; j < box.width; j+=pathing){
            compPos.x = pos.x << 2 * j;
            // future[futurePos.x] = true;
            doneAXIS[0] = future[futurePos.x] == false;
            // doneAXIS[0] = true;
            // doneAXIS[0] =  doneAXIS[0] &! /* blocked ->*/(past[futurePos.x] &! (past[futurePos.x] ^ true));
            if(!doneAXIS[0]) break;
          }
        }
        if(direction == 1 /* Directions::UPLEFT */ || direction == 2 /* Directions::UPRIGHT */) {
          futurePos.y = pos.y >> 2;
          for(int j = 0; j < box.height; j+=pathing){
            compPos.y = pos.y >> 2 * j;
            // future[futurePos.y] = true;
            doneAXIS[1] = future[futurePos.y] == false;

            // doneAXIS[0] = true;
            // doneAXIS[0] =  doneAXIS[0] &! /* blocked ->*/(past[futurePos.y] &! (past[futurePos.y] ^ true));
            if(!doneAXIS[1]) break;
          }
          // future[pos.y >> 2] = true;
        } else {
          futurePos.y = pos.y << 2;
          for(int j = 0; j < box.height; j+=pathing)
            // compPos.y = pos.y << 2 * j;
            // future[futurePos.y] = true;
            doneAXIS[1] = future[pos.y << 2 * j] == false;
            // doneAXIS[0] = true;
            // doneAXIS[0] =  doneAXIS[0] &! /* blocked ->*/(past[futurePos.y] &! (past[futurePos.y] ^ true));
            if(!doneAXIS[1]) break;
          }
        }
        if(doneAXIS[0] && doneAXIS[1]){
          pos.x = futurePos.x;
          pos.y = futurePos.y;
          future[pos.x] = true;
          future[pos.y] = true;
          done = true;
        } else {
          // noMove[pos.x] = true;
          // noMove[pos.y] = true;
          direction = (direction + 1) % 4;
          allDone = false;
        }

      }
      past = future;
      loops++;
    }
    // past = emptyArr;
    // for(int i = 0; i < funnySquares.size(); i++){
    //   for(int i = 0; i < box.width; i++)  past[pos.x << 2 * i] = true;
    //   for(int i = 0; i < box.height; i++) past[pos.y << 2 * i] = true;
    // }
    read = future;
  }


  }
};

std::array<FunnySquare, 50> funnySquares;

