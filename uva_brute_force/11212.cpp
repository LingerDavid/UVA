#include<iostream>
#include<memory.h>

using namespace std;

int state[100000][10];
int count;
int init[10],target[10];
int queue[100000][10];
int front, rear;
int step, n;
int sstep[100000];

void move(int* s, int* ts, int sl, int sr, int tl, int tr){
	if(sl > sr || tl > tr)return;
	int d = tl - sl;
	memcpy(ts, s, sizeof(int) * n);

	memmove(ts + sl, ts + tl, sizeof(int) * (tr - tl + 1));
	memcpy(ts + sl + (tr - tl + 1), s + sl, sizeof(int) * (sr - sl + 1));

}

void try_to_insert(int* s, int step){
	bool visit = false;
	for(int i = 0; i < count; i++){
		if(memcmp(state[i], state[count], sizeof(int) * n) == 0){
			visit = true;
			break;
		}
	}
	if(!visit){
		memcpy(queue[rear], state[count], sizeof(int) * n);
		sstep[rear] = step;
		rear++;
		count++;
	}
}

void paste(int* s, int l, int r, int step){
	for(int i = 0; i < n; i++){
		if(l <= i && i <= r)continue;
		if(i == n - 1){
			if(n - 1 < r + 1)continue;
			move(s, state[count], l, r, r + 1, n - 1);
			try_to_insert(state[count], step + 1);
		}
		if(i < l)move(s, state[count], i, l - 1, l, r);
		else move(s, state[count], l, r, r + 1, i - 1);
		try_to_insert(state[count], step + 1);
	}
}

void cut(int* s, int step){
	for(int l = 0; l < n; l++){
		for(int r = l; r < n; r++){
			paste(s, l, r, step);
		}
	}
}

void pop(int* s, int* step){
	memcpy(s, queue[front], sizeof(int) * n);
	*step = sstep[front];
	front++;
}

void bfs(){
	int s[10];
	int tstep;
	count = 1;
	front = 0;
	rear = 1;
	memcpy(queue[0], init, sizeof(int) * n);
	memcpy(state[0], init, sizeof(int) * n);
	while(front < rear){
		pop(s, &tstep);
		if(memcmp(s, target, sizeof(int) * n) == 0){
			step = tstep;
			break;
		}
		cut(s, tstep);
	}	
}

int main(){
	int k = 0;
	while(true){
		k++;
		cin >> n;
		if(n == 0) break;
		for(int i = 0; i < n; i++){
			cin >> init[i];
			target[i] = i + 1;
		}
		bfs();
		cout << "Case " << k << ": " << step << endl;
	}
	return 0;
}
