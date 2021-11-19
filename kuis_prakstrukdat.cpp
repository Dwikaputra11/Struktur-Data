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
	int statusVaksin;
}; 
struct typenode{
	int jmlNode;
	typeinfo info;
	typeptr next;
};

typeptr head,temp;
int sumNode = 0;
int umur,nik,vaksin,sistol,diastol,suhu,dosis; string nama;
string statusVaksin[3] = {"Belum Melakukan Vaksin", "Sudah Melakukan Vaksin Pertama", "Proses Vaksinasi Anda Sudah Selesai"};
string tipeVaksin[3] = {"Sinovac", "Astrazeneca", "Moderna"};

int menu();
void inputList(string nama, int umur, int nik, double suhu,int dosis, string tensi, int vaksin);
void check();
void buatListBaru();
void inputList();
void inputPeserta();
void displayData();
void hapusPeserta(int nik);

int main()
{	
	char loop = 'y';
	int pil; 
	buatListBaru();
	while(loop == 'y' || loop == 'Y'){
		do{
			try{
				pil = menu(); // error handling jika input tidak sesuai opsi
				if(pil >= 1 || pil <= 5) throw "Pilih Opsi Sesuai Tertera di Menu\n";
			}catch(const char* e){
				cout << e << endl;
			}
		}while(pil >= 1 || pil <= 5);
		system("cls");
		enum{INPUT = 1,DISPLAY,CHECK,DELETE,EXIT};
		switch(pil){
			case INPUT:
			inputPeserta();
			break;
			case DISPLAY:
			displayData();
			break;
			case CHECK:
			check();
			break;
			case DELETE:
			cout << "Input NIK Peserta Vaksinasi : ";cin >> nik;
			hapusPeserta(nik);
			break;
			case EXIT:
			break;
		}
		cout << "Kembali ke Menu Utama (y/n)? "; cin >> loop;
		system("cls");
	}

	return 0;
}

int menu(){
	int pil;
	cout <<"\n======= APLIKASI PESERTA VAKSINASI =======\n";
	cout <<"1. Input Data\n2. Lihat Peserta Vaksinasi\n3. Cek Status Vaksinasi\n4. Hapus Data Vaksinasi\n5. Keluar\n";
	cout <<"Pilih : ";cin >> pil;
	return pil;
}

void buatListBaru(){
	head = new typenode();
	head->jmlNode = sumNode;
	head->next = head;
}

