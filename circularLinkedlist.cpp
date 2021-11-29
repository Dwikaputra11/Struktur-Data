#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
typedef string typeinfo;
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
	int n;

	createNewList();

	cout << "Masukkan banyak nama : "; cin >> n;cin.ignore();
	string k;
	while(n--){
		cout << "Masukkan Nama : "; getline(cin,k);
		circularLinkedList(k);
	}

	display();

	return 0;
}

void createNewList(){
	typeptr newList;
	head = new typenode();
	head->info = to_string(sumNode);
	head->next = head;
}


void circularLinkedList(typeinfo num){
	typeptr newNode,temp;
	newNode = new typenode();
	newNode->info = num;
	cout << newNode -> info; enter;
	sumNode++;

	if(head->next == head){
		newNode->next = head;
		head-> next = newNode;
		head-> info = to_string(sumNode);
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
		head->info = to_string(sumNode);
	}
}

void display(){
	typeptr temp = new typenode();
	temp = head->next;

	while(temp != head){
		cout << temp->info << " ";
		temp = temp->next;
	}
	enter;
	cout << "Jumlah Node : " << head->info;
	enter;
}

// cout <<"Number : " << newNode->info << " New Node Next : " << newNode->next; enter;