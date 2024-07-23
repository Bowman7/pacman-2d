#pragma once

#include"raylib.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<random>

#include"grid2.hpp"
#include"pac.hpp"
#include"ghost.hpp"

struct Coin{
  int x;
  int y;
  bool visited;
};

//for path
struct Pos{
  int x;
  int y;
  int heuristic;
  int pathcost;
  int cost;
  int dir;
};

class Game{
public:
  Game();
  ~Game();
  void Update();
  void HandleInputs();
  void Draw();
  void InitCoin();
  void DrawCoin();
  int CheckNeighbours(int,int);
  void CheckCollision();
  void EatCoin();
  
  //func to find thepath
  void FindPath(int,int,int,int);
  void CheckPaths(Pos,int,int);
  bool IsValidPath(int,int);
  void SortQueue();
  void PrintQueue();
  void PrintFinal();
  void MoveToEat();
  bool EventTriggered(double);
  void RoamGhost();
  int GetRandomNum();
  int GetNum();
  bool IsNextDirValid(int);
  bool GhostHitWall();
  void GhostScatter();
private:
  //ghost mode 0:scatter 1:atk
  int ghostMode = 0;
  
  //time keep
  double lastUpdatedTime = 0.0f;
  int count =0;
  int qcount = 0;
  //for path finding
  std::vector<Pos> finalStack;
  std::vector<Pos> queue;
  //bool findGhostPath =true;
  
  Maze maze;
  Coin coin[40][40];
  Pac pac;
  Ghost ghost;
};