void inputPeserta(){
	string pass;bool boolsuhu,booltensi,boolumur;int jml;
	cout << "======== PESERTA VAKSINASI ========\n";
	cout << "Screening Tahap 1\n";
	cout << " Nama\t: ";cin.ignore();getline(cin,nama);
	cout << " Umur\t: "; cin >> umur;
	cout << " NIK\t: "; cin >> nik;
	do{
		try{// error  handling untuk input jika tidak 1/2
			cout << " Dosis Vaksin ke : "; cin >> dosis;
			if(dosis != 2 && dosis != 1) throw "Pilihan antara 1/2";
		}catch(const char* e){
			cout << e << endl;
		}
	}while(dosis != 2 && dosis != 1);
	cout << "Screening Tahap 2\n";
	cout << " Suhu Badan\t: "; cin >> suhu;
	cout << " Tekanan Darah\t: "; cin >> sistol >> diastol;
	boolumur = (umur > 12);
	boolsuhu = (suhu <= 37.5);
	booltensi = ((sistol >= 100 && sistol <= 120) && (diastol >= 60 && diastol <= 90));
	pass = (boolsuhu && booltensi)? "Anda Bisa Divaksin" : "Mohon Maaf Anda belum dapat melakukan Vaksinasi";
	cout <<"Status : " << pass << "\n\n";
	if(boolsuhu && booltensi && boolumur){
		string tensi = to_string(sistol) + "/" + to_string(diastol);
		cout << "Screening Tahap 3\n";
		cout << "Daftar Vaksin Yang Tersedia\n";
		cout << "1. Sinovac\n2. Astrazaneca\n3. Moderna\n";
		cout << "Vaksin Yang Kita Pilih No : "; cin >> vaksin;
		cout << " Penginputan Data Selesai\n";
		inputList(nama,umur,nik,suhu,dosis - 1,tensi,vaksin);
	}
}
void inputList(string nama, int umur, int nik, double suhu,int dosis,string tensi, int vaksin){
	typeptr nb;
	nb = new typenode();
	nb->info.nama = nama;
	nb->info.umur = umur;
	nb->info.nik = nik;
	nb->info.statusVaksin = dosis;
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
	cout << "\n======== LIST PESERTA VAKSINASI ========\n\n";
	if(head->next == head) listkosong;
	else{
		temp = head->next;
		cout << string(110,'-') << endl;
		cout <<"|" <<  setw(12) << "NIK" << setw(10) << 
		"|" <<  setw(12) << "Nama" << setw(10) 
		<< "|" << setw(11) << "Umur" << setw(9) 
		<< "|" << setw(7) << "Suhu" << setw(5) << "|"
		<< setw(8) << "Tensi" << setw(4) << "|"
		<<  setw(15) << "Tipe Vaksin" << setw(7) << "|\n";
		cout << string(110,'-') << endl;
		while(temp != head){
			cout <<"|" <<  setw(15) << temp->info.nik << setw(7) << 
			"|" <<  setw(12) << temp->info.nama << setw(10) 
			<< "|" << setw(9) << temp->info.umur << setw(11) 
			<< "|" << setw(6) << temp->info.suhu << setw(6) << "|"
			<< setw(8) << temp->info.tensi << setw(4) << "|"
			<<  setw(12) << tipeVaksin[temp->info.tipeVaksin - 1] << setw(10) << "|\n";
			temp = temp->next;
		}
		cout << string(110,'-') << endl;
		enter;
		cout << "Jumlah Peserta Vaksinasi : " << head->jmlNode;
		enter;
	}
}

void check(){
	cout << "\n======== DATA PESERTA VAKSINASI ========\n";
	cout << "Silahkan Masukkan NIK yang ingin anda cek\n NIK : "; cin >> nik;
	cout << "\n======== LIST DATA PESERTA NIK ========\n\n";
	cout << string(110,'-') << endl;
	cout <<"|" <<  setw(12) << "NIK" << setw(10) << 
		"|" <<  setw(12) << "Nama" << setw(10) 
		<< "|" << setw(11) << "Umur" << setw(9) 
		<< "|" << setw(7) << "Suhu" << setw(5) << "|"
		<< setw(8) << "Tensi" << setw(4) << "|"
		<<  setw(15) << "Tipe Vaksin" << setw(7) << "|\n";
	cout << string(110,'-') << endl;
	char inject,confirm; 
	temp = head->next;
	while(temp != head){
		if(temp->info.nik == nik){
			cout <<"|" <<  setw(15) << temp->info.nik << setw(7) << 
			"|" <<  setw(12) << temp->info.nama << setw(10) 
			<< "|" << setw(9) << temp->info.umur << setw(11) 
			<< "|" << setw(6) << temp->info.suhu << setw(6) << "|"
			<< setw(8) << temp->info.tensi << setw(4) << "|"
			<<  setw(12) << tipeVaksin[temp->info.tipeVaksin - 1] << setw(10) << "|\n";
			cout << string(110,'-') << endl << endl;
			cout << "Status Vaksin : " << statusVaksin[temp->info.statusVaksin] << "\n";
			if(temp->info.statusVaksin < 2){
				cout << "Lakukan Vaksinasi ? "; cin >> inject;
				cout << "Yakin ? "; cin >> confirm;
				if((inject == 'y' || inject == 'Y') && (confirm == 'y' || confirm == 'Y')) temp->info.statusVaksin++;
			}
		}
		temp = temp->next;
	}
	enter;
}

void hapusPeserta(int nikHapus){
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
			sumNode--;
			head->jmlNode--;
			cout << "Peserta Vaksinasi dengan NIK " << nik << " berhasil terhapus dari list...\n";
		}
	}	
}