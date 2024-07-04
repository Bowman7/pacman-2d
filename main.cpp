#include"raylib.h"

#define WIDTH 800
#define HEIGHT 800

int main(){
  //init window
  InitWindow(WIDTH,HEIGHT,"window");
  SetTargetFPS(60);

  while(!WindowShouldClose()){
    //handle input

    //update

    //draw
    BeginDrawing();
    ClearBackground(BLUE);

    EndDrawing();
  }

  return 0;
}
