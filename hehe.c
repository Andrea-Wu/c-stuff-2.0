#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct node {
	char* name;
	struct node* next;
} node;

node* create(char* name, node* next);
void printLL(node* headPt);
node* mergeSort(node* head);
node* split(node* head);
node* merge(node* head1, node* head2);
void* sort(void* args);
void writeToFile(FILE* stream, node* village, node* town, node* city);
void writeSingleName(FILE* stream, node location);

//global varbs
node* args1Pt;
node* args2Pt;
node* args3Pt;

node* idk1;
node* idk2;
node* idk3;

void main(int argc, char* argv[]) {
	if(argc != 3){
		printf("try again");
		return;
	}
	
	FILE* fp = fopen(argv[1], "r"); //open filestream
	if (fp == NULL) {
		printf("file not found");
	}
	
	char town[100];
	fgets(town, 100, fp); //this is needed so that the words village, town, and city aren't considered names 

	const char s[] = " \t\n";

	//linked list stuff
	node* temp1 = NULL;
	node* temp2 = NULL;
	node* temp3 = NULL;
	node* head1 = NULL;
	node* head2 = NULL;
	node* head3 = NULL;

	while(!feof(fp)){
		char buff[100];  
		
		fgets(buff, 100, fp);
		char* nameArr[3]; 

		char* token; 
		token = strtok(buff,s);//tokenizes the first name  //SO APPARENTLY WHEN YOU TOKENIZE, YOU'RE CREATING A POINTER TO A LOCATION INSIDE THE BUFFFER.
					//NOT CREATING A NEW STRING. c is not java :(
		int i = 0;//iterator for nameArr[]
		while(token != NULL){ 
		
			nameArr[i] = token;
			token = strtok(NULL,s);//i'm not sure why this works   //maybe s[] stores previous   	
										//token as a delim
												
			i = i+1;
		}

		if(nameArr[0] == NULL && nameArr[1] == NULL && nameArr[2] == NULL){ 
			break;								
		}else if(nameArr[2] == NULL && nameArr[1] == NULL){ //there is 1 name
			(*temp3).next = create(nameArr[0], NULL); 
			temp3 = (*temp3).next;              

		}else if(nameArr[2] == NULL){//there are 2 names
			(*temp3).next = create(nameArr[1], NULL);  
			(*temp2).next = create(nameArr[0], NULL);

			temp3 = (*temp3).next;
			temp2 = (*temp2).next;

		}else{//there are 3 names. this works by assuming that none of the three lists is empty.
				if(head3 == NULL){//if head3 is null, then all heads are null
					head3 = create( nameArr[2], NULL);
					head2 = create(nameArr[1], NULL);
					head1 = create(nameArr[0], NULL);

					temp3 = head3;
					temp2 = head2;
					temp1 = head1;	
				}else{
					(*temp3).next = create(nameArr[2], NULL);
					(*temp2).next = create(nameArr[1], NULL);
					(*temp1).next = create(nameArr[0], NULL);

					temp3 = (*temp3).next;
					temp2 = (*temp2).next;
					temp1 = (*temp1).next;

				}
 
		}
		nameArr[0] = NULL;
		nameArr[1] = NULL;
		nameArr[2] = NULL; //resets nameArr[] for next line	

	}
	fclose(fp); 


	//this is going to be super ratchet: creating a node called "name", where next is head of sorted, and name is the type of residence
	args1Pt = create("village", head1);
	args2Pt = create("town", head2);
	args3Pt = create("city", head3);


	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	
	pthread_create(&thread3, NULL, (void*)&sort, (void *)args3Pt);
	pthread_create(&thread2, NULL, (void*)&sort, (void *)args2Pt);
	pthread_create(&thread1, NULL, (void*)&sort, (void *)args1Pt);

	
	pthread_join(thread3,(void**)&idk3);
	pthread_join(thread2,(void**)&idk2);
	pthread_join(thread1,(void**)&idk1);

	node* h3 = (node*)idk3;
	node* h2 = (node*)idk2;
	node* h1 = (node*)idk1;

	//now we gotta write to file
	FILE* newFile = fopen(argv[2], "w");
	writeToFile(newFile, h1, h2, h3);
	fclose(newFile);
	
}


node* create(char* name, node* next) {
	node* new_node = (node*)malloc(sizeof(node));
	char* newName = (char*)malloc(sizeof(char) * strlen(name));
	strcpy(newName, name); //strcpy(new,old)
	new_node-> name = newName;
	new_node->next = next;
	return new_node;

}


void printLL(node* headPt){
	printf("\n");
	while(headPt != NULL){
		node myHead = *headPt;
		printf("%s!\n",myHead.name);
		headPt = myHead.next;
	}
	printf("\n");

}

void writeToFile(FILE* stream, node* village, node* town, node* city){
	fputs("village", stream);
	int i;
	for(i = 0; i < 23; i++){
		fputs(" ", stream);
	}

	fputs("town", stream);
	for(i = 0; i <26; i++){
		fputs(" ", stream);
	}

	fputs("city", stream);
	for(i = 0; i < 26; i++){
		fputs(" ", stream);
	}

	fputs("\n\n", stream);

	while(village != NULL || town != NULL || city != NULL){
		
		if(village == NULL){
			for(i = 0; i < 30; i++){
				fputs(" ", stream);
			} 
		}else{
			writeSingleName(stream, *village);
			village = (*village).next;
		}

		if(town == NULL){
			for(i = 0; i < 30; i++){
				fputs(" ", stream);
			}
		}else{
			writeSingleName(stream, *town);
			town = (*town).next;
		}

		writeSingleName(stream, *city);
		city = (*city).next;

		fputs("\n", stream);
	}
		                              
}

void writeSingleName(FILE* stream, node location){//does not iterate
	int numSpaces;
	char nameAgain[50];
	char* name;
	int i;

	name = location.name;
	strcpy(nameAgain, name);//idk if necessary
	fputs(nameAgain, stream);
	numSpaces = 30 - strlen(nameAgain);
	for(i = 0; i < numSpaces; i++){
		fputs(" ", stream);
	}
}

void* sort(void* args){
	node* arguments = args;
	char* type = (*arguments).name;
	node* head = (node*)malloc(sizeof(node*));
	head = (*arguments).next;
	head = mergeSort(head);
	printf("I am the %s thread, and I have finished sorting!\n", type);
	return (void*)head;
}


node* split(node *head){
    int size = 0;
    node *current = head;
    while(current != NULL){
        size++;
        current = current->next;
    }

    size = (size+1)/2;
    current = head;

    while(size > 1){
        size--;
        current = current->next;    
    }
    node *second = current->next;
    current->next = NULL;
    return second;
}

node* mergeSort(node *head){
    if (head == NULL || head->next == NULL)
        return head;

    node *head2 = split(head);

    head = mergeSort(head);
    head2 = mergeSort(head2);
    return merge(head, head2);
}

node* merge(node *head1, node *head2){
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;

    if(strcmp(head1->name, head2->name) < 0){
        head1->next = merge(head1->next, head2);
        return head1;
    }
    else{
        head2->next = merge(head1, head2->next);
        return head2;
    }
}

