#pragma once

#include"raylib.h"
#include<iostream>

enum g_direction{
  gn=0,
  gs,
  ge,
  gw
};

class Ghost{
public:
  Ghost();
  ~Ghost();
  void Update();
  void Draw();
  void InitGhost();
  
  void Move(int);
  void MoveToDir();
  bool EventTriggered(double);

  int GetX(){
    return x;
  }
  int GetY(){
    return y;
  }
  void SetX(int x){
    this->x =x;
  }
  void SetY(int y){
    this->y = y;
  }
  int GetDir(){
    switch(dir){
    case gn:
      return 1;break;
    case gs:
      return 2;break;
    case ge:
      return 3;break;
    case gw:
      return 4;break;
    default:
      break;
    }
    return 0;
  }

  void RevertNorth(){
    y+=1;
  }
  void RevertSouth(){
    y-=1;
  }
  void RevertEast(){
    x-=1;
  }
  void RevertWest(){
    x+=1;
  }

  int GetMode(){
    return mode;
  }
  void SetScatterMode(){
    mode =0;
  }
  void SetHuntMode(){
    mode =1;
  }
  
private:
  int mode;//0:scatter,1:chase,2:run
  int x;
  int y;
  g_direction dir;
  double lastUpdatedTime=0.0;
};
