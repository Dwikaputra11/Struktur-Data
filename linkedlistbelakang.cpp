#include <iostream>

using namespace std;

typedef int typeinfo;
typedef struct typenode *typeptr;
struct typenode{
	typeinfo info;
	typeptr next;
};

typeptr awal, akhir;
void buatlistbaru();
void sisibelakang(typeinfo IB);
void cetaklist();

int main(){
	typeinfo angka;
	char ulangi = 'y';

	buatlistbaru();

	while(ulangi == 'y'){
		cout << "Menyisipkan belakang : "; cin >> angka;

		sisibelakang(angka);

		cout << endl;

		cetaklist();

		cout << endl << endl;

		cout << "Apakah kamu ingin mengulangi? (Y/N)"; cin >> ulangi;

		cout << endl;
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

void sisibelakang(typeinfo IB){
	typeptr NB;
	NB = (typenode *)malloc(sizeof(typenode));
	NB -> info = IB;

	if(awal == NULL){
		awal = NB;
		akhir = NB;
	}else{
		akhir -> next = NB;
	}

	akhir = NB;
	akhir -> next = NULL;
}

void cetaklist(){
	typeptr bantu;
	bantu = awal;

	while(bantu != NULL){
		cout << " " << bantu -> info;
		bantu = bantu -> next;
	}
}