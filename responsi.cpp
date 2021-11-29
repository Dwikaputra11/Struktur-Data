#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include <string>

typedef struct Data *typeptr;
struct Data{
    int no;
    typeptr next;
};
typeptr awal,akhir;
typeptr pinjamAwal,pinjamAkhir;

using namespace std;

int jumlahData = 0;
int jumlahPinjam = 0;
string namaFileDaftar = "data.txt";
string namaFilePinjam= "pinjam.txt";

int menu();
void daftar();
int readData();
void tambah();
void buatList();
void tambahFile(int[],int);
void tambahFile(int);
void updateFile();
void pinjam();
void daftarPinjam();
void tambahFilePinjam(int);
void kembali();
void updateFileKembalian(int);

int main()
{   
    while(true){

        int pilih = menu();

        switch (pilih)
        {
        case 1:
            tambah();
            break;
        case 2:
            pinjam();
            break;
        case 3:
            daftar();
            break;
        case 4:
            kembali();
            break;
        case 5:
            daftarPinjam();
            break;
        default:
            break;
        }
        // cout << "ulang ? "; cin >> ulang;
    }
    

    return 0;
}

int menu(){
    int p; 
    cout << "MENU\n";
    cout << "1. TAMBAH STOK BARU\n";
    cout << "2. PINJAM BUKU\n";
    cout << "3. LIHAT DAFTAR STOK BUKU\n";
    cout << "4. KEMBALIKAN BUKU\n";
    cout << "5. LIHAT DAFTAR BUKU YANG DINPINJAM\n";
    cout << "6. EXIT\n";
    cout << "Pilih : "; cin >> p;

    return p; 
}

void buatList(){
    awal = new Data();
    akhir = new Data();
    awal = NULL;
    akhir = NULL;
}

void daftar(){ // stack
    buatList();
    jumlahData = readData();
    typeptr temp;
    temp = awal;
    cout << "==== Daftar Stok Buku ====\n";
    while(temp != NULL){
        cout << temp->no << endl;
        temp = temp->next;
    }
}
void tambah(){
    int n,no;
    cout << "Jumlah buku yang diinput : "; cin >> n;
    int a[n];
    int i = 0;
    while(n--){
        cout << "Nomor Buku : "; cin >> a[i];
        i++;
    }
    tambahFile(a,i);
}

void tambahFile(int a[], int i){
    ofstream myFile;
    myFile.open(namaFileDaftar,ios::app);
    while(--i >= 0){
        myFile << a[i] << endl;
    }
    myFile.close();
}
void tambahFile(int a){
    ofstream myFile;
    myFile.open(namaFileDaftar,ios::app);
    myFile << a << endl;
    myFile.close();
}

void updateFile(){
    ofstream myFile;
    myFile.open(namaFileDaftar,ios::trunc);
    typeptr temp;
    temp = awal;
    while(temp != NULL){
        myFile << temp->no << endl;
        temp = temp->next;
    }
    myFile.close();
}
void updateFileKembalian(int no){
    buatList();
    readData();
    ofstream myFile;
    myFile.open(namaFileDaftar,ios::trunc);
    typeptr data,temp;
    data = new Data;
    data->no = no;
    data->next = awal;
    awal = data;
    temp = awal;
    while(temp != NULL){
        myFile << temp->no << endl;
        temp = temp->next;
    }
    myFile.close();
}

int readData(){
    ifstream myFile;
	myFile.open(namaFileDaftar);
    int no = 0;
	int sumData = 0;
	if(myFile.is_open()){
		while(myFile >> no){
            typeptr data;
            data = new Data();
            data->no = no;
            if(awal == NULL){
                awal = data;
                akhir = data;
                akhir -> next = NULL;
            }else{
                akhir->next = data;
                akhir = data;
                akhir->next = NULL;
            }
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
			sumData++;
		}
        myFile.close();
		return sumData; 
	}else{
		return -1;
    }
}

/* PINJAM */
void tambahFilePinjam(int no){
    ofstream myFile;
    myFile.open(namaFilePinjam,ios::app);
    myFile << no << endl;
    myFile.close();
}
void updateFilePinjam(){
    ofstream myFile;
    myFile.open(namaFilePinjam,ios::trunc);
    typeptr temp;
    temp = awal;
    while(temp != NULL){
        myFile << temp->no << endl;
        temp = temp->next;
    }
    myFile.close();
}
void pinjam(){
    buatList();
    jumlahData = readData();
    if(jumlahData == 0){
        cout << "Data Masih Kosong!\n";
    }else{
        typeptr hapus,data;
        data = new Data();
        hapus = new Data();
        hapus = awal;
        typeptr temp;
        data ->no = awal->no;
        awal = hapus->next;
        tambahFilePinjam(data->no);
        updateFile();
        free(hapus);
        cout << "BUKU BERHASIL DIPINJAM\n";
    }   
}
int readDataPinjam(){
    buatList();
    ifstream myFile;
	myFile.open(namaFilePinjam);
    int no = 0;
	int sumData = 0;
	if(myFile.is_open()){
		while(myFile >> no){
            typeptr data;
            data = new Data();
            data->no = no;
            if(awal == NULL){
                awal = data;
                akhir = data;
                akhir -> next = NULL;
            }else{
                data->next = awal;
                awal = data;
            }
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
			sumData++;
		}
        myFile.close();
		return sumData; 
	}else{
		return -1;
	}
}
void daftarPinjam(){ // queue
    cout << "==== Daftar Buku Yang Dipinjam ====\n";
    typeptr temp;
    int sum = readDataPinjam();
    temp = awal;
    while(temp != NULL){
        cout << temp->no << endl; 
        temp = temp->next;
    }
}
/* AKHIR PINJAM */

void kembali(){
    readDataPinjam();
    typeptr data,temp,hapus;
    hapus = new Data();
    data = new Data();
    data->no = akhir->no;
    temp = awal;
    while(temp->next != akhir){
        temp = temp->next;
    }
    updateFilePinjam();
    updateFileKembalian(data->no);
    akhir = temp;
    free(hapus);
    cout << "BUKU BERHASIL DIKEMBALIKAN\n";
}
