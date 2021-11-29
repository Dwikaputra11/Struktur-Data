#ifndef __KERETA
#define __KERETA

#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;
extern int bound;
extern int countEmpty,countValue;
// typedef struct Kereta *typeptr;
struct Kereta
{
    string nama;
    int no_penumpang;
    Kereta *next;
    int kosong;
};
extern Kereta *firstValue, *firstEmpty, *lastValue, *lastEmpty;

// typeptr first,last;

void input(string,int);
void display();
void clear(char*);
void checkEmpty();

#endif
