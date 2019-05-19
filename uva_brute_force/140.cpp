#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

#define max(a,b) (a > b ? a : b)
#define abs(a) (a > 0 ? a : -a)

char graph[26][8], pt[8];
int link[26], pos[26], tpos[26], n;
bool flag[8];

int bandwidth(char* s){
	int b = 0;
	for(int i = 0; s[i]; i++){
		int a = 0;
		for(int j = 0; j < link[s[i] - 'A']; j++){
			int k = tpos[graph[i][j] - 'A'];
			a = max(abs(k - i), a);
		}
		b = max(b, a);
	}
	return b;
}

void iterate(char* s, int index, char* rs, int& rest){
	if(index == n){
		int t = bandwidth(s);
		if(rest == 0){
			strcpy(rs, s);
			rest = t;
		}
		else if(t < rest){
			rest = t;
			strcpy(rs, s);
		}
		return;
	}
	for(int i = 0; i < 26; i++){
		if(pos[i] == -1)continue;
		int j = pos[i];
		if(flag[j]){
			s[index] = i + 'A';
			flag[j] = false;
			tpos[s[index] - 'A'] = index;
			iterate(s, index + 1, rs, rest);
			flag[j] = true;
		}
	}
}

int main(){
	char s[100];
	while(true){
		gets(s);
		if(s[0] == '#')break;
		int i = 0,j = 0;
		for(int k = 0; k < 26; k++){
			pos[k] = -1;
		}
		while(true){
			int t = s[j] - 'A';
			char node = s[j];
			if(pos[t] == -1){
				pos[t] = i;
				pt[i] = s[j];
				i++;
			}
			j += 2;
			
			while('A' <= s[j] && s[j] <= 'Z'){
				if(!strchr(graph[t], s[j])){
					graph[t][link[t]] = s[j];
					link[t] = link[t] + 1;
				}
				int k = s[j] - 'A';
				if(pos[k] == -1){
					pos[k] = i;
					pt[i] = s[j];
					i++;
				}
				if(!strchr(graph[k], node)){
					graph[k][link[k]] = node;
					link[k] = link[k] + 1;
				
				}
				j++;
			}
			if(s[j] == '\0')break;
			j++;
		}
		n = i;
		int rest = 0;
		char rs[100];
		s[n] = '\0';
		rs[n] = '\0';
		for(int k = 0; k < n; k++){
			flag[k] = true;
		}
		iterate(s, 0, rs, rest);
		for(int k = 0; rs[k]; k++){
			cout << rs[k] << ' ';
		}
		cout << "->" << rest << endl;
	}
	return 0;
}
