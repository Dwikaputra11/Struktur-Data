#ifndef __PESAWAT
#define __PESAWAT

#include <iostream>
#include <string>
#include <malloc.h>
#include <fstream>
#include <limits>
using namespace std;
extern int bound;
extern int countEmpty,countValue;
extern string airPlaneBooking;
extern string airPlaneEmptySeat;
struct Pesawat
{
    string nama;
    int no_penumpang;
    Pesawat *next;
    int kosong;
};
extern Pesawat *planeFirstValue, *planeLastValue, *planeFirstEmpty, *planeLastEmpty;

// typeptr first,last;
void createAirPlane();
void inputAirPlane(string,int);
void displayAirPlane();
void checkEmptyAirPlane();
bool isBookedAirPlane(int);

// write and read from file
void writeFileBookingAirPlane(string[],int[],int);
void readFileBookingAirPlane();
void writeEmptySeatAirPlane(string[],int[],int);
void readEmptySeatAirPlane();
void updateFileBookingAirPlane(int,int); 
void updateEmptySeatAirPlane();
void removeFromBookingAirPlane(int);

#endif
