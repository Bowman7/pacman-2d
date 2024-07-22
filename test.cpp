#include<iostream>
#include<vector>
#include<stdio.h>

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

  Pos top = queue.begin();
  //top.x = queue[0].x;
  //top.y = queue[0].y;
  //top.cost =queue[0].cost;
  printf("Top queue: posx[%d] posy[%d] cost[%d] \n",
	 top.x,top.y,top.cost
	 );

 
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
