#define RESOLUTION 64
#define SCRWIDTH   512
#define SCRHEIGHT  512

#define MAXRES sizeof(uintmax_t)
#define RESOLUTION MAXRES

#define XARRSIZE      (SCRWIDTH  / sizeof(uintmax_t)) * (RESOLUTION / sizeof(uintmax_t)) + 1
#define YARRSIZE      (SCRHEIGHT / sizeof(uintmax_t)) * (RESOLUTION / sizeof(uintmax_t)) + 1
#define LASTINDEXXMAX  SCRWIDTH  - (XARRSIZE - 1 * sizeof(uintmax_t))
#define LASTINDEXYMAX  SCRHEIGHT - (YARRSIZE - 1 * sizeof(uintmax_t))

#include <array>
#include <limits.h>
#include <cstdlib>
#include <cstdint>
#include <cmath>

std::array<uintmax_t, XARRSIZE> rightMovingBoxes;
std::array<uintmax_t, XARRSIZE> leftMovingBoxes;

std::array<uintmax_t, YARRSIZE> upMovingBoxes;
std::array<uintmax_t, YARRSIZE> downMovingBoxes;

std::array<uintmax_t, XARRSIZE> oldRightMovingBoxes;
std::array<uintmax_t, XARRSIZE> oldLeftMovingBoxes;

std::array<uintmax_t, YARRSIZE> oldUpMovingBoxes;
std::array<uintmax_t, YARRSIZE> oldDownMovingBoxes;

std::array<uintmax_t, XARRSIZE> newRightMovingBoxes;
std::array<uintmax_t, XARRSIZE> newLeftMovingBoxes;

std::array<uintmax_t, YARRSIZE> newUpMovingBoxes;
std::array<uintmax_t, YARRSIZE> newDownMovingBoxes;

std::array<uintmax_t, XARRSIZE> finalxBoxes;
std::array<uintmax_t, YARRSIZE> finalyBoxes;

bool contigousOverflow(int x){
  return x & true && x & INT_MIN;
}

// SIZE = box.contigousWidth/height
bool contigousUnderflow(uintmax_t x, int size){
  return x & size < size;
}

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

// struct BOB{
//   int width, height;
//   uintmax_t contigousWidth, contigousHeight;
//   uintmax_t contigousWidthMINUS, contigousHeightMINUS;
//   bool movRight;
//   bool movDown;
// };

bool emplaceCountigous(
  std::array<uintmax_t, XARRSIZE>* xArr,     std::array<uintmax_t, YARRSIZE>* yArr,
  std::array<uintmax_t, XARRSIZE> xArrOther, std::array<uintmax_t, YARRSIZE> yArrOther
  ){
  int index;
  uintmax_t newBoxX;
  uintmax_t newBoxY;
  std::array<uintmax_t, XARRSIZE> xtmpArr = *xArr;
  std::array<uintmax_t, YARRSIZE> ytmpArr = *yArr;

  index   = rand() % SCRWIDTH  - width;;
  newBoxX = contigousWidthMin  << index;

  index   = rand() % SCRHEIGHT - height;
  newBoxY = contigousHeightMin << index;

  if(!(~newBoxX & (xtmpArr[index] | xArrOther[index])) &&
     !(~newBoxY & (ytmpArr[index] | yArrOther[index]))) {
      xtmpArr[index] |= newBoxX;
      ytmpArr[index] |= newBoxY;

      xArr = &xtmpArr;
      yArr = &ytmpArr;
      return true;
  }

  return false;
}


void fillScreen(int width, int height, int boxCount, int maxMiss){
  std::array<uintmax_t, XARRSIZE> xTemp;
  std::array<uintmax_t, YARRSIZE> yTemp;
  // int misses = 0;

  int i = 0;
  int index;
  uintmax_t newBoxX;
  uintmax_t newBoxY;

  while(i < boxCount && maxMiss > 0){
    int direction = rand() % 4;
    switch(direction){
      case 0:  // up right  direction
        if(!emplaceCountigous(&rightMovingBoxes, &upMovingBoxes,   leftMovingBoxes,  downMovingBoxes)) maxMiss--;

      break;
      case 1:  //down left direction
        if(!emplaceCountigous(&leftMovingBoxes,  &downMovingBoxes, rightMovingBoxes, upMovingBoxes))   maxMiss--;

      break;
      case 2:  //down right direction
        if(!emplaceCountigous(&rightMovingBoxes, &downMovingBoxes, leftMovingBoxes,  upMovingBoxes))   maxMiss--;

      break;
      case 3:  // up left direction
        if(!emplaceCountigous(&leftMovingBoxes,  &upMovingBoxes,   rightMovingBoxes, downMovingBoxes)) maxMiss--;

      break;
    }
    i++;
  }
}


