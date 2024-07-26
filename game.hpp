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

//for A*
struct Node{
  int x;
  int y;
  float localVal = 1024.0f;
  float globalVal = 1024.0f;
  int dir;//n:0,s:1,e:2,w:3
  bool visited;
};
struct pathTile{
  int x;
  int y;
  int dir;
  bool visited;
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
  void CheckPaths(int,int,int,int);
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
  bool NoBounceback(int);
  bool IsPacNear();
  void HuntPacman();
  bool ModeTriggered(double);
  bool InFinalStack(int,int);
  bool IsOneDiff(int,int);
  bool InQueue(int,int);
  void SolveAStar();
  void InitPathTile();
  void sortList();
  void printList();
private:
  //for A*
  int tcount =0;
  std::vector<Node> list;
  pathTile tile[40][40];
  //ghost mode 0:scatter 1:atk
  //bool ghostDestReached = false;
  int pacDist;
  int ghostMode = 1;
  bool pathFound = false;
  //time keep
  double lastUpdatedTime = 0.0f;
  double ghostModeChange  =0.0f;
 
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
