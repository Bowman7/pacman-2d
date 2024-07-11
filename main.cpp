#include"raylib.h"

#define WIDTH 1000
#define HEIGHT 1000

#include"game.hpp"

int main(){
  //init window
  InitWindow(WIDTH,HEIGHT,"window");
  SetTargetFPS(60);

  Game game;
  while(!WindowShouldClose()){
    //handle input
    game.HandleInputs();
    //update
    game.Update();
    //draw
    BeginDrawing();
    ClearBackground(BLUE);

    game.Draw();
    EndDrawing();
  }

  return 0;
}
