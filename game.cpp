#include"game.hpp"

Game::Game(){
  InitCoin();
}

Game::~Game(){

}
//print final stack
void Game::PrintFinal(){
  for(int i=0;i<finalStack.size();i++){
    printf(" posx:[%d] posy:[%d] cost[%d]->",finalStack[i].x,finalStack[i].y,finalStack[i].cost);
  }
  printf("\n");
}
//print queue
void Game::PrintQueue(){
  for(int i=0;i<queue.size();i++){
    printf(" posx:[%d] posy:[%d] cost[%d]->",queue[i].x,queue[i].y,queue[i].cost);
  }
  printf("\n");
}
//sort queue
void Game::SortQueue(){
  for(int i=0;i<queue.size();i++){
    for(int j=0;j<queue.size()-i-1;j++){
      if(queue.at(j).cost < queue.at(j-1).cost){
	Pos temp;
	temp = queue.at(j);
	queue.at(j) = queue.at(j+1);
	queue.at(j+1) = temp;
      }
    }
  }
}
//check if path is valid
bool Game::IsValidPath(int x, int y){
   if(maze.IsWalkable(x-1,y-1) ==1 &&
      maze.IsWalkable(x,y-1) == 1 &&
      maze.IsWalkable(x-1,y) == 1 &&
      maze.IsWalkable(x,y) == 1
      ){
     return true;
   }
   return false;
}
//check paths
void Game::CheckPaths(Pos val,int gx,int gy){
  //for north
  if(IsValidPath(val.x,val.y-1)){
    Pos temp;
    temp.x = val.x;
    temp.y = val.y-1;
    temp.heuristic = abs(gx-temp.x)+abs(gy-temp.y);
    temp.pathcost = 1;
    temp.cost = temp.heuristic+temp.pathcost;
    queue.push_back(temp);
    //sort queue acc to cost
    if(queue.size()>2){
      //PrintQueue();
    }
    
  }
  //for south
  if(IsValidPath(val.x,val.y+1)){
    Pos temp;
    temp.x = val.x;
    temp.y = val.y+1;
    temp.heuristic = abs(gx-temp.x)+abs(gy-temp.y);
    temp.pathcost = 1;
    temp.cost = temp.heuristic+temp.pathcost;
    queue.push_back(temp);
    //sort queue acc to cost
    if(queue.size()>2){
      //PrintQueue();
    }
    
  }
  //for east
  if(IsValidPath(val.x+1,val.y)){
    Pos temp;
    temp.x = val.x+1;
    temp.y = val.y;
    temp.heuristic = abs(gx-temp.x)+abs(gy-temp.y);
    temp.pathcost = 1;
    temp.cost = temp.heuristic+temp.pathcost;
    queue.push_back(temp);
    //sort queue acc to cost
    if(queue.size()>2){
      //PrintQueue();
    }
    
  }
  //for west
  if(IsValidPath(val.x-1,val.y)){
    Pos temp;
    temp.x = val.x-1;
    temp.y = val.y;
    temp.heuristic = abs(gx-temp.x)+abs(gy-temp.y);
    temp.pathcost = 1;
    temp.cost = temp.heuristic+temp.pathcost;
    queue.push_back(temp);
    //sort queue acc to cost
   if(queue.size()>2){
     //PrintQueue();
   }
  }
}
//for path finding
void Game::FindPath(int x, int y,int gx,int gy){
  if(abs(gx-x)+abs(gy-y) ==0){
    return ;
  }
  //first push the pacman pos
  Pos val;
  val.x =x;
  val.y = y;
  val.heuristic = abs(gx-x)+abs(gy-y);
  val.pathcost = 0;
  val.cost = val.heuristic + val.pathcost;
  finalStack.push_back(val);
  //check NSEW and push into queue
  CheckPaths(val,gx,gy);
 
  
  //check for new top of queue
  Pos topQueue = queue[queue.size()];
  queue.erase(queue.begin());
  FindPath(topQueue.x,topQueue.y,gx,gy);
}
//eat coin
void Game::EatCoin(){
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      if(coin[i][j].x == pac.GetX() && coin[i][j].y == pac.GetY()){
	coin[i][j].visited = true;
      }
    }
  }
}
//collision
void Game::CheckCollision(){
  //1 2 3 4
  //for pacman
  if(maze.IsWalkable(pac.GetX()-1,pac.GetY()-1) ==2 ||
     maze.IsWalkable(pac.GetX(),pac.GetY()-1) == 2 ||
     maze.IsWalkable(pac.GetX()-1,pac.GetY()) == 2 ||
     maze.IsWalkable(pac.GetX(),pac.GetY()) == 2
     ){
    switch(pac.GetDir()){
    case 1:
      pac.RevertNorth();break;
    case 2:
      pac.RevertSouth();break;
    case 3:
      pac.RevertEast();break;
    case 4:
      pac.RevertWest();break;
    }
  }
  //for ghost
  if(maze.IsWalkable(ghost.GetX()-1,ghost.GetY()-1) ==2 ||
     maze.IsWalkable(ghost.GetX(),ghost.GetY()-1) == 2 ||
     maze.IsWalkable(ghost.GetX()-1,ghost.GetY()) == 2 ||
     maze.IsWalkable(ghost.GetX(),ghost.GetY()) == 2
     ){
    switch(ghost.GetDir()){
    case 1:
      ghost.RevertNorth();break;
    case 2:
      ghost.RevertSouth();break;
    case 3:
      ghost.RevertEast();break;
    case 4:
      ghost.RevertWest();break;
    }
  }
}
//init coin
void Game::InitCoin(){

  int x=2;
  int y=2;
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      coin[i][j].x = x;
      coin[i][j].y = y;
      coin[i][j].visited = false;
      y++;
    }
    x++;
    y=2;
  }
}
//check neighbours
int Game::CheckNeighbours(int x,int y){
  //check all dir
  //1
  if(maze.IsWalkable(x-1,y-1) == 1 &&
     maze.IsWalkable(x,y-1) == 1 &&
     maze.IsWalkable(x-1,y) == 1 &&
     maze.IsWalkable(x,y) == 1)
    {
      return 0;
    }
  
  return 1;
}

