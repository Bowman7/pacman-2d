#include"game.hpp"

Game::Game(){
  InitCoin();
}

Game::~Game(){

}

//init coin
void Game::InitCoin(){
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
      int val = maze.IsWalkable(i,i);
      if(val == 1){
	coin[i][j].SetEatenFalse();
      }
    }
  }
}
void Game::Update(){

}
void Game::HandleInputs(){

}

void Game::Draw(){
  maze.Draw();
  for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
      coin[i][j].Draw(i,j);
    }
  }
}
