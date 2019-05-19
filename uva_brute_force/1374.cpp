#include<iostream>
#include<memory.h>

using namespace std;

int record[10000];
int result;
int target;
bool visit[10000];

bool dfs(int* record, int depth, int max_depth){
	if(depth == max_depth){
		if(record[depth] == target){
			return true;
		}
		else return false;
	}
	if((1 << (max_depth - depth)) * record[depth] < target)return false;
	for(int i = 0; i <= depth; i++){
		record[depth + 1] = record[i] + record[depth];
		visit[record[depth+1]] = true;
		if(dfs(record, depth + 1, max_depth))return true;
		visit[record[depth+1]] = false;
	}
	for(int i = 0; i <= depth; i++){
		record[depth + 1] = record[depth] - record[i];
		if(record[depth + 1] > 0 && !visit[record[depth+1]]){
			visit[record[depth+1]] = true;
			if(dfs(record, depth + 1, max_depth))return true;
			visit[record[depth+1]] = false;
		}
	}
	return false;
}

void iter_dfs(){
	int max_depth = target - 1; 
	record[0] = 1;
	memset(visit, 0, sizeof(bool) * 10000);
	for(int i = 0; i <= max_depth; i++){
		if(dfs(record, 0, i)){
			result = i;
			return;
		}
	}
}

int main(){
	while(true){
		cin >> target;
		if(target == 0)break;
		iter_dfs();
		cout << result << endl;
	}
	return 0;
}
