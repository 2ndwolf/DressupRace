#define RESOLUTION 64
#define SCRWIDTH   512
#define SCRHEIGHT  512

int pathing = 1;

#include <array>
#include <limits.h>
#include <cstdlib>
#include <cstdint>
#include <cmath>

std::array<bool, (RESOLUTION * RESOLUTION) << 1> past;
std::array<bool, (RESOLUTION * RESOLUTION) << 1> future;
std::array<bool, (RESOLUTION * RESOLUTION) << 1> collisions;
std::array<bool, (RESOLUTION * RESOLUTION) << 1> read;
std::array<bool, (RESOLUTION * RESOLUTION) << 1> noMove;
std::array<bool, (RESOLUTION * RESOLUTION) << 1> emptyArr; // array with a border of true
std::array<FunnySquare, 50> funnySquares;

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
  Vec2 pos; // coordinates in the table
  Box box;
  int direction;
  std::array<bool,2> doneAXIS;
  bool done;

  std::array<bool, (RESOLUTION * RESOLUTION) << 1> doFuture(){
    for(int i = 0; i < funnySquares.size(); i++){
      for(int x = 0; x < box.width; x+=pathing){
        if(future[pos.x >> 2 * x] == true) collisions[pos.x >> 2 * x];
        future[pos.x >> 2 * x] = true;
      }
      for(int y = 0; y < box.width; y+=pathing){
        if(future[pos.y >> 2 * y] == true) collisions[pos.y >> 2 * y];
        future[pos.y >> 2 * y] = true;
      }
    }
  }

  void checkCollisions(int maxLoops){
  int loops = 0;
  bool allDone = false;
  Vec2 futurePos;
  // Vec2 compPos;
  doFuture();
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
            doneAXIS[0] = collisions[(pos.x + j) >> 2] == false;
            if(!doneAXIS[0]) break;
            // else future[pos.x >> 2 * j] = true;
          }
        } else {
          futurePos.x = pos.x << 2;
          for(int j = 0; j < box.width; j+=pathing){
            doneAXIS[0] = collisions[(pos.x + j) << 2] == false;
            if(!doneAXIS[0]) break;
          }
        }
        if(direction == 1 /* Directions::UPLEFT */ || direction == 2 /* Directions::UPRIGHT */) {
          futurePos.y = pos.y >> 2;
          for(int j = 0; j < box.height; j+=pathing){
            doneAXIS[1] = collisions[(pos.y + j) >> 2] == false;
            if(!doneAXIS[1]) break;
          }
          // collisions[pos.y >> 2] = true;
        } else {
          futurePos.y = pos.y << 2;
          for(int j = 0; j < box.height; j+=pathing)
            doneAXIS[1] = collisions[(pos.y + j) << 2] == false;
            if(!doneAXIS[1]) break;
          }
        }
        if(doneAXIS[0] && doneAXIS[1]){
          if(direction == 0 || direction == 3){
            for(int j = 0; j < box.width; j++){
              future[futurePos.x + j] = true;
            }
          } else {
            for(int j = futurePos.x; j < futurePos.x + box.width; j++){
              
            }
          }
          if(direction == 1 || direction == 2){
            for(int j = futurePos.y; j < futurePos.y + box.width; j++){
              
            }
          } else {
            for(int j = futurePos.y; j < futurePos.y + box.width; j++){
              
            }
          }
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
      loops++;
    }
    read = future;
  }
};


bool isOdd(int num){
  return num & true;
}


int add(int x, int y){
  int keep = x & y << 1;
  int res = x ^ y;
    while(keep){
      x = keep;
      keep = keep & res << 1;
      res = x ^ res;
    }
  return res;
}

bool overflows(int x){
  return x & INT_MIN;
}

bool contigousOverflow(int x){
  return x & true && x & INT_MIN;
}

// SIZE = box.contigousWidth/height
bool contigousUnderflow(uintmax_t x, int size){
  return x & size < size;
}

// std::array<int, sizeof(int)> square;
// x + width << 1 & INT_MAX


int Xpos;
int Ypos;


int fillContigous(int size){
  int num = 1;
  int i = 0;
  for(;size;){
    num = num | 1 << i;
    i++;
  }
  return num;
}

int fillContigousBackwards(int size){
  int num = 1;
  int i = 0;
  for(;size;){
    num = num | INT_MIN >> i;
    i++;
  }
  return num;
}

