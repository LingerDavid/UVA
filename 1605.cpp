#include<iostream>

using namespace std;

void solve(int n){
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			cout << char('A' + i);
		}
		cout << endl;
	}
	cout << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			cout << char('A' + j);
		}
		cout << endl;
	}
}

int main(){
	int n = 0;
	while(cin >> n){
		solve(n);
	}
	cout << endl;
	return 0;
}
