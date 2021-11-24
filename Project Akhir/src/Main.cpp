#include <iostream>
#include <fstream>
#include "Kereta.h"

int bound = 30,temp;
int firstValue = 0,lastValue = 0,firstEmpty = 0,lastEmpty = 0,countEmpty = 0;
using namespace std;

int main(int argc, char const *argv[])
{
    Kereta *train;
    create(train);

    char nama[50];
    int pos;

    cout << "Nama : ";cin.ignore();cin.getline(nama,sizeof(nama));
    cout << "Position : ";cin >> pos;

    input(train,nama,pos);
    display(train);

    
    return 0;
}