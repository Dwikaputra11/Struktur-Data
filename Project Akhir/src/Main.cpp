#include <iostream>
#include <fstream>
#include <vector>
#include "Kereta.h"
#include "Pesawat.h"

int bound = 30;
int countEmpty = 0, countValue = 0;
Kereta *trainFirstValue,*trainLastValue,*trainFirstEmpty,*trainLastEmpty;
Pesawat *planeFirstValue, *planeLastValue, *planeFirstEmpty, *planeLastEmpty;
string trainBooking;
string trainEmptySeat;
string airPlaneBooking;
string airPlaneEmptySeat;
string ruteKereta,rutePesawat;

using namespace std;

void kereta(), pesawat(), exit(), inputKereta();
int menu();
void showKereta();
void inputKereta();
void showPesawat();
void inputPesawat();

int main()
{
    bool loop = true;
    int n,num,to,from,pilihan;
    char y;
    while(loop){
        system("cls");
        cout << "\t\t|===========================================================|\n";
        cout << "\t\t|\tBooking Tiket dan Seat Pesawat dan Kereta Api       |\t\n";
        cout << "\t\t|===========================================================|\n\n";
        cout << "\t\t\t1. Tiket Pesawat"<<"\n";
        cout << "\t\t\t2. Tiket Kereta Api"<< "\n";
        cout << "\t\t\t3. Keluar\n\n";
        cout << "\t\tIngin memesan tiket (1 atau 2) : ";cin>>pilihan;
        switch (pilihan)
        {
            case 1 : 
                system("cls");
                pesawat();
                break;
            case 2 : 
                system("cls");
                kereta();
                break;
            case 3 : 
                exit();
                loop = false;
        }
    }


    return 0;
}
int menu(){
    int no;
    cout << "------   Menu  ------ \n\n";
    cout << "1. Booking Tiket\n";
    cout << "2. Lihat Daftar Booking\n";
    cout << "3. Batal Booking\n";
    cout << "4. Pindah Seat\n";
    cout << "0. Kembali ke Pilih Rute\n";
    cout << "9. Kembali ke Menu Utama\n";
    cout << "Pilih \'(1/2/3/4/0/9)\': "; cin >> no;
    return no;
}

void kereta(){
    int n,num,to,from,pil;
    bool loop = true,isOpenFile = true;
    string rute[3] = {"Sleman - Semarang", "Sleman - Bogor", "Sleman - Surabaya"};
    string ruteFile[3] = {"trainSlemanToSemarang.txt", "trainSlemanToBogor.txt", "trainSlemanToSurabaya.txt"};
    string ruteFileEmpty[3] = {"trainEmptySlemanToSemarang.txt", "trainEmptySlemanToBogor.txt", "trainEmptySlemanToSurabaya.txt"};

    system("cls");
    while (loop){
        bool loopOpsi = true;
        system("cls");
        cout<<"\tPilihan Rute Booking Tiket Kereta\n";
        cout<<"1. Sleman - Semarang\n2. Sleman - Bogor\n3. Sleman - Surabaya\n0. Kembali\nTujuan Anda(1,2,3) : ";cin>>pil;
        if(pil==0)break;
        ruteKereta = rute[pil-1];
        trainBooking = ruteFile[pil-1];
        trainEmptySeat = ruteFileEmpty[pil - 1];

        system("cls");
        int del, from, to;
        while(loopOpsi){
            cout << "Rute " << ruteKereta << endl << endl;
            int opsi = menu();
            // Check File sudah ada atau tidak
            ifstream myFile;
            myFile.open(trainBooking);
            if(!myFile.is_open()){
                isOpenFile = false;
            }else isOpenFile = true;
            myFile.close();

            switch (opsi){
                case 1 : 
                    inputKereta();
                    break;
                case 2 :
                    if(isOpenFile){    
                        showKereta();
                        cout << "\n\n";
                        system("pause");
                    }else{
                        cout << "\n\nTidak bisa menampilkan pemesanan\nBelum ada pemesenan tiket yang terdata!\n";
                        system("pause");
                    }
                    break;
                case 3 : 
                    system("cls");
                    cout << "==== OPSI BATAL BOOKING ====";
                    if(isOpenFile){
                        showKereta();
                        cout << "\n\nNomor Seat yang Ingin Dibatalkan : "; cin >> del;
                        removeFromBookingTrain(del);
                        system("pause");
                    }else{
                        cout << "\n\nPembatalan Gagal!\nBelum ada pemesanan tiket yang terdata!\n";
                        system("pause");
                    }
                    break;
                case 4 : 
                    system("cls");
                    cout << "==== OPSI PEMINDAHAN SEAT ====\n";
                    if(isOpenFile){
                        showKereta();
                        cout << "\n\nNomor Seat Semula : "; cin >> from;
                        cout << "Nomor Seat yang Ingin Dibooking : "; cin >> to;
                        updateFileBookingTrain(from,to);
                        system("pause");
                    }else{
                        cout << "\n\nPembaruaan Gagal!\nBelum ada pemesanan tiket yang terdata!\n";
                        system("pause");
                    }
                    break;
                case 0 :
                    loopOpsi = false;
                    break;
                case 9 : 
                    loopOpsi = false;
                    loop = false;
                    break;
            }
            system("cls");
        }
    }
}

