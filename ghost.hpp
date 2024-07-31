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
  void SetColor(int col){
    //0: red 1: pink 2: blue 3: orange
    if(col == 0){
      color = RED;
    }else if(col == 1){
      color = PINK;
    }else if(col == 2){
      color = SKYBLUE;
    }else if(col == 3){
      color = ORANGE;
    }
  }
 
private:

  Color color;
  int x;
  int y;
  g_direction dir;
  double lastUpdatedTime=0.0;
};