std::array<uintmax_t, XARRSIZE> rightToLeftArr(
  int i, int size, int realSpeed,
  uintmax_t collisionMap,
  std::array<uintmax_t, XARRSIZE> arrayFrom, std::array<uintmax_t, XARRSIZE> arrayTo,
  uintmax_t contigousMin, uintmax_t contigousMax){
  
  int offset = 0;

  for(int j = 0; j < sizeof(uintmax_t); j++){
    offset = 0;
    if(collisionMap >> j & true){
      while(collisionMap >> (j + offset) & true && j + offset < sizeof(uintmax_t)) offset++;
      uintmax_t oldBox = (contigousMin << (j - size - offset - realSpeed));
      if(contigousOverflow(oldBox)){
        // if(oldBox > LASTINDEXXMAX) this shouldn't happen... EVER!!
        arrayTo  [i]   |=  ( oldBox & contigousMax);
        arrayTo  [i+1] |=  (~oldBox | contigousMin);
        arrayFrom[i]   &= ~( oldBox & contigousMax);
        arrayFrom[i+1] &= ~(~oldBox | contigousMin);

      } else {
        arrayTo  [i] |=  oldBox;
        arrayFrom[i] &= ~oldBox;
      }
      j+=size;
    } 
  }

  return arrayTo;
}

std::array<uintmax_t, YARRSIZE> downToUpArr(
  int i, int size, int realSpeed,
  uintmax_t collisionMap,
  std::array<uintmax_t, XARRSIZE> arrayFrom, std::array<uintmax_t, XARRSIZE> arrayTo,
  uintmax_t contigousMin, uintmax_t contigousMax){

  int offset = 0;

  for(int j = 0; j < sizeof(uintmax_t); j++){
    offset = 0;
    if(collisionMap >> j & true){
      while(collisionMap >> (j + offset) & true && j + offset < sizeof(uintmax_t)) offset++;
      uintmax_t oldBox = (contigousMin << (j - size - offset - realSpeed));
      if(contigousOverflow(oldBox)){
        // if(oldBox > LASTINDEXXMAX) this shouldn't happen... EVER!!
        arrayTo  [i]   |=  ( oldBox & contigousMax);
        arrayTo  [i+1] |=  (~oldBox | contigousMin);
        arrayFrom[i]   &= ~( oldBox & contigousMax);
        arrayFrom[i+1] &= ~(~oldBox | contigousMin);

      } else {
        arrayTo  [i] |=  oldBox;
        arrayFrom[i] &= ~oldBox;
      }
      j+=size;
    } 
  }

  return arrayTo;
}

std::array<uintmax_t, XARRSIZE> leftToRightArr(
  int i, int size, int realSpeed,
  uintmax_t collisionMap,
  std::array<uintmax_t, XARRSIZE> arrayFrom, std::array<uintmax_t, XARRSIZE> arrayTo,
  uintmax_t contigousMin, uintmax_t contigousMax){
  
  int offset = 0;

  for(int j = 0; j < sizeof(uintmax_t); j++){
    offset = 0;
    if(collisionMap >> j & true){
      while(collisionMap >> (j + offset) & true && j + offset < sizeof(uintmax_t)) offset++;
      uintmax_t oldBox = (contigousMin << (j + offset + realSpeed));
      if(contigousUnderflow(oldBox, size)){
        // Figure out underflow
        arrayTo  [ i ] |=  ( oldBox & contigousMin);
        arrayTo  [i-1] |=  (~oldBox | contigousMax);
        arrayFrom[ i ] &= ~( oldBox & contigousMin);
        arrayFrom[i-1] &= ~(~oldBox | contigousMax);

      } else {
        arrayTo  [i] |=  oldBox;
        arrayFrom[i] &= ~oldBox;
      }
      j+=size;
    } 
  }

  return arrayTo;
}

