#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
} node;

node* create(int data, node* next);
node* printLL(node* headPt);

int main(){
	node* headPt = create(3, NULL);
	(*headPt).next = create(4, NULL);

	headPt = printLL(headPt);
	printLL(headPt);

}

node* create(int data, node* next){
	node* newNode = (node*)malloc(sizeof(node));
	newNode -> data = data;
	newNode -> next = next;
	return newNode;
} 

node* printLL(node* headPt){
	node* temp = NULL;
	while(headPt != NULL){
		node head = *headPt;
		if(temp == NULL){
			temp = &head;
		}else{
		}
		printf("%d\n", head.data);
		head.data = 420;               //the variable head is a copy of the headPointer that is passed in. But can I directly change value of object in headPt?
		headPt = head.next;
	}

	return temp;
}
