#include"raylib.h"

#define WIDTH 1000
#define HEIGHT 1000

#include"game.hpp"

enum State{
  STARTWINDOW=0,
  STARTCUTSCENE,
  GAMEPLAY,
  GAMEOVER,
  GAMEWON
};
int main(){
  //init window
  InitWindow(WIDTH,HEIGHT,"window");
  SetTargetFPS(60);

  State currentState = STARTWINDOW;

  Game game;
  while(!WindowShouldClose()){
    switch(currentState){
    case STARTWINDOW:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = STARTCUTSCENE;
      }
    }break;
    case STARTCUTSCENE:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = GAMEPLAY;
      }
    }break;
    case GAMEPLAY:{
      //handle input
      game.HandleInputs();
      //update
      game.Update();
      
    }break;
    case GAMEOVER:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = STARTWINDOW;
      }
    }break;
    case GAMEWON:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = STARTWINDOW;
      }
    }break;
    default:
      break;
    }
    
    
    //draw
    BeginDrawing();
    ClearBackground(BLUE);

    switch(currentState){
    case STARTWINDOW:{
      DrawText("Start window",20,20,40,WHITE);
    }break;
    case STARTCUTSCENE:{
      DrawText("Start cutscene",20,20,40,WHITE);
    }break;
    case GAMEPLAY:{
      game.Draw();
    }break;
    case GAMEOVER:{
      DrawText("Game over",20,20,40,WHITE);
    }break;
    case GAMEWON:{
      DrawText("Game won",20,20,40,WHITE);
    }break;
    default:
      break;
    }
    
    EndDrawing();
  }

  return 0;
}
