#include <iostream>
#include <string.h>

using namespace std;

int ss[100000], vs[100000], ns[100000];
int s, n, c, d;

void solve(){
	cin >> c;

	for(int i = 0; i < c; i++){
		cin >> s >> n;
		for(int j = 0; j <  n; j++){
			cin >> vs[j];
		}
		memset(ss, 0, sizeof(int) * s);
		memset(ns, 0, sizeof(int) * s);
		d = 0;
		for(int k = 0; k < n; k++){
			int e = k,
			    h = k + 1 - s;


			if(h - 1 >= 0){
				
				if(ns[vs[h - 1]] == 2){
					d--;
				}
				ns[vs[h - 1]]--;
			}
			
			if(ns[vs[e]] == 1){
				d++;
			}
			ns[vs[e]]++;
			if(d){
				ss[e % s] = true;
			}
		}
		int result = 0;
		for(int j = 0; j < s; j++){
			if(!ss[j])result++;
		}
		cout << result << endl;
	}
}


int main(){
	solve();
	return 0;
}
