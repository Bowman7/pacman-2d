#include"grid.hpp"

Maze::Maze(){
  InitMaze();
  //testMove();
  carvePassage(1,1);
  //carveEnding();
  //carveStart();
  //SetupPath();
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
//print dir
void Maze::PrintDir(directions dir[]){
  std::cout<<" Dir:{";
  for(int i=0;i<4;i++){
    std::cout<<dir[i]<<" ,";
  }
  std::cout<<"}"<<std::endl;
}

//check path and break walls
void Maze::CreatePath(int cx,int cy){
  printf("path created from :maze[%d][%d]\n",cx,cy);
  printf("stack top : %d\n",top);
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
      if(maze[cx-3][cy].bckDir == E){
	maze[cx-1][cy].color = GREEN;
	maze[cx-1][cy+1].color = GREEN;
      }
    }
  default:
    break;
  }
}
//check for available directions
void Maze::CheckAvailableDir(){
  bool foundDir = false;
  if(!foundDir){
    directions dir[4] ={N,S,E,W};
    Shuffle(dir);
    //PrintDir(dir);
    for(int i=0;i<4;i++){
      //printf("At pos: maze[%d][%d]\n",stack[top].x,stack[top].y);
      //std::cout<<"Dir[i] = "<<dir[i]<<std::endl;
      int xStep,yStep;
      GetStep(xStep,yStep,dir[i]);
      int newX = stack[top].x+xStep;
      int newY = stack[top].y+yStep;

      //printf("next pos: maze[%d][%d]\n",newX,newY);

      if(newX>=0 && newX<20 && newY>=0 && newY<40 && maze[newX][newY].visited== false){
	maze[stack[top].x][stack[top].y].fwdDir = dir[i];
	maze[newX][newY].bckDir = opposite(dir[i]);
	std::cout<<"Goes in dir: "<<dir[i]<<std::endl;
	printf("[%d}[%d] -> [%d][%d] \n",stack[top].x,stack[top].y,newX,newY);
	//create path
	CreatePath(stack[top].x,stack[top].y);
	Push(newX,newY);
	PushEnd(newX,newY);
	CheckAvailableDir();
      }
    }
    CreatePath(stack[top].x,stack[top].y);
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
//carve start
void Maze::carveStart(){
   for(int i=0;i<2;i++){
    //hor color
    maze[(1)+i][1].color = RED;
    //vert color
    maze[(1)+i][(1)+1].color = RED;
   }
}
//carve ending
void Maze::carveEnding(){
  printf("end pos: pos[%d][%d]\n",posStack[e_top].x,posStack[e_top].y);
  for(int i=0;i<2;i++){
    //hor color
    maze[(posStack[e_top].x)+i][posStack[e_top].y].color =WHITE;
    //vert color
    maze[(posStack[e_top].x)+i][(posStack[e_top].y)+1].color = WHITE;
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

//setup path
void Maze::SetupPath(){
  
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
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
      maze[i][j].color = GREEN;
      maze[i][j].visited =  false;
      maze[i][j].fwdDir =N;
      maze[i][j].bckDir =N;
    }
  }
  //Walls
  for(int i=0;i<20;i+=3){
    for(int j=0;j<40;j++){
      //vert walls
      maze[i][j].color = DARKBLUE;
    }
  }
  //hor walls
  for(int i=0;i<40;i+=3){
    for(int j=0;j<20;j++){
      maze[j][i].color = DARKBLUE;
    }
  }
  
}

void Maze::Draw(){
  //draw all box
  for(int i=0;i<20;i++){
    for(int j =0;j<40;j++){
      DrawRectangle(i*size,j*size,size,size,maze[i][j].color);
    }
  }
  
  //draw line
  for(int i=0;i<20;i++){
    //vert
    DrawLine(i*size,0,i*size,40*size,BLACK);
  }
  for(int i=0;i<40;i++){
    //hor
    DrawLine(0,i*size,20*size,i*size,BLACK);
  }
  
}
