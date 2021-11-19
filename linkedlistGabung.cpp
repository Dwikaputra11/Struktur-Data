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
void sisipDepan(typeinfo IB);
void sisipTengah(typeinfo IB);
void sisipBelakang(typeinfo IB);
void hapus(typeinfo IB);
void cetaklist();
void cetakNodeBelakang();

int main(){
	typeinfo angka;
	int pilih;
	char ulangi = 'y';

	buatlistbaru();
	enum{DEPAN = 1, TENGAH, BELAKANG, HAPUS,CTKBLKNG};

	while(ulangi == 'y'){
		cout << "Pilih Input\n";
		cout << "1. Sisip Depan\n";
		cout << "2. Sisip Tengah\n";
		cout << "3. Sisip Belakang\n";
		cout << "4. Hapus Node\n";
		cout << "5. Cetak Node Dari BElakang\n";

		cout << "Pilih : ";cin >> pilih;

		switch(pilih){
			case DEPAN:
			cout << "Menyisipkan Depan : "; cin >> angka;
			sisipDepan(angka);
			break;
			case TENGAH:
			cout << "Menyisipkan Tengah : "; cin >> angka;
			sisipTengah(angka);
			break;
			case BELAKANG:
			cout << "Menyisipkan Belakang : "; cin >> angka;
			sisipBelakang(angka);
			break;
			case HAPUS:
			cout << "Menghapus Nilai : "; cin >> angka;
			hapus(angka);
			break;
			case CTKBLKNG:
			cetakNodeBelakang();
			break;
		}

		cout << " " << endl;

		cetaklist();

		cout << endl << endl;

		cout << "Apakah kamu ingin mengulangi? (Y/N)"; cin >> ulangi;


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

void sisipDepan(typeinfo IB){
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

void sisipTengah(typeinfo IB){
	typeptr NB,bantu;
	NB = (typenode*)malloc(sizeof(typenode));
	NB -> info = IB;

	if(awal == NULL){ // 10
		awal = NB;
		akhir = NB;
		awal -> next = NULL;
	}else if(awal == akhir){  // 20
		sisipBelakang(IB); // 10 20
	}else{
		bantu = awal;
		while((IB > bantu->next->info) && (bantu->next != NULL)){
			bantu = bantu->next;
		}
		NB->next = bantu->next; // A -> C == B -> C
		bantu->next = NB;		// A -> B = A -> B -> C
	}
}
void sisipBelakang(typeinfo IB){
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

void hapus(typeinfo IB){
	typeptr hapus,bantu;
	hapus = (typenode*)malloc(sizeof(typenode));
	hapus->info = IB;

	if(awal == NULL){
		cout << "List Masih Kosong\n";
	}else{
		if(awal->info == IB){
			hapus = awal;// A B
			awal = hapus->next;// B
			free(hapus);
		}else{
			bantu = awal;
			while((bantu->next->info != IB) && (bantu->next != NULL)){
				bantu = bantu->next;
			}
			hapus = bantu->next;
			if(hapus == NULL){
				cout << "List Tidak Ditemukan...\n";
			}
			else if(hapus == akhir){
				akhir = bantu;		// B -> C, C->info = IB, B akhir
				bantu->next = NULL; // 
			}else{
				bantu->next = hapus->next;	// A->B->C , B->info = IB
											// A -> C
			}
			free(hapus);
		}
	}
}

void cetaklist(){
	typeptr bantu;
	bantu = awal;

	while(bantu != NULL){
		cout << " " << bantu -> info;
		bantu = bantu -> next;
	}
}

void cetakNodeBelakang(){
	typeptr bantu, ekor;
	ekor = awal;
	awal = akhir;

	do{
		bantu = ekor;
		while(bantu->next != akhir){
			bantu = bantu->next;
		}
		akhir->next = bantu;
		akhir = bantu;
	}while(akhir != ekor);
	akhir->next = NULL;
	bantu = awal;
}

