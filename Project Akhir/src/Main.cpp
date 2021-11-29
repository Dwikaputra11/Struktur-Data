#include <iostream>
#include <fstream>
#include "Kereta.h"

int bound = 30;
int countEmpty = 0, countValue = 0;
Kereta *firstValue,*lastValue,*firstEmpty,*lastEmpty;
string nameFileBooking = "trainBooking.txt";
string nameFileEmptySeat = "trainEmptySeat.txt";

using namespace std;

int main(int argc, char const *argv[])
{
    int n,num;
    char y;
    cout << "Banyak bookingan (<30) : "; cin >> n;
    string nama[n];
    int pos[n];
    for(int i = 0; i < n; i++)
    {
        cout << "Nama : ";cin.ignore();getline(cin,nama[i]);//cin.getline(nama,sizeof(nama));
        cout << "Position : ";cin >> pos[i];
    }
    writeFileBooking(nama,pos,n);
    readFileBooking();
    readEmptySeat();
    display();

    cout << "\nUpdate ? (y/n) "; cin >> y;
    if(y == 'y' || y == 'Y'){
        cout << "Nomor seat yang mau dihapus : "; cin >> num;
        removeFromBooking(num);
        display();
    }

    
    return 0;
}