#include"raylib.h"

#define WIDTH 1300
#define HEIGHT 1000

#include"game.hpp"

enum State{
  STARTWINDOW=0,
  STARTCUTSCENE,
  GAMEPLAY,
  GAMEOVER,
  GAMEWON,
  CUTSCENE_ONE,
  CUTSCENE_TWO,
  CUTSCENE_THREE
};
int main(){
  //init window
  InitWindow(WIDTH,HEIGHT,"window");
  SetTargetFPS(60);

  State currentState = STARTWINDOW;
  //main game obj
  Game game;
  //levels
  int level = 0;
  //main loop
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
      printf("In gameplay\n");
      //skip
      if(IsKeyPressed(KEY_ENTER)){
	level++;
	if(level == 1){
	currentState = CUTSCENE_ONE;
	}else if(level ==2){
	  currentState = CUTSCENE_TWO;
	}else if(level ==3){
	  currentState = CUTSCENE_THREE;
	}
      }
      //check for game won
      if(game.IsGameWon()){
	//init game
	game.GameInit();
	level++;
	if(level == 1){
	  currentState = CUTSCENE_ONE;
	}else if(level == 2){
	  currentState = CUTSCENE_TWO;
	}else if(level == 3){
	  currentState == CUTSCENE_THREE;
	}else if(level = 4){
	  currentState = GAMEWON;
	}
      }
      //check for game over
      if(game.IsGameOver()){
	//init game
	game.GameInit();
	currentState = GAMEOVER;
      }
      //handle input
      game.HandleInputs();
      //update
      game.Update();
      
    }break;
    case CUTSCENE_ONE:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = GAMEPLAY;
      }
    }break;
    case CUTSCENE_TWO:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = GAMEPLAY;
      }
    }break;
    case CUTSCENE_THREE:{
      if(IsKeyPressed(KEY_ENTER)){
	currentState = GAMEPLAY;
      }
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
    ClearBackground(BLACK);

    switch(currentState){
    case STARTWINDOW:{
      DrawText("Start window",20,20,40,WHITE);
    }break;
    case STARTCUTSCENE:{
      DrawText("Start cutscene",20,20,40,WHITE);
    }break;
    case GAMEPLAY:{
      
      game.Draw();
      if(level==0){
	DrawText("LEVEL ZERO",20,20,40,WHITE);
      }
      if(level == 1){
	DrawText("LEVEL ONE",20,20,40,WHITE);
      }
      if(level == 2){
	DrawText("LEVEL TWO",20,20,40,WHITE);
      }
      if(level == 3){
	DrawText("LEVEL THREE",20,20,40,WHITE);
      }
    
    }break;
    case CUTSCENE_ONE:
      {
	DrawText("Cutscene one",20,20,40,WHITE);
      }break;
    case CUTSCENE_TWO:
      {
	DrawText("Cutscene two",20,20,40,WHITE);
      }break;
    case CUTSCENE_THREE:
      {
	DrawText("Cutscene three",20,20,40,WHITE);
      }break;
    case GAMEOVER:{
      DrawText("Game over rrrr ",20,20,40,WHITE);
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