void Game::Update(){
  pac.MoveToDir();
  ghost.MoveToDir();
  CheckCollision();
  EatCoin();
  //apth finding
  FindPath(pac.GetX(),pac.GetY(),ghost.GetX(),ghost.GetY());
  //print vals
  if(count <1){
    printf("Queue : \n");
    PrintQueue(); 
    printf("Final stack: \n");
    PrintFinal();
    //new pos
    //finalStack.push_back(queue[0]);
    //SortQueue();
    printf("Queue : \n");
    PrintQueue(); 
    count++;
  }
 
}
void Game::HandleInputs(){
  //n:1,S:2,E:3,W:4
  //north
  if(IsKeyPressed(KEY_W)){
    pac.Move(1);
  }
  //south
  if(IsKeyPressed(KEY_S)){
    pac.Move(2);
  }
  //east
  if(IsKeyPressed(KEY_D)){
    pac.Move(3);
  }
  //west
  if(IsKeyPressed(KEY_A)){
    pac.Move(4);
  }
  //FOR GHOST
  if(IsKeyPressed(KEY_UP)){
    ghost.Move(1);
  }
  //south
  if(IsKeyPressed(KEY_DOWN)){
    ghost.Move(2);
  }
  //east
  if(IsKeyPressed(KEY_RIGHT)){
    ghost.Move(3);
  }
  //west
  if(IsKeyPressed(KEY_LEFT)){
    ghost.Move(4);
  }
}


void Game::DrawCoin(){
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      if(maze.IsWalkable(coin[i][j].x,coin[i][j].y) == 1){
	if(CheckNeighbours(coin[i][j].x,coin[i][j].y) == 0 &&
	   coin[i][j].visited == false
	   ){
	  DrawCircle(coin[i][j].x*25,coin[i][j].y*25,3,GOLD);
	}
      }
    }
  }
}

void Game::Draw(){
  maze.Draw();
  DrawCoin();
  pac.Draw();
  ghost.Draw();
 
}
