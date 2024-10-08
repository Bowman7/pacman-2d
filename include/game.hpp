#pragma once

#include"raylib.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<random>
#include<limits>

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
  float localVal = std::numeric_limits<float>::infinity();
  float globalVal =  std::numeric_limits<float>::infinity();
  int dir;//n:0,s:1,e:2,w:3
  bool visited;
  std::vector<Node*> vecNeighbours; 
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
  int GetNum(int);
  bool IsNextDirValid(int,int);
  bool GhostHitWall();
  void GhostScatter();
  bool NoBounceback(int,int);
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
  void printTile();
  void listSwap(Node &,Node &);
  void modAStar(int);
  void InitMoveDirBeforeScatter();
  void RedMoveSeq();
  bool pinkGhostHitWall();
  void RoamPinkGhost();
  void InitPinkMoveDir();
  //for pink ghost
  void PinkMoveSeq();
  void PinkInitPathTile();
  int PinkEastWest();
  int PinkNorthSouth();
  //for blue ghost
  void InitBlueMoveDir();
  void BlueMoveSeq();
  void BlueInitPathTile();
  void RoamBlueGhost();
  bool blueGhostHitWall();
  int BlueNorthSouth();
  int BlueEastWest();
  //for orange ghost
  void InitOrangeMoveDir();
  bool orangeGhostHitWall();
  void RoamOrangeGhost();
  void OrangeScatter();
  //for health pacman
  void UpdateHealth();
  void DrawHealth();
  void CheckWonOrOver();
  bool IsGameOver(){
    return gameOver;
  }
  bool IsGameWon(){
    return gameWon;
  }
  
  //init game after game over
  void GameInit();
  void UpdateEatenSpirits();
  //bool
  bool ShieldSpawn(double);
  void DrawShield();

  bool Hit(){
    return hit;
  }
  void HitFalse(){
    hit = false;
  }
  bool Grab(){
    return grab;
  }
  void GrabFalse(){
    grab =false;
  }
private:
  //if hit
  bool grab = false;
  bool hit=false;;
  //for shield
  Image shield_image;
  Texture2D shield_tex;
  //for health texture
  Image health_image;
  Texture2D health_tex;
  Rectangle health_frameRec;
  Vector2 health_position;
  //for ghost texture
  Image ghost_image;
  Texture2D ghost_tex;
  Rectangle frameRec;
  //for shield
  double lastUpdatedShield= 0.0f;
  bool shieldActive = false;
  int shield;
  //spirits
  int eatenSpirits=0;
  int totalSpirit;
  bool CollectedAllSouls = false;
  //check gameown or over
  bool gameOver = false;
  bool gameWon = false;
  //health
  int pacHealth;
  //for pacman running
  int curDir;
  int nextDir;
  bool nextDirWPresent = false;
  bool nextDirEPresent = false;
  bool nextDirNPresent = false;
  bool nextDirSPresent = false;
  bool IsCollideWall = false;
 
  int iter = 0;
  int dist;  
  int tcount =0;
  int wcount = 0;
  //main list
  std::vector<Node*> list;
  
  //orange ghost
  Ghost orangeGhost;
  pathTile orangeTile[40][40];
  int ocount = 0;
  int oFinalTileX,oFinalTileY;
  bool oReachedLastTile = false;
  bool oPathFound = false;
  int oGhostMode = 0;

  //red ghost
  Ghost ghost;
  pathTile tile[40][40];
  int rcount = 0;
  int rFinalTileX,rFinalTileY;
  bool rReachedLastTile = false;
  bool rPathFound = false;
  bool starReached = false;
  int ghostMode = 0; //  1: hunt
  
  //pink ghost
  Ghost pinkGhost;
  pathTile pinkTile[40][40];
  int pcount =0;
  int pFinalTileX,pFinalTileY;
  bool pReachedLastTile = false;
  bool pPathFound = false;
  int pGhostMode = 0;

  //blue ghost
  Ghost blueGhost;
  pathTile blueTile[40][40];
  int bcount=0;
  int bFinalTileX,bFinalTileY;
  bool bReachedLastTile = false;
  bool bPathFound = false;
  int bGhostMode = 0;

  
  //ghost mode 0:scatter 1:atk
  int pacDist;
  
  //bool pathFound = false;
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
  
};
