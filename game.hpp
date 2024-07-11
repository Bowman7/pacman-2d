#pragma once

#include"raylib.h"
#include<iostream>

#include"grid2.hpp"
#include"coin.hpp"
class Game{
public:
  Game();
  ~Game();
  void Update();
  void HandleInputs();
  void Draw();

  void InitCoin();
private:
  Maze maze;
  Coin coin[20][40];
};
