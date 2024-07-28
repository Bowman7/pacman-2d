#include<iostream>
#include<random>
#include<algorithm>
#include<vector>
enum direction{
  N=0,
  S,
  E,
  W
};


void shuffle(direction dir[]){
  std::vector<int>val{0,1,2,3};
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(val.begin(),val.end(),g);

  for(int i=0;i<4;i++){
    switch(val[i]){
    case 0:
      dir[i] =N;break;
    case 1:
      dir[i] = S;break;
    case 2:
      dir[i]=E;break;
    case 3:
      dir[i] = W;break;
    default:
      break;
    }
    //std::cout<<"val :"<<val[i]<<std::endl;
  }
  
}
int main(){
  direction dir[4] = {N,S,E,W};
  shuffle(dir);
  for(int i=0;i<4;i++){
    std::cout<<"dirl :"<<dir[i]<<std::endl;
  }

  return 0;
}
