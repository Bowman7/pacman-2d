#include"ghost.hpp"

Ghost::Ghost(){
  InitGhost();
  mode = 1;
}

Ghost::~Ghost(){

}

//event triggered
bool Ghost::EventTriggered(double time){
  double currentTime = GetTime();
  if(currentTime - lastUpdatedTime >=time){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//move
void Ghost::Move(int val){
  switch(val){
  case 0:
    currentDir = gn;break;
  case 1:
    currentDir = gs;break;
  case 2:
    currentDir = ge;break;
  case 3:
    currentDir = gw;break;
  default:
    break;
  }
}
//moving
void Ghost::MoveToDir(){
  if(EventTriggered(0.1)){
    switch(currentDir){
    case gn:
      y--;break;
    case gs:
      y++;break;
    case ge:
      x++;break;
    case gw:
      x--;break;
    default:
      break;
    }
  }
}
//init pacman
void Ghost::InitGhost(){
  x =10;
  y =20;
}

//draw pacman
void Ghost::Draw(){
  DrawCircle(x*25,y*25,20,RED);
}
