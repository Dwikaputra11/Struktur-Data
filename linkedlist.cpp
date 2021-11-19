#include <iostream>

using namespace std;

typedef int typeinfo;
typedef struct typenode *typeptr;
struct typenode{
	typeinfo info;
	typeptr next;
};

typeptr awal = NULL, akhir = NULL;
void sisipnode(typeinfo IB);
void cetaklist(int n);

int main(){
	typeinfo angka;
	typeinfo arr[6] = {30,60,90,120,150,180};
	for(int i = 0; i < 6; i++){
		sisipnode(arr[i]);
	}
	cetaklist(130);
	return 0;
}

void sisipnode(typeinfo IB){
	typeptr NB,bantu;
	NB = (typenode *)malloc(sizeof(typenode));
	NB -> info = IB;
	NB->next = NULL;

	if(awal == NULL){
		awal = NB;
		akhir = NB;
	}else{
		if(awal->info >= IB){
			NB->next = awal;
			awal = NB;
		}else if(awal == akhir){
			awal -> next = NB;
			akhir = NB;
		}else{
			bantu = awal;
			while((bantu->next->info <= IB) && (bantu->next != NULL)){
				bantu = bantu->next;
				if(bantu -> next == NULL) break;
			}
			if(bantu->next == NULL){
				bantu->next = NB;
				akhir = NB;
			}else{
				NB->next = bantu->next;
				bantu->next = NB;
			}

		}
	}
}

void cetaklist(int n){
	typeptr bantu;
	bantu = awal;
	int count = 0;
	while(bantu != NULL){
		if(bantu->info <= n){
			count++;
			cout << " " << bantu -> info;
		}
		bantu = bantu -> next;
	}
	cout << "Jumlah Node : " << count;
}