struct BOB{
  int width, height;
  uintmax_t contigousWidth, contigousHeight;
  uintmax_t contigousWidthMINUS, contigousHeightMINUS;
  bool movRight;
  bool movDown;
};

bool emplaceCountigous(uintmax_t contigous, int size){
  int temp = contigous << ((rand() % sizeof(int)) - size);;;;;;
  return false;
}

BOB createBox(int width, int height){
  BOB box;
  box.contigousWidth = fillContigous(width);
  box.contigousHeight = fillContigous(height);
  box.contigousWidthMINUS = fillContigousBackwards(width);
  box.contigousHeightMINUS = fillContigousBackwards(height);

  box.width = width;
  box.height = height;
  if(rand() & true) rightMovingBoxes[rand() % rightMovingBoxes.size()] |= emplaceCountigous(box.contigousWidth, width);
  else              leftMovingBoxes [rand() % leftMovingBoxes.size()]  |= emplaceCountigous(box.contigousWidth, width);
  if(rand() & true) upMovingBoxes   [rand() % upMovingBoxes.size()]    |= emplaceCountigous(box.contigousHeight, height);
  else              downMovingBoxes [rand() % downMovingBoxes.size()]  |= emplaceCountigous(box.contigousHeight, height);

  // box.boxInX = ;
  // box.boxInY = emplaceCountigous(box.contigousHeight, height);
  return box;
}

// void noice(){
  BOB box = createBox(16,16);
// }
// 

// #define 
#define MAXRES sizeof(uintmax_t)
#define RESOLUTION MAXRES

#define XARRSIZE (SCRWIDTH / sizeof(uintmax_t)) * (RESOLUTION / sizeof(uintmax_t)) + 1
#define LASTINDEXXMAX SCRWIDTH - (XARRSIZE - 1 * sizeof(uintmax_t))
#define YARRSIZE (SCRHEIGHT / sizeof(uintmax_t)) * (RESOLUTION / sizeof(uintmax_t)) + 1
#define LASTINDEXYMAX SCRHEIGHY - (YARRSIZE - 1 * sizeof(uintmax_t))

std::array<uintmax_t, XARRSIZE> rightMovingBoxes;
std::array<uintmax_t, XARRSIZE> leftMovingBoxes;
// std::array<uintmax_t, XARRSIZE> testxBoxes;
// std::array<uintmax_t, XARRSIZE> testyBoxes;
std::array<uintmax_t, XARRSIZE> finalxBoxes;
std::array<uintmax_t, XARRSIZE> finalyBoxes;
std::array<uintmax_t, YARRSIZE> upMovingBoxes;
std::array<uintmax_t, YARRSIZE> downMovingBoxes;

// std::array<uintmax_t, XARRSIZE> xcollisions;
// std::array<uintmax_t, YARRSIZE> ycollisions;

// void changeToLeftDirection(int i, uintmax_t row){
//   //Move colliding left going boxes to right
//   leftMovingBoxes[i]  |= row;
//   // Erase colliding boxes from right moving boxes
//   rightMovingBoxes[i] = ~row & rightMovingBoxes[i];
// }
// void changeToRightDirection(int i, uintmax_t row){
//   rightMovingBoxes[i]  |= row;
//   leftMovingBoxes[i] = ~row & leftMovingBoxes[i];
// }
// void changeToUpDirection(int i, uintmax_t row){
//   upMovingBoxes[i]  |= row;
//   downMovingBoxes[i] = ~row & downMovingBoxes[i];
// }
// void changeToDownDirection(int i, uintmax_t row){
//   downMovingBoxes[i]  |= row;
//   upMovingBoxes[i] = ~row & upMovingBoxes[i];
// }

std::array<uintmax_t, XARRSIZE> addDirection(int i, uintmax_t collisionMap, uintmax_t contigousMin, uintmax_t contigousMax, std::array<uintmax_t, XARRSIZE> newArray, int size){
  for(int j = 0; j < sizeof(uintmax_t); j++){
    if(collisionMap >> j & true){
      uintmax_t newBox = contigousMin << j;
      if(contigousOverflow(newBox)){
        newArray[i]      |= (newBox  & contigousMax);
        newArray[i+1]    |= (~newBox | contigousMin);
      } else newArray[i] |= newBox;
      j+=size;
    } 
  }
  return newArray;
}


