#include"ghost.hpp"

Ghost::Ghost(){
  InitGhost();
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
    dir = gn;break;
  case 1:
    dir = gs;break;
  case 2:
    dir = ge;break;
  case 3:
    dir = gw;break;
  default:
    break;
  }
}
//moving
void Ghost::MoveToDir(){
  if(EventTriggered(0.1)){
    switch(dir){
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
  x =38;
  y =2;
}

//draw pacman
void Ghost::Draw(){
  DrawCircle(x*25,y*25,20,color);
}
