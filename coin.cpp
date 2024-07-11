#include"coin.hpp"

Coin::Coin(){
  eaten =  true;
}


void Coin::Draw(int x,int y){
  DrawCircle(x+12,y+12,12,YELLOW);
}
