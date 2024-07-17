#include"pac.hpp"

Pac::Pac(){
  InitPacman();
}

Pac::~Pac(){

}
//event triggered
bool Pac::EventTriggered(double time){
  double currentTime = GetTime();
  if(currentTime - lastUpdatedTime >=time){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//move
void Pac::Move(int val){
  switch(val){
  case 1:
    dir = n;break;
  case 2:
    dir = s;break;
  case 3:
    dir = e;break;
  case 4:
    dir = w;break;
  default:
    break;
  }
}
//moving
void Pac::MoveToDir(){
  if(EventTriggered(0.1)){
    switch(dir){
    case n:
      y--;break;
    case s:
      y++;break;
    case e:
      x++;break;
    case w:
      x--;break;
    default:
      break;
    }
  }
}
//init pacman
void Pac::InitPacman(){
  x =2;
  y =2;
  lives = 3;
}

//draw pacman
void Pac::Draw(){
  DrawCircle(x*25,y*25,20,YELLOW);
}
