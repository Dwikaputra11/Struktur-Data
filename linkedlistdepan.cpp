#include <iostream>

using namespace std;

typedef int typeinfo;
typedef struct typenode *typeptr;
	// inisialisasi nama dari typenode yang bertipe pointer
struct typenode{
	typeinfo info;
	typeptr next;
};
typeptr awal, akhir;

void buatlistbaru();
void sisidepan(typeinfo IB);
void cetaklist();

int main(){
	typeinfo angka;
	char ulangi = 'y';

	buatlistbaru();

	while(ulangi == 'y'){
		cout << "Menyisipkan depan : "; cin >> angka;

		sisidepan(angka);

		cout << " " << endl;

		cetaklist();

		cout << endl << endl;

		cout << "Apakah kamu ingin mengulangi? (Y/N)"; cin >> ulangi;

		system("cls");

		cout << " " << endl;
	}

	exit(1);

	system("pause");
	return 0;
}

void buatlistbaru(){
	typeptr list;
	list = (typenode *)malloc(sizeof(typenode));
	list = NULL;
	awal = list;
	akhir = list;
}

void sisidepan(typeinfo IB){
	typeptr NB;
	NB = (typenode *)malloc(sizeof(typenode));
	NB -> info = IB;

	if(awal == NULL){
		awal = NB;
		akhir = NB;
		awal -> next = NULL; 
	}else{
		NB -> next = awal;
	}

	awal = NB;
}

void cetaklist(){
	typeptr bantu;
	bantu = awal;

	while(bantu != NULL){
		cout << " " << bantu -> info;
		bantu = bantu -> next;
	}
}