std::array<uintmax_t, XARRSIZE> moveAdd(int speed, std::array<uintmax_t, XARRSIZE> rightMovingBoxes, std::array<uintmax_t, XARRSIZE>* collisions, uintmax_t contigousMin, uintmax_t contigousMax){
  // int speed; // Must be even unless MAXRES
  std::array<uintmax_t, XARRSIZE> testBoxes;
  std::array<uintmax_t, XARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < rightMovingBoxes.size(); i++){
    testBoxes[i] |= rightMovingBoxes[i] << (speed / (sizeof(uintmax_t) / RESOLUTION));

  if(contigousOverflow(testBoxes[i])){
      if(i + 1 < rightMovingBoxes.size()){
        // Pass overflow to next index
        testBoxes[i+1] |= ~testBoxes[i] & contigousMin;
        if(testBoxes[i+1] > LASTINDEXXMAX) {
          // Ensure collision
          collisionBoxes[i+1] |= ((contigousMax | contigousMin) & testBoxes[i+1]);
        }
      } else {
        collisionBoxes[i] |= ((contigousMax | contigousMin) & testBoxes[i]);
      }
    }

  }

  collisions = &collisionBoxes;
  return testBoxes;
}

std::array<uintmax_t, XARRSIZE> moveRemove(int speed, std::array<uintmax_t, XARRSIZE> leftMovingBoxes, std::array<uintmax_t, XARRSIZE>* collisions, uintmax_t contigousMin){
  // int speed; // Must be even unless MAXRES
  std::array<uintmax_t, XARRSIZE> testBoxes;
  std::array<uintmax_t, XARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < leftMovingBoxes.size(); i++){
    testBoxes[i] |= leftMovingBoxes[i] >> (speed / (sizeof(uintmax_t) / RESOLUTION));

  if(contigousUnderflow(testBoxes[i], contigousMin)){
      if(i - 1 > 0){
        // Pass underflow to previous index
        testBoxes[i-1] |= ~(contigousMin & testBoxes[i]);
      } else {
        collisionBoxes[i] |= contigousMin;
      }
    }

  }

  collisions = &collisionBoxes;
  return testBoxes;
}

void cycle(){
  std::array<uintmax_t, XARRSIZE> xcollisions;
  std::array<uintmax_t, YARRSIZE> ycollisions;
  std::array<uintmax_t, XARRSIZE> futurexBoxes;
  std::array<uintmax_t, YARRSIZE> futureyBoxes;

  rightMovingBoxes = moveAdd    (2, rightMovingBoxes, &xcollisions, box.contigousWidth,  box.contigousWidthMINUS);
  leftMovingBoxes  = moveRemove (2, leftMovingBoxes,  &xcollisions, box.contigousWidth);
  downMovingBoxes  = moveAdd    (2, downMovingBoxes,  &ycollisions, box.contigousHeight, box.contigousHeightMINUS);
  upMovingBoxes    = moveRemove (2, upMovingBoxes,    &ycollisions, box.contigousHeight);

  uintmax_t hasXCollisions = 0;
  uintmax_t hasYCollisions = 0;
  for(int i = 0; i < XARRSIZE; i++){
    // testxBoxes[i]  |= rightMovingBoxes[i] | leftMovingBoxes[i];
    xcollisions[i]  &= rightMovingBoxes[i] & leftMovingBoxes[i];
    futurexBoxes[i] |= rightMovingBoxes[i] | leftMovingBoxes[i];
    hasXCollisions  |= xcollisions[i];
    addDirection   (i, xcollisions[i] & rightMovingBoxes[i], box.contigousWidth, box.contigousWidthMINUS, leftMovingBoxes, size);
    removeDirection(i, xcollisions[i], box.contigousWidth);
  }
  for(int i = 0; i < YARRSIZE; i++){
    // testyBoxes[i]  |= upMovingBoxes[i] | downMovingBoxes[i];
    ycollisions[i] &= upMovingBoxes[i] & downMovingBoxes[i];

    hasYCollisions |= ycollisions[i];
    changeToUpDirection  (i, ycollisions[i] & upMovingBoxes[i]  );
    changeToDownDirection(i, ycollisions[i] & downMovingBoxes[i]);
  }
  if(hasXCollisions | hasYCollisions) cycle();
  else {
    
    finalxBoxes = testxBoxes;
    finalyBoxes = testyBoxes;
  }
}