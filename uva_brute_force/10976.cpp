#include<iostream>

using namespace std;

void solve(int k){
	for(int y = k + 1; y <= 2 * k; y++){
		for( int x = y; x * y <= k * (x + y); x++){
			if(k * (x + y) == x * y){
				cout<<"1/"<<k<<" = 1/"<<x<<" + 1/"<<y<<endl;
			}
		}
	}
}

int main(){
	int k;
	while(cin>>k){
		solve(k);
	}
	return 0;
}
