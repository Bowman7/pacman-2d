#include"maze.hpp"

Maze::Maze(){
  InitMaze();
  //testMove();
  carvePassage(0,0);
  SetupPath();
}

Maze::~Maze(){

}

//shuffle
void Maze::Shuffle(directions dir[]){
  std::vector<int>val{0,1,2,3};
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(val.begin(),val.end(),g);

  for(int i=0;i<4;i++){
    switch(val[i]){
    case 0:
      dir[i] =N;break;
    case 1:
      dir[i] = S;break;
    case 2:
      dir[i]=E;break;
    case 3:
      dir[i] = W;break;
    default:
      break;
    }
  } 
}
//opposite
directions Maze::opposite(directions dir){
  switch(dir){
  case N:
    return S;break;
  case S:
    return N;break;
  case E:
    return W;break;
  case W:
    return E;break;
  default:
    break;
  }
  return N;
}
//gets steps acc to direction
void Maze::GetStep(int &xStep,int &yStep,directions dir){
  switch(dir){
  case N:
    xStep =0;
    yStep = -3;
    break;
  case S:
    xStep = 0;
    yStep = 3;
    break;
  case E:
    xStep = 3;
    yStep = 0;
    break;
  case W:
    xStep = -3;
    yStep = 0;
    break;
  default:
    break;
  }
}
//set direction
void Maze::SetDirection(int &nx,int &ny,directions dir[]){
  bool foundDir = false;
  if(!foundDir){
    for(int i=0;i<4;i++){
      int xStep,yStep;
      GetStep(xStep,yStep,dir[i]);
      
      int newx =nx+xStep;
      int newy =ny+yStep;
      
      if(nx>=0 && nx<9 && ny>=0 && ny<=9 && maze[nx][ny].visited== false){
	maze[nx][ny].fwdDir = dir[i];
	maze[nx][ny].visited =  true;
	maze[newx][newy].bckDir = opposite(dir[i]);
	printf("[%d}[%d] -> [%d][%d] \n",nx,ny,newx,newy);
	nx = newx;
	ny = newy;
	foundDir = true;
      }
    }
    Pop();
    nx = stack[top].x;
    ny = stack[top].y;
    foundDir = true;
  }
}
//check for available directions
void Maze::CheckAvailableDir(){
  bool foundDir = false;
  if(!foundDir){
    directions dir[4];
    Shuffle(dir);
    for(int i=0;i<4;i++){
      int xStep,yStep;
      GetStep(xStep,yStep,dir[i]);

      int newX = stack[top].x+xStep;
      int newY = stack[top].y+yStep;

      if(newX>=0 && newX<9 && newX>0 && newY<9 && maze[newX][newY].visited== false){
	maze[stack[top].x][stack[top].y].fwdDir = dir[i];
	maze[newX][newY].bckDir = opposite(dir[i]);
	std::cout<<"Goes in dir: "<<dir[i]<<std::endl;
	printf("[%d}[%d] -> [%d][%d] \n",stack[top].x,stack[top].y,newX,newY);
	Push(newX,newY);
	pushPath(newX,newY);
	foundDir = true;
      }
    }
    Pop();
    foundDir = true;
  }
}
//MAIN ALGO: CARVE PASSAGE
void Maze::carvePassage(int cx,int cy){
  Push(cx,cy);
  while(!IsEmpty()){
    CheckAvailableDir();
    
  }
}

//get direction
directions Maze::GetDirection(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);
  float random = dist6(rng);
  int rand = (int)random;
  switch(rand){
  case 0:
    return N;break;
  case 1:
    return S;break;
  case 2:
    return E;break;
  case 3:
    return W;break;
  }
  return N;
}
//print dir
void Maze::PrintDir(directions dir[]){
  for(int i=0;i<4;i++){
    std::cout<<"Dir :"<<dir[i]<<std::endl;
  }
}

//check path and break walls
void Maze::CheckPath(int cx,int cy){
  switch(maze[cx][cy].fwdDir){
  case E:
    {
      if(maze[cx+3][cy].bckDir == W){
	maze[cx+2][cy].color = GREEN;
	maze[cx+2][cy+1].color = GREEN;
      }
    }break;

  case S:
    {
      if(maze[cx][cy+3].bckDir == N){
	maze[cx][cy+2].color =  GREEN;
	maze[cx+1][cy+2].color = GREEN;
      }
    }
  case N:
    {
      if(maze[cx][cy-3].bckDir == S){
	maze[cx][cy-1].color = GREEN;
	maze[cx+1][cy-1].color = GREEN;
      }
    }break;
  case W:
    {
      if(maze[cx-2][cy].bckDir == E){
	maze[cx-1][cy].color = GREEN;
	maze[cx-1][cy+1].color = GREEN;
      }
    }
  default:
    break;
  }
}
//Linkup paths
void Maze::LinkUp(struct Stack s1,struct Stack s2){
  for(int i=s1.x;i<=s2.x;i++){
    for(int j=s1.y;j<=s2.y;j++){
      maze[i][j].color = GREEN;
    }
  }
}
//setup path
void Maze::SetupPath(){
  for(int i=0;i<p_top;i++){
    LinkUp(pathStack[i],pathStack[i+1]);
  }
}

//test move
void Maze::testMove(){
  maze[0][0].fwdDir = E;
  maze[3][0].bckDir = W;

  maze[3][0].fwdDir = S;
  maze[3][3].bckDir = N;

  maze[6][6].fwdDir = N;
  maze[6][3].bckDir = S;

}
//init maze
void Maze::InitMaze(){
  //set all block
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      maze[i][j].color = GREEN;
      maze[i][j].visited =  false;
    }
  }
  //Walls
  for(int i=0;i<9;i++){
    for(int j=2;j<9;j+=3){
      //vert walls
      maze[j][i].color = RED;
      //hroz walls
      maze[i][j].color = RED;
    }
  }
}

void Maze::Draw(){

  //draw all box
  for(int i=0;i<9;i++){
    for(int j =0;j<9;j++){
      DrawRectangle(i*size,j*size,size,size,maze[i][j].color);
    }
  }
  //draw line
  for(int i=0;i<=9;i++){
    //vert
    DrawLine(i*size,0,i*size,9*size,BLACK);
    //hor
    DrawLine(0,i*size,9*size,i*size,BLACK);
  }
  
}
