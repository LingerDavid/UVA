#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>

using namespace std;

char map[20][20];
int link[300];//number of states
int graph[300][5];//state of move
bool visit[8000000];//record of the states
int step[8000000];
int front,rear;
int queue[8000000];
int n, init, target, tstep;

bool is_legal(int t, int nt){
	int* a = (int*)malloc(sizeof(int) * n);
	int* b = (int *)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++){
		a[i] = t & (0x00ff);
		t = t >> 8;
		b[i] = nt & (0x00ff);
		nt = nt >> 8;
	}
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(b[i] == b[j])return false;//不准重合
			if(b[i] == a[j] && b[j] == a[i])return false;//不准交叉
		}
	}
	free(a);
	free(b);
	return true;
}

void move(int t, int d = 0, int nt = 0){
	if(d == n){
		if(!visit[nt] && is_legal(t, nt)){
			queue[rear++] = nt;
			step[nt] = step[t] + 1;
			visit[nt] = true;
		}
		return;
	}
	int p = (t >> (d * 8)) & (0x00ff);
	for(int i = 0; i < link[p]; i++){
		nt = (nt & (~(0x00ff << (d * 8)))) + (graph[p][i] << (d * 8));
		move(t, d + 1, nt);
	}
}

void solve(){
	front = 0;rear = 1;
	visit[init] = true;
	queue[front] = init;
	step[init] = 0;
	while(front < rear){
		int t = queue[front++];
		if(t == target){
			tstep = step[t];
			break;
		}
		move(t); 
	}
}

int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int main(){
	int w,h;
	char s[18];
	while(true){
		cin>>w>>h>>n;
		if(w == 0)break;
		gets(s);
		for(int i = 0; i < h; i++){
			gets(s);
			for(int j = 0; j < w; j++){
				map[i][j] = s[j];
			}
		}
		for(int i = 0; i < h; i++){
			for(int j = 0; j < w; j++){
				if(map[i][j] == '#')continue;
				int t = i * w + j;
				if(islower(map[i][j])){
					init = init + (t << ((map[i][j] - 'a') * 8));
				}
				else if(isupper(map[i][j])){
					target = target + (t << ((map[i][j] - 'A') * 8));
				}
				graph[t][link[t]] = t;
				link[t] = link[t] + 1;
				for(int k = 0; k < 4; k++){
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if(x < 0 || x >= h || y < 0 || y >= w || map[x][y] == '#')continue;
					graph[t][link[t]] = x * w + y;
					link[t] = link[t] + 1;
					
				}
			}
		}
		for(int i = 0; i < h * w; i++){
			visit[i] = false;
		}
		solve();
		cout << tstep << endl;
	}
	return 0;
}
