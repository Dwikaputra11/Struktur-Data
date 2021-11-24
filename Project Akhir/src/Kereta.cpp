#include "Kereta.h"
#include <iostream>
#include <string>

void create(Kereta *train){
	// intinya ngasik value awal aja
    train = (Kereta*)malloc(sizeof(Kereta));
    for(int i = 0; i < bound; i++){
        train->no_penumpang = 0; // ini aku gak tau aksesnya gmn
        train->next = 0;
    }
};
void input(Kereta *train,char* name,int num){
	train->nama = name;
	train->no_penumpang = num;

	if(firstValue == 0){
		train->next = 0;
		firstValue = num;
	}else{
		temp = firstValue;
		while(train->next != 0){
			temp = train->next;
		}
		train->next = num;
		train->next = 0;
	}
	lastValue = num;
	checkEmpty(train);
}
void checkEmpty(Kereta *train){
    temp = -1;
	countEmpty = bound;
	// cout << "before position: ";
	// for(int i = 0; i < max; i++){
	// 	cout << pos[i].position << " ";
	// }
	// cout << "\nbefore next: ";
	// for(int i = 0; i < max; i++){
	// 	cout << pos[i].next << " ";
	// }
	for(int i = 0; i < bound; i++){
		if(train->no_penumpang == 0){
			if(temp == -1){
				firstEmpty = i;
				temp = i;
			}else{
				(train + temp)->next = i;
				temp = i;
			}
			countEmpty--;
		}
	}
	lastEmpty = temp + 1;
}
void display(Kereta *train){
    temp = firstValue;
    cout << "\nSeat yang telah di booking : \n";
    while((train + temp)->next != 0){
        cout << "Seat nomor " << train->no_penumpang << " atas nama " << train->nama << "\n";
        temp = train->next;
	}
    cout << "Seat nomor " << train->no_penumpang << " atas nama " << train->nama << "\n\n";

    cout << "Seat Kosong : ";
    temp = firstEmpty;
    while(train->next != 0){
        cout << train->next << " ";
        temp = train->next;
    }
    cout << lastEmpty << "\n\n";
}
// void clear(Kereta *train,const char* nama);