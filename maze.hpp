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

struct Stack{
    int x;
    int y;
};

class Maze{
public:
  Maze();
  ~Maze();
  void InitMaze();
  void Draw();

  void testMove();
  
  void Shuffle(directions dir[]);
  void PrintDir(directions dir[]);
  directions opposite(directions dir);
  void SetupPath();
  void CheckPath(int,int);
  directions GetDirection();
  void GetStep(int &,int&,directions);
  void carvePassage(int x,int y);
  void Push(int x,int y){
    top++;
    stack[top].x = x;
    stack[top].y = y;
    maze[x][y].visited = true;
  }
  void pushPath(int x,int y){
    p_top++;
    pathStack[top].x = x;
    pathStack[top].y = y;
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
  void SetDirection(int&,int&,directions dir[]);
  void CheckAvailableDir();
  void LinkUp(struct Stack,struct Stack);
private:
  
  Stack stack[9];
  Stack pathStack[9];
  int top = -1;
  int p_top=-1;
  
  struct s_maze{
    //more imp
    directions fwdDir;
    directions bckDir;

    bool visited;
    Color color;
  };
  s_maze maze[9][9];

  int size = 100;

  

};
