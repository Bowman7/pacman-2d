#include"game.hpp"

Game::Game(){
  InitCoin();

  //red ghost init
  ghost.SetColor(0);//red
  ghost.SetX(38);
  ghost.SetY(38);

  //pink ghost init
  pinkGhost.SetColor(1);
  pinkGhost.SetX(2);
  pinkGhost.SetY(38);

  //blue ghost init
  blueGhost.SetColor(2);
  blueGhost.SetX(38);
  blueGhost.SetY(2);
  
  //orange ghost init
  orangeGhost.SetColor(3);
  orangeGhost.SetX(20);
  orangeGhost.SetY(20);
  
  //for packnight
  pac.SetX(2);
  pac.SetY(2);
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

//print final stack
void Game::PrintFinal(){
  printf("Final Stack: \n");
  for(int i=0;i<finalStack.size();i++){
    printf(" index:[%d] posx:[%d] posy:[%d] cost: %d\n",i,
	   finalStack[i].x,finalStack[i].y,finalStack[i].cost);
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
  printf("Sort queue \n");
  printf("Queue before sort\n");
  PrintQueue();
  int size = queue.size();
  for(int i=0;i<size;++i){
    for(int j=0;j<size-i-1;++j){
      if(queue[j].cost > queue[j+1].cost){
	Pos temp;
	temp = queue[j];
	queue[j] = queue[j+1];
	queue[j+1] =temp;
      }
    }
  }
  printf("Queue after sort");
  PrintQueue();
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
//check if it is alredy in finalstack
bool Game::InFinalStack(int x,int y){
  for(int i=0;i<finalStack.size();i++){
    if(finalStack[i].x == x && finalStack[i].y == y){
      return true;
    }
  }
  return false;
}
//check if it is already in queue
bool Game::InQueue(int x,int y){
  for(int i=0;i<queue.size();i++){
    if(queue[i].x == x && queue[i].y == y){
      return true;
    }
  }
  return false;
}
//check paths
void Game::CheckPaths(int x,int y,int gx,int gy){
  
  //for north
  int nx = x;
  int ny = y-1;
  if(IsValidPath(nx,ny)){
    Pos temp;
    temp.x = nx;
    temp.y = ny;
    int heu = abs(gx-nx)+abs(gy-ny);
    int cost = 1+ heu;
    temp.heuristic = heu;
    temp.pathcost = 1;
    temp.cost = cost;
    if(!InFinalStack(nx,ny) && !InQueue(nx,ny)){
      queue.push_back(temp);
    }
    
  }
  //for south
  int sx =x;
  int sy = y+1;
  if(IsValidPath(sx,sy)){
    Pos temp;
    temp.x = sx;
    temp.y = sy;
    int heu = abs(gx-sx)+abs(gy-sy);
    int cost = 1+ heu;
    temp.heuristic = heu;
    temp.pathcost = 1;
    temp.cost = cost;
    if(!InFinalStack(sx,sy) && !InQueue(sx,sy)){
      queue.push_back(temp);
    }
    
  }
  //for east
  int ex =x+1;
  int ey = y;
  if(IsValidPath(ex,ey)){
    Pos temp;
    temp.x = ex;
    temp.y = ey;
    int heu = abs(gx-ex)+abs(gy-ey);
    int cost = 1+ heu;
    temp.heuristic = heu;
    temp.pathcost = 1;
    temp.cost = cost;
    if(!InFinalStack(ex,ey) && !InQueue(ex,ey)){
      queue.push_back(temp);
    }
  }
  //for west
  int wx =x-1;
  int wy = y;
  if(IsValidPath(wx,wy)){
    Pos temp;
    temp.x = wx;
    temp.y = wy;
    int heu = abs(gx-wx)+abs(gy-wy);
    int cost = 1+ heu;
    temp.heuristic = heu;
    temp.pathcost = 1;
    temp.cost = cost;
    if(!InFinalStack(wx,wy) && !InQueue(wx,wy)){
      queue.push_back(temp);
    }
      
  }
  //sort
  if(queue.size()>1){
    SortQueue();
  }
}

//check if the diff between the new pos and old pos in finalstack is one
bool Game::IsOneDiff(int x,int y){
  int size = finalStack.size()-1;
  int fx = finalStack[size].x;
  int fy = finalStack[size].y;
  if(x-fx == 1 && fy-y ==0 ||//east
     x-fx == -1 && fy-y == 0||//west
     x-fx == 0 && y-fy == -1||//north
     x-fx == 0 && y-fy == 1//south
     ){
    return true;
  }
  return false;
}
//for path finding
void Game::FindPath(int x, int y,int gx,int gy){
  printf("PacDist : %d\n",pacDist);
  if(finalStack.size() == pacDist){
    printf("Path found \n");
    
    return;
  }
  //first push the pacman pos
  Pos val;
  val.x =x;
  val.y = y;
  int heu = abs(gx-x)+abs(gy-y);
  int cost = 1+ heu;
  val.heuristic = heu;
  val.pathcost = 1;
  val.cost = cost;
  if(finalStack.empty()){
    finalStack.push_back(val);
  }
  if(!finalStack.empty()){
    printf("Pos of ghost posx: %d posy: %d\n",gx,gy);
    printf("\nFinal stack before push\n");
    PrintFinal();
    //PrintQueue();
    if(IsOneDiff(val.x,val.y)){
      printf("One diff exist push!\n");
      finalStack.push_back(val);
    }
    printf("Final stack after push\n");
    PrintFinal();
  }
  //printf("Into queue\n");
  //check NSEW and push into queue
  CheckPaths(x,y,gx,gy);
  
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
  //for redghost
  if(maze.IsWalkable(ghost.GetX()-1,ghost.GetY()-1) ==2 ||
     maze.IsWalkable(ghost.GetX(),ghost.GetY()-1) == 2 ||
     maze.IsWalkable(ghost.GetX()-1,ghost.GetY()) == 2 ||
     maze.IsWalkable(ghost.GetX(),ghost.GetY()) == 2
     ){
    switch(ghost.GetDir()){
    case 0:
      ghost.RevertNorth();break;
    case 1:
      ghost.RevertSouth();break;
    case 2:
      ghost.RevertEast();break;
    case 3:
      ghost.RevertWest();break;
    }
  }
  //for pink ghost
  if(maze.IsWalkable(pinkGhost.GetX()-1,pinkGhost.GetY()-1) ==2 ||
     maze.IsWalkable(pinkGhost.GetX(),pinkGhost.GetY()-1) == 2 ||
     maze.IsWalkable(pinkGhost.GetX()-1,pinkGhost.GetY()) == 2 ||
     maze.IsWalkable(pinkGhost.GetX(),pinkGhost.GetY()) == 2
     ){
    switch(pinkGhost.GetDir()){
    case 0:
      pinkGhost.RevertNorth();break;
    case 1:
      pinkGhost.RevertSouth();break;
    case 2:
      pinkGhost.RevertEast();break;
    case 3:
      pinkGhost.RevertWest();break;
    }
  }
  //for blue ghost
  if(maze.IsWalkable(blueGhost.GetX()-1,blueGhost.GetY()-1) ==2 ||
     maze.IsWalkable(blueGhost.GetX(),blueGhost.GetY()-1) == 2 ||
     maze.IsWalkable(blueGhost.GetX()-1,blueGhost.GetY()) == 2 ||
     maze.IsWalkable(blueGhost.GetX(),blueGhost.GetY()) == 2
     ){
    switch(blueGhost.GetDir()){
    case 0:
      blueGhost.RevertNorth();break;
    case 1:
      blueGhost.RevertSouth();break;
    case 2:
      blueGhost.RevertEast();break;
    case 3:
      blueGhost.RevertWest();break;
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
//get rand num
int Game::GetRandomNum(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);
  int random = dist6(rng);
  return random;
}

//check is next dir is valid
bool Game::IsNextDirValid(int val,int ghostType){
  int valX;
  int valY;
  if(ghostType == 0){//for red ghost
    valX = ghost.GetX();
    valY = ghost.GetY();
  }else if(ghostType == 1){//for pink ghost
    valX = pinkGhost.GetX();
    valY = pinkGhost.GetY();
  }else if(ghostType == 2){//blue ghost
    valX = blueGhost.GetX();
    valY = blueGhost.GetY();
  }else if(ghostType == 3){//for orange ghost
    valX = orangeGhost.GetX();
    valY = orangeGhost.GetY();
  }
  //north
  if(val == 0){
    if(IsValidPath(valX,valY-1)){
      return true;
    }
  }
  //south
  if(val == 1){
    if(IsValidPath(valX,valY+1)){
      return true;
    }
  }
  //east
  if(val == 2){
    if(IsValidPath(valX+1,valY)){
      return true;
    }
  }
  //west
  if(val == 3){
    if(IsValidPath(valX-1,valY)){
      return true;
    }
  }
  return false;
}
//check bounce back dir
bool Game::NoBounceback(int val,int ghostType){
  int dir;
  if(ghostType == 0){//for red ghost
    dir = ghost.GetDir();
  }else if(ghostType == 1){//for pink ghost
    dir = pinkGhost.GetDir();
  }else if(ghostType == 2){//for blue ghost
    dir = blueGhost.GetDir();
  }else if(ghostType == 3){//for orange ghost
    dir = orangeGhost.GetDir();
  }
  //north
  if(dir==0 && val==1){
    return false;
  }
  if(dir==1 && val==0){
    return false;
  }
  if(dir==2 && val == 3){
    return false;
  }
  if(dir==3 && val==2){
    return false;
  }
  return true;
  
}
//ret for red ghost
int Game::GetNum(int ghostType){
  int num;
  num = GetRandomNum();
  if(NoBounceback(num,ghostType)){
    //printf("No bounce back\n");
    //check if valid path
    if(IsNextDirValid(num,ghostType)){
      return num;
    }
  }
  
  return GetNum(ghostType);
}
//ghost hits wall
bool Game::GhostHitWall(){
  //for red ghost
  switch(ghost.GetDir()){
  case 0:
    {//north
      if(!IsValidPath(ghost.GetX(),ghost.GetY()-1)){
	//printf("Hits north wall\n");
	return true;
      }
    }break;
  case 1:
    {//south
      if(!IsValidPath(ghost.GetX(),ghost.GetY()+1)){
	//printf("Hits south wall\n");
	return true;
      }
    }break;
  case 2:
    {//east
      if(!IsValidPath(ghost.GetX()+1,ghost.GetY())){
	//printf("Hits east wall\n");
	return true;
      }
    }break;
  case 3:
    {//west
      if(!IsValidPath(ghost.GetX()-1,ghost.GetY())){
	//printf("Hits west wall\n");
	return true;
      }
    }break;
  }
  
  return false;
}
//pink ghost hits wall check
bool Game::pinkGhostHitWall(){  
  //for pink ghost
  switch(pinkGhost.GetDir()){
  case 0:
    {//north
      if(!IsValidPath(pinkGhost.GetX(),pinkGhost.GetY()-1)){
	//printf("Hits north wall\n");
	return true;
      }
    }break;
  case 1:
    {//south
      if(!IsValidPath(pinkGhost.GetX(),pinkGhost.GetY()+1)){
	//printf("Hits south wall\n");
	return true;
      }
    }break;
  case 2:
    {//east
      if(!IsValidPath(pinkGhost.GetX()+1,pinkGhost.GetY())){
	//printf("Hits east wall\n");
	return true;
      }
    }break;
  case 3:
    {//west
      if(!IsValidPath(pinkGhost.GetX()-1,pinkGhost.GetY())){
	//printf("Hits west wall\n");
	return true;
      }
    }break;
  default:
    return false;
  }
  return false;
}
//chec for blue ghost hitting wall
bool Game::blueGhostHitWall(){  
  //for blue ghost
  switch(blueGhost.GetDir()){
  case 0:
    {//north
      if(!IsValidPath(blueGhost.GetX(),blueGhost.GetY()-1)){
	//printf("Hits north wall\n");
	return true;
      }
    }break;
  case 1:
    {//south
      if(!IsValidPath(blueGhost.GetX(),blueGhost.GetY()+1)){
	//printf("Hits south wall\n");
	return true;
      }
    }break;
  case 2:
    {//east
      if(!IsValidPath(blueGhost.GetX()+1,blueGhost.GetY())){
	//printf("Hits east wall\n");
	return true;
      }
    }break;
  case 3:
    {//west
      if(!IsValidPath(blueGhost.GetX()-1,blueGhost.GetY())){
	//printf("Hits west wall\n");
	return true;
      }
    }break;
  default:
    return false;
  }
  return false;
}
//check for orange ghost hitting wall
bool Game::orangeGhostHitWall(){  
  //for orange ghost
  switch(orangeGhost.GetDir()){
  case 0:
    {//north
      if(!IsValidPath(orangeGhost.GetX(),orangeGhost.GetY()-1)){
	//printf("Hits north wall\n");
	return true;
      }
    }break;
  case 1:
    {//south
      if(!IsValidPath(orangeGhost.GetX(),orangeGhost.GetY()+1)){
	//printf("Hits south wall\n");
	return true;
      }
    }break;
  case 2:
    {//east
      if(!IsValidPath(orangeGhost.GetX()+1,orangeGhost.GetY())){
	//printf("Hits east wall\n");
	return true;
      }
    }break;
  case 3:
    {//west
      if(!IsValidPath(orangeGhost.GetX()-1,orangeGhost.GetY())){
	//printf("Hits west wall\n");
	return true;
      }
    }break;
  default:
    return false;
  }
  return false;
}
//roam red ghost
void Game::RoamGhost(){
  int num = GetNum(0);//0 for red ghost
  ghost.Move(num);
  
}
//roam pink ghost
void Game::RoamPinkGhost(){
  int pnum = GetNum(1);//1 for pink ghost
  pinkGhost.Move(pnum);
}
//roam blue ghost
void Game::RoamBlueGhost(){
  int bnum = GetNum(2);//for 2 for blue ghost
  blueGhost.Move(bnum);
}
//roam orange ghost
void Game::RoamOrangeGhost(){//3 for orange ghost
  int onum = GetNum(3);
  orangeGhost.Move(onum);
}

//ghost scatter mode
void Game::GhostScatter(){
  //for red ghost
  if(GhostHitWall()){
    //printf("\nGhost hit wall\n");
    RoamGhost();
  }
  //for pink ghost
  if(pinkGhostHitWall()){
    RoamPinkGhost();
  }
  //for blue ghost
  if(blueGhostHitWall()){
    RoamBlueGhost();
  }
  
  //move to pointed directions
  ghost.MoveToDir();
  pinkGhost.MoveToDir();
  blueGhost.MoveToDir();
  
}
//dscatter only for orange ghost
void Game::OrangeScatter(){
  //for orange ghost
  if(orangeGhostHitWall()){
    RoamOrangeGhost();
  }

  orangeGhost.MoveToDir();
}
//is pacmna near boundry
bool Game::IsPacNear(){
  int diffX = abs(pac.GetX() - ghost.GetX());
  int diffY = abs(pac.GetY() - ghost.GetY());
  if(diffX<=20 && diffY<=20){
    return true;
  }
  return false;
}
//move to eat
void Game::MoveToEat(){
  /*
  int size = finalStack.size()-1;
  int x = finalStack[size].x - ghost.GetX();
  int y = finalStack[size].y - ghost.GetY();

  if(x==0 && y<1){//north
    ghost.Move(0);
    return;
  }
  if(x==0 && y>1){//south
    ghost.Move(1);
    return;
  }
  if(x>1 && y==0){//east
    ghost.Move(2);
    return;
  }
  if(x<1 && y==0){//west
    ghost.Move(3);
    return;
  }
  */
  int size = finalStack.size()-1;
  int x = finalStack[size].x;
  int y = finalStack[size].y;
  if(IsValidPath(x,y)){
    ghost.SetX(x);
    ghost.SetY(y);
    //printf("Moved ghost to eat posx: %d  posy:%d \n",x,y);
    finalStack.pop_back();
  }
}
//hunt pacman
void Game::HuntPacman(){
  FindPath(pac.GetX(),pac.GetY(),ghost.GetX(),ghost.GetY());
}

//check last Mode change
bool Game::ModeTriggered(double time){
  double currentTime = GetTime();
  if(currentTime-ghostModeChange >= time){
    ghostModeChange = currentTime;
    return true;
  }
  return false;
}
//swap core val
void Game::listSwap(Node &n1,Node &n2){
  Node temp;
  temp = n1;
  n1 = n2;
  n2 = temp;
}
//sort list
void Game::sortList(){
  int size = list.size();
  for(int i=0;i<size;++i){
    for(int j=0;j<size-i-1;++j){
      Node *n1 = list[j];
      Node *n2 = list[j+1];
      if(n1->globalVal > n2->globalVal){
	Node *temp;
	temp = list[j];
	list[j] = list[j+1];
	list[j+1] = temp;
      }
    }
  }
}
//init path tile for red ghost
void Game::InitPathTile(){
  //init path tile
  //printf("\nINIT PATH TILE \n");
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      tile[i][j].x =i;
      tile[i][j].y = j;
      tile[i][j].dir = 9;//5 by def
      tile[i][j].visited = 0;
    }
  }
}
//init path tile for pink ghost
void Game::PinkInitPathTile(){
  //init path tile
  //printf("\nINIT PATH TILE \n");
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      pinkTile[i][j].x =i;
      pinkTile[i][j].y = j;
      pinkTile[i][j].dir = 9;//5 by def
      pinkTile[i][j].visited = false;
    }
  }
}
//init path tile for blue ghost
void Game::BlueInitPathTile(){
  //init path tile
  //printf("\nINIT PATH TILE \n");
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      blueTile[i][j].x =i;
      blueTile[i][j].y = j;
      blueTile[i][j].dir = 9;//5 by def
      blueTile[i][j].visited = false;
    }
  }
}
//print list
void Game::printList(){
  int size = list.size();
  for(int i=0;i<size;i++){
    printf(" x: %d y: %d local: %f global: %f dir:%d visited : %d\n",
	   list[i]->x,list[i]->y,list[i]->localVal,list[i]->globalVal,
	   list[i]->dir,list[i]->visited);
  }
}


