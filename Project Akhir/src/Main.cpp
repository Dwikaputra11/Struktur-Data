#include <iostream>
#include <fstream>
#include "Kereta.h"
#include "Pesawat.h"

int bound = 30;
int countEmpty = 0, countValue = 0;
Kereta *trainFirstValue,*trainLastValue,*trainFirstEmpty,*trainLastEmpty;
Pesawat *planeFirstValue, *planeLastValue, *planeFirstEmpty, *planeLastEmpty;
string trainBooking = "trainBooking.txt";
string trainEmptySeat = "trainEmptySeat.txt";
string airPlaneBooking = "airPlaneBooking.txt";
string airPlaneEmptySeat = "airPlaneEmptySeat.txt";

using namespace std;

int main(int argc, char const *argv[])
{
    int n,num,to,from;
    char y;
    cout << "Banyak bookingan (<30) : "; cin >> n;
    string nama[n],mNama;
    int pos[n],mPos;
    for(int i = 0; i < n; i++)
    {
        bool redo = true;
        while(redo){
            cout << "Nama : ";cin.ignore();getline(cin,mNama);
            cout << "Position : ";cin >> mPos;

            if(!isBookedTrain(mPos)){
                nama[i] = mNama;
                pos[i] = mPos;
                redo = false;
            }else{
                char lihat;
                cout << "Nomor seat sudah dibooking!\n";
                cout << "Silahkan Input Ulang !\n"; system("pause");
                cout << "Lihat Daftar Booking (y/n) ?"; cin >> lihat;
                if(lihat == 'y'){
                    displayTrain();
                }
            }
        }
    }
    writeFileBookingTrain(nama,pos,n);
    readFileBookingTrain();
    readEmptySeatTrain();
    displayTrain();

    cout << "\nUpdate ? (y/n) "; cin >> y;
    if(y == 'y' || y == 'Y'){
        cout << "Nomor seat yang mau dipindah : "; cin >> from;
        cout << "Nomor seat yang mau dibooking : "; cin >> to;
        updateFileBookingTrain(from,to);
        displayTrain();
        // cout << "Nomor seat yang mau dihapus : "; cin >> num;
        // removeFromBooking(num);
        // display();
    }

    
    return 0;
}