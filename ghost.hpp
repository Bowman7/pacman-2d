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
    switch(currentDir){
    case gn:
      return 0;break;
    case gs:
      return 1;break;
    case ge:
      return 2;break;
    case gw:
      return 3;break;
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
  bool CheckPreviousDir(int val){
    g_direction valDir;
    switch(val){
    case 0:
      valDir = gn;break;
    case 1:
      valDir = gs;break;
    case 2:
      valDir = ge;break;
    case 3:
      valDir = gw;break;
    }
    //now check val
    if(valDir == previousDir){
      return true;
    }
    return false;
    
  }
  void SetPrevDir(){
    previousDir = currentDir;
  }
  
private:
  g_direction currentDir = gw;
  g_direction previousDir = ge;
  
  int mode;//0:scatter,1:chase,2:run
  int x;
  int y;
  g_direction dir;
  double lastUpdatedTime=0.0;
};
