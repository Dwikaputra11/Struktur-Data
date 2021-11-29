#include <iostream>
#include <fstream>
#include "Kereta.h"

int bound = 30;
int countEmpty = 0, countValue = 0;
Kereta *firstValue,*lastValue,*firstEmpty,*lastEmpty;
void create(){
	cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
    // train = new Kereta;//(Kereta*)malloc(sizeof(Kereta));
	firstValue = new Kereta; 
	lastValue = new Kereta;
	firstEmpty = new Kereta;
	lastEmpty = new Kereta;
	firstValue = NULL;
	lastValue = NULL;
	lastEmpty = NULL;
	firstEmpty = NULL;
};
using namespace std;

int main(int argc, char const *argv[])
{
    create();
    string nama;
    int pos,n;

    cout << "Banyak bookingan (<30) : "; cin >> n;
    while (n--)
    {
        cout << "Nama : ";cin.ignore();getline(cin,nama);//cin.getline(nama,sizeof(nama));
        cout << "Position : ";cin >> pos;
        input(nama,pos);
    }
    display();

    
    return 0;
}