float heuristic(int ax,int ay , int bx,int by){
  float val = (bx-ax)*(bx-ax)+(by-ay)*(by-ay);
  return val;
}

//check fours steps in east or west
int Game::PinkEastWest(){
  int jX = pac.GetX();
  int jY = pac.GetY();
  int dir = pac.GetDir();
  if(dir == 2){//east
    if(IsValidPath(jX+2,jY)){
      if(IsValidPath(jX+4,jY)){
	return jX+4;
      }
      return jX+2;
    }
    return jX;
  }else if(dir == 3){//west
    if(IsValidPath(jX-2,jY)){
      if(IsValidPath(jX-4,jY)){
	return jX-4;
      }
      return jX-2;
    }
    return jX;
  }

  return jX;
}
//check four steps for east west for blue ghost
int Game::BlueEastWest(){
  int jX = pac.GetX();
  int jY = pac.GetY();
  int dir = pac.GetDir();
  if(dir == 2){//east
    if(IsValidPath(jX-2,jY)){
      if(IsValidPath(jX-4,jY)){
	return jX-4;
      }
      return jX-2;
    }
    return jX;
  }else if(dir == 3){//west
    if(IsValidPath(jX+2,jY)){
      if(IsValidPath(jX+4,jY)){
	return jX+4;
      }
      return jX+2;
    }
    return jX;
  }

  return jX;
}
//check three steps in north or south
int Game::PinkNorthSouth(){
  int jX = pac.GetX();
  int jY = pac.GetY();
  int dir = pac.GetDir();
  if(dir == 0){//north
    if(IsValidPath(jX,jY-2)){
      if(IsValidPath(jX,jY-4)){
	return jY-4;
      }
      return jY-2;
    }
    return jY;
  }else if(dir == 1){//south
    if(IsValidPath(jX,jY+2)){
      if(IsValidPath(jX,jY+4)){
	return jY+4;
      }
      return jY+2;
    }
    return jY;
  }

  return jY;
}
//check  four step north south for blue ghost
int Game::BlueNorthSouth(){
  int jX = pac.GetX();
  int jY = pac.GetY();
  int dir = pac.GetDir();
  if(dir == 0){//north
    if(IsValidPath(jX,jY+2)){
      if(IsValidPath(jX,jY+4)){
	return jY+4;
      }
      return jY+2;
    }
    return jY;
  }else if(dir == 1){//south
    if(IsValidPath(jX,jY-2)){
      if(IsValidPath(jX,jY-4)){
	return jY-4;
      }
      return jY-2;
    }
    return jY;
  }

  return jY;
}
//modified a* for all ghosts
void Game::modAStar(int ghostType){
  //printf("ASTAR\n");
  //init list
  if(!list.empty()){
    list.clear();
  }
  
  //init nodes
  Node *nodeEnd = new Node;
  int ghostPosX;
  int ghostPosY;
  
  
  if(ghostType == 0){//for red ghost
    nodeEnd->x = ghost.GetX();
    nodeEnd->y = ghost.GetY();
    ghostPosX = ghost.GetX();
    ghostPosY = ghost.GetY();
    
  }else if(ghostType == 1){//for pink ghost
    //check for four forward 
    int posX = pinkGhost.GetX();
    int posY = pinkGhost.GetY();
    nodeEnd->x = posX;
    nodeEnd->y = posY;
    ghostPosX  = pinkGhost.GetX();
    ghostPosY  = pinkGhost.GetY();
    
  }else if(ghostType == 2){//for blue ghost
    //check for four forward 
    int posX = blueGhost.GetX();
    int posY = blueGhost.GetY();
    nodeEnd->x = posX;
    nodeEnd->y = posY;
    ghostPosX  = blueGhost.GetX();
    ghostPosY  = blueGhost.GetY();
  }
  
  Node *nodeStart = new Node;
  int startPosX;
  int startPosY;
  if(ghostType == 0){//for red ghost
    nodeStart->x = pac.GetX();
    nodeStart->y = pac.GetY();
    startPosX = pac.GetX();
    startPosY = pac.GetY();
    
  }else if(ghostType == 1){//for pink ghost
    int jumpPosX = pac.GetX();
    int jumpPosY = pac.GetY();
    int dir = pac.GetDir();
    if(dir == 2 || dir == 3){
      jumpPosX = PinkEastWest();
    }else if(dir == 0 || dir == 1){
      jumpPosY = PinkNorthSouth();
    }
    nodeStart->x = jumpPosX;
    nodeStart->y = jumpPosY;
    startPosX = jumpPosX;
    startPosY = jumpPosY;
    
  }else if(ghostType == 2){//for blue
    int jumpPosX = pac.GetX();
    int jumpPosY = pac.GetY();
    int dir = pac.GetDir();
    if(dir == 2 || dir == 3){
      jumpPosX = BlueEastWest();
    }else if(dir == 0 || dir == 1){
      jumpPosY = BlueNorthSouth();
    }
    nodeStart->x = jumpPosX;
    nodeStart->y = jumpPosY;
    startPosX = jumpPosX;
    startPosY = jumpPosY;
  }
  
  //set the first pointer to the currentNode
  Node *nodeCurrent = nodeStart;
  nodeCurrent->localVal = 0.0f;
  nodeCurrent->globalVal = heuristic(startPosX,startPosY,ghostPosX,ghostPosY);
  
  list.push_back(nodeStart);
  
  int  totalIter = abs(ghostPosX-startPosX)+abs(ghostPosY-startPosY);
  //main while loop
  while(!list.empty() && !starReached){
    if(list[0]->x==nodeEnd->x && list[0]->y==nodeEnd->y ){
      starReached = true;
    }
    if(iter<totalIter){
      //printf("\n\nIteration : %d\n\n",iter);
    }
    //sort
    if(list.size()>1){
      sortList();
    }
    if(iter<totalIter){
      //printf("list before sort:\n");
      //printList();
      //printf("list after sort\n");
      //printList();
    }
    
    //pop front
    while(!list.empty() && list[0]->visited == true){
      list.erase(list.begin());
      if(iter<totalIter){
	//printf("list after erase:\n");
	//printList();
      }
    }
    //if empty break
    if(list.empty()){
      break;
    }

    nodeCurrent = list[0];
    nodeCurrent->visited = true;
    int x = list[0]->x;
    int y = list[0]->y;
    if(ghostType == 0){
      tile[x][y].visited = true;
    }else if(ghostType == 1){
      if(wcount<1){
	//printf("seg fault area: x:%d y:%d \n",x,y);
      }
      pinkTile[x][y].visited = true;
    }else if(ghostType == 2){//blue ghost
      blueTile[x][y].visited = true;
    }
    if(iter<totalIter){
      //printf("After setting first list ele visited:\n");
      //printList();
      //printf("tile[%d][%d] visited = %d\n",x,y,tile[x][y].visited);
    }

    //check for neighbours and point the currentNode to it
    
    //north neighbour
    Node *nNeighbour =  new Node;
    int nx = nodeCurrent->x;
    int ny = nodeCurrent->y-1;
    bool ntileVisited;//change acc to ghost type
    if(ghostType == 0){
      ntileVisited = tile[nx][ny].visited; 
    }else if(ghostType == 1){
      ntileVisited = pinkTile[nx][ny].visited;
    }else if(ghostType == 2){
      ntileVisited = blueTile[nx][ny].visited;
    }
    if(IsValidPath(nx,ny) && !ntileVisited){
      
      nNeighbour->x= nx;
      nNeighbour->y = ny;
      nNeighbour->dir = 0;//north
      
      nodeCurrent->vecNeighbours.push_back(nNeighbour);
    }

    //south Neighbour
    Node *sNeighbour =  new Node;
    int sx = nodeCurrent->x;
    int sy = nodeCurrent->y+1;
    bool stileVisited;//change acc to ghost type
    if(ghostType == 0){
      stileVisited = tile[sx][sy].visited; 
    }else if(ghostType == 1){
      stileVisited = pinkTile[sx][sy].visited;
    }else if(ghostType == 2){
      stileVisited = blueTile[sx][sy].visited;
    }
    if(IsValidPath(sx,sy) && !stileVisited){
      
      sNeighbour->x= sx;
      sNeighbour->y = sy;
      sNeighbour->dir = 1;//south
      
      nodeCurrent->vecNeighbours.push_back(sNeighbour);
    }
   
    //east neighbour
    Node *eNeighbour =  new Node;
    int ex = nodeCurrent->x+1;
    int ey = nodeCurrent->y;
    bool etileVisited;//change acc to ghost type
    if(ghostType == 0){
      etileVisited = tile[ex][ey].visited; 
    }else if(ghostType == 1){
      etileVisited = pinkTile[ex][ey].visited;
    }else if(ghostType == 2){
      etileVisited = blueTile[ex][ey].visited;
    }
    if(IsValidPath(ex,ey) && !etileVisited){
      
      eNeighbour->x= ex;
      eNeighbour->y = ey;
      eNeighbour->dir = 2;//east
      eNeighbour->visited = false;
      
      nodeCurrent->vecNeighbours.push_back(eNeighbour);

      if(iter<totalIter){
	//printf("East side neighbour present!: \n");
	//printList();

      }
    }
    
    //west neighbour
    Node *wNeighbour = new Node;
    int wx = nodeCurrent->x-1;
    int wy = nodeCurrent->y;
    bool wtileVisited;//change acc to ghost type
    if(ghostType == 0){
      wtileVisited = tile[wx][wy].visited; 
    }else if(ghostType == 1){
      wtileVisited = pinkTile[wx][wy].visited;
    }else if(ghostType == 2){
      wtileVisited = blueTile[wx][wy].visited;
    }
    if(IsValidPath(wx,wy) && !wtileVisited){
      
      wNeighbour->x = wx;
      wNeighbour->y = wy;
      wNeighbour->dir = 3;//west
      wNeighbour->visited = false;
      
      nodeCurrent->vecNeighbours.push_back(wNeighbour);
      
      if(iter<totalIter){
	//printf("West  side neighbour present!: \n");
	//printList();	
      }
    }
    
    
    //iterate through the neighbours
    int size = nodeCurrent->vecNeighbours.size();
    std::vector<Node*> nodeNeighbour;
    //push all current neighbours into new nodeNeighbour
    for(int i=0;i<size;i++){
      nodeNeighbour.push_back(nodeCurrent->vecNeighbours[i]);
    }
    if(iter<totalIter){
      //printf("print neihgbours before checking and pushing:\n");
      int s = nodeNeighbour.size();
      for(int i=0;i<s;i++){
	/*printf(" x: %d y: %d local: %f global: %f dir:%d visited: %d tile[%d][%d]visit: %d\n",
	       nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeNeighbour[i]->localVal,
	       nodeNeighbour[i]->globalVal,nodeNeighbour[i]->dir,nodeNeighbour[i]->visited,
	       x,y,tile[x][y].visited);
	*/
      }
    }
    //check all neighbours
    for(int i=0;i<size;i++){
      if(!nodeNeighbour[i]->visited){
	list.push_back(nodeNeighbour[i]);
	if(iter<totalIter){
	  //printf("list after pusing neighbour\n");
	  //printList();
	}
      }
      
      //check cur local with neighbour to change neighbours local
      float possiblyLowerLocal = nodeCurrent->localVal + 1;
      if(iter<totalIter){
	//printf("possible lower local value to check: %f\n",possiblyLowerLocal);
      }
      
      if(possiblyLowerLocal < nodeNeighbour[i]->localVal){
	
	
	//check dir and set acc
	if(nodeNeighbour[i]->dir == 0){//if north parent is south
	  
	  nodeNeighbour[i]->dir = 1;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  if(ghostType == 0){
	    tile[x][y].dir = dir;
	  }else if(ghostType == 1){
	    pinkTile[x][y].dir = dir;
	  }else if(ghostType == 2){
	    blueTile[x][y].dir = dir;
	  }
	  
	}else if(nodeNeighbour[i]->dir==1){//if south parent is north
	  
	  nodeNeighbour[i]->dir = 0;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  if(ghostType == 0){
	    tile[x][y].dir = dir;
	  }else if(ghostType == 1){
	    pinkTile[x][y].dir = dir;
	  }else if(ghostType == 2){
	    blueTile[x][y].dir = dir;
	  }
	  
	}else if(nodeNeighbour[i]->dir ==2){//if east parent is west
	  
	  nodeNeighbour[i]->dir = 3;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  if(ghostType == 0){
	    tile[x][y].dir = dir;
	  }else if(ghostType == 1){
	    pinkTile[x][y].dir = dir;
	  }else if(ghostType == 2){
	    blueTile[x][y].dir = dir;
	  }
	 
	}else if(nodeNeighbour[i]->dir == 3){//if west parent is east
	  
	  nodeNeighbour[i]->dir = 2;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir =  nodeNeighbour[i]->dir;
	  if(ghostType == 0){
	    tile[x][y].dir = dir;
	  }else if(ghostType == 1){
	    pinkTile[x][y].dir = dir;
	  }else if(ghostType == 2){
	    blueTile[x][y].dir = dir;
	  }
	}
	

	nodeNeighbour[i]->localVal = possiblyLowerLocal;

	if(iter<totalIter){
	  //printf("neighbour local val:%f\n",nodeNeighbour[i]->localVal);
	}
	//setting the global val
	float val = heuristic(nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeEnd->x,nodeEnd->y);

	if(iter<totalIter){
	  //printf("new gobal val of neighbour: %f\n",val);
	}
	nodeNeighbour[i]->globalVal = nodeNeighbour[i]->localVal+val;
	
	if(iter<totalIter){
	  //printf("local val is lower than neighbour ,update neihghboru val\n");
	  //printf("neighbour after update\n");
	  /*printf(" x: %d y: %d local: %f global: %f dir:%d visited : %d\n",
		 nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeNeighbour[i]->localVal,
		 nodeNeighbour[i]->globalVal,nodeNeighbour[i]->dir,nodeNeighbour[i]->visited);
	  */
	  //printf("list after updating neighbour\n");
	  //printList();
	}
      } 
    }
    iter++;
  }
}

//WORKING ASTAR FUNC
void Game::SolveAStar(){
  printf("ASTAR\n");
  //init list
  if(!list.empty()){
    list.clear();
  }

  //init nodes
  Node *nodeEnd = new Node;
  nodeEnd->x = ghost.GetX();
  nodeEnd->y = ghost.GetY();
  
  Node *nodeStart = new Node;
  nodeStart->x = pac.GetX();
  nodeStart->y = pac.GetY();
  
  //set the first pointer to the currentNode
  Node *nodeCurrent = nodeStart;
  nodeCurrent->localVal = 0.0f;
  nodeCurrent->globalVal = heuristic(pac.GetX(),pac.GetY(),ghost.GetX(),ghost.GetY());
  
  list.push_back(nodeStart);
  
  int  totalIter = abs(ghost.GetX()-pac.GetX())+abs(ghost.GetY()-pac.GetY());
  //main while loop
  while(!list.empty() && !starReached){
    if(list[0]->x==nodeEnd->x && list[0]->y==nodeEnd->y ){
      starReached = true;
    }
    if(iter<totalIter){
      printf("\n\nIteration : %d\n\n",iter);
    }
    //sort
    if(list.size()>1){
      sortList();
    }
    if(iter<totalIter){
      printf("list before sort:\n");
      printList();
      printf("list after sort\n");
      printList();
    }
    
    //pop front
    while(!list.empty() && list[0]->visited == true){
      list.erase(list.begin());
      if(iter<totalIter){
	printf("list after erase:\n");
	printList();
      }
    }
    //if empty break
    if(list.empty()){
      break;
    }

    nodeCurrent = list[0];
    nodeCurrent->visited = true;
    int x = list[0]->x;
    int y = list[0]->y;
    tile[x][y].visited = true;
    if(iter<totalIter){
      printf("After setting first list ele visited:\n");
      printList();
      printf("tile[%d][%d] visited = %d\n",x,y,tile[x][y].visited);
    }

    //check for neighbours and point the currentNode to it
    
    //north neighbour
    Node *nNeighbour =  new Node;
    int nx = nodeCurrent->x;
    int ny = nodeCurrent->y-1;
    if(IsValidPath(nx,ny) && !tile[nx][ny].visited){
      
      nNeighbour->x= nx;
      nNeighbour->y = ny;
      nNeighbour->dir = 0;//north
      
      nodeCurrent->vecNeighbours.push_back(nNeighbour);
    }

    //south Neighbour
    Node *sNeighbour =  new Node;
    int sx = nodeCurrent->x;
    int sy = nodeCurrent->y+1;
    if(IsValidPath(sx,sy) && !tile[sx][sy].visited){
      
      sNeighbour->x= sx;
      sNeighbour->y = sy;
      sNeighbour->dir = 1;//south
      
      nodeCurrent->vecNeighbours.push_back(sNeighbour);
    }
   
    //east neighbour
    Node *eNeighbour =  new Node;
    int ex = nodeCurrent->x+1;
    int ey = nodeCurrent->y;
    if(IsValidPath(ex,ey) && !tile[ex][ey].visited){
      
      eNeighbour->x= ex;
      eNeighbour->y = ey;
      eNeighbour->dir = 2;//east
      eNeighbour->visited = false;
      
      nodeCurrent->vecNeighbours.push_back(eNeighbour);

      if(iter<totalIter){
	printf("East side neighbour present!: \n");
	printList();

      }
    }
    
    //west neighbour
    Node *wNeighbour = new Node;
    int wx = nodeCurrent->x-1;
    int wy = nodeCurrent->y;
    if(IsValidPath(wx,wy) && !tile[wx][wy].visited){
      
      wNeighbour->x = wx;
      wNeighbour->y = wy;
      wNeighbour->dir = 3;//west
      wNeighbour->visited = false;
      
      nodeCurrent->vecNeighbours.push_back(wNeighbour);
      
      if(iter<totalIter){
	printf("West  side neighbour present!: \n");
	printList();	
      }
    }
    
    
    //iterate through the neighbours
    int size = nodeCurrent->vecNeighbours.size();
    std::vector<Node*> nodeNeighbour;
    //push all current neighbours into new nodeNeighbour
    for(int i=0;i<size;i++){
      nodeNeighbour.push_back(nodeCurrent->vecNeighbours[i]);
    }
    if(iter<totalIter){
      printf("print neihgbours before checking and pushing:\n");
      int s = nodeNeighbour.size();
      for(int i=0;i<s;i++){
	printf(" x: %d y: %d local: %f global: %f dir:%d visited: %d tile[%d][%d]visit: %d\n",
	       nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeNeighbour[i]->localVal,
	       nodeNeighbour[i]->globalVal,nodeNeighbour[i]->dir,nodeNeighbour[i]->visited,
	       x,y,tile[x][y].visited);
      }
    }
    //check all neighbours
    for(int i=0;i<size;i++){
      if(!nodeNeighbour[i]->visited){
	list.push_back(nodeNeighbour[i]);
	if(iter<totalIter){
	  printf("list after pusing neighbour\n");
	  printList();
	}
      }
      
      //check cur local with neighbour to change neighbours local
      float possiblyLowerLocal = nodeCurrent->localVal + 1;
      if(iter<totalIter){
	printf("possible lower local value to check: %f\n",possiblyLowerLocal);
      }
      
      if(possiblyLowerLocal < nodeNeighbour[i]->localVal){
	
	
	//check dir and set acc
	if(nodeNeighbour[i]->dir == 0){//if north parent is south
	  
	  nodeNeighbour[i]->dir = 1;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  tile[x][y].dir = dir;
	  
	}else if(nodeNeighbour[i]->dir==1){//if south parent is north
	  
	  nodeNeighbour[i]->dir = 0;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  tile[x][y].dir = dir;
	  
	}else if(nodeNeighbour[i]->dir ==2){//if east parent is west
	  
	  nodeNeighbour[i]->dir = 3;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir = nodeNeighbour[i]->dir;
	  tile[x][y].dir = dir;
	 
	}else if(nodeNeighbour[i]->dir == 3){//if west parent is east
	  
	  nodeNeighbour[i]->dir = 2;
	  nodeNeighbour[i]->visited = false;
	  int x = nodeNeighbour[i]->x;
	  int y = nodeNeighbour[i]->y;
	  int dir =  nodeNeighbour[i]->dir;
	  tile[x][y].dir = dir;
	}
	

	nodeNeighbour[i]->localVal = possiblyLowerLocal;
	if(iter<totalIter){
	  printf("neighbour local val:%f\n",nodeNeighbour[i]->localVal);
	}
	//setting the global val
	float val = heuristic(nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeEnd->x,nodeEnd->y);
	if(iter<totalIter){
	  printf("new gobal val of neighbour: %f\n",val);
	}
	nodeNeighbour[i]->globalVal = nodeNeighbour[i]->localVal+val;
	
	if(iter<totalIter){
	  printf("local val is lower than neighbour ,update neihghboru val\n");
	  printf("neighbour after update\n");
	  printf(" x: %d y: %d local: %f global: %f dir:%d visited : %d\n",
		 nodeNeighbour[i]->x,nodeNeighbour[i]->y,nodeNeighbour[i]->localVal,
		 nodeNeighbour[i]->globalVal,nodeNeighbour[i]->dir,nodeNeighbour[i]->visited);

	  printf("list after updating neighbour\n");
	  printList();
	}
      } 
    }
    iter++;
  }
}
//print tile path
void Game::printTile(){
  printf("Tile path:\n");
  //print tile
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      printf(" %d ",tile[j][i].dir);
    }
    printf("\n");
  }
}
//init move dir before scatter
void Game::InitMoveDirBeforeScatter(){
  //for red ghost
  //nsew
  int num = GetRandomNum();
  switch(num){
  case 0:{
    if(IsValidPath(ghost.GetX(),ghost.GetY()-1)){
      ghost.Move(0);
      return;
    }
  }break;
  case 1:{
    if(IsValidPath(ghost.GetX(),ghost.GetY()+1)){
      ghost.Move(1);
      return;
    }
  }break;
  case 2:{
    if(IsValidPath(ghost.GetX()+1,ghost.GetY())){
      ghost.Move(2);
      return;
    }
  }break;
  case 3:{
    if(IsValidPath(ghost.GetX()-1,ghost.GetY())){
      ghost.Move(3);
      return;
    }
  }break;
  default:
    break;
  }
  InitMoveDirBeforeScatter();
}
//init move dir for pink
void Game::InitPinkMoveDir(){
  //for red ghost
  //nsew
  int pnum = GetRandomNum();
  switch(pnum){
  case 0:{
    if(IsValidPath(pinkGhost.GetX(),pinkGhost.GetY()-1)){
      pinkGhost.Move(0);
      return;
    }
  }break;
  case 1:{
    if(IsValidPath(pinkGhost.GetX(),pinkGhost.GetY()+1)){
      pinkGhost.Move(1);
      return;
    }
  }break;
  case 2:{
    if(IsValidPath(pinkGhost.GetX()+1,pinkGhost.GetY())){
      pinkGhost.Move(2);
      return;
    }
  }break;
  case 3:{
    if(IsValidPath(pinkGhost.GetX()-1,pinkGhost.GetY())){
      pinkGhost.Move(3);
      return;
    }
  }break;
  default:
    break;
  }
  InitPinkMoveDir();
}
//init move dir for blue
void Game::InitBlueMoveDir(){
  //for blue ghost
  //nsew
  int bnum = GetRandomNum();
  switch(bnum){
  case 0:{
    if(IsValidPath(blueGhost.GetX(),blueGhost.GetY()-1)){
      blueGhost.Move(0);
      return;
    }
  }break;
  case 1:{
    if(IsValidPath(blueGhost.GetX(),blueGhost.GetY()+1)){
      blueGhost.Move(1);
      return;
    }
  }break;
  case 2:{
    if(IsValidPath(blueGhost.GetX()+1,blueGhost.GetY())){
      blueGhost.Move(2);
      return;
    }
  }break;
  case 3:{
    if(IsValidPath(blueGhost.GetX()-1,blueGhost.GetY())){
      blueGhost.Move(3);
      return;
    }
  }break;
  default:
    break;
  }
  InitBlueMoveDir();
}
//init orange move dir
void Game::InitOrangeMoveDir(){
  //for orange ghost
  //nsew
  int onum = GetRandomNum();
  switch(onum){
  case 0:{
    if(IsValidPath(orangeGhost.GetX(),orangeGhost.GetY()-1)){
      orangeGhost.Move(0);
      return;
    }
  }break;
  case 1:{
    if(IsValidPath(orangeGhost.GetX(),orangeGhost.GetY()+1)){
      orangeGhost.Move(1);
      return;
    }
  }break;
  case 2:{
    if(IsValidPath(orangeGhost.GetX()+1,orangeGhost.GetY())){
      orangeGhost.Move(2);
      return;
    }
  }break;
  case 3:{
    if(IsValidPath(orangeGhost.GetX()-1,orangeGhost.GetY())){
      orangeGhost.Move(3);
      return;
    }
  }break;
  default:
    break;
  }
  InitOrangeMoveDir();
}
//conditions for red ghost move seq
void Game::RedMoveSeq(){
  if(rcount<1){
    rFinalTileX = pac.GetX();
    rFinalTileY = pac.GetY();
    rcount++;
  }
  //check if rached last tile
  if(ghost.GetX()==rFinalTileX && ghost.GetY()==rFinalTileY){
    rReachedLastTile = true;
    rcount--;
  }
  if(rReachedLastTile){
    rPathFound = false;
    starReached = false;
  }
  if(!rPathFound){
    InitPathTile();
    //printf("Tile before A star\n");
    //printTile();
    
    //SolveAStar();
    modAStar(0);//0 :red ghost
    
    //printf("Tile After A star\n");
    //printTile();
    rPathFound = true;
  }
  
  if(rPathFound){  
    int x  =ghost.GetX();
    int y = ghost.GetY();
    int dir = tile[x][y].dir;
    ghost.Move(dir);
    ghost.MoveToDir();
  }
}
//pink move sequence
void Game::PinkMoveSeq(){
  if(pcount<1){
    pFinalTileX = pac.GetX();
    pFinalTileY = pac.GetY();
    pcount++;
  }
  //check if rached last tile
  if(pinkGhost.GetX()==pFinalTileX && pinkGhost.GetY()==pFinalTileY){
    pReachedLastTile = true;
    pcount--;
  }
  if(pReachedLastTile){
    pPathFound = false;
    starReached = false;
  }
  if(!pPathFound){
    PinkInitPathTile();
    //Before A star
    //printTile();
    
    //SolveAStar();
    modAStar(1);//1 :pink ghost
    
    //printf("Tile After A star\n");
    //printTile();
    pPathFound = true;
  }
  
  if(pPathFound){  
    int x  = pinkGhost.GetX();
    int y =  pinkGhost.GetY();
    int dir = pinkTile[x][y].dir;
    pinkGhost.Move(dir);
    pinkGhost.MoveToDir();
  }
}
//move sequence for blue ghost
void Game::BlueMoveSeq(){
  if(bcount<1){
    bFinalTileX = pac.GetX();
    bFinalTileY = pac.GetY();
    bcount++;
  }
  //check if rached last tile
  if(blueGhost.GetX()==bFinalTileX && blueGhost.GetY()==bFinalTileY){
    bReachedLastTile = true;
    bcount--;
  }
  if(bReachedLastTile){
    bPathFound = false;
    starReached = false;
  }
  if(!bPathFound){
    BlueInitPathTile();
    //Before A star
    //printTile();
    
    //SolveAStar();
    modAStar(2);//1 :blue ghost
    
    //printf("Tile After A star\n");
    //printTile();
    bPathFound = true;
  }
  
  if(bPathFound){  
    int x  = blueGhost.GetX();
    int y =  blueGhost.GetY();
    int dir = blueTile[x][y].dir;
    blueGhost.Move(dir);
    blueGhost.MoveToDir();
  }
}

void Game::Update(){

  //move pacman
  if(nextDirPresent){
    //for east
    if(IsValidPath(pac.GetX()+1,pac.GetY()) && IsValidPath(pac.GetX()-1,pac.GetY()) ||
       IsValidPath(pac.GetX()+1,pac.GetY()) && !IsValidPath(pac.GetX()-1,pac.GetY())
       ){
      {
	pac.Move(nextDir);
	nextDirPresent = false;
      }
    }
    //for west
    else if(IsValidPath(pac.GetX()-1,pac.GetY()) && IsValidPath(pac.GetX()+1,pac.GetY()) ||
       IsValidPath(pac.GetX()-1,pac.GetY()) && !IsValidPath(pac.GetX()+1,pac.GetY())
       ){
      {
	pac.Move(nextDir);
	nextDirPresent = false;
      }
    }
    
    pac.MoveToDir();
  }else{
    pac.MoveToDir();
  }

  
  //change mode to scatter :0 for scatter , 1 for hunt
  if(ModeTriggered(5.0)){
    //change to scatter
    if(ghostMode == 1){

      InitMoveDirBeforeScatter();
      InitPinkMoveDir();
      InitBlueMoveDir();
      //InitOrangeMoveDir();
      
      printf("\nSCATTER MODE\n");
      ghostMode = 0;//for red ghost
      pGhostMode = 0;//for pink ghost
      bGhostMode = 0;//for blue ghost
      
    }else if(ghostMode == 0){//hunt mode
      printf("\nHUNT MODE\n");
      //for red ghost
      if(!rReachedLastTile){
	rReachedLastTile = true;
      }
      ghostMode = 1;
      if(pGhostMode == 0){
	//for pink ghost
	if(!pReachedLastTile){
	  pReachedLastTile = true;
	}
	pGhostMode = 1;
      }
      //for blue ghost
      if(bGhostMode == 0){
	if(!bReachedLastTile){
	  bReachedLastTile = true;
	}
	bGhostMode = 1;
      }
    }
  }

  //modes
  if(ghostMode == 0){
    //GhostScatter();
  }
  if(ghostMode == 1){
    //for red ghost
    //RedMoveSeq();
  }
  //for pink ghost
  if(pGhostMode == 1){
    //for pink ghost
    //PinkMoveSeq();
  }
  //for blue ghost
  if(bGhostMode == 1){
    //BlueMoveSeq();
  }
  if(oGhostMode == 0){
    //OrangeScatter();
  }
  
  CheckCollision();
  EatCoin();
  
}

