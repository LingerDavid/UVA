#include<iostream>
#include<memory.h>

using namespace std;

bool vis[22];
int map[22][22];
int street[22];
int cur_pos;
int path[22];
int path_len;
int count;
int target;

void dfs(int pos){
	if(pos == target){
		cout << '\t';
		for(int i = 0; i < path_len; i++){
			cout << path[i] << ' ';
		}
		cout << endl;
		count++;
		return;
	}
	for(int i = 0; i < street[pos]; i++){
		if(vis[map[pos][i]])continue;
		vis[map[pos][i]] = true;
		path[path_len++] = map[pos][i];
		dfs(map[pos][i]);
		path_len--;
		vis[map[pos][i]] = false;
	}
}

void init(){
	cur_pos = 1;
	path_len = 1;
	path[0] = 1;
	count = 0;
	vis[1] = true;
}

void insert(int a, int b){
	int i;
	for(i = street[a] - 1; i >= 0 && b < map[a][i]; i--)map[a][i + 1] = map[a][i];
	map[a][i + 1] = b;
	if(street[a] == 0)vis[a] = false;
	street[a] += 1;
}

int main(){
	int k = 1;
	int n, a, b;
	while(cin >> target){
		memset(street, 0, sizeof(street));
		while(true){
			cin >> a >> b;
			if(a ==0 && b == 0)break;
			insert(a, b);
			insert(b, a);	
		}
		init();
		cout << "CASE " << k << ':' << endl; 
		dfs(cur_pos);
		cout << "There are " << count << " routes from the firestation";
	       	cout << "to the streetcorner " << target << '.' << endl;
	}
	return 0;
}
