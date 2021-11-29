#ifndef __KERETA
#define __KERETA

#include <iostream>
#include <string>
#include <malloc.h>
#include <fstream>
#include <limits>
using namespace std;
extern int bound;
extern int countEmpty,countValue;
extern string nameFileBooking;
extern string nameFileEmptySeat;
struct Kereta
{
    string nama;
    int no_penumpang;
    Kereta *next;
    int kosong;
};
extern Kereta *firstValue, *firstEmpty, *lastValue, *lastEmpty;

// typeptr first,last;
void create();
void input(string,int);
void display();
void clear(char*);
void checkEmpty();

// write and read from file
void writeFileBooking(string[],int[],int);
void readFileBooking();
void writeEmptySeat(string[],int[],int);
void readEmptySeat();
void updateFileBooking(); 
void updateEmptySeat();
void removeFromBooking(int);

#endif
