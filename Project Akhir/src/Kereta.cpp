#include "Kereta.h"

void createTrain(){
	cout << "Masuk Create Linklist\n";
	// intinya ngasik value awal aja
    // train = new Kereta;//(Kereta*)malloc(sizeof(Kereta));
	trainFirstValue = new Kereta; 
	trainLastValue = new Kereta;
	trainFirstEmpty = new Kereta;
	trainLastEmpty = new Kereta;
	trainFirstValue = NULL;
	trainLastValue = NULL;
	trainLastEmpty = NULL;
	trainFirstEmpty = NULL;
};

void inputTrain(string name,int num){ // stack
	cout << "Masuk Input\n";
	Kereta *train;
	train = new Kereta;
	train->nama = name;
	train->no_penumpang = num;
	cout << train->nama << " " << train->no_penumpang << endl;

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
void checkEmptyTrain(){
	countEmpty = 0;
	cout << "Masuk Check Empty\n";
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
void displayTrain(){
	// checkEmpty();
	Kereta *temp;
    temp = trainFirstValue;
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
    temp = trainFirstEmpty;
    while(temp != NULL){
        cout << temp->kosong << " ";
        temp = temp->next;
    }
}

bool isBookedTrain(int no){
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
void writeFileBookingTrain(string nama[],int pos[],int n){
	createTrain();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
		inputTrain(nama[i],pos[i]);
	}
	Kereta *temp;
	ofstream myFile;
	myFile.open(trainBooking,ios::trunc);
	temp = trainFirstValue;
	while(temp != NULL){
		myFile << temp->nama << endl;
		myFile << temp->no_penumpang << endl;
		temp = temp -> next;
	}
	myFile.close();
	writeEmptySeatTrain(nama,pos,n);
}
void readFileBookingTrain(){
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
			// cout << "nama : " << nama << " no : " << no << endl;

			if(trainFirstValue == NULL){
				// cout << "First Value NULL\n";
				trainFirstValue = train; 
				trainLastValue = train;
				trainLastValue->next = NULL;
			}else{
				trainLastValue->next = train;
				trainLastValue = train;
				trainLastValue->next = NULL;
			}
			myFile.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	myFile.close();
	// readEmptySeat();
}
/* END OF READ & WRITE FILE BOOKING */

/* READ & WRITE FILE EMPTY SEAT */
void writeEmptySeatTrain(string nama[],int pos[],int n){ // queue
	createTrain();
	countValue = 0;
	for(int i = 0; i < n; i++){
		cout << nama[i] << " " << pos[i] << endl;
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
void readEmptySeatTrain(){
	createTrain();
	ifstream myFile;
	int no;
	myFile.open(trainEmptySeat);
	if(myFile.is_open()){
		while(myFile >> no){
			Kereta *train;
			train = new Kereta;
			train->kosong = no;
			// cout << " no : " << no << endl;

			if(trainFirstEmpty == NULL){
				// cout << "First Value NULL\n";
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
void removeFromBookingTrain(int no){
	readFileBookingTrain();
	cout << "Masuk Remove\n";
	bool isBook = true;
	cout << "isBook " << isBook << endl;
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
		cout << "\nADA\n";
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
void updateFileBookingTrain(int from, int to){
	readFileBookingTrain();
	cout << "Masuk Update Booking\n";
	bool isFound = false;
	Kereta *temp,*node;
	node = new Kereta;
	// node->no_penumpang = to;

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