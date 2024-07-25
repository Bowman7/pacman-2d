#include<stdio.h>
#include<iostream>


void InitMaze(int maze[][10]){
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      maze[i][j] = 0;
    }
  }
  //add walls
  //vert walls
  for(int i=0;i<10;i+=2){
    for(int j=0;j<10;j++){
      maze[j][i] = 1;
      maze[i][j] = 1;
    }
  }
}

void PrintMaze(int maze[][10]){
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      printf("-%d-",maze[i][j]);
     
    }
    printf("\n");
  }
}

int main(){

  int maze[10][10];
  InitMaze(maze);

  PrintMaze(maze);
  return 0;
}
