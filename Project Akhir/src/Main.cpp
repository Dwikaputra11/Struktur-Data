#include <iostream>
#include <fstream>
#include "Kereta.h"
#include "Kereta.cpp"

int bound = 30,temp;
using namespace std;

int main(int argc, char const *argv[])
{
    Kereta *train;
    create(&train);

    string nama;
    int pos;

    cout << "Nama : ";cin >> nama;
    cout << "Position : ";cin >> pos;

    // input(&train,nama,pos);
    // display(train);

    
    return 0;
}