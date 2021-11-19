#include <bits/stdc++.h>
using namespace std;

typedef struct typenode *typeptr;
struct typenode{
	typeptr next;
	typeptr prev;
	int info;
};

typeptr awal = NULL, akhir = NULL;

void sisipnode(int angka); 
void backward();
int main()
{
	int arr[6] = {45,55,65,75,85,95};
	for(int i = 0; i < 6; i++){
		sisipnode(arr[i]);
	}
	backward();

	return 0;
}


void sisipnode(int IB){
	typeptr NB,bantu;
	NB = (typenode *)malloc(sizeof(typenode));
	NB -> info = IB;
	NB->next = NULL;
	NB->prev = NULL;

	if(awal == NULL){
		awal = NB;
		akhir = NB;
	}else{
		if(awal->info >= IB){
			NB->next = awal;
			awal->prev = NB;
			awal = NB;
		}else if(awal == akhir){
			awal -> next = NB;
			akhir = NB;
			akhir->prev = awal;
		}else{
			bantu = awal;
			while((bantu->next->info <= IB) && (bantu->next != NULL)){
				bantu = bantu->next;
				if(bantu -> next == NULL) break;
			}
			if(bantu->next == NULL){
				bantu->next = NB;
				akhir = NB;
				akhir->prev = bantu;
			}else{
				NB->next = bantu->next;
				NB->prev = bantu;
				NB->next->prev = NB;
				bantu->next = NB;
			}

		}
	}
}

void backward(){
	typeptr bantu;
	int i = 1;
	bantu = akhir;
	while(bantu != NULL){
		if(i%2 == 0) cout << bantu->info << " ";
		++i;
		bantu = bantu->prev;
	}
}



