#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>

using namespace std;


struct CNUM{
	int number;
	int count;

	CNUM(){
		number = 0;
		count = 0;
	}

	CNUM(int number, int count = 1){
		this->number = number;
		this->count = count;
	}

	CNUM& operator++(){
		this->count += 1;
		return *this;
	}

	int getCount() const{
		return this->count;
	}

	int getNumber() const{
		return this->number;
	}
	CNUM& operator=(const CNUM& cnum){
		this->number = cnum.getNumber();
		this->count = cnum.getCount();

		return *this;
	}

};

int cmp(const void* a, const void* b){
	CNUM* ca = (CNUM*)a;
	CNUM* cb = (CNUM*)b;

	return ca->getNumber() > cb->getNumber();
}

static const int MAX_SIZE = 4000;

CNUM sum_A_B[MAX_SIZE][MAX_SIZE];
int len_sum[MAX_SIZE] = {0};
int record[MAX_SIZE];
int len_record = 0;

int A[MAX_SIZE], B[MAX_SIZE], C[MAX_SIZE], D[MAX_SIZE];

int n;

int my_hash(int number){
	if(number >= 0){
		return number % MAX_SIZE;
	}
	else{
		return ((-number / MAX_SIZE + 1) * MAX_SIZE + number) % MAX_SIZE;
	}
}

void init(){
	memset(len_sum, 0, sizeof(int) * n);
	len_record = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int sum = A[i] + B[j];

			int index = my_hash(sum);

			int vect_size = len_sum[index];
			
			int k;
			for(k = 0; k < vect_size; k++){
				if(sum_A_B[index][k].getNumber() == sum)break;
			}

			if(k == vect_size){

				if(vect_size == 0){
					record[len_record] = index;
					len_record += 1;
				}
				sum_A_B[index][k] = CNUM(sum);
				len_sum[index] += 1;
			}
			else{
				++sum_A_B[index][k];
			}

		}
	}

	for(int i = 0; i < len_record; i++){
		qsort((void*)sum_A_B[record[i]], len_sum[record[i]], sizeof(CNUM), cmp);
	}
}

void solve(){
	int rest = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int sum = -(C[i] + D[j]);

			int index = my_hash(sum);

			CNUM* search_array = sum_A_B[index];

			int len = len_sum[index];

			int left = 0;
			int right = len - 1;
			
			int mid;
			while(left <= right){
				mid = left + (right - left) / 2;

				if(search_array[mid].getNumber() == sum){
					break;
				}
				else if(search_array[mid].getNumber() < sum){
					left = mid + 1;
				}
				else{
					right = mid - 1;
				}
			}
			if(left <= right){
				rest += search_array[mid].getCount();
			}

		}
	}

	cout << rest << endl;
}

int main(){
	/*
	int c = 0;
	cin >> c;

	for(int i = 0; i < c; i++){
		cin >> n;
		for(int j = 0; j < n; j++){
			cin >> A[j] >> B[j] >> C[j] >> D[j];
		}
		init();
		solve();
	}*/

	int c = 1;
	for(int i = 0; i < c; i++){
		n = 6;
		int tA[10] = {-45,-41,-36,-36,26,-32};
		int tB[10] = {22, -27, 53, 30, -38, -54};
		int tC[10] = {42, 56, -37, -75, -10, -6};
		int tD[10] = {-16, 30, 77, -46, 62, 45};

		for(int j = 0; j < n; j++){
			A[j] = tA[j];
			B[j] = tB[j];
			C[j] = tC[j];
			D[j] = tD[j];
		}
		init();
		solve();
	}
	return 0;
}
