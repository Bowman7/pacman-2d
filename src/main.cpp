#include"raylib.h"

#define WIDTH 1300
#define HEIGHT 1000

#include"../include/game.hpp"

enum State{
  STARTWINDOW=0,
  STARTCUTSCENE,
  GAMEPLAY,
  CUTSCENE_ONE,
  CUTSCENE_TWO,
  CUTSCENE_THREE,
  GAMEOVER,
  GAMEWON
  
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
  //load loading screen
  Image loading_image;
  Texture2D loading_tex;
  Texture2D gameover_tex;
  Texture2D cutSceneone_tex;
  Texture2D redStone_tex;
  Texture2D blueStone_tex;
  Texture2D yellowStone_tex;
  Texture2D gamewon_tex;
  loading_image = LoadImage("Texture/startscreen.png");
  loading_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/gameover.png");
  gameover_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/firstscenelarge.png");
  cutSceneone_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/cutscene2large.png");
  redStone_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/cutscene3large.png");
  blueStone_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/cutscene4large.png");
  yellowStone_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);
  loading_image = LoadImage("Texture/gamewonlarge.png");
  gamewon_tex = LoadTextureFromImage(loading_image);
  UnloadImage(loading_image);

  //for music
  Music music;
 
  Sound selectSound;
  Sound gameWin;
  Sound gameWinCutscene;
  Sound gameOver;
  InitAudioDevice();
  music = LoadMusicStream("Music/gamemusic1.mp3");
  PlayMusicStream(music);
  selectSound = LoadSound("Music/select-sound.mp3");
  gameWin = LoadSound("Music/orpheus.mp3");
  gameWinCutscene = LoadSound("Music/levelup.mp3");
  gameOver = LoadSound("Music/gameover.wav");

  
  
  //main loop
  while(!WindowShouldClose()){
    UpdateMusicStream(music);
    switch(currentState){
    case STARTWINDOW:{
      
      if(IsKeyPressed(KEY_ENTER)){
	PlaySound(selectSound);
	currentState = STARTCUTSCENE;
      }
    }break;
    case STARTCUTSCENE:{
      if(IsKeyPressed(KEY_ENTER)){
	PlaySound(selectSound);
	StopMusicStream(music);
	currentState = GAMEPLAY;
      }
    }break;
    case GAMEPLAY:
      {
      
      //printf("In gameplay\n");
      //skip

      /*
      if(IsKeyPressed(KEY_ENTER)){
	if(level == 0){
	  level++;
	  currentState = CUTSCENE_ONE;
	}else if(level ==1){
	  level++;
	  currentState = CUTSCENE_TWO;
	}else if(level ==2){
	  level++;
	  currentState = CUTSCENE_THREE;
	}else if(level == 3){
	  level= 0;;
	  currentState = GAMEWON;
	}
      }
      */
      //check for game won
      if(game.IsGameWon()){
	printf("Current level: %d\n",level);
	//level++;
	if(level<3){
	  PlaySound(gameWinCutscene);
	}else{
	  PlaySound(gameWin);
	}
	switch(level){
	case 0:
	  {
	    level++;
	    //init game
	    game.GameInit();
	    currentState = CUTSCENE_ONE;
	  }break;
	case 1:
	  {
	    level++;
	    //init game
	    game.GameInit();
	    currentState = CUTSCENE_TWO;
	  }break;
	case 2:
	  {
	    level++;
	    //init game
	    game.GameInit();
	    currentState = CUTSCENE_THREE;
	  }break;
	case 3:
	  {
	    level = 0;
	    game.GameInit();
	    currentState = GAMEWON;
	  }break;
	default:
	  break;
	}
      }
      //check for game over
      if(game.IsGameOver()){
	//init game
	game.GameInit();
	PlaySound(gameOver);
	currentState = GAMEOVER;
      }
      //handle input
      game.HandleInputs();
      //update
      game.Update();
      
    }break;
      
    case CUTSCENE_ONE:{
      printf("Ini cut scene one\n"); 
      if(IsKeyPressed(KEY_ENTER)){
	PlaySound(selectSound);
	currentState = GAMEPLAY;
      }
    }break;
      
    case CUTSCENE_TWO:{
      printf("Ini cut scene two\n");
      if(IsKeyPressed(KEY_ENTER)){
	PlaySound(selectSound);
	currentState = GAMEPLAY;
      }
    }break;
      
    case CUTSCENE_THREE:{
      printf("Ini cut scene three\n"); 
      if(IsKeyPressed(KEY_ENTER)){
	PlaySound(selectSound);
	currentState = GAMEPLAY;
      }
    }break;
      
    case GAMEOVER:{
      if(IsKeyPressed(KEY_ENTER)){
	PlayMusicStream(music);
	currentState = STARTWINDOW;
      }
    }break;
      
    case GAMEWON:{
      if(IsKeyPressed(KEY_ENTER)){
	StopSound(gameWin);
	PlayMusicStream(music);
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
      //DrawText("Start window",20,20,40,WHITE);
      DrawTexture(loading_tex,0,0,WHITE);
    }break;
    case STARTCUTSCENE:{
      //DrawText("Start cutscene",20,20,40,WHITE);
      DrawTexture(cutSceneone_tex,440,330,WHITE);
    }break;
    case GAMEPLAY:{
      
      game.Draw();
      /*
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
      */
    }break;
      
    case CUTSCENE_ONE:
      {
	//DrawText("Cutscene one",20,20,40,WHITE);
	DrawTexture(redStone_tex,440,330,WHITE);
      }break;
      
    case CUTSCENE_TWO:
      {
	//DrawText("Cutscene two",20,20,40,WHITE);
	DrawTexture(blueStone_tex,440,330,WHITE);
      }break;
      
    case CUTSCENE_THREE:
      {
	//DrawText("Cutscene three",20,20,40,WHITE);
	DrawTexture(yellowStone_tex,440,330,WHITE);
      }break;
      
    case GAMEOVER:{
      //DrawText("Game over rrrr ",20,20,40,WHITE);
      DrawTexture(gameover_tex,440,330,WHITE);
    }break;
      
    case GAMEWON:{
      //DrawText("Game won",20,20,40,WHITE);
      DrawTexture(gamewon_tex,440,340,WHITE);
    }break;
    default:
      break;
    }
    
    EndDrawing();
  }

  return 0;
}
