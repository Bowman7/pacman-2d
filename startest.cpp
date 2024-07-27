#include<stdio.h>
#include<vector>
#include<random>

struct Node{
  int x;
  int y;
  int global;
};

std::vector<Node*> list;



void printList(){
  printf("\n List\n");
  int size = list.size();
  for(int i=0;i<10;i++){
    printf(" x: %d y: %d global: %d \n",list[i]->x,list[i]->y,list[i]->global);
  }
}
void sortList(){
  int size = list.size();
  for(int i=0;i<size;i++){
    for(int j=0;j<size-i-1;j++){
      Node *n1 = list[j];
      Node *n2 = list[j+1];
      if(n1->global > n2->global){
	Node *temp;
	temp = list[j];
	list[j] = list[j+1];
	list[j+1] =temp;
      }
      
    }
  }
}
int main(){

  Node * one = new Node;
  one->x = 1;
  one->y =0;
  one->global = 50;
  list.push_back(one);

  Node * two = new Node;
  two->x = 2;
  two->y =0;
  two->global = 20;
  list.push_back(two);
  printf("before sort\n");
  printList();
  printf("sort\n");
  sortList();
  printf("after sort\n");
  printList();
  
  for(int i=0;i<10;i++){
    Node* temp = new Node;
    temp->x = i;
    temp->y = 0;
    temp->global = rand()%100;
    list.push_back(temp);
  }

  printList();
  sortList();
  printList();
  
  return 0;
}
