#include "Kereta.h"

void input(string name,int num){ // stack
	cout << "Masuk Input\n";
	Kereta *train;
	train = new Kereta;
	train->nama = name;
	train->no_penumpang = num;
	cout << train->nama << " " << train->no_penumpang << endl;

	if(firstValue == NULL){
		firstValue = train;
		lastValue = train;
		lastValue->next = NULL;
	}else{
		train->next = firstValue;
		firstValue = train;
	}
	countValue++;
}
void checkEmpty(){
	cout << "Masuk Check Empty\n";
    Kereta *temp,*empty;
	for(int i = 1; i <= bound; i++){
		temp = firstValue;
		while(temp->no_penumpang != i && temp->next != NULL){
			temp = temp->next;
		}
		if(temp->no_penumpang != i){
			empty = new Kereta;
			empty ->kosong = i;
			if(firstEmpty == NULL){
				firstEmpty = empty;
				lastEmpty = empty;
				lastEmpty->next = NULL;
			}else{
				lastEmpty->next = empty;
				lastEmpty = empty;
				lastEmpty->next = NULL;
			}
			countEmpty++;
		}
	}
}
void display(){
	checkEmpty();
	Kereta *temp;
    temp = firstValue;
    cout << "\nSeat yang telah di booking : \n";
    while(temp != NULL){
        cout << "Seat nomor " << temp->no_penumpang << " atas nama " << temp->nama << "\n";
        temp = temp->next;
	}

    cout << "\nSeat Kosong : ";
    temp = firstEmpty;
    while(temp != NULL){
        cout << temp->kosong << " ";
        temp = temp->next;
    }
}
// void clear(Kereta *train,const char* nama);