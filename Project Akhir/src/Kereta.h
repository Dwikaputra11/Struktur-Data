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
extern string trainBooking;
extern string trainEmptySeat;
struct Kereta
{
    string nama;
    int no_penumpang;
    Kereta *next;
    int kosong;
};
extern Kereta *trainFirstValue,*trainLastValue,*trainFirstEmpty,*trainLastEmpty;

// typeptr first,last;
void creatTrain();
void inputTrain(string,int);
void displayTrain();
void checkEmptyTrain();
bool isBookedTrain(int);

// write and read from file
void writeFileBookingTrain(string[],int[],int);
void readFileBookingTrain();
void writeEmptySeatTrain(string[],int[],int);
void readEmptySeatTrain();
void updateFileBookingTrain(int,int); 
void updateEmptySeatTrain();
void removeFromBookingTrain(int);

#endif
