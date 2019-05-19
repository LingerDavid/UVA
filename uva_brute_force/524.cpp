#include<iostream>
#include<string.h>

using namespace std;
bool flag[17];
int a[100][16], k;
bool is_prime(int num){
	for(int i = 2; i < int(num / 1.41); i++){
		if(num % i == 0)return false;
	}
	return true;
}

bool is_legal(int* s, int n){
	for(int i = 0; i < n; i++){
		if(!is_prime(s[i] + s[(i + 1) % n])){
			return false;
		}
	}
	return true;
}

void solve(int* s, int index, int n){
	if(index == n){
		if(is_legal(s, n)){
			//memcpy(a[k], s, sizeof(int) * n);
			//k++;
			for(int i = 0; i < n; i++){
				cout << s[i] << ' ';
			}
			cout << endl;
		}
		return;
	}
	for(int i = 2; i <= n; i++){
		if(flag[i]){
			flag[i] = false;
			s[index] = i;
			solve(s, index + 1, n);
			flag[i] = true;
		}	
	}
}

int main(){
	int n, i = 1;
	int s[16];
	s[0] = 1;flag[1] = false;
	k = 0;
	while(cin >> n){
		cout << "Case " << i << ':' << endl;
		for(int j = 2; j <= n; j++)flag[j] = true;
		solve(s, 1, n);
		i++;
		/*
		for(int j = 0; j < k; j++){
			for(int b = 0; b < n; b++){
				cout << a[j][b] << ' ';
			}
			cout << endl;
		}
		for(int j = 0; j < k; j++){
			cout << 1 << ' ';
			for(int b = n - 1; b >= 1; b--){
				cout << a[j][b] << ' ';
			}
			cout << endl;
		}*/
	}
	return 0;
}
