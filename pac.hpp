#pragma once


#include"raylib.h"
#include<iostream>

enum direction{
  n=0,
  s,
  e,
  w
};

class Pac{
public:
  Pac();
  ~Pac();
  void Update();
  void Draw();
  void InitPacman();
  
  void Move(int);
  void MoveToDir();
  bool EventTriggered(double);

  int GetX(){
    return x;
  }
  int GetY(){
    return y;
  }
  int GetDir(){
    switch(dir){
    case n:
      return 1;break;
    case s:
      return 2;break;
    case e:
      return 3;break;
    case w:
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
private:
  int x;
  int y;
  int lives;
  direction dir;
  double lastUpdatedTime=0.0;
};
