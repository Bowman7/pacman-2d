#include"coin.hpp"

Coin::Coin(){
  coin.x = 1;
  coin.y = 1;
  coin.visible = true;
  coin.size = 50;
}

void Coin::SetVal(int x,int y,bool vis){
  this->coin.x = x;
  this->coin.y = y;
  this->coin.visible = vis;
}
void Coin::Draw(){
  DrawCircle(coin.x*coin.size,coin.y*coin.size,5,LIGHTBLUE)
  DrawCircle(coin.x*coin.size,coin.y*coin.size,6,WHITE);
}
