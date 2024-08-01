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
  void SetX(int x){
    this->x = x;
  }
  void SetY(int y){
    this->y = y;
  }
  int GetDir(){
    switch(dir){
    case n:
      return 0;break;
    case s:
      return 1;break;
    case e:
      return 2;break;
    case w:
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
  bool IsMoving(){
    return moving;
  }
  void SetNotMoving(){
    moving = false;
  }
  void SetMoving(){
    moving = true;
  }
private:
  bool moving =false;
  int x;
  int y;
  int lives;
  direction dir;
  direction nextDir;
  double lastUpdatedTime=0.0;
};
