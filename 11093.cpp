#include <iostream>

using namespace std;

void solve(){
	int n = 0;
	cin >> n;
	int a[100001],
		b[100001];
	for(int i = 1; i <= n; i++){
		int m = 0;
		cin >> m;
		
		for(int j = 0; j < m; j++){
			cin >> a[j];
		}
		for(int j = 0; j < m; j++){
			cin >> b[j];
		}
		int sum = 0, p = 0, left = m, rest = 0;
		bool flag = false;
		while(left){
			if(sum + a[p] - b[p] > 0){
				sum += a[p] -  b[p];
				left--;
			}
			else{
				sum = 0;
				left = m;
				rest = (p + 1) % m;
				if(flag)break;
			}
			if(p + 1 == m && !flag)flag = true;
			p = (p + 1) % m;
		}
		if(left == 0){
			cout << "Case " << i << ": Possible from station " << rest + 1 << endl;
		}
		else{
			cout << "Case " << i << ": Not possible" << endl;
		}

	}
}

int main(){
	solve();
	return 0;
}
