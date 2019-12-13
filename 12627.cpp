#include <iostream>
#include <math.h>

using namespace std;

int g(int k, int r){
	if(r <= 0)return 0;
	if(k == 0)return 1;

	int len = (1 << k);

	if(r < len / 2 || r == len / 2){
		return g(k - 1, r);
	}
	else{
		return 2 * g(k - 1, r - len / 2) + int(pow(3, (k  -1)));
	}
}

int f(int k, int r){
	if(r <= 0)return 0;
	if(k == 0)return 1;

	int len = 1 << k;

	if(r < len / 2 || r == len / 2){
		return 2 * f(k - 1, r);
	}
	else{
		return f(k - 1, r - len / 2) + 2 * int(pow(3, (k - 1)));
	}
}

void solve(){
	int n;

	cin >> n;

	for(int i = 0; i < n; i++){
		int K, A, B;
		cin >> K >> A >> B;
		int ng = g(K, (1 << K) - B),
		    nf = f(K, A - 1),
		    nc = int(pow(3, K));
		cout << ng << ',' << nf << ',' << nc << endl;
		cout << "Case "  << i + 1 << ": " << nc - ng - nf << endl;
		
	}
}

int main(){

	solve();

	return 0;
}
