#include<iostream>

using namespace std;

int n;
int a;
long long last;
long long result;

#define abs(x) (x < 0 ? -x : x)

void solve(){
	while(cin >> n && n){
		last = 0;
		result = 0;
		for(int i = 0; i < n; i++){
			cin >> a;
			result += abs(last);
			last += a;
		}
		cout << result << endl;
	}
}

int main(){
	solve();
	return 0;
}
