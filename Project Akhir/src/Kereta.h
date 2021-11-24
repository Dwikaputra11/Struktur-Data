#ifndef __KERETA
#define __KERETA

#include <iostream>
#include <string>
using namespace std;
extern int bound;

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
