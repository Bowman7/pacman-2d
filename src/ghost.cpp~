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
void Ghost::Draw(Texture2D ghost_tex,Rectangle frameRec,int ghostType){
  switch(ghostType){
  case 0://red ghost
    {
      frameRec.x = 0.0f;
    }break;
  case 1://pink ghost
    {
      frameRec.x = 50.0f;
    }break;
  case 2://blue
    {
      frameRec.x = 100.0f;
    }break;
  case 3://orange
    {
      frameRec.x = 150.0f;
    }break;
  default:
    break;
  }
  if(dir == 0){//north
    frameRec.y =0.0f;
  }else if(dir == 1){//south
    frameRec.y = 50.0f;
  }else if(dir == 2){//east
    frameRec.y = 100.0f;
  }else if(dir == 3){//west
    frameRec.y = 150.0f;
  }
  Vector2 position;
  int texX = x-1;
  int texY = y-1;
  position.x = texX*25;
  position.y = texY*25;
  //DrawCircle(x*25,y*25,20,color);
  //DrawTexture(ghost_tex,texX*25,texY*25,WHITE);
  DrawTextureRec(ghost_tex,frameRec,position,WHITE);
}
