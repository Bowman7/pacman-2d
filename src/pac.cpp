#include"../include/pac.hpp"

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
  case 0:
    dir = n;break;
  case 1:
    dir = s;break;
  case 2:
    dir = e;break;
  case 3:
    dir = w;
    break;
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
  //load textures
  pac_image = LoadImage("Texture/packnight.png");
  pac_texture = LoadTextureFromImage(pac_image);
  UnloadImage(pac_image);
  //set frameRec
  frameRec={0.0f,0.0f,(float)pac_texture.width/4,(float)pac_texture.height/4};
  currentFrame = 0;
}
//check if time to update frame
bool Pac::IsUpdateFrameTime(double time){
  double currentTime = GetTime();
  if(currentTime-lastUpdateFrame>=time){
    lastUpdateFrame = currentTime;
    return true;
  }
  return false;
}
//update
void Pac::Update(){
   //check dir
  if(dir == 0){//north
    frameRec.y = 50.0f;
  }else if(dir == 1){//south
    frameRec.y = 0.0f;
  }else if(dir == 2){//east
    frameRec.y = 100.0f;
  }else if(dir == 3){//west
    frameRec.y = 150.0f;
  }
  //inc current frame
  if(IsUpdateFrameTime(0.1)){
    currentFrame++;
    if(currentFrame >3){
      currentFrame = 0;
    }
    frameRec.x = (float)currentFrame*(float)pac_texture.width/4;
  }
  
}
//draw pacman
void Pac::Draw(){
  //DrawCircle(x*25,y*25,20,YELLOW);
  int texX = x-1;
  int texY = y-1;
  position.x = texX*25;
  position.y = texY*25;
 
  //DrawTexture(pac_texture,texX*25,texY*25,WHITE);
  DrawTextureRec(pac_texture,frameRec,position,WHITE);
}