std::array<uintmax_t, YARRSIZE> upToDownArr(
  int i, int size, int realSpeed,
  uintmax_t collisionMap,
  std::array<uintmax_t, YARRSIZE> arrayFrom,
  std::array<uintmax_t, YARRSIZE> arrayTo,
  uintmax_t contigousMin, uintmax_t contigousMax){

  int offset = 0;

  for(int j = 0; j < sizeof(uintmax_t); j++){
    offset = 0;
    if(collisionMap >> j & true){
      while(collisionMap >> (j + offset) & true && j + offset < sizeof(uintmax_t)) offset++;
      uintmax_t oldBox = (contigousMin << (j + offset + realSpeed));
      if(contigousUnderflow(oldBox, size)){
        // Figure out underflow
        arrayTo  [ i ] |=  ( oldBox & contigousMin);
        arrayTo  [i-1] |=  (~oldBox | contigousMax);
        arrayFrom[ i ] &= ~( oldBox & contigousMin);
        arrayFrom[i-1] &= ~(~oldBox | contigousMax);

      } else {
        arrayTo  [i] |=  oldBox;
        arrayFrom[i] &= ~oldBox;
      }
      j+=size;
    } 
  }

  return arrayTo;
}

std::array<uintmax_t, XARRSIZE> moveRight(
  int realSpeed,
  std::array<uintmax_t, XARRSIZE> movingBoxes,
  std::array<uintmax_t, XARRSIZE>* collisions,
  uintmax_t contigousMin, uintmax_t contigousMax){
  // int realSpeed; // Must be even unless MAXRES
  std::array<uintmax_t, XARRSIZE> testBoxes;
  std::array<uintmax_t, XARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < movingBoxes.size(); i++){
    testBoxes[i] |= movingBoxes[i] << realSpeed;

  if(contigousOverflow(testBoxes[i])){
      if(i + 1 < movingBoxes.size()){
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

std::array<uintmax_t, XARRSIZE> moveLeft(
  int realSpeed,
  std::array<uintmax_t, XARRSIZE> movingBoxes,
  std::array<uintmax_t, XARRSIZE>* collisions,
  uintmax_t contigousMin, uintmax_t contigousMax){
  // int speed; // Must be even unless MAXRES
  std::array<uintmax_t, XARRSIZE> testBoxes;
  std::array<uintmax_t, XARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < movingBoxes.size(); i++){
    testBoxes[i] |= movingBoxes[i] >> realSpeed;

  if(contigousUnderflow(testBoxes[i], contigousMin)){
      if(i - 1 > 0){
        // Pass underflow to previous index
        testBoxes   [i-1] |= ~(contigousMin & testBoxes[i]);
      } else {
        collisionBoxes[i] |= contigousMin;
      }
    }
    
  }

  collisions = &collisionBoxes;
  return testBoxes;
}

std::array<uintmax_t, YARRSIZE> moveDown(
  int realSpeed,
  std::array<uintmax_t, YARRSIZE> movingBoxes,
  std::array<uintmax_t, YARRSIZE>* collisions,
  uintmax_t contigousMin, uintmax_t contigousMax){
  // int realSpeed; // Must be even unless MAXRES
  std::array<uintmax_t, YARRSIZE> testBoxes;
  std::array<uintmax_t, YARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < movingBoxes.size(); i++){
    testBoxes[i] |= movingBoxes[i] << realSpeed;

  if(contigousOverflow(testBoxes[i])){
      if(i + 1 < movingBoxes.size()){
        // Pass overflow to next index
        testBoxes[i+1] |= ~testBoxes[i] & contigousMin;
        if(testBoxes[i+1] > LASTINDEXYMAX) {
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

std::array<uintmax_t, YARRSIZE> moveUp(
  int realSpeed,
  std::array<uintmax_t, XARRSIZE> movingBoxes,
  std::array<uintmax_t, XARRSIZE>* collisions,
  uintmax_t contigousMin, uintmax_t contigousMax){
  // int realSpeed; // Must be even unless MAXRES
  std::array<uintmax_t, YARRSIZE> testBoxes;
  std::array<uintmax_t, YARRSIZE> collisionBoxes = *collisions;

  for(int i = 0; i < movingBoxes.size(); i++){
    testBoxes[i] |= movingBoxes[i] >> realSpeed;

  if(contigousUnderflow(testBoxes[i], contigousMin)){
      if(i - 1 > 0){
        // Pass underflow to previous index
        testBoxes   [i-1] |= ~(contigousMin & testBoxes[i]);
      } else {
        collisionBoxes[i] |= contigousMin;
      }
    }

  }

  collisions = &collisionBoxes;
  return testBoxes;
}


int width  = 16;
int height = 16;

uintmax_t contigousWidthMin  = fillContigous(width);
uintmax_t contigousHeightMin = fillContigous(height);
uintmax_t contigousWidthMax  = fillContigousBackwards(width);
uintmax_t contigousHeightMax = fillContigousBackwards(height);

int speed = 2;
int realSpeed = (speed / (sizeof(uintmax_t) / RESOLUTION));

void cycle(bool cycleAgain){
  std::array<uintmax_t, XARRSIZE> xcollisions ;
  std::array<uintmax_t, YARRSIZE> ycollisions ;
  std::array<uintmax_t, XARRSIZE> futurexBoxes;
  std::array<uintmax_t, YARRSIZE> futureyBoxes;

  oldRightMovingBoxes = rightMovingBoxes;
  oldLeftMovingBoxes  = leftMovingBoxes ;
  oldDownMovingBoxes  = downMovingBoxes ;
  oldUpMovingBoxes    = upMovingBoxes   ;

  rightMovingBoxes = moveRight (realSpeed, rightMovingBoxes, &xcollisions, contigousWidthMin,  contigousWidthMax );
  leftMovingBoxes  = moveLeft  (realSpeed, leftMovingBoxes,  &xcollisions, contigousWidthMin,  contigousWidthMax );
  downMovingBoxes  = moveDown  (realSpeed, downMovingBoxes,  &ycollisions, contigousHeightMin, contigousHeightMax);
  upMovingBoxes    = moveUp    (realSpeed, upMovingBoxes,    &ycollisions, contigousHeightMin, contigousHeightMax);

  uintmax_t hasXCollisions = 0;
  uintmax_t hasYCollisions = 0;

  for(int i = 0; i < XARRSIZE; i++){
    xcollisions[i]  &= rightMovingBoxes[i] & leftMovingBoxes[i];
    futurexBoxes[i] |= rightMovingBoxes[i] | leftMovingBoxes[i];
    hasXCollisions  |= xcollisions[i];
    newLeftMovingBoxes  = rightToLeftArr(i, width, realSpeed, xcollisions[i] & rightMovingBoxes[i], oldRightMovingBoxes, oldLeftMovingBoxes , contigousWidthMin, contigousWidthMax);
    newRightMovingBoxes = leftToRightArr(i, width, realSpeed, xcollisions[i] & leftMovingBoxes [i], oldLeftMovingBoxes , oldRightMovingBoxes, contigousWidthMin, contigousWidthMax);
  }
  for(int i = 0; i < YARRSIZE; i++){
    ycollisions[i]  &= upMovingBoxes[i] & downMovingBoxes[i];
    futureyBoxes[i] |= upMovingBoxes[i] | downMovingBoxes[i];
    hasYCollisions  |= ycollisions[i];
    newUpMovingBoxes    = downToUpArr  (i, height, realSpeed, xcollisions[i] & downMovingBoxes [i], oldDownMovingBoxes , oldUpMovingBoxes   , contigousHeightMin, contigousHeightMax);
    newDownMovingBoxes  = upToDownArr  (i, height, realSpeed, xcollisions[i] & upMovingBoxes   [i], oldUpMovingBoxes   , oldDownMovingBoxes , contigousHeightMin, contigousHeightMax);
  }
  if((hasXCollisions | hasYCollisions) & cycleAgain) {
    rightMovingBoxes = newRightMovingBoxes;
    leftMovingBoxes  = newLeftMovingBoxes ;
    downMovingBoxes  = newDownMovingBoxes ;
    upMovingBoxes    = newUpMovingBoxes   ;
    cycle(false);
  } 
  else {
    
    finalxBoxes = futurexBoxes;
    finalyBoxes = futureyBoxes;

    // wait 16ms then cycle again
  }
}