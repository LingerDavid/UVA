#include<iostream>

using namespace std;

int n, K;
char map[20][20];
int pos[26];
int num[26];
char nmap[20][20];

bool is_legal(int sw, int sh, int sx, int sy, int index){
	int lx = pos[index] / n;
	int ly = pos[index] % n;
	for(int i = sx, j = 0; j < sh; j++){
		for(int k = sy, d = 0; d < sw; d++){
			if(i + j < 0 || k + d < 0 || i + j >= n || k + d >= n)	return false;
			if(map[i + j][k + d] != '.' && !(i + j == lx && k + d == ly))return false;
		}
	}
	return true;
}

void sit(int sw, int sh, int sx, int sy, int index){
	for(int i = sx, j = 0; j < sh; j++){
		for(int k = sy, d = 0; d < sw; d++){
			map[i + j][k + d] = 'A' + index;
		}
	}
}

void stand(int sw, int sh, int sx, int sy, int index){
	int lx = pos[index] / n;
	int ly = pos[index] % n;
	for(int i = sx, j = 0; j < sh; j++){
		for(int k = sy, d = 0; d < sw; d++){
			if(i + j == lx && k + d == ly)map[lx][ly] = '0' + num[index];
			else map[i + j][k + d] = '.';
		}
	}
}


void arrange(int x, int y, char t, char s){
	int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
	for(int i = 0; i < 4; i++){
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if(nx < 0 || ny < 0 || nx >= n || ny >= n)continue;
		if(map[nx][ny] != t || nmap[nx][ny] == s)continue;
		nmap[nx][ny] = s;
		arrange(nx, ny, t, s);
	}
}

void format_print(){
	int index = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			nmap[i][j] = '\0';
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(nmap[i][j])continue;
			nmap[i][j] = index + 'A';
			arrange(i, j, map[i][j], index + 'A');
			index++;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << nmap[i][j];
		}
		cout << endl;
	}
}

void dfs(int index){
	if(index == K){
		format_print();
		return;
	}
	int x = pos[index] / n;
	int y = pos[index] % n;

	int size = num[index];
	for(int i = 1; i <= size; i++){
		if(size % i)continue;
		int sw = i; int sh = size / i;
		int j;
		for(j = 0; j < size; j++){
			int sx = j / sw;
			int sy = j % sw;
			if(!is_legal(sw, sh, x - sx, y - sy, index))continue;
			sit(sw, sh, x - sx, y - sy, index);
			dfs(index + 1);
			stand(sw, sh, x - sx, y - sy, index);
		}
	}
}

int main(){
	while(true){
		cin >> n >> K;
		if(n == 0 && K == 0)break;
		int index = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> map[i][j];
				if(map[i][j] != '.'){
					pos[index] = i * n + j;
					num[index++] = map[i][j] - '0';
				}
			}
		}
		dfs(0);
	}
	return 0;
}
