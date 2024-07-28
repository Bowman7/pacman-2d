#pragma once

#include"raylib.h"
#include<iostream>

struct s_coin{
  int x;
  int y;
  bool visible;
  int size;
};
class Coin{
public:
  Coin();
  ~Coin(){}
  void Draw();
  void SetVal(int,int,bool);
  
private:
  s_coin coin; 
};
