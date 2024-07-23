#include<iostream>
#include<vector>
#include<stdio.h>
#include<random>

struct Pos{
  int x;
  int y;
  int cost;
};

std::vector<Pos> queue;

void SortQueue(){
  for(int i=0;i<queue.size();i++){
    for(int j=0;j<queue.size()-i-1;j++){
      if(queue[j].cost > queue[j+1].cost){
	Pos temp;
	temp = queue[j];
	queue[j] = queue[j+1];
	queue[j+1] =temp;
      }
    }
  }
}
void PrintQueue(){
  printf("Queue: \n");
  for(int i=0;i<queue.size();i++){
    printf(" pos[%d] posx[%d] posy[%d] cost[%d] \n",
	   i,queue[i].x,queue[i].y,queue[i].cost);
  }
  printf("\n");
}
int GetRandomNum(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);
  int random = dist6(rng);
  return random;
}
int main(){
  
  for(int i=0;i<5;i++){
    Pos val;
    val.x = rand()%10;
    val.y = rand()%10;
    val.cost = rand()%10;
    queue.push_back(val);
  }
  PrintQueue();
  SortQueue();
  printf("Sorted \n");
  PrintQueue();

  int size = queue.size();
  int px = queue[size-1].x;
  int py = queue[size-1].y;
  int cost = queue[size-1].cost;

  printf("PX: %d PY: %d cost: %d\n",px,py,cost);
  //get rand num
  int num = GetRandomNum();
  printf("Num: %d\n",num);
 
  /*
  int size = queue.size()-1;
  printf("Top of queue : pos[%d] cost[%d]\n",size,queue[size].cost);
  Pos topQueu = queue[size];
  printf("Top queue val: cost:[%d]\n",topQueu.cost);
  queue.pop_back();
  PrintQueue();
  //clear queues
  if(!queue.empty()){
    printf("Not empty\n");
    queue.clear();
  }
  if(queue.empty()){
    printf("Empty\n");
  }
  */
  return 0;
  
}
