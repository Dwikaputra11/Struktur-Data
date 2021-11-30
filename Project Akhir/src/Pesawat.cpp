#include "Pesawat.h"

void createAirPlane(){
	cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
    // train = new Pesawat;//(Pesawat*)malloc(sizeof(Pesawat));
	planeFirstValue = new Pesawat; 
	planeLastValue = new Pesawat;
	planeFirstEmpty = new Pesawat;
	planeLastEmpty = new Pesawat;
	planeFirstValue = NULL;
	planeLastValue = NULL;
	planeLastEmpty = NULL;
	planeFirstEmpty = NULL;
};

void inputAirPlane(string name,int num){ // stack
	cout << "Masuk Input\n";
	Pesawat *train;
	train = new Pesawat;
	train->nama = name;
	train->no_penumpang = num;
	cout << train->nama << " " << train->no_penumpang << endl;

	if(planeFirstValue == NULL){
		planeFirstValue = train;
		planeLastValue = train;
		planeLastValue->next = NULL;
	}else{
		train->next = planeFirstValue;
		planeFirstValue = train;
	}
	countValue++;
}
void checkEmptyAirPlane(){
	countEmpty = 0;
	cout << "Masuk Check Empty\n";
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
void displayAirPlane(){
	// checkEmpty();
	Pesawat *temp;
    temp = planeFirstValue;
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
    temp = planeFirstEmpty;
    while(temp != NULL){
        cout << temp->kosong << " ";
        temp = temp->next;
    }
}

bool isBookedAirPlane(int no){
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
void writeFileBookingAirPlane(string nama[],int pos[],int n){
	createAirPlane();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
		inputAirPlane(nama[i],pos[i]);
	}
	Pesawat *temp;
	ofstream myFile;
	myFile.open(airPlaneBooking,ios::trunc);
	temp = planeFirstValue;
	while(temp != NULL){
		myFile << temp->nama << endl;
		myFile << temp->no_penumpang << endl;
		temp = temp -> next;
	}
	myFile.close();
	writeEmptySeatAirPlane(nama,pos,n);
}
void readFileBookingAirPlane(){
	createAirPlane();
	ifstream myFile;
	string nama;
	int no;
	myFile.open(airPlaneBooking);
	if(myFile.is_open()){
		while(myFile >> nama){
			Pesawat *train;
			train = new Pesawat;
			train->nama = nama;
			myFile >> no; 
			train->no_penumpang = no;
			// cout << "nama : " << nama << " no : " << no << endl;

			if(planeFirstValue == NULL){
				// cout << "First Value NULL\n";
				planeFirstValue = train; 
				planeLastValue = train;
				planeLastValue->next = NULL;
			}else{
				planeLastValue->next = train;
				planeLastValue = train;
				planeLastValue->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
	// readEmptySeat();
}
/* END OF READ & WRITE FILE BOOKING */

/* READ & WRITE FILE EMPTY SEAT */
void writeEmptySeatAirPlane(string nama[],int pos[],int n){ // queue
	createAirPlane();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
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
void readEmptySeatAirPlane(){
	createAirPlane();
	ifstream myFile;
	int no;
	myFile.open(airPlaneEmptySeat);
	if(myFile.is_open()){
		while(myFile >> no){
			Pesawat *train;
			train = new Pesawat;
			train->kosong = no;
			// cout << " no : " << no << endl;

			if(planeFirstEmpty == NULL){
				// cout << "First Value NULL\n";
				planeFirstEmpty = train; 
				planeLastEmpty = train;
				planeLastEmpty->next = NULL;
			}else{
				planeLastEmpty->next = train;
				planeLastEmpty = train;
				planeLastEmpty->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
}
/* END OF READ & WRITE FILE EMPTY SEAT */

/* DELETE FILE BOOKING */
void removeFromBookingAirPlane(int no){
	readFileBookingAirPlane();
	cout << "Masuk Remove\n";
	bool isBook = true;
	cout << "isBook " << isBook << endl;
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
		cout << "\nADA\n";
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
void updateFileBookingAirPlane(int from, int to){
	readFileBookingAirPlane();
	cout << "Masuk Update Booking\n";
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
