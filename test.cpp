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
    printf(" pos[%d] cost[%d] \n",i,queue[i].cost);
  }
  printf("\n");
}
int main(){
  
  for(int i=0;i<5;i++){
    Pos val;
    val.cost = rand()%10;
    queue.push_back(val);
  }
  PrintQueue();
  SortQueue();
  printf("Sorted \n");
  PrintQueue();
  printf("remove 1st element \n");
  queue.erase(queue.begin());
  queue.erase(queue.begin());
  PrintQueue();
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
