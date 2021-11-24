#ifndef __KERETA
#define __KERETA

#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;
int firstValue = 0,lastValue = 0,firstEmpty = 0,lastEmpty = 0,countEmpty = 0;
extern int bound;
extern int temp;

struct Kereta
{
    string nama;
    int no_penumpang;
    int next;
};

// TODO: masih error disini
void create(Kereta *train);
void input(Kereta *train,const char*,int);
void display(Kereta train);
void clear(Kereta *train,const char*);
void checkEmpty(Kereta *train);

#endif
