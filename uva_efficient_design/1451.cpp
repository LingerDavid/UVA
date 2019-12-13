#include<iostream>
#include<stack>
#include<stdio.h>
#include<string.h>

using namespace std;

int n;
int S[100];
int L;

void solve(){
	cin >> n >> L;
	char str[100] = {'\0'};
	getchar();	
	fgets(str, 100, stdin);

	for(int i = 0; i < n; i++){
		S[i] = str[i] - '0';
		if(i == 0)continue;
		S[i] += S[i - 1];
	}

	int stack[100][2];
	int c = 0;
		
	int t = 0;
	int l = 0, r = 0, nl = 0, nr = 0;
	double k = 0.0, max_k = 0.0;
	for(int i = 0; i < n; i++){
		while(c >= 2){
			double dx1 = stack[c - 1][0] - stack[c - 2][0];
			double dy1 = stack[c - 1][1] - stack[c - 2][1];
			double dx2 = i - stack[c - 1][0];
			double dy2 = S[i] - stack[c - 1][1];

			if(dy1 / dx1 - dy2 / dx2 < 10E-10)break;

			c--;
		}
		stack[c][0] = i;
		stack[c][1] = S[i];
		c++;
		
		if(i - L + 1 <= 0)continue;
		
		for(; t + 1 < c && i - stack[t + 1][0] >= L; t++){
			double dx1 = i - stack[t + 1][0];
			double dy1 = S[i] - stack[t + 1][1];
			double dx2 = i - stack[t][0];
			double dy2 = S[i] - stack[t][1];
			double dk = dy1 / dx1 - dy2 / dx2;
			if(dk < 0)break;
			if(-10E-10 < dk && dk < 10E-10)break;
			
			l = stack[t + 1][0];
			r = i;
			k = (S[r] - S[l]) / double(r - l);
		}
		if(k > max_k){
			nl = l + 2;
			nr = r + 1;
			max_k = k;
		}
	}
	cout << nl << ' ' << nr << endl;
}

int main(){
	int k = 0;
	cin >> k;
	for(int i = 0; i < k; i++){
		solve();
	}
	return 0;
}
