#include <iostream>

using namespace std;

char map[5][20];
int tmove[20];
int fnclock;
int n;

bool confict(int l, int r){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < n; j++){
			if(map[i][(j - l) % n] == 'X' && map[i][(j - r) % n] == 'X')return true;
		}
	}
	return false;
}

void dfs(int* move, int task){
	if(move[task - 1] + n >= fnclock)return;
	if(task == 10){
		fnclock = move[task - 1] + n;
		return;
	}
	for(int i = 1; i <= n; i++){
		int j;
		for(j = task - 1; j >= 0 && i + move[task - 1] - move[j] < n; j--){
			if(confict(0, move[task - 1] - move[j] + i))break;
		}
		if(j >= 0 && i + move[task - 1] - move[j] < n)continue;
		move[task] = move[task - 1] + i;
		dfs(move, task + 1);
	}
}

int main(){
	while(true){
		cin >> n;
		if(n == 0)break;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < n; j++){
				cin >> map[i][j];
			}
		}
		fnclock = 10 * n;
		tmove[0] = 0;
		dfs(tmove, 1);
		cout << fnclock << endl;
	}
	return 0;
}
