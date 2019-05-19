#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

int init_puzzle[10];
int puzzle[10];
int record[10];
int n;
bool is_first[10];
int count;
int turn;
int final_turn;
int final_puzzle[10];

void dfs(int pos){
	if(pos >= n){
		int k = 0;
		int num = 0;
		int ans[3];
		for(int i = 0; i < n; i++){
			if(is_first[i]){
				if(num)ans[k++] = num;
				num = record[i];
			}
			else{
				num = num * 10 + record[i];
			}
		}
		ans[2] = num;
		if(ans[0] * ans[1] != ans[2])return;

		count++;
		return;
	}
	if(count > 1)return;
	for(; pos < n && puzzle[pos]; pos++)record[pos] = puzzle[pos];
	if(pos == n){
		dfs(pos);
	}
	else{
		for(int i = 1; i <= 9; i++){
			record[pos] = i;
			dfs(pos + 1);
		}
	}
}

void enum_puzzle(int pos){
	if(pos == n){
		dfs(0);
		if(turn >= final_turn)return;
		if(count == 1){
			final_turn = turn;
			for(int i = 0; i < n; i++){
				final_puzzle[i] = puzzle[i];
			}
		};
		count = 0;
		return;
	}
	if(final_turn <= turn)return;
	puzzle[pos] = init_puzzle[pos];
	enum_puzzle(pos + 1);
	turn++;
	if(1 <= init_puzzle[pos] && init_puzzle[pos]<= 9){
		puzzle[pos] = 0;
		enum_puzzle(pos + 1);
	}
	else{
		for(int i = 1; i <= 9; i++){
			puzzle[pos] = i;
			enum_puzzle(pos + 1);
		}
	}
	turn--;
}

int main(){
	char s[13];
	int k = 1;
	while(true){
		gets(s);
		if(s[0] == '0')break;
		bool flag= true;
		int len = strlen(s);
		count = 0;
		turn = 0;
		final_turn = 10;
		n = 0;
		for(int i = 0; i < len; i++){
			if(('1' <= s[i] && s[i] <= '9') || s[i] == '*'){
				if(flag){
					is_first[n] = true;
					flag = false;
				}
				else is_first[n] = false;
				if(s[i] == '*')init_puzzle[n] = 0;
				else init_puzzle[n] = s[i] - '0';
				n++;
			}
			else{
				flag = true;
			}
		}
		enum_puzzle(0);
		cout << "Case " << k++ << ": ";
		for(int i = 0; i < n; i++){
			if(i && is_first[i])cout << ' ';
			if(1 <= final_puzzle[i] && final_puzzle[i] <= 9)cout << final_puzzle[i];
			else cout << '*';
		}
		cout << endl;
	}
	return 0;
}
