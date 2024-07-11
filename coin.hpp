#pragma once

#include"raylib.h"
#include<iostream>

class Coin{
public:
  Coin();
  ~Coin(){}
  void Draw(int,int);
  bool IsEaten(){
    return eaten;
  }
  void SetEatenFalse(){
    eaten = false;
  }
private:
  int x;
  int y;
  bool eaten;
};