//handle inputs
void Game::HandleInputs(){
  //n:1,S:2,E:3,W:4
  //north
  if(IsKeyPressed(KEY_W)){
    if(IsValidPath(pac.GetX(),pac.GetY()-1)){
      
      pac.Move(0);   
    }
  }
  //south
  if(IsKeyPressed(KEY_S)){
    if(IsValidPath(pac.GetX(),pac.GetY()+1)){
      pac.Move(1);
      
    }
  }
  
  //east
  if(IsKeyPressed(KEY_D)){
    curDir = pac.GetDir();
    nextDir == 2;
    if(curDir != nextDir){
      nextDirPresent = true;
    }
    if(IsValidPath(pac.GetX()+1,pac.GetY())){
      pac.Move(2);
      
    }
  }
  //west
  if(IsKeyPressed(KEY_A)){
    curDir = pac.GetDir();
    nextDir = 3;
    if(curDir != nextDir){
      nextDirPresent = true;
    }
    if(IsValidPath(pac.GetX()-1,pac.GetY())){
      pac.Move(3);
    }
  }
  //FOR GHOST
  if(IsKeyPressed(KEY_UP)){
    pinkGhost.Move(0);
  }
  //south
  if(IsKeyPressed(KEY_DOWN)){
    pinkGhost.Move(1);
  }
  //east
  if(IsKeyPressed(KEY_RIGHT)){
    pinkGhost.Move(2);
  }
  //west
  if(IsKeyPressed(KEY_LEFT)){
    pinkGhost.Move(3);
  }
  
}


void Game::DrawCoin(){
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      if(maze.IsWalkable(coin[i][j].x,coin[i][j].y) == 1){
	if(CheckNeighbours(coin[i][j].x,coin[i][j].y) == 0 &&
	   coin[i][j].visited == false
	   ){
	  DrawCircle(coin[i][j].x*25,coin[i][j].y*25,3,BLUE);
	  DrawCircle(coin[i][j].x*25,coin[i][j].y*25,1,WHITE);
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
  pinkGhost.Draw();
  blueGhost.Draw();
  orangeGhost.Draw();
 
}
