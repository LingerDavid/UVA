#include<iostream>
#include<memory.h>
#include<limits.h>

using namespace std;

int state[10000][24];
int record[10000][100];
int sstep[10000];
int count;
int queue[10000][24];
int front, rear;
int init[24];
int step;
int res_rec[1000];
int number;
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int group[8][7]{0, 2, 6, 11, 15, 20, 22},
		{1, 3, 8, 12, 17, 21, 23},
		{4, 5, 6, 7, 8, 9, 10},
		{13, 14, 15, 16, 17, 18, 19}};
int dir[8] = {-1, -1, 1, 1, 1, 1, -1, -1};

bool is_target(int* s){
	for(int i = 0; i < 8; i++){
		if(s[center[0]] != s[center[i]])return false;
	}
	return true;
}

void move(int* s, int* rec, int stp){
	int temp;
	bool visit;
	
	for(int i = 0; i < 8; i++){
		if(dir[i] == 1){
			temp = s[group[i][6]];
			for(int j = 6; j > 0; j--){
				s[group[i][j]] = s[group[i][j - 1]];
			}
			s[group[i][0]] = temp;
		}
		else{
			temp = s[group[i][0]];
			for(int j = 0; j < 6; j++){
				s[group[i][j]] = s[group[i][j + 1]];
			}
			s[group[i][6]] = temp;
		}
		visit = false;	
		for(int j = 0; j < count; j++){
			if(memcmp(s, state[j], sizeof(int) * 24) == 0){
				visit = true;
				break;
			}
		}
		if(!visit){
			memcpy(queue[rear], s, sizeof(int) * 24);
			memcpy(state[count++], s, sizeof(int) * 24);
			memcpy(record[rear], rec,sizeof(int) * step);
			record[rear][step] = i;
			astep[rear] = step + 1;
			rear++;	
		}
	}
}

bool less(int* s1, int* s2, int step){
	for(int i = 0; i < step; i++){
		if(s1[i] < s2[i])return true;
	}
	return false;
}

void bfs(){
	int s[24];
	int rec[1000];
	int stp;
	
	front = 0;rear = 1;count = 1;
	memcpy(queue[0], init, sizeof(int) * 24);
	memcpy(state[0], init, sizeof(int) * 24);
	astep[0] = 0;
	step = INT_MAX;
	while(front < rear){
		memcpy(s, queue[front], sizeof(int) * 24);
		stp = astep[front];
		if(stp > 0)memcpy(rec, record[front], sizeof(int) * stp);
		if(is_target(s)){
			if(stp < step){
				step = stp;
				memcpy(res_rec, rec, sizeof(int) * stp);
				number = s[center[0]];
			}
			else if(stp == step){
				if(less(rec, res_rec)){
					memcpy(res_rec, rec, sizeof(int) * step);
					number = s[center[0]];
				}	
			}
			else{
				break;
			}
		}
	
	}
}
int main(){
	while(true){
		cin >> init[0];
		if(init[0] == 0)break;
		for(int i = 1; i < 24; i++){
			cin >> init[i];
		}
		bfs();
		for(int i = 0; i < step; i++){
			cout << ('A' + res_rec[i])
		}
		cout << endl << number << endl;
	}
	return 0;
}
