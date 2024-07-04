#include"maze.hpp"

Maze::Maze(){
  InitMaze();
}

Maze::~Maze(){

}
//init maze
void Maze::InitMaze(){
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      for(int k=i;k<2;k++){
	for(int l=j;l<2;l++<){
	   maze[k][l].val = 0;
	   maze[k][l].color = GREEN;
	   maze[k][l].visited = false;
	}
      }
      maze[i][j+3].val = 1;
      maze[i][j+3].color = RED;
      maze[i][j+3].visited = false;
    }
     maze[i+3][j].val = 1;
     maze[i+3][j].color = RED;
     maze[i+3][j].visited = false;
  }
}
void Maze::Draw(){
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      
    }
  }
}
