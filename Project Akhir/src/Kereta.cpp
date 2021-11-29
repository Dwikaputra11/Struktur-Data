#include "Kereta.h"

void create(){
	cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
    // train = new Kereta;//(Kereta*)malloc(sizeof(Kereta));
	firstValue = new Kereta; 
	lastValue = new Kereta;
	firstEmpty = new Kereta;
	lastEmpty = new Kereta;
	firstValue = NULL;
	lastValue = NULL;
	lastEmpty = NULL;
	firstEmpty = NULL;
};

void input(string name,int num){ // stack
	cout << "Masuk Input\n";
	Kereta *train;
	train = new Kereta;
	train->nama = name;
	train->no_penumpang = num;
	cout << train->nama << " " << train->no_penumpang << endl;

	if(firstValue == NULL){
		firstValue = train;
		lastValue = train;
		lastValue->next = NULL;
	}else{
		train->next = firstValue;
		firstValue = train;
	}
	countValue++;
}
void checkEmpty(){
	countEmpty = 0;
	cout << "Masuk Check Empty\n";
    Kereta *temp,*empty;
	for(int i = 1; i <= bound; i++){
		temp = firstValue;
		while(temp->no_penumpang != i && temp->next != NULL){
			temp = temp->next;
		}
		if(temp->no_penumpang != i){
			empty = new Kereta;
			empty ->kosong = i;
			if(firstEmpty == NULL){
				firstEmpty = empty;
				lastEmpty = empty;
				lastEmpty->next = NULL;
			}else{
				lastEmpty->next = empty;
				lastEmpty = empty;
				lastEmpty->next = NULL;
			}
			countEmpty++;
		}
	}
}
void display(){
	// checkEmpty();
	Kereta *temp;
    temp = firstValue;
	int count = 0;
    cout << "\nSeat yang telah di booking : \n";
	cout << "Jumlah Booking : " << countValue << endl;
    while(temp != NULL && count != 5){
        cout << "Seat nomor " << temp->no_penumpang << " atas nama " << temp->nama << "\n";
        temp = temp->next;
		count++;
	}

    cout << "\nSeat Kosong : \n";
	cout << "Jumlah Seat Kosong : " << countEmpty << endl;
    temp = firstEmpty;
    while(temp != NULL){
        cout << temp->kosong << " ";
        temp = temp->next;
    }
}

/* ============ FILE SECTION ============ */

/* READ & WRITE FILE BOOKING */
void writeFileBooking(string nama[],int pos[],int n){
	create();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
		input(nama[i],pos[i]);
	}
	Kereta *temp;
	ofstream myFile;
	myFile.open(nameFileBooking,ios::trunc);
	temp = firstValue;
	while(temp != NULL){
		myFile << temp->nama << endl;
		myFile << temp->no_penumpang << endl;
		temp = temp -> next;
	}
	myFile.close();
	writeEmptySeat(nama,pos,n);
}
void readFileBooking(){
	create();
	ifstream myFile;
	string nama;
	int no;
	myFile.open(nameFileBooking);
	if(myFile.is_open()){
		while(myFile >> nama){
			Kereta *train;
			train = new Kereta;
			train->nama = nama;
			myFile >> no; 
			train->no_penumpang = no;
			// cout << "nama : " << nama << " no : " << no << endl;

			if(firstValue == NULL){
				// cout << "First Value NULL\n";
				firstValue = train; 
				lastValue = train;
				lastValue->next = NULL;
			}else{
				lastValue->next = train;
				lastValue = train;
				lastValue->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
	// readEmptySeat();
}
/* END OF READ & WRITE FILE BOOKING */

/* READ & WRITE FILE EMPTY SEAT */
void writeEmptySeat(string nama[],int pos[],int n){ // queue
	create();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
		input(nama[i],pos[i]);
	}
	checkEmpty(); 
	Kereta *temp;
	ofstream myFile;
	myFile.open(nameFileEmptySeat,ios::trunc);
	temp = firstEmpty;
	while(temp != NULL){
		myFile << temp->kosong << endl;
		temp = temp -> next;
	}
	myFile.close();
}
void readEmptySeat(){
	create();
	ifstream myFile;
	int no;
	myFile.open(nameFileEmptySeat);
	if(myFile.is_open()){
		while(myFile >> no){
			Kereta *train;
			train = new Kereta;
			train->kosong = no;
			// cout << " no : " << no << endl;

			if(firstEmpty == NULL){
				// cout << "First Value NULL\n";
				firstEmpty = train; 
				lastEmpty = train;
				lastEmpty->next = NULL;
			}else{
				lastEmpty->next = train;
				lastEmpty = train;
				lastEmpty->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE EMPTY SEAT */

/* DELETE FILE BOOKING */
void removeFromBooking(int no){
	readFileBooking();
	cout << "Masuk Remove\n";
	bool isBook = true;
	cout << "isBook " << isBook << endl;
	Kereta *hapus,*temp;
	hapus = new Kereta;
	if(firstValue->no_penumpang == no){
		hapus = firstValue;
		firstValue = hapus->next;
		free(hapus);
	}else{
		temp = firstValue;
		while(temp ->next -> no_penumpang != no && temp != NULL){
			temp = temp->next;
		}
		hapus = temp->next;
		if(hapus == NULL){
			cout << "No Penumpang Belum Booking\n";
			isBook = false;
		}else if(hapus == lastValue){
			lastValue = temp;
			lastValue->next = NULL;
		}else{
			temp->next = hapus->next;
		}
	}

	if(isBook){
		countValue--; 
		cout << "\nADA\n";
		free(hapus);
		// update file booking
		Kereta *value;
		ofstream fileBooking;
		fileBooking.open(nameFileBooking,ios::trunc);
		value = firstValue;
		while(value != NULL){
			fileBooking << value->nama << endl;
			fileBooking << value->no_penumpang << endl;
			value = value -> next;
		}
		fileBooking.close();
		checkEmpty();
		// update file empty seat
		Kereta *empty;
		ofstream fileEmptySeat;
		fileEmptySeat.open(nameFileEmptySeat,ios::trunc);
		empty = firstEmpty;
		while(empty != NULL){
			fileEmptySeat << empty->kosong << endl;
			empty = empty -> next;
		}
		fileEmptySeat.close();
		cout << "Nomor Seat Berhasil dihapus dari list\n";
	}
	
}
/* END OF DELETE FILE BOOKING */


// void clear(Kereta *train,const char* nama);

/* ============ END OF FILE SECTION ============ */