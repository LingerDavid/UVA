#include<iostream>

using namespace std;

#define min(a, b) a < b ? a : b

bool visit[16];
int map[16][16];
int links[16];
int n;

bool dfs(int p, int s, int f){
	if(visit[p])return true;
	visit[p] = true;

	for(int i = 0; i < links[p]; i++){
		if(1 << (map[p][i] - 1) & s)continue;
		if(map[p][i] == f)continue;
		if(dfs(map[p][i], s, p))return true;
	}
	return false;
}

int num(int s){
	int i;
	for(i = 0; s; s /= 2)i = i + s % 2;
	return i;
}
bool circle(int s){
	int k=0;
	for(int i = 1; i <= n; i++){
		visit[i] = false;
	}
	for(int i = 1; i <= n; i++){
		if(visit[i])continue;
		if(1 << (i - 1) & s)continue;
		k++;
		if(dfs(i, s, 0))return false;
	}
	return k - 1 <= num(s);
}
bool branch(int s){
	for(int i = 1; i <= n; i++){
		int k = 0;
		if(1 << (i - 1) & s)continue;
		for(int j = 0; j < links[j]; j++){
			if(1 << (map[i][j] - 1) & s)continue;
			k++;
		}
		if(k > 2)return false;
	}
	return true;
}
bool is_legal(int s){
	return circle(s) && branch(s);
}
int solve(){
	int ans = n;
	for(int i = 0; i < (1 << n); i++){
		if(!is_legal(i))continue;
		ans = min(ans, num(i));
	}
	return ans;
}
int main(){
	int k = 1;
	while(true){
		cin >> n;
		if(n == 0)break;
		for(int i = 1; i <= n; i++){
			links[i] = 0;
		}
		while(true){
			int a, b;
			cin >> a >> b;
			if(a == -1 && b == -1)break;
			map[a][links[a]++] = b;
			map[b][links[b]++] = a;
		}
		cout << "Set " << k++ << ": Minimum links to open is " << solve() << endl;
	}
	return 0;
}
