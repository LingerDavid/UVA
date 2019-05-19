#include<iostream>
#include<memory.h>

using namespace std;

bool disable[10000000];
int path[1000];
int final_path[1000];
int count;
bool ok;

int find_max(int b, int a, int n){
	while(b * n < a){
		n++;
	}
	return n;
}

int gcd(int a, int b){
	return a % b ? gcd(b, a % b):b;
}

void dfs(int b, int a, int n, int iter_cur, int iter_max){
	if(iter_cur == iter_max){
		if(b)return;
		if(!ok){
			memcpy(final_path, path, sizeof(int) * iter_max);
			ok = true;
		}
		else{
			bool should_cpy = false;
			for(int i = iter_max - 1; i >= 0; i--){
				if(path[i] < final_path[i]){
					should_cpy = true;
					break;
				}
				else if(path[i] > final_path[i]){
					break;
				}
			}
			if(!should_cpy)return;
			memcpy(final_path, path, sizeof(int) * iter_max);
		}
		return;
	}
	int limit = a * (iter_max - iter_cur) / b;
	int init_max = find_max(b, a, n);
	for(int i = init_max; i <= limit; i++){
		if(disable[i])continue;
		int max = i;
		int nb = b * max - a;
		int na = a * max;
		path[iter_cur] = max;
		if(nb){
			int k = gcd(na, nb);
			nb /= k;na /= k;
		}
		dfs(nb, na, max + 1, iter_cur + 1, iter_max);
	}
}

int iter_dfs(int b, int a){
	for(int i = 1; ; i++){
		dfs(b, a, 1, 0, i);
		if(ok)return i;
	}
	return -1;
}

int main(){
	int k;
	cin >> k;
	for(int i = 0; i < k; i++){
		ok = false;
		memset(disable, 0, sizeof(disable));
		int a, b, c;
		cin >> b >> a >> c;
		for(int j = 0; j < c; j++){
			int d;
			cin >> d;
			disable[d] = true;
		}
		int iter_max = iter_dfs(b, a);
		cout << "Case " << i + 1 << ": " << b << '/' << a << '=';
		for(int i = 0; i < iter_max; i++){
			cout << "1/" << final_path[i];
			if(i < iter_max - 1)cout << '+';
		}
		cout << endl;
	}
	return 0;
}