void inputKereta(){
    string mNama;
    int mPos;
    int num;
    cout << "Banyak Tiket di Booking : "; cin >> num;
    string nama[num];
    int pos[num];
    vector<int> v;
    for(int i = 0; i < num; i++){
        bool redo = true;
        while(redo){
            cout << "\nNama : ";cin.ignore();getline(cin,mNama);
            cout << "Position : ";cin >> mPos;
            v.push_back(mPos);

            if(v.size() == 1){
                redo = false;
            }else{
                for(int j = 1; j < v.size(); j++){
                    if(v[j] ==  v[j - 1]){
                        redo = true;
                        v.erase(v.begin() + j);
                        break;
                    }else redo = false;
                }
            }

            if(!isBookedTrain(mPos) && !redo){
                nama[i] = mNama;
                pos[i] = mPos;
            }else redo = true;

            if(redo){
                char lihat;
                cout << "Nomor seat sudah dibooking!\n";
                cout << "Silahkan Input Ulang !\n"; system("pause");
                // cout << "Lihat Daftar Booking (y/n) ?"; cin >> lihat;
                // if(lihat == 'y'){
                //     showKereta();
                // }
            }
        }
    }
    writeFileBookingTrain(nama,pos,num);
    cout << "\n\n===== Booking Berhasil! =====\n";
    system("pause");
}

void showKereta(){
    readFileBookingTrain();
    readEmptySeatTrain();
    displayTrain();
}


void exit(){
    cout<<"\n\n\n\t\t\t\tTerima Kasih Atas Kunjungan Anda\n\t\t\t\t\tStruktur Data UPN\n\t\t\t\t";
    system("pause");
}

void pesawat(){
    int pil;
    bool loop = true,isOpenFile = true;
    string rute[3] = {"Yogyakarta - Bali", "Medan - Bali", "Jakarta - Yogyakarta"};
    string ruteFile[3] = {"planeYogyaToBali.txt", "planeMedanToBali.txt","planeJakartaToYogya.txt"};
    string ruteFileEmpty[3] = {"planeEmptyYogyaToBali.txt", "planeEmptyMedanToBali.txt","planeEmptyJakartaToYogya.txt"};
    while(loop){
        bool loopOpsi = true;
        system("cls");
        cout<<"\tPilihan Rute Booking Tiket Pesawat\n";
        cout<<"1. Yogyakarta - Bali\n2. Medan - Bali\n3. Jakarta - Yogyakarta\n0. Kembali\nTujuan Anda(1,2,3) : ";cin>>pil;
        system("cls");
        if (pil==0)break;        
        rutePesawat = rute[pil - 1];
        airPlaneBooking = ruteFile[pil - 1];
        airPlaneEmptySeat = ruteFileEmpty[pil - 1];

        while(loopOpsi){
            cout << "Rute " << rutePesawat << endl << endl;
            int opsi = menu();

            // mengecek file ada atau tidak
            ifstream myFile;
            myFile.open(airPlaneBooking);
            if(!myFile.is_open()){
                isOpenFile = false;
            }else isOpenFile = true;
            myFile.close();

            int del,from, to;
            switch(opsi){
                case 1:
                    inputPesawat();
                break;
                case 2:
                    if(isOpenFile){
                        showPesawat();
                        cout << "\n\n";
                        system("pause");
                    }else{
                        cout << "\n\nTidak bisa menampilkan pemesanan\nBelum ada pemesenan tiket yang terdata!\n";
                        system("pause");
                    }
                break;
                case 3:
                    cout << "==== OPSI BATAL BOOKING ====";
                    if(isOpenFile){
                        showPesawat();
                        cout << "\n\nNomor Seat yang Ingin Dibatalkan : "; cin >> del;
                        removeFromBookingAirPlane(del);
                        system("pause");
                    }else{
                        cout << "\n\nPembatalan Gagal!\nBelum ada pemesanan tiket yang terdata!\n";
                        system("pause");
                    }
                break;
                case 4:
                    cout << "==== OPSI PEMINDAHAN SEAT ====\n";
                    if(isOpenFile){
                        showPesawat();
                        cout << "\n\nNomor Seat Semula : "; cin >> from;
                        cout << "Nomor Seat yang Ingin Dibooking : "; cin >> to;
                        updateFileBookingAirPlane(from,to);
                        system("pause");
                    }else{
                        cout << "\n\nPembaruaan Gagal!\nBelum ada pemesanan tiket yang terdata!\n";
                        system("pause");
                    }
                break;
                case 0:
                    loopOpsi = false;  
                    break;
                case 9:
                    loopOpsi = false;
                    loop = false;
                    break;
            }
            system("cls");
        }
    }
}

void inputPesawat(){
    string mNama;
    int mPos;
    int num;
    cout << "Banyak Tiket di Booking : "; cin >> num;
    string nama[num];
    int pos[num];
    vector<int> v;
    for(int i = 0; i < num; i++){
        bool redo = true;
        while(redo){
            cout << "\nNama : ";cin.ignore();getline(cin,mNama);
            cout << "Position : ";cin >> mPos;
            v.push_back(mPos);

            if(v.size() == 1){
                redo = false;
            }else{
                for(int j = 1; j < v.size(); j++){
                    if(v[j] ==  v[j - 1]){
                        redo = true;
                        v.erase(v.begin() + j);
                        break;
                    }else redo = false;
                }
            }

            if(!isBookedAirPlane(mPos) && !redo){
                nama[i] = mNama;
                pos[i] = mPos;
            }else redo = true;

            if(redo){
                char lihat;
                cout << "Nomor seat sudah dibooking!\n";
                cout << "Silahkan Input Ulang !\n"; system("pause");
                // cout << "Lihat Daftar Booking (y/n) ?"; cin >> lihat;
                // if(lihat == 'y'){
                //     showPesawat();
                // }
            }
        }
    }
    writeFileBookingAirPlane(nama,pos,num);
    cout << "\n\n===== Booking Berhasil! =====\n";
    system("pause");
}

void showPesawat(){
    readFileBookingAirPlane();
    readEmptySeatAirPlane();
    displayAirPlane();
}