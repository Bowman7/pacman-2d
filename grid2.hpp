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
  int colVal;//1 green,2 blue
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
    //printf("pop [%d][%d]\n",stack[top].x,stack[top].y);
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
  //reflect maze
  void ReflectMaze();
  void PrintLine();
  void DeadEndsHorz();//clear horizontal dead ends
  int CheckPaths(int,int);
  void clearDeadEnd(int,int);
  
private:
  s_maze maze[20][40];
  s_maze maze2[20][40];
  Stack stack[90];
  
  int top = -1;

  int size = 25;

  

};
