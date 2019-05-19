#include<iostream>

using namespace std;

int N;
int a[18];

long test(){
	int i,j;
	long result=a[0],tmp;
	for(i=0 ; i < N; i++){
		tmp=1;
		for(j = i; j < N; j++){
			tmp *= a[j];
			if(tmp > result){
				result=tmp;
			}
		}
	}
	return result;
}

int main(){
	int k = 0;
	while(cin >> N){
		for(int i = 0;i < N ;i++){
			cin >> a[i];
		}
		cout << "Case #" << ++k << "The maximum product is "<< test() << '.' << endl;
	
	}
	return 0;
}

