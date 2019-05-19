#include<iostream>
#include<memory.h>
#include<string.h>
#include<stdio.h>
#include<fstream>

using namespace std;

int rect[9][8];
bool visit[40];
bool target[40];
bool chosen[9];
int max_depth;

#define DEBUG

void init(){
	memset(visit, 0, sizeof(bool) * 40);
	memset(target, 0, sizeof(bool) * 40);
	memset(chosen, 0, sizeof(bool) * 9);
	int k = 0;
	int b[8] = {0, 1, 4, 6, 13, 15, 18, 19};
	for(int i = 0; i + 1 < 4; i++){//col
		for(int j = 0; j + 1 < 4; j++){//row
			for(int c = 0, t = i * 9 + j; c < 8; c++){
				rect[k][c] = t + b[c];
			}
			k++;
		}
	}
}

void overlap(bool visit[40], int rect_index){
	for(int i = 0; i < 8; i++){
		visit[rect[rect_index][i]] = true;
	}
	int inner_border[4] = {rect[rect_index][0] + 5,
	rect[rect_index][0] + 14,
	rect[rect_index][0] + 9,
	rect[rect_index][0] + 10};
	for(int i = 0; i < 4; i++){
		visit[inner_border[i]] = false;
	}

}

void test_overlap(){
#ifdef DEBUG
	for(int i = 0; i < 40; i++){
		cout << visit[i];
		if(i < 39)cout << ',';
	}
	cout << endl;
	overlap(visit, 0);
	overlap(visit, 1);
	overlap(visit, 4);
	for(int i = 0; i < 40; i++){
		cout << visit[i];
		if(i < 39)cout << ',';
	}
	cout << endl;
#endif
}

bool same(bool visit[40]){
	for(int i = 0; i < 40; i++){
		if(visit[i] != target[i])return false;
	}
	return true;
}

bool dfs(bool tvisit[40], int depth){
	if(depth > max_depth){
		if(same(tvisit)){
			return true;
		}
		return false;
	}
	bool nvisit[40];
	for(int i = 0; i < 9;i++){
		if(chosen[i])continue;
		memcpy(nvisit, tvisit, 40 * sizeof(bool));
		overlap(nvisit, i);
		chosen[i] = true;
		if(dfs(nvisit, depth + 1))return true;
		chosen[i] = false;
	}
	return false;
}

bool iter_dfs(){
	for(int i = 0; i < 7; i++){
		max_depth = i;
		if(dfs(visit, 0))return true;
	}
	return false;
}

int main(){
	char a;
	int k = 1;
#ifdef DEBUG
	ifstream in("12113.i");
	ofstream out("12113.o");
#endif
	while(true){
#ifdef DEBUG
		a = in.get();
#else
		a = getchar();
#endif
		if(a == '0')break;
		char c;
		init();
		for(int i = 0; i < 5; i++){
			for(int j = (i == 0 ? 1 : 0); j < 9; j++){
#ifdef DEBUG
				c = in.get();
#else
				c = getchar();
#endif
				if(i == 0)continue;
				if(j % 2 == 1){
					if(c == '_'){
						target[(i - 2) * 9 + j / 2 + 9] = 1;
					}
				}
				else{
					if(c == '|'){
						target[(i - 2) * 9 + j / 2 + 4] = 1;
					}
				}
			}
#ifdef DEBUG
			c = in.get();
			in.get();
#else
			c = getchar();//#
			getchar();//\n
#endif
		}
#ifdef DEBUG
		out << "Case " << k++ << ":";
#else
		cout << "Case " << k++ << ":" ;
#endif
		if(iter_dfs()){
#ifdef DEBUG
			out << "Yes" << endl;
#else
			cout << "Yes" << endl;
#endif
		}
		else{
#ifdef DEBUG
			out << "No" << endl;
#else
			cout << "No"<< endl;
#endif
		}
	}
#ifdef DEBUG
	in.close();
	out.close();
#endif
	return 0;
}
