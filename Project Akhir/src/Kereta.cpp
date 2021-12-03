#include "Kereta.h"

void createTrain(){ // membuat linklist struct Kereta
	// cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
	trainFirstValue = new Kereta; 
	trainLastValue = new Kereta;
	trainFirstEmpty = new Kereta;
	trainLastEmpty = new Kereta;
	trainFirstValue = NULL;
	trainLastValue = NULL;
	trainLastEmpty = NULL;
	trainFirstEmpty = NULL;
};

void inputTrain(string name,int num){ // Dimasukan ke File dengan metode Stack;
	Kereta *train;
	train = new Kereta;
	train->nama = name;
	train->no_penumpang = num;

	if(trainFirstValue == NULL){
		trainFirstValue = train;
		trainLastValue = train;
		trainLastValue->next = NULL;
	}else{
		train->next = trainFirstValue;
		trainFirstValue = train;
	}
	countValue++;
}
void checkEmptyTrain(){ // Mengecek seat kosong dari pemesanan seat
	countEmpty = 0;
    Kereta *temp,*empty;
	for(int i = 1; i <= bound; i++){
		temp = trainFirstValue;
		while(temp->no_penumpang != i && temp->next != NULL){
			temp = temp->next;
		}
		if(temp->no_penumpang != i){
			empty = new Kereta;
			empty ->kosong = i;
			if(trainFirstEmpty == NULL){
				trainFirstEmpty = empty;
				trainLastEmpty = empty;
				trainLastEmpty->next = NULL;
			}else{
				trainLastEmpty->next = empty;
				trainLastEmpty = empty;
				trainLastEmpty->next = NULL;
			}
			countEmpty++;
		}
	}
}
void displayTrain(){ // Ditampilakn dengan metode queue
	int count = 1;
    cout << "\nSeat yang telah di booking : \n";
	cout << "Jumlah Booking : " << countValue << endl;
	int x = 4; // jarak enter untuk mengerluarkan "-"
	int y = 2; // jarak enter untuk mengeluarkan nomor atau karakter
	
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
					Kereta *tempValue,*tempEmpty;
					tempEmpty = trainFirstEmpty;
					tempValue = trainFirstValue;
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

bool isBookedTrain(int no){ // mengecek apakah seat sudah dibooking
	readFileBookingTrain();
	bool status = false;
	Kereta *temp;
	temp = trainFirstValue;

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
void writeFileBookingTrain(string nama[],int pos[],int n){ // menulis data ke File
	createTrain();
	countValue = 0;
	for(int i = 0; i < n; i++){
		// cout << nama[i] << " " << pos[i] << endl;
		inputTrain(nama[i],pos[i]);
	}
	Kereta *temp;
	ofstream myFile;
	myFile.open(trainBooking,ios::app);
	temp = trainFirstValue;
	while(temp != NULL){
		myFile << temp->nama << endl;
		myFile << temp->no_penumpang << endl;
		temp = temp -> next;
	}
	myFile.close();
	writeEmptySeatTrain(nama,pos,n);
}
void readFileBookingTrain(){ // membaca data dari File
	countValue = 0;
	createTrain();
	ifstream myFile;
	string nama;
	int no;
	myFile.open(trainBooking);
	if(myFile.is_open()){
		while(myFile >> nama){
			Kereta *train;
			train = new Kereta;
			train->nama = nama;
			myFile >> no; 
			train->no_penumpang = no;

			if(trainFirstValue == NULL){
				trainFirstValue = train; 
				trainLastValue = train;
				trainLastValue->next = NULL;
			}else{
				trainLastValue->next = train;
				trainLastValue = train;
				trainLastValue->next = NULL;
			}
			countValue++;
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE BOOKING */

/* READ & WRITE FILE EMPTY SEAT */
void writeEmptySeatTrain(string nama[],int pos[],int n){ // Ditulis dengan Metode Queue
	createTrain();
	countValue = 0;
	for(int i = 0; i < n; i++){
		inputTrain(nama[i],pos[i]);
	}
	checkEmptyTrain(); 
	Kereta *temp;
	ofstream myFile;
	myFile.open(trainEmptySeat,ios::trunc);
	temp = trainFirstEmpty;
	while(temp != NULL){
		myFile << temp->kosong << endl;
		temp = temp -> next;
	}
	myFile.close();
}
void readEmptySeatTrain(){ // Membaca file seat kosong
	ifstream myFile;
	int no;
	myFile.open(trainEmptySeat);
	if(myFile.is_open()){
		while(myFile >> no){
			Kereta *train;
			train = new Kereta;
			train->kosong = no;

			if(trainFirstEmpty == NULL){
				trainFirstEmpty = train; 
				trainLastEmpty = train;
				trainLastEmpty->next = NULL;
			}else{
				trainLastEmpty->next = train;
				trainLastEmpty = train;
				trainLastEmpty->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE EMPTY SEAT */

/* DELETE FILE BOOKING */
void removeFromBookingTrain(int no){ // membatalkan pemesanan
	readFileBookingTrain(); // membaca file dimasukkan ke linklist
	bool isBook = true;
	Kereta *hapus,*temp;
	hapus = new Kereta;
	if(trainFirstValue->no_penumpang == no){
		hapus = trainFirstValue;
		trainFirstValue = hapus->next;
		free(hapus);
	}else{
		temp = trainFirstValue;
		while(temp ->next -> no_penumpang != no && temp != NULL){
			temp = temp->next;
		}
		hapus = temp->next;
		if(hapus == NULL){
			cout << "No Penumpang Belum Booking\n";
			isBook = false;
		}else if(hapus == trainLastValue){
			trainLastValue = temp;
			trainLastValue->next = NULL;
		}else{
			temp->next = hapus->next;
		}
	}

	if(isBook){
		countValue--; 
		free(hapus);
		// update file booking
		Kereta *value;
		ofstream fileBooking;
		fileBooking.open(trainBooking,ios::trunc);
		value = trainFirstValue;
		while(value != NULL){
			fileBooking << value->nama << endl;
			fileBooking << value->no_penumpang << endl;
			value = value -> next;
		}
		fileBooking.close();
		checkEmptyTrain();
		// update file empty seat
		Kereta *empty;
		ofstream fileEmptySeat;
		fileEmptySeat.open(trainEmptySeat,ios::trunc);
		empty = trainFirstEmpty;
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
void updateFileBookingTrain(int from, int to){ // menukar nomor seat dengan yang diingkan
	readFileBookingTrain();
	// cout << "Masuk Update Booking\n";
	bool isFound = false;
	Kereta *temp,*node;
	node = new Kereta;

	temp = trainFirstValue;
	while(temp -> no_penumpang != from && temp != NULL){
		temp = temp->next;
	}
	if(temp == NULL){
		cout << "Nomor seat belum dibooking!\n";
	}else{
		cout << "Nomer seat Ditemukan\n";
		temp->no_penumpang = to;
		Kereta *value;
		ofstream fileBooking;
		fileBooking.open(trainBooking,ios::trunc);
		value = trainFirstValue;
		while(value != NULL){
			fileBooking << value->nama << endl;
			fileBooking << value->no_penumpang << endl;
			value = value -> next;
		}
		fileBooking.close();
		checkEmptyTrain();
		// update file empty seat
		Kereta *empty;
		ofstream fileEmptySeat;
		fileEmptySeat.open(trainEmptySeat,ios::trunc);
		empty = trainFirstEmpty;
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