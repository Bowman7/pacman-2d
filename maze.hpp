#pragma once

#include"raylib.h"

class Maze{
public:
  Maze();
  ~Maze();
  void InitMaze();
  void Draw();
private:
  struct s_maze{
    int val;//0:box 1:wall
    Color color;
    bool visited;
  };
  s_maze maze[30][30];//10X10 2x2gspcae (3x3-2x2)wallspace
  
};
