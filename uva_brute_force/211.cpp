#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

int pips[7][8];
int maps[7][8];
int bone[7][7];
bool bone_vis[29];
int count;

int dir[2][2] = {{0, 1},{1, 0}};

void dfs(){
	
	int i, j, tx, ty;
	for(tx = 0; tx < 7; tx++){
		for(ty = 0; ty < 8; ty++){
			if(!maps[tx][ty])goto NEXT;
		}
	}
NEXT:
	if(tx == 7 && ty == 8){
		count++;
		for(i = 0; i < 7; i++){
			for(j = 0; j < 8; j++){
				cout << setw(2) << maps[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		return;
	}
	for(i = 0; i < 2; i++){
		int nx = tx + dir[i][0];
		int ny = ty + dir[i][1];
		if(nx >= 7 || ny >= 8)continue;
		int b1 = pips[tx][ty];
		int b2 = pips[nx][ny];
		int tbone = bone[b1][b2] | bone[b2][b1];
		if(!tbone || bone_vis[tbone] || maps[nx][ny])continue;
		maps[tx][ty] = maps[nx][ny] = tbone;
		bone_vis[tbone] = true;
		dfs();
		bone_vis[tbone] = false;
		maps[tx][ty] = maps[nx][ny] = 0;
	}
}

int main(){
	for(int i = 0; i <= 6; i++){
		for(int j = 0; j <= 6; j++){
			bone[i][j] = 0;
		}
	}
	for(int i = 1; i <= 28; i++){
		bone_vis[i] = false;
	}
	for(int i = 0, k = 1; i <= 6; i++){
		for(int j = i; j <= 6; j++){
			bone[i][j] = k++;
		}
	}
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 8; j++){
			maps[i][j] = 0;
		}
	}
	ifstream fin("211.i");
	int k = 1;
	while(fin >> pips[0][0] && !fin.eof()){
		cout << "Layout #" << k << ':' << endl;
		cout << endl;
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 8; j++){
				if(!i && !j){
					cout << pips[0][0] << ' ';
					continue;
				}
				fin >> pips[i][j];
				cout << pips[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		cout << "Maps resulting from layout #" << k << " are:" << endl;
		cout << endl;
		count = 0;
		dfs();
		cout << "There are " << count << " solution(s) from layout #" << k++ << endl;
		cout << endl;
		
	}
	fin.close();
	return 0;
}
