#include<iostream>
#include <string.h>

using namespace std;

void solve(){
	int n;
	cin >> n;
	int p[10000], s[10000], h[10000];
	
	for(int i = 0; i < n; i++){
		int m;
		cin >> m;
		for(int j = 0; j < m; j++){
			
			cin >> p[j];

		}
		for(int j = 0; j < m; j++){
			cin >> s[j];
		}

		memset(h, 0, sizeof(int) * n);
		int height = s[0];
		for(int j = 0; j < m; j++){
			
			if(height < p[j]){
				height = p[j];
			}
			else if(height > s[j]){
				height = s[j];
			}
			else{
				//keep
				
			}
			h[j] = height;
		}
		height = s[m - 1];
		for(int j = m - 1; j >= 0; j--){
			if(height < p[j]){
				height = p[j];
			}
			else if(height > s[j]){
				height = s[j];
			}
			else{
				//keep
			}
			if(height < h[j])h[j] = height;
		}
		
		int rest = 0;
		for(int j = 0; j < m; j++){
			cout << h[j] << ' ';
			rest += (h[j] - p[j]);
		}
		cout << endl;
		cout << rest << endl;

		
	}
}

int main(){
	solve();
	return 0;
}
