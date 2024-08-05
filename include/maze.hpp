#pragma once

#include"raylib.h"
#include<iostream>
#include<random>
#include<algorithm>
#include<vector>
#include"stdio.h"

enum directions{
    N =0,
    S,
    E,
    W
};
struct s_maze{
  //more imp
  directions fwdDir;
  directions bckDir;

  bool visited;
  Color color;
};
struct Stack{
  int x;
  int y;
};

class Maze{
public:
  Maze();
  ~Maze();
  
  void Draw();

  void testMove();
  
  void InitMaze();
  void Shuffle(directions dir[]);
  directions opposite(directions dir);
  void SetupPath();
  void CreatePath(int,int);
  directions GetDirection();
  void GetStep(int &,int&,directions);
  void carvePassage(int x,int y);
  void Push(int x,int y){
    top++;
    stack[top].x = x;
    stack[top].y = y;
    maze[x][y].visited = true;
  }
  void Pop(){
    printf("pop [%d][%d]\n",stack[top].x,stack[top].y);
    top--;
  }
  bool IsEmpty(){
    if(top==-1){
      return true;
    }
    return false;
  }
  void CheckAvailableDir();
  void PrintDir(directions dir[]);
 
private:
  s_maze maze[9][9];
  Stack stack[9];
  
  int top = -1;

  int size = 100;

  

};
