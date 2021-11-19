#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
typedef int typeinfo;
#define allocationNode (typenode*)malloc(sizeof(typenode))
#define enter cout << "\n"
struct typenode{
	typeinfo info;
	typeptr next;
};

int sumNode = 0;
typeptr head;

void createNewList();
void circularLinkedList(typeinfo num);
void display();

int main()
{
	createNewList();
	int arr[6] = {125,150,175,200,225,250};
	for(int i = 0; i < 6; i++){
		circularLinkedList(arr[i]);
	}
	
	display();

	return 0;
}

void createNewList(){
	typeptr newList;
	head = (typenode*)malloc(sizeof(typenode));
	head->info = sumNode;
	head->next = head;
}


void circularLinkedList(typeinfo num){
	typeptr newNode,temp;
	newNode = (typenode*)malloc(sizeof(typenode));
	newNode->info = num;
	sumNode++;

	if(head->next == head){
		newNode->next = head;
		head-> next = newNode;
		head-> info = sumNode;
	}else{
		if(head->next->info >= num){
			newNode->next = head->next;
			head-> next = newNode;
		}else{
			temp = head;
			while(temp -> next != head && temp->next->info <= num)
				temp = temp->next;
			newNode->next = temp->next;
			temp->next = newNode;
		}
		head->info = sumNode;
	}
}

void display(){
	typeptr temp = (typenode*)malloc(sizeof(typenode));
	temp = head->next;

	while(temp != head){
		if(temp->info != head->next->info)cout << temp->info << " ";
		temp = temp->next;
	}
}