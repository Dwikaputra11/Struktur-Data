#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
#define enter cout << "\n"
#define listkosong cout << "List Kosong\n"
struct typeinfo{
	string nama;
	int umur;
	int golDar;
}; 
struct typenode{
	int jmlNode;
	typeinfo info;
	typeptr next;
};

typeptr head,temp;
int sumNode = 0;
int umur;string nama; int golDar;
string golonganDarah[4] = {"O", "A", "B", "AB"};

int menu();
void inputList(string nama, int umur, int golDar);
void check();
void buatListBaru();
void inputList();
void inputPendonor();
void displayData();
void hapusPendonor(string nama);

int main()
{	
	char loop = 'y';

	while(loop == 'y' || loop == 'Y'){
		int pil = menu();
		system("cls");
		enum{INPUT = 1, DISPLAY, CHECK,DELETE};
		switch(pil){
			case INPUT:
			buatListBaru();
			inputPendonor();
			break;
			case DISPLAY:
			displayData();
			break;
			case CHECK:
			check();
			break;
			case DELETE:
			cout << "Nama Pendonor : ";cin.ignore();getline(cin,nama);
			hapusPendonor(nama);
			break;
		}
		cout << "Kembali ke Menu Utama (y/n)? "; cin >> loop;
		system("cls");
	}

	return 0;
}

int menu(){
	int pil;
	cout <<"\n======= APLIKASI CEK PENDONOR =======\n";
	cout <<"1. Input Pendonor\n2. Lihat Data Pendonor\n3. Cek Kandidat Pendonor\n4. Hapus Data Pendonor\n";
	cout <<"Pilih : ";cin >> pil;
	return pil;
}

void buatListBaru(){
	head = new typenode();
	head->jmlNode = sumNode;
	head->next = head;
}

void inputPendonor(){
	string pass;bool boolpass;int jml;
	cout << "======== PENDONOR ========\n";
	cout << "Jumlah Pendonor : "; cin >> jml;
	while(jml--){
		cout << "Nama : ";cin.ignore();getline(cin,nama);
		cout << "Umur : "; cin >> umur;
		boolpass = (umur >= 17 && umur <= 60);
		do{
			try{
					cout << "Golongan Darah\n1. O\n2. A\n3. B\n4. AB\n";
					cout << "Pilih : "; cin >> golDar;
					if(golDar > 4) throw "Pilih angka sesuai pilihan!\n";
			}catch (const char* e){
				cout << e << endl;
			}
		}while(golDar > 4);
		pass = (boolpass)? "Bisa Donor" : "Tidak Bisa Donor";
		cout <<"Status : " << pass << "\n\n";
		if(boolpass) inputList(nama,umur,golDar - 1);
	}
}
void inputList(string nama, int umur,int golDar){
	typeptr nb;
	nb = new typenode();
	nb->info.nama = nama;
	nb->info.umur = umur;
	nb->info.golDar = golDar;
	sumNode++;

	if(head->next == head){
		head->next = nb;
		nb->next = head;
	}else{
		if(head->next->info.golDar >= golDar){
			nb->next = head-> next;
			head->next= nb;
		}else{
			temp = head->next;
			while(temp->next!=head && temp->info.golDar <= golDar) temp = temp->next;
			nb->next = temp->next;
			temp->next = nb;
		}
	}
	head->jmlNode = sumNode;
}
void displayData(){
	cout << "\n======== LIST PENDONOR ========\n\n";
	if(head->next == head) listkosong;
	else{
		temp = head->next;
		cout << string(66,'-') << endl;
		cout <<"|" <<  setw(12) << "Nama" << setw(10) 
		<< "|" << setw(11) << "Umur" << setw(9) 
		<< "|" << setw(18) << "Golongan Darah" << setw(6) << "|\n";  
		cout << string(66,'-') << endl;
		while(temp != head){
			cout << "|" << setw(13) << temp->info.nama << setw(9) 
			<< "|" << setw(10) << temp->info.umur << setw(10)
			<< "|" << setw(12) << golonganDarah[temp->info.golDar] << setw(12) << "|\n";
			temp = temp->next;
		}
		cout << string(66,'-') << endl;
		enter;
		cout << "Jumlah Peminjam : " << head->jmlNode;
		enter;
	}
}

void check(){
	bool valCondition[4][4] ={
		// O   A   B   AB pendonor
		{true, false, false, false}, // O penerima
		{true, true, false, false}, // A
		{true, false, true, false}, // B
		{true, true, true, true} // AB
	};
	cout << "\n======== DATA PENERIMA ========\n";
	cout << "Nama : "; cin >> nama;
	cout << "Umur : "; cin >> umur;
	do{
		try{
			cout << "Golongan Darah\n1. O\n2. A\n3. B\n4. AB\n";
			cout << "Pilih : "; cin >> golDar;
			if(golDar > 4) throw "Silahkan angka sesuai pilihan!\n";
		}catch (const char* e){
			cout << e << endl;
		}
	}while(golDar > 4);
	cout << "\n======== LIST DATA PENDONOR ========\n\n";
	cout << string(66,'-') << endl;
	cout <<"|" <<  setw(12) << "Nama" << setw(10) 
	<< "|" << setw(11) << "Umur" << setw(9) 
	<< "|" << setw(18) << "Golongan Darah" << setw(6) << "|\n";  
	cout << string(66,'-') << endl;
	for(int i = 0; i < 4; i++){
		if(valCondition[golDar - 1][i]){
			temp = head->next;
			while(temp != head){
				if(temp->info.golDar == i){
					cout << "|" << setw(13) << temp->info.nama << setw(9) 
					<< "|" << setw(10) << temp->info.umur << setw(10)
					<< "|" << setw(12) << golonganDarah[temp->info.golDar] << setw(12) << "|\n";
				}
				temp = temp->next;
			}	
		}
	}
	cout << string(66,'-') << endl;
	enter;
}

void hapusPendonor(string nama){
	typeptr hapus;bool found;
	hapus = new typenode();
	hapus->info.nama = nama;

	if(head->next == head) listkosong;
	else{
		hapus = head->next;
		if(head->next->info.nama == nama){
			head->next = hapus->next;
			found = true;
		}else{
			while(temp->next!=head && temp->next->info.nama != nama){
				temp = temp->next;
				found = (temp->next->info.nama == nama);
			}
			if(found){
				hapus = temp->next;
				temp->next = hapus->next;
			}else cout << "Nama Tidak Ditemukan...\n";
		}
		if(found){
			free(hapus);
			head->jmlNode--;
			cout << "Pendonor dengan nama " << nama << " berhasil terhapus dari list...\n";
		}
	}	
}