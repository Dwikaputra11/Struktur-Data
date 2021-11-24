#include "Kereta.h"

int firstValue = 0,lastValue = 0,firstEmpty = 0,lastEmpty = 0,countEmpty = 0;
extern int temp;

void create(Kereta *train){
	// intinya ngasik value awal aja
    train = new Kereta[bound];
    for(int i = 0; i < bound; i++){
        *(train + i)->no_penumpang = 0; // ini aku gak tau aksesnya gmn
        *(train + i)->next = 0;
    }
};
void input(Kereta *train,string name,int num){
    int temp;
	*(train + num)->nama = name;
	*(train + num)->no_penumpang = num;

	if(firstValue == 0){
		*(train + num)->next = 0;
		firstValue = num;
	}else{
		temp = firstValue;
		while(train[temp]->next != 0){
			temp = train[temp]->next;
		}
		*(train + temp)->next = num;
		*(train + num)->next = 0;
	}
	lastValue = num;
	checkEmpty(train);
}
void checkEmpty(Kereta *train){
    int temp = -1;
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
		if(*(train + i)->no_penumpang == 0){
			if(temp == -1){
				firstEmpty = i;
				temp = i;
			}else{
				*(train + temp)->next = i;
				temp = i;
			}
			countEmpty--;
		}
	}
	lastEmpty = temp + 1;
}
void display(Kereta *train){
    int temp = firstValue;
    cout << "\nSeat yang telah di booking : \n";
    while(*(train + temp)->next != 0){
        cout << "Seat nomor " << *(train + temp).no_penumpang << " atas nama " << *(train + temp).nama << "\n";
        temp = train[temp].next;
    }
    cout << "Seat nomor " << *(train + lastValue).no_penumpang << " atas nama " << *(train + lastValue).nama << "\n\n";

    cout << "Seat Kosong : ";
    temp = firstEmpty;
    while(*(train + temp)->next != 0){
        cout << *(train + temp).next << " ";
        temp = *(train + temp).next;
    }
    cout << lastEmpty << "\n\n";
}
// void clear(Kereta *train,const char* nama);