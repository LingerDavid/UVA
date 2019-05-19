#include<iostream>
#include<string.h>

using namespace std;

bool is_legal(char* s, int len){
	for(int i = 0; i < len / 2; i++){
		if(!strncmp(s + len - 1 - i, s + len - 2 - 2 * i, i + 1))return false;
	}
	return true;
}

bool iterate(char* s, int e, int n, int L, int& index){
	if(index == n){
		s[e] = '\0';
		return true;
	}
	for(int i = 0; i < L; i++){
		s[e] = 'A' + i;
		if(is_legal(s, e + 1) && iterate(s, e + 1, n, L, ++index)) return true;
	}
	return false;
}

void print(char* s){
	for(int i = 0, a = 0, b = 0; s[i]; i++, a++){
		cout << s[i];
		if(a % 4 == 3) {
			if(b % 16 == 15)cout << endl;
			else cout << ' ';
			b++;
		}
	}
	cout << endl;
}

void solve(int n, int L){
	char s[80];
	int index = 0;
	iterate(s, 0, n, L, index);
	print(s); 
}

int main(){
	int n, L;
	while(true){
		cin >>n >> L;
		if(n ==0 && L == 0)break;
		solve(n, L);
	}
	return 0;
}
