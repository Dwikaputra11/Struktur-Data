#include "Pesawat.h"

void createAirPlane(){ // membuat linklist struct Pesawat
	// cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
	planeFirstValue = new Pesawat; 
	planeLastValue = new Pesawat;
	planeFirstEmpty = new Pesawat;
	planeLastEmpty = new Pesawat;
	planeFirstValue = NULL;
	planeLastValue = NULL;
	planeLastEmpty = NULL;
	planeFirstEmpty = NULL;
};

void inputAirPlane(string name,int num){ // Dimasukan ke File dengan metode Stack;
	Pesawat *plane;
	plane = new Pesawat;
	plane->nama = name;
	plane->no_penumpang = num;

	if(planeFirstValue == NULL){
		planeFirstValue = plane;
		planeLastValue = plane;
		planeLastValue->next = NULL;
	}else{
		plane->next = planeFirstValue;
		planeFirstValue = plane;
	}
	countValue++;
}
void checkEmptyAirPlane(){ // Mengecek seat kosong dari pemesanan seat
	countEmpty = 0;
    Pesawat *temp,*empty;
	for(int i = 1; i <= bound; i++){
		temp = planeFirstValue;
		while(temp->no_penumpang != i && temp->next != NULL){
			temp = temp->next;
		}
		if(temp->no_penumpang != i){
			empty = new Pesawat;
			empty ->kosong = i;
			if(planeFirstEmpty == NULL){
				planeFirstEmpty = empty;
				planeLastEmpty = empty;
				planeLastEmpty->next = NULL;
			}else{
				planeLastEmpty->next = empty;
				planeLastEmpty = empty;
				planeLastEmpty->next = NULL;
			}
			countEmpty++;
		}
	}
}
void displayAirPlane(){ // Ditampilakn dengan metode queue
	int count = 1;
    cout << "\nSeat yang telah di booking : \n";
	cout << "Jumlah Booking : " << countValue << endl;
	int x = 4; // jarak enter untuk mengerluarkan "-"
	int y = 2; // jarak enter untuk mengeluarkan nomor atau karakter
	int t = 0; // untuk index dalam pengecekan nomor dari player1
	int a = 0; // untuk index dalam pengecekan nomor dari player2
	
	for(int i = 0; i < 25; i++){
		int p = 9; // jarak spasi untuk memunculkan "|"
        if(i == x){
            for(int j = 0; j < 39; j++){
                if(j >= 18 && j <= 21){
                    cout << " ";
                }else{
                    cout << "-";
                }
            }
            cout << endl;
            x+=4;
        }else if(i == y){
            int r = 5; // jarak spasi untuk memunculkan nomor
			y = y + 4;
            for(int j = 1; j < 39; j++ ){
                if(j == p){
                    cout << "|";
                    if(p == 18){
                        p += 13;
                    }else{
                        p += 9;
                    }
                }else 
                if(j == r){
					Pesawat *tempValue,*tempEmpty;
					tempEmpty = planeFirstEmpty;
					tempValue = planeFirstValue;
					while(tempValue -> no_penumpang != count && tempValue -> next != NULL){
						tempValue = tempValue->next;
					}
                    if(tempValue -> next == NULL && tempValue -> no_penumpang != count){
						cout << "X";	
					}else{
						cout << "O";
					}
					count++;
                    if(r == 14){
                        r += 13;
                    }else{
                        r = r + 9;
                    }	
                }else if(j == 22){
                    cout << "|";
                }else {
                    cout << " ";// spasi pada baris yang muncul angka
                }
            }
            cout << endl;
        }else{
            int num = 0;
            for(int j = 1; j < 39; j++ ){
                // if(j == 27){
                //     cout << " " << endl;
                // }
                if(j == p){
                    cout << "|";
                    if(p == 18){
                        p += 13;
                    }else{
                        p = p + 9;
                    }
                }else if(j == 22){
                    cout << "|";
                }else{
                    cout << " ";
                }	
            }
            cout << endl;
        }	
	}
	cout << "\n\nKeterangan\n";
	cout << "O : Telah dibooking\n";
	cout << "X : Belum dibooking\n";
}

bool isBookedAirPlane(int no){ // mengecek apakah seat sudah dibooking
	readFileBookingAirPlane();
	bool status = false;
	Pesawat *temp;
	temp = planeFirstValue;

	while(temp != NULL){
		if(temp->no_penumpang == no){
			status = true;
			break;
		}
		temp = temp->next;
	}

	return status;
}

/* ============ FILE SECTION ============ */

