#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
typedef string typeNama;
typedef int typeNHariSekali;
typedef bool typeIsFill;
#define enter cout << "\n"
#define listkosong cout << "List Kosong\n"
struct typenode{
	typeIsFill isFill = false; 
	typeNama nama;
	typeNHariSekali hari; 
	typeptr next;
};

int sumNode = 0;
typeptr head;

int menu();
void createNewList();
void circularLinkedList(typeNama nama,typeNHariSekali hari);
void generateJadwal();
void display();

int main()
{
	int n, opsi;string k;int jml;
	char loop = 'y';
	enum{CREATE = 1,ADD, DISPLAY, GENERATE};
	head = new typenode();
	while(loop == 'y' || loop == 'Y'){
		opsi = menu();
		switch(opsi){
			case CREATE:{
				createNewList();
				cout << "Banyak peminjam : "; cin >> n;
				while(n--){
					cout << "Masukkan Nama : ";cin.ignore(); getline(cin,k);
					cout << "Peminjaman setiap n hari : "; cin >> jml;
					circularLinkedList(k,jml);
				}
			}
			break;
			case ADD:
			if(!head->isFill) cout << "Buat Jadwal Terlebih Dahulu!\n";
			else{
				cout << "Banyak peminjam tambahan : "; cin >> n;
				while(n--){
					cout << "Masukkan Nama : ";cin.ignore(); getline(cin,k);
					cout << "Peminjaman setiap n hari : "; cin >> jml;
					circularLinkedList(k,jml);
				}
			} 
			break;
			case DISPLAY:
			display();
			break;
			case GENERATE:
			generateJadwal();
			break;
		}
		cout << "\nKembali ke Menu (y/n) : "; cin >> loop;
	}
	return 0;
}

int menu(){
	int pil;
	cout << "JADWAL PEMINJAMAN MOBIL\n";
	cout << "1. Buat Jadwal\n";
	cout << "2. Tambah Peminjam\n"; 
	cout << "3. Tampilkan Peminjam\n";
	cout << "4. Generate Jadwal\n";
	cout << "Pilih : "; cin >> pil;
	return pil;
}

void createNewList(){
	typeptr newList;
	head = new typenode();
	head->isFill = true;
	head->hari = sumNode;
	head->next = head;
}


void circularLinkedList(typeNama nama,typeNHariSekali hari){
	typeptr newNode,temp;
	newNode = new typenode();
	newNode->nama = nama;
	newNode->hari = hari;
	newNode->isFill = true;
	sumNode++;

	if(head->next == head){
		newNode->next = head;
		head-> next = newNode;
		head-> hari = sumNode;
	}else{
		if(head->next->hari >= hari){
			newNode->next = head->next;
			head-> next = newNode;
		}else{
			temp = head;
			while(temp -> next != head && temp->next->hari <= hari)
				temp = temp->next;
			newNode->next = temp->next;
			temp->next = newNode;
		}
		head->hari = sumNode;
	}
}

void generateJadwal(){
	int jmlHari = 1,minggu = 0;
	typeptr temp,temp1;
	string arrHari[7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
	if(head->next == head) listkosong;
	else{
		while(jmlHari <= 30){
			bool fill = false;
			if(jmlHari%7 == 1){
				cout << "\n====== Minggu ke-" << ++minggu << " ======\n";
			}
			cout << arrHari[jmlHari%7] << "\t: ";
			temp = head->next;
			while(temp->next != head){
				if(jmlHari%temp->hari==0){
					fill = true;
					cout << temp -> nama << " ";
				}
				temp = temp->next;
				if(temp -> next == head && jmlHari%temp-> hari == 0){
					fill = true;
					cout << temp -> nama;
				}
			}
			if(!fill){
				cout << "Kosong";
			}
			jmlHari++;
			enter;
		}
	}
}

void display(){
	if(head->next == head) listkosong;
	else{
		typeptr temp = new typenode();
		temp = head->next;
		cout << string(44,'-') << endl;
		cout <<"|" <<  setw(12) << "Nama" << setw(10) << "|" << setw(12) << "Hari" << setw(10) << "|\n";  
		cout << string(44,'-') << endl;
		while(temp != head){
			cout << "|" << setw(13) << temp->nama << setw(9) << "|" << setw(10) << temp->hari << setw(12) << "|\n";
			temp = temp->next;
		}
		cout << string(44,'-') << endl;
		enter;
		cout << "Jumlah Peminjam : " << head->hari;
		enter;
	}
}