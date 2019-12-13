#include <iostream>
#include <string.h>

using namespace std;

int inputs[200000][2];
int outputs[200000];
int values[200000];
int n, m;

int net_in(int index, int b){
	return index <= b ? 1 : 0;
}

bool net(int b){
	for(int i = 1; i <= m; i++){
		int src1 = inputs[i][0],
		src2 = inputs[i][1],
		input1 = src1 < 0 ? net_in(-src1, b) : values[src1],
		input2 = src2 < 0 ? net_in(-src2, b) : values[src2];
		values[i] = !(input1 && input2);
	}
	return values[m];
}

void solve(){
	int d;
	cin >> d;
	for(int i = 0; i < d; i++){

		cin >> n >> m;
		int m2 = m * 2;
		for(int j = 1; j <= m2; j += 2){
			int index = (1 + j) / 2;
			cin >> 	inputs[index][0] >> inputs[index][1];
		}
		
		int x0 = net(0);
		int x1 = net(n);
		int left = 1, right = n;
		if(x0 == x1){
			right = 0;
		}

		while(left <= right){
			int p = (left + right) / 2;

			int val = net(p);

			if(val != x0){
				left = p + 1;
			}
			else{
				right = p - 1;
			}
		}
		for(int j = 1; j <= n; j++){
			if(j < right)cout << 1;
			else if(j == right)cout << 'x';
			else cout << 0;
		}
		cout << endl;
	}
}

int main(){
	solve();
}