/* READ & WRITE FILE BOOKING */
void writeFileBookingAirPlane(string nama[],int pos[],int n){ // menulis data ke File
	createAirPlane();
	countValue = 0;
	for(int i = 0; i < n; i++){
		// cout << nama[i] << " " << pos[i] << endl;
		inputAirPlane(nama[i],pos[i]);
	}
	Pesawat *temp;
	ofstream myFile;
	myFile.open(airPlaneBooking,ios::app);
	temp = planeFirstValue;
	while(temp != NULL){
		myFile << temp->nama << endl;
		myFile << temp->no_penumpang << endl;
		temp = temp -> next;
	}
	myFile.close();
	writeEmptySeatAirPlane(nama,pos,n);
}
void readFileBookingAirPlane(){ // membaca data dari File
	countValue = 0;
	createAirPlane();
	ifstream myFile;
	string nama;
	int no;
	myFile.open(airPlaneBooking);
	if(myFile.is_open()){
		while(myFile >> nama){
			Pesawat *plane;
			plane = new Pesawat;
			plane->nama = nama;
			myFile >> no; 
			plane->no_penumpang = no;

			if(planeFirstValue == NULL){
				planeFirstValue = plane; 
				planeLastValue = plane;
				planeLastValue->next = NULL;
			}else{
				planeLastValue->next = plane;
				planeLastValue = plane;
				planeLastValue->next = NULL;
			}
			countValue++;
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE BOOKING */

/* READ & WRITE FILE EMPTY SEAT */
void writeEmptySeatAirPlane(string nama[],int pos[],int n){ // Ditulis dengan Metode Queue
	createAirPlane();
	countValue = 0;
	for(int i = 0; i < n; i++){
		inputAirPlane(nama[i],pos[i]);
	}
	checkEmptyAirPlane(); 
	Pesawat *temp;
	ofstream myFile;
	myFile.open(airPlaneEmptySeat,ios::trunc);
	temp = planeFirstEmpty;
	while(temp != NULL){
		myFile << temp->kosong << endl;
		temp = temp -> next;
	}
	myFile.close();
}
void readEmptySeatAirPlane(){ // Membaca file seat kosong
	// createAirPlane();
	ifstream myFile;
	int no;
	myFile.open(airPlaneEmptySeat);
	if(myFile.is_open()){
		while(myFile >> no){
			Pesawat *plane;
			plane = new Pesawat;
			plane->kosong = no;

			if(planeFirstEmpty == NULL){
				planeFirstEmpty = plane; 
				planeLastEmpty = plane;
				planeLastEmpty->next = NULL;
			}else{
				planeLastEmpty->next = plane;
				planeLastEmpty = plane;
				planeLastEmpty->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE EMPTY SEAT */

/* DELETE FILE BOOKING */
void removeFromBookingAirPlane(int no){ // membatalkan pemesanan
	readFileBookingAirPlane(); // membaca file dimasukkan ke linklist
	// cout << "Masuk Remove\n";
	bool isBook = true;
	// cout << "isBook " << isBook << endl;
	Pesawat *hapus,*temp;
	hapus = new Pesawat;
	if(planeFirstValue->no_penumpang == no){
		hapus = planeFirstValue;
		planeFirstValue = hapus->next;
		free(hapus);
	}else{
		temp = planeFirstValue;
		while(temp ->next -> no_penumpang != no && temp != NULL){
			temp = temp->next;
		}
		hapus = temp->next;
		if(hapus == NULL){
			cout << "No Penumpang Belum Booking\n";
			isBook = false;
		}else if(hapus == planeLastValue){
			planeLastValue = temp;
			planeLastValue->next = NULL;
		}else{
			temp->next = hapus->next;
		}
	}

	if(isBook){
		countValue--; 
		// cout << "\nADA\n";
		free(hapus);
		// update file booking
		Pesawat *value;
		ofstream fileBooking;
		fileBooking.open(airPlaneBooking,ios::trunc);
		value = planeFirstValue;
		while(value != NULL){
			fileBooking << value->nama << endl;
			fileBooking << value->no_penumpang << endl;
			value = value -> next;
		}
		fileBooking.close();
		checkEmptyAirPlane();
		// update file empty seat
		Pesawat *empty;
		ofstream fileEmptySeat;
		fileEmptySeat.open(airPlaneEmptySeat,ios::trunc);
		empty = planeFirstEmpty;
		while(empty != NULL){
			fileEmptySeat << empty->kosong << endl;
			empty = empty -> next;
		}
		fileEmptySeat.close();
		cout << "Nomor Seat Berhasil dihapus dari list\n";
	}
	
}
/* END OF DELETE FILE BOOKING */

/* UPDATE FILE BOOKING */
void updateFileBookingAirPlane(int from, int to){ // menukar nomor seat dengan yang diingkan
	readFileBookingAirPlane();
	// cout << "Masuk Update Booking\n";
	bool isFound = false;
	Pesawat *temp,*node;
	node = new Pesawat;
	// node->no_penumpang = to;

	temp = planeFirstValue;
	while(temp -> no_penumpang != from && temp != NULL){
		temp = temp->next;
	}
	if(temp == NULL){
		cout << "Nomor seat belum dibooking!\n";
	}else{
		cout << "Nomer seat Ditemukan\n";
		temp->no_penumpang = to;
		Pesawat *value;
		ofstream fileBooking;
		fileBooking.open(airPlaneBooking,ios::trunc);
		value = planeFirstValue;
		while(value != NULL){
			fileBooking << value->nama << endl;
			fileBooking << value->no_penumpang << endl;
			value = value -> next;
		}
		fileBooking.close();
		checkEmptyAirPlane();
		// update file empty seat
		Pesawat *empty;
		ofstream fileEmptySeat;
		fileEmptySeat.open(airPlaneEmptySeat,ios::trunc);
		empty = planeFirstEmpty;
		while(empty != NULL){
			fileEmptySeat << empty->kosong << endl;
			empty = empty -> next;
		}
		fileEmptySeat.close();
		cout << "Nomor seat berhasil dipindahkan!\n";
	}

}	
/* END OF UPDATE FILE BOOKING */


/* ============ END OF FILE SECTION ============ */
