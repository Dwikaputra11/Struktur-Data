#include <iostream>
using namespace std;

#define max 10

struct node{
	string name;
	int position;
	int next;
}; node *pos;

int firstValue = 0,lastValue = 0,firstEmpty = 0,lastEmpty = 0,countEmpty = 0;

bool isEmptyList();
bool isBooked(int num);
void input(string name, int num);
void removeFromList(string name, int num);
void create();
void checkEmpty();
void display();

int main(){

	int num,t,pilih;
	char loop;
	string name;
	create();
	do{
		cout << "\n===== Booking Kereta =====\n";
		cout << "\nJumlah Seat tersedia : " << max - countEmpty << "\n\n";
		cout << "1. Booking seat\n";
		cout << "2. List seat\n";
		cout << "3. Batal Booking\n";
		cout << "Pilih opsi : ";cin >> pilih;
		switch(pilih){
			case 1:
			cout << "Banyak penumpang booking: ";cin >> t;
			while(t--){
				bool isInput = true;
				while(isInput){
					cout << "Nama : "; cin.ignore(); getline(cin,name);
					cout << "Nomor seat(1-10) : "; cin >> num;
					if(!isBooked(num)){
						input(name,num);
						isInput = false;
					}else{
						cout << "\nNomor Seat sudah di booking, silahkan pilih seat berbeda!\n\n";
					}	
				}
			}
			break; 
			case 2:
			display();
			break;
			case 3:
			cout << "Nama : "; cin.ignore(); getline(cin,name);
			cout << "Nomor seat : "; cin >> num;
			removeFromList(name,num);
			break;
			default:
			cout << "pilih sesuai opsi";
		}
		cout << "Kembali ke menu awal (y/n) ? "; cin >> loop;
	}while(loop == 'y' || loop == 'Y');
	return 0;
}

bool isEmptyList(){
	if(firstValue == 0) return true;
	else return false;
}

bool isBooked(int num){
	int temp = firstValue;
	while(pos[temp].position != num && pos[temp].next != 0){
		temp = pos[temp].next;
	}
	if(pos[temp].position == num) return true;
	else return false;
}

void create(){
	pos = new node[max];
	for(int i = 0; i < max; i++){
		pos[i].next = 0;
		pos[i].position = 0;
	}
}

void input(string name, int num){
	int temp;
	pos[num].name = name;
	pos[num].position = num;

	if(firstValue == 0){
		pos[num].next = 0;
		firstValue = num;
	}else{
		temp = firstValue;
		while(pos[temp].next != 0){
			temp = pos[temp].next;
		}
		pos[temp].next = num;
		pos[num].next = 0;
	}
	lastValue = num;
	checkEmpty();
}

void checkEmpty(){
	int temp = -1;
	countEmpty = max;
	// cout << "before position: ";
	// for(int i = 0; i < max; i++){
	// 	cout << pos[i].position << " ";
	// }
	// cout << "\nbefore next: ";
	// for(int i = 0; i < max; i++){
	// 	cout << pos[i].next << " ";
	// }
	for(int i = 0; i < max; i++){
		if(pos[i].position == 0){
			if(temp == -1){
				firstEmpty = i;
				temp = i;
			}else{
				pos[temp].next = i;
				temp = i;
			}
			countEmpty--;
		}
	}
	lastEmpty = temp + 1;
}

void removeFromList(string name, int num){
	if(isEmptyList()){
		cout << "\nDaftar booking masih kosong\n";
	}else{
		int temp; 
		bool isRemove = false;
		if(num == firstValue){
			firstValue = pos[num].next;
			isRemove = true;
		}else{
			temp = firstValue;
			while(pos[pos[temp].next].position != num && pos[temp].next != 0){
				temp = pos[temp].next;
			}
			if(pos[pos[temp].next].position == lastValue){
				lastValue = pos[temp].position;
				pos[lastValue].next = 0;
				isRemove = true; 
			}else{
				pos[temp].next = pos[pos[temp].next].next;
				pos[pos[temp].next].next = 0; 
				isRemove = true;
			}
		}
		if(!isRemove){
			cout << "Seat tidak bisa dibatalkan karena belum ada pembookingan\n";
		}else{
			pos[num].position = 0;
			pos[num].name = "";
			cout << "Pembatalan booking berhasil\n";
		}
		checkEmpty();
	}
}

void display(){
	if(isEmptyList()){
		cout << "\nDaftar booking masih kosong\n";
	}else{
		int temp = firstValue;
		cout << "\nSeat yang telah di booking : \n";
		while(pos[temp].next != 0){
			cout << "Seat nomor " << pos[temp].position << " atas nama " << pos[temp].name << "\n";
			temp = pos[temp].next;
		}
		cout << "Seat nomor " << pos[lastValue].position << " atas nama " << pos[lastValue].name << "\n\n";

		cout << "Seat Kosong : ";
		temp = firstEmpty;
		while(pos[temp].next != 0){
			cout << pos[temp].next << " ";
			temp = pos[temp].next;
		}
		cout << lastEmpty << "\n\n";
	}
}