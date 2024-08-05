#include"../include/grid2.hpp"

Maze::Maze(){
  InitMaze();
  //testMove();
  carvePassage(1,1);
  DeadEndsHorz();
  CoverBoundry();
  ReflectMaze();
  InitFinalMaze();

  
  //SetupPath();
  
  //load textures
  wall_image = LoadImage("Texture/wall.png");
  wall_tex = LoadTextureFromImage(wall_image);
  UnloadImage(wall_image);
}

Maze::~Maze(){

}

//init final maze
void Maze::InitFinalMaze(){
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
      f_maze[i][j] = maze[i][j];
      f_maze[i+20][j]=maze2[i][j];
    }
  }
}

//cover th =e boundry walls
void Maze::CoverBoundry(){
  //horizontal
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j+=39){
      maze[i][j].color = DARKBLUE;
      maze[i][j].colVal = 2;
    }
  }
}
//check in n,s,e,w if forward dir is present
int Maze::CheckPaths(int i,int j){
  //printf("In check paths pos: maze[%d][%d] \n",i,j);
  //north
  int val =0;
  if(i>=1 && i<40 && j>=1&& j<40){
    if(maze[i][j-1].colVal == 1){
      //printf("north clear,north val : maze[%d][%d] : %d \n",i,j-1,maze[i][j-1].colVal);
      val++;
    }
    //south
    if(maze[i][j+2].colVal == 1){
      //printf("south clear \n");
      val++;
    }
    //east
    if(maze[i+2][j].colVal == 1){
      //printf("east clear \n");
      val++;
    }
    //west
    if(maze[i-1][j].colVal == 1){
      //printf("west clear \n");
      val++;
    }
  }
  //printf("val : %d \n",val);
  return val;
}
//clear dead end
void Maze::clearDeadEnd(int x,int y){
  directions dir[4] = {N,S,E,W};
  Shuffle(dir);
  bool carved = false;
  while(!carved){
    for(int i=0;i<4;i++){
      switch(dir[i]){
      case E:
	{
	  if(x>=1 && x<20 && y>=1 &&y<40){
	    if( maze[x+2][y].colVal == 2 && maze[x+3][y].colVal == 1 ){
	      //printf("east side carve from maze[%d][%d] to maze[%d][%d] \n",x,y,x+2,y);
	      maze[x+2][y].color = BLACK;
	      maze[x+2][y+1].color = BLACK;

	      maze[x+2][y].colVal = 1;
	      maze[x+2][y+1].colVal = 1;
	    }
	  }
	  carved = true;
	}break;
      case W:
	{
	  if(x>=1 && x<20 && y>=1 &&y<40){
	    if(maze[x-1][y].colVal == 2 &&maze[x-3][y].colVal ==1 ){
	      //printf("west side carve \n");
	      maze[x-1][y].color = BLACK;
	      maze[x-1][y+1].color = BLACK;

	      maze[x-1][y].colVal = 1;
	      maze[x-1][y+1].colVal = 1;
	    }
	  }
	  carved = true;
	}break;
      case N:
	{
	  if(x>=1 && x<20 && y>=1 && y<40){
	    if(maze[x][y-1].colVal == 2 && maze[x][y-3].colVal == 1){
	      //printf("north side carve \n");
	      maze[x][y-1].color = BLACK;
	      maze[x+1][y-1].color = BLACK;

	      maze[x][y-1].colVal = 1;
	      maze[x+1][y-1].colVal = 1;
	      
	    }
	  }
	}break;
      case S:
	{
	  if(x>=1 && x<20 && y>=1 && y<40){
	    if(maze[x][y+2].colVal == 2 && maze[x][y+3].colVal == 1){
	      //printf("south side carve \n");
	      maze[x][y+2].color = BLACK;
	      maze[x+1][y+2].color = BLACK;
	      
	      maze[x][y+2].colVal = 1;
	      maze[x+1][y+2].colVal = 1;
	    }
	  }
	}break;
      default:
	break;
      }
    }
  }
}
//clear hor dead ends
void Maze::DeadEndsHorz(){
  /*
  int validPaths;
  if(maze[4][4].colVal == 1){
    validPaths = CheckPaths(4,4);
  }
  if(validPaths<2){
    printf("A dead end \n");
    clearDeadEnd(4,4);
  }
  //maze[4][4].colVal = 3;
  */
  int validPaths = 0;
  //final check
  for(int i=1;i<20;i++){
    for(int j=1;j<40;j++){
      if(maze[i][j].colVal == 1){//is black zone
	validPaths = CheckPaths(i,j);
      }
      if(validPaths <2){
	clearDeadEnd(i,j);
      }
    }
  }
  
  
}
//reflect maze
void Maze::ReflectMaze(){
  //transfer
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
      maze2[i][j] = maze[i][j];
    }
  }
  //reflect
  for(int i=0;i<10;i++){
    for(int j=0;j<40;j++){
      s_maze temp;
      temp =maze[i][j];
      maze2[i][j] = maze2[19-i][j];
      maze2[19-i][j] = temp;
    }
  }
  
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
  //printf("path created from :maze[%d][%d]\n",cx,cy);
  switch(maze[cx][cy].fwdDir){
  case E:
    {
      if(maze[cx+3][cy].bckDir == W){
	maze[cx+2][cy].color = BLACK;
	maze[cx+2][cy+1].color = BLACK;
	
	maze[cx+2][cy].colVal = 1;
	maze[cx+2][cy+1].colVal = 1;;
      }
    }break;

  case S:
    {
      if(maze[cx][cy+3].bckDir == N){
	maze[cx][cy+2].color =  BLACK;
	maze[cx+1][cy+2].color = BLACK;

	maze[cx][cy+2].colVal =  1;
	maze[cx+1][cy+2].colVal = 1;
      }
    }
  case N:
    {
      if(maze[cx][cy-3].bckDir == S){
	maze[cx][cy-1].color = BLACK;
	maze[cx+1][cy-1].color = BLACK;

	maze[cx][cy-1].colVal = 1;
	maze[cx+1][cy-1].colVal = 1;
      }
    }break;
  case W:
    {
      if(maze[cx-3][cy].bckDir == E){
	maze[cx-1][cy].color = BLACK;
	maze[cx-1][cy+1].color = BLACK;

	maze[cx-1][cy].colVal = 1;
	maze[cx-1][cy+1].colVal = 1;
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
	//std::cout<<"Goes in dir: "<<dir[i]<<std::endl;
	//printf("[%d}[%d] -> [%d][%d] \n",stack[top].x,stack[top].y,newX,newY);
	//create path
	CreatePath(stack[top].x,stack[top].y);
	Push(newX,newY);
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
      maze[i][j].color = BLACK;
      maze[i][j].visited =  false;
      maze[i][j].colVal = 1;
    }
  }
  //Walls
  for(int i=0;i<20;i+=3){
    for(int j=0;j<40;j++){
      //vert walls
      maze[i][j].color = DARKBLUE;
      maze[i][j].colVal = 2;//blue value
    }
  }
  //hor walls
  for(int i=0;i<40;i+=3){
    for(int j=0;j<20;j++){
      //vert walls
      maze[j][i].color = DARKBLUE;
      maze[j][i].colVal = 2;//blue value
    }
  }
   
}

void Maze::PrintLine(){
  //draw line
  for(int i=0;i<=40;i++){
    //vert
    DrawLine(i*size,0,i*size,40*size,RED);
   
  }
  //hor
  for(int i=0;i<40;i++){
    //hor
    DrawLine(0,i*size,40*size,i*size,RED);
  }
}

void Maze::Draw(){
  
  for(int i=0;i<40;i++){
    for(int j=0;j<40;j++){
      Color col;
      if(f_maze[i][j].colVal == 1){
	col = BLACK;
      }else if(f_maze[i][j].colVal == 2){
	col = DARKBLUE;
      }else{
	col = RED;
      }

      int x = i*25;
      int y = j*25;
      if(f_maze[i][j].colVal == 2){
	DrawTexture(wall_tex,x,y,WHITE);
      }else if(f_maze[i][j].colVal == 1){
	DrawRectangle(i*size,j*size,size,size,f_maze[i][j].color);
      }
    }
  }
  //print grid
  //PrintLine();
  
  
}
