#ifndef __KERETA
#define __KERETA

#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;
extern int bound;
extern int temp;
extern int firstValue,firstEmpty,lastValue,lastEmpty,countEmpty;

struct Kereta
{
    char nama[50];
    int no_penumpang;
    int next;
    int kosong[100];
};

// TODO: masih error disini
void create(Kereta *train);
void input(Kereta *train,char*,int);
void display(Kereta *train);
void clear(Kereta *train,char*);
void checkEmpty(Kereta *train);

#endif
