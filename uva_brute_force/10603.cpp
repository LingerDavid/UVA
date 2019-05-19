#include<iostream>
#include<limits.h>

using namespace std;

bool state[201][201];
int p[3], d;
int mp[3];
int md,ms;

//Use the array to record the answers corresponding to
//the different target.
int ans[205];

void dfs(int* p, int step){
	for(int i = 0; i < 3; i++){
		/*
		if(md < p[i] && p[i] <= d){
			md = p[i];
			ms = step;
		}
		else if(md == p[i] && step < ms){
			ms = step;
		}*/
		if(ans[p[i]] == -1 || ans[p[i]] > step)ans[p[i]] = step;
	}
	int op[3];
	op[0]=p[0];op[1]=p[1];op[2]=p[2];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(i == j)continue;
			int top[3];
			top[0]=op[0];top[1]=op[1];top[2]=op[2];
			int t = min(mp[j], op[j] + op[i]);
			int water = t - op[j];
			op[i] = op[i] - water;
			op[j] = t;
			if(!state[op[0]][op[1]]){
				state[op[0]][op[1]] = true;
				dfs(op, step + water);
				state[op[0]][op[1]] = false;
			}
			op[0]=top[0];op[1]=top[1];op[2]=top[2];
		}
	}
}

void init(){
	for(int i = 0; i < 201; i++){
		for(int j = 0; j < 200; j++){
			state[i][j] = false;
		}
	}
	for(int i = 0; i < 205; i++){
		ans[i] = -1;
	}
}

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		init();
		cin >> mp[0] >> mp[1] >> mp[2] >> d;
		p[0] = p[1] = 0;p[2] = mp[2];
		state[0][0] = true;
		md = 0;ms = INT_MAX;
		int step = 0;
		dfs(p, step);
		for(int i = 0; i < 205; i++){
			if(ans[d] > 0){
				ms = ans[d];
				md = d;	
				break;
			}
			d--;
		}
		cout << ms << ' ' << md << endl;
	}
	return 0;
}
