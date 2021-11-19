#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
#define enter cout << "\n"
#define listkosong cout << "List Kosong\n"
struct typeinfo{
	int nik;
	string nama;
	int umur;
	int suhu;
	string tensi; 
	int tipeVaksin;
	string statusVaksin;
}; 
struct typenode{
	int jmlNode;
	typeinfo info;
	typeptr next;
};

typeptr head,temp;
int sumNode = 0;
int umur,nik,vaksin,sistol,diastol,suhu; string nama;
string golonganDarah[3] = {"Sinovac", "Astrazeneca", "Moderna"};

int menu();
void inputList(string nama, int umur, int nik, double suhu,string tensi, int vaksin);
void check();
void buatListBaru();
void inputList();
void inputPendonor();
void displayData();
void hapusPendonor(int nik);

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
			cout << "Nama Pendonor : ";cin >> nik;
			hapusPendonor(nik);
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
	cout <<"1. Input Data\n2. Lihat Peserta Vaksinasi\n3. Cek Status Vaksinasi\n4. Hapus Data Vaksinasi\n";
	cout <<"Pilih : ";cin >> pil;
	return pil;
}

void buatListBaru(){
	head = new typenode();
	head->jmlNode = sumNode;
	head->next = head;
}

void inputPendonor(){
	string pass;bool boolsuhu,booltensi;int jml;
	cout << "======== PESERTA VAKSINASI ========\n";
	cout << "Jumlah Pendonor : "; cin >> jml;
	while(jml--){
		cout << "Screening Tahap 1\n";
		cout << " Nama\t: ";cin.ignore();getline(cin,nama);
		cout << " Umur\t: "; cin >> umur;
		cout << " NIK\t: "; cin >> nik;
		cout << " Dosis Vaksin ke-1\n\n";
		cout << "Screening Tahap 2\n";
		cout << " Suhu Badan\t: "; cin >> suhu;
		cout << " Tekanan Darah\t: "; cin >> sistol >> diastol;

		boolsuhu = (suhu <= 37.5);
		booltensi = ((sistol >= 100 && sistol <= 120) && (diastol >= 60 && diastol <= 90));
		pass = (boolsuhu && booltensi)? "Anda Bisa Divaksin" : "Mohon Maaf Anda belum dapat melakukan Vaksinasi";
		cout <<"Status : " << pass << "\n\n";
		if(boolsuhu && booltensi){
			string tensi = sistol + "/" + diastol;
			cout << "Screening Tahap 3\n";
			cout << "Daftar Vaksin Yang Tersedia\n";
			cout << "1. Sinovac\n2. Astrazaneca\n3. Moderna\n";
			cout << "Vaksin Yang Kita Pilih No : "; cin >> vaksin;
			cout << " Penginputan Data Selesai\n";
			inputList(nama,umur,nik,suhu,tensi,vaksin);
		}
	}
}
void inputList(string nama, int umur, int nik, double suhu,string tensi, int vaksin){
	typeptr nb;
	nb = new typenode();
	nb->info.nama = nama;
	nb->info.umur = umur;
	nb->info.nik = nik;
	nb->info.suhu = suhu;
	nb->info.tensi = tensi;
	nb->info.tipeVaksin = vaksin;
	sumNode++;

	if(head->next == head){
		head->next = nb;
		nb->next = head;
	}else{
		if(head->next->info.nik >= nik){
			nb->next = head-> next;
			head->next= nb;
		}else{
			temp = head->next;
			while(temp->next!=head && temp->info.nik <= nik) temp = temp->next;
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
		cout <<"|" <<  setw(12) << "NIK" << setw(10) << 
		"|" <<  setw(12) << "Nama" << setw(10) 
		<< "|" << setw(11) << "Umur" << setw(9) 
		<< "|" << setw(6) << "Suhu" << setw(6) << "|"
		<< "|" << setw(6) << "Tensi" << setw(6) << "|"
		<<  setw(12) << "Tipe Vaksin" << "|\n";
		cout << string(66,'-') << endl;
		while(temp != head){
			cout <<"|" <<  setw(12) << temp->info.nik << setw(10) << 
			"|" <<  setw(12) << temp->info.nama << setw(10) 
			<< "|" << setw(11) << temp->info.umur << setw(9) 
			<< "|" << setw(6) << temp->info.suhu << setw(6) << "|"
			<< "|" << setw(6) << temp->info.tensi << setw(6) << "|"
			<<  setw(12) << temp->info.tipeVaksin << "|\n";
			temp = temp->next;
		}
		cout << string(66,'-') << endl;
		enter;
		cout << "Jumlah Peminjam : " << head->jmlNode;
		enter;
	}
}

void check(){
	cout << "\n======== DATA PESERTA WEB ========\n";
	cout << "Silahkan Masukkan NIK yang ingin anda cek\n NIK : "; cin >> nik;
	cout << "\n======== LIST DATA PENDONOR ========\n\n";
	cout << string(66,'-') << endl;
	cout <<"|" <<  setw(12) << "Nama" << setw(10) 
	<< "|" << setw(11) << "Umur" << setw(9) 
	<< "|" << setw(18) << "Golongan Darah" << setw(6) << "|\n";  
	cout << string(66,'-') << endl;
	temp = head->next;
	while(temp != head){
		if(temp->info.nik == nik){
			cout <<"|" <<  setw(12) << temp->info.nik << setw(10) << 
			"|" <<  setw(12) << temp->info.nama << setw(10) 
			<< "|" << setw(11) << temp->info.umur << setw(9) 
			<< "|" << setw(6) << temp->info.suhu << setw(6) << "|"
			<< "|" << setw(6) << temp->info.tensi << setw(6) << "|"
			<<  setw(12) << temp->info.tipeVaksin << "|\n";
		}
		temp = temp->next;
	}
	cout << string(66,'-') << endl;
	enter;
}

void hapusPendonor(int nikHapus){
	typeptr hapus;bool found;
	hapus = new typenode();
	hapus->info.nik = nikHapus;

	if(head->next == head) listkosong;
	else{
		hapus = head->next;
		if(head->next->info.nik == nikHapus){
			cout << head->next->info.nama << endl;
			head->next = hapus->next;
			found = true;
		}else{
			while(temp->next!=head && temp->next->info.nik != nikHapus){
				temp = temp->next;
				found = (temp->next->info.nik == nikHapus);
			}
			if(found){
				cout << temp->next->info.nama << endl; 
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