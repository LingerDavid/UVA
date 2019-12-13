#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

int x[5000][2];
int y[5000][2];
int n;

int my_index[5000];
int tx[5000];
int ty[5000];

int rest[5000][2];

int cmp_x(const void* a, const void* b){
	int ai = (*(int*)a) - 1;
	int bi = (*(int*)b) - 1;

	 if(x[ai][0] == x[bi][0]){
		int alen = x[ai][1] - x[ai][0];
		int blen = x[bi][1] - x[bi][0];
		return alen - blen;
	}
	 else{
		return x[ai][0] -x[bi][0];
	 }

}
int cmp_y(const void* a, const void* b){
	int ai = (*(int*)a) - 1;
	int bi = (*(int*)b) - 1;

	 if(y[ai][0] == y[bi][0]){
		int alen = y[ai][1] - y[ai][0];
		int blen = y[bi][1] - y[bi][0];
		return alen - blen;
	}
	 else{
		return y[ai][0] -y[bi][0];
	 }
}

void solve(){
	memcpy(tx, my_index, sizeof(int) * n);

	qsort(tx, n, sizeof(int), cmp_x);
	for(int i = 0; i < n; i++){
		cout << tx[i] << ' ';
	}
	cout << endl;
	memcpy(ty, my_index, sizeof(int) * n);

	qsort(ty, n, sizeof(int), cmp_y);

	for(int i = 0; i < n; i++){
		rest[tx[i] - 1][0] = i + 1;
		rest[ty[i] - 1][1] = i + 1;
	}

	for(int i = 0; i < n; i++){
		cout << rest[i][0] << ' ' << rest[i][1] << endl;
	}
}

int main(){
	
	while(true){
		cin >> n;
		if(n == 0)break;

		for(int i = 0; i < n; i++){
			my_index[i] = i + 1;
			cin >> x[i][0] >> y[i][0] >> x[i][1] >> y[i][1];
		}
		
		solve();
	}
	/*
	n = 8;
	int tx[8][2] = {{1, 2},
		{5, 8},
		{2, 5},
		{2, 5},
		{6, 8},
		{6, 8},
		{6, 8},
		{3, 7}};
	int ty[8][2] = {{1, 2},
		{7, 8},
		{2, 5},
		{2, 5},
		{3, 6},
		{3, 5},
		{3, 8},
		{6, 8}};
	for(int i = 0; i < n; i++){
		my_index[i] = i + 1;
		x[i][0] = tx[i][0];
		x[i][1] = tx[i][1];
		y[i][0] = ty[i][0];
		y[i][1] = ty[i][1];
	}
	solve();
	*/
	return 0;
}
