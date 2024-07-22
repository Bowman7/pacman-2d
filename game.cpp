#include"game.hpp"

Game::Game(){
  InitCoin();
}

Game::~Game(){

}
//time keep
bool Game::EventTriggered(double time){
  double currentTime = GetTime();
  if(currentTime -lastUpdatedTime >= time){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
  
}
//move to eat pacman
void Game::MoveToEat(){
    int gx = ghost.GetX();
    int gy = ghost.GetY();
    int px = ghostPath.x;
    int py = ghostPath.y;

    int diffX = px - gx;
    int diffY = py - gy;
    //printf(" gx : %d\n",gx);
    //printf(" gy : %d \n",gy);
    //printf(" px : %d\n",px);
    //printf(" py : %d \n",py);
    //printf(" diffx : %d\n",diffX);
    //printf(" diffY : %d \n",diffY);
    //east
    if(diffX >0 && diffY == 0 ){
      printf("ghost Move right \n");
      ghost.Move(3);
    }
    //west
    if(diffX <0 && diffY == 0 ){
      printf("ghost Move left \n");
      ghost.Move(4);
    }
    //north
    if(diffX == 0 && diffY<0){
      printf("ghost move north\n");
      ghost.Move(1);
    }
    //south
    if(diffX == 0 && diffY>0){
      printf("ghost move south\n");
      ghost.Move(2);
    }
}
//print final stack
void Game::PrintFinal(){
  printf("Final queue: \n");
  for(int i=0;i<finalStack.size();i++){
    printf(" index:[%d] posx:[%d] posy:[%d] \n",i,finalStack[i].x,finalStack[i].y);
  }
  printf("\n");
}
//print queue
void Game::PrintQueue(){
  printf("Queue: \n");
  for(int i=0;i<queue.size();i++){
    printf(" index:[%d] posx:[%d] posy:[%d] cost[%d] \n",i,queue[i].x,
	   queue[i].y,queue[i].cost);
  }
  printf("\n");
}
//sort queue
void Game::SortQueue(){
  int size = queue.size();
  
  for(int i=0;i<size-1;i++){
    for(int j=0;j<size-i-1;j++){
      if(queue[j].cost > queue[j+1].cost){
	Pos temp;
	temp = queue[j];
	queue[j] = queue[j+1];
	queue[j+1] =temp;
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
      SortQueue();
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
      SortQueue();
    
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
      SortQueue();
     
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
     SortQueue();
    
   }
  }
}
//for path finding
void Game::FindPath(int x, int y,int gx,int gy){ 
  if(abs(gx-x)+abs(gy-y) == 0){
    return;
  }
  //first push the pacman pos
  Pos val;
  val.x =x;
  val.y = y;
  val.heuristic = abs(gx-x)+abs(gy-y);
  val.pathcost = 1;
  val.cost = val.heuristic + val.pathcost;
  finalStack.push_back(val);
  //check NSEW and push into queue
  CheckPaths(val,gx,gy);
  //check for new top of queue
  if(!queue.empty()){
    Pos topQueue = queue[0];
    queue.erase(queue.begin());
    FindPath(topQueue.x,topQueue.y,gx,gy);
  }  
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
  //check if ghost reached wall
  if(ghost.GetX() == 39 && ghost.GetY() == 2){
    ghost.SetHuntMode();
  }
  //pacmove
  pac.MoveToDir();
  CheckCollision();
  EatCoin();
  
  ghost.MoveToDir();
  
  if(!queue.empty()){
    queue.clear();
  }
  //clear finalstack
  if(!finalStack.empty()){
    finalStack.clear();
  }
  if(ghost.GetMode()==0){
    FindPath(39,2,ghost.GetX(),ghost.GetY());
    int size = finalStack.size();
    ghostPath = finalStack[size-1];
  }
  if(ghost.GetMode()==1){
    FindPath(pac.GetX(),pac.GetY(),ghost.GetX(),ghost.GetY());
    int size = finalStack.size();
    ghostPath = finalStack[size-1];
  }
  //print path
  if(count<1){
    PrintQueue();
    PrintFinal();
    count++;
  }
  //ghost movement
  MoveToEat();
  
}
void Game::HandleInputs(){
  //n:1,S:2,E:3,W:4
  //north
  if(IsKeyPressed(KEY_W)){
    if(IsValidPath(pac.GetX(),pac.GetY()-1)){
      pac.Move(1);
      count--;
    }
  }
  //south
  if(IsKeyPressed(KEY_S)){
    if(IsValidPath(pac.GetX(),pac.GetY()+1)){
      pac.Move(2);
      count--;
    }
  }
  //east
  if(IsKeyPressed(KEY_D)){
    if(IsValidPath(pac.GetX()+1,pac.GetY())){
      pac.Move(3);
      count--;
    }
  }
  //west
  if(IsKeyPressed(KEY_A)){
    if(IsValidPath(pac.GetX()-1,pac.GetY())){
    pac.Move(4);
    count--;
    }
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
