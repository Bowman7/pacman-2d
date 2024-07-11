#include"raylib.h"

#define WIDTH 1000
#define HEIGHT 1000

#include"grid2.hpp"

int main(){
  //init window
  InitWindow(WIDTH,HEIGHT,"window");
  SetTargetFPS(60);

  Maze mazee;
  while(!WindowShouldClose()){
    //handle input

    //update
    
    //draw
    BeginDrawing();
    ClearBackground(BLUE);

    mazee.Draw();
    EndDrawing();
  }

  return 0;
}
