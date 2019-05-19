#include<iostream>

using namespace std;

struct pt{
	int x;
	int y;

	bool operator ==(const pt& tps){
		if(x == tps.x && y == tps.y){
			return true;	
		}
		return false;
	}
};

int dir[4][2] = {{-1, 0}, {0,1}, {1, 0}, {0, -1}};
pt blocks[50];
int blk_cnt;
int turn_dir[4][2] = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
int ans;
char cdir[4] = {'w', 'n', 'e', 's'};
char path[20];

bool is_block(pt opos, pt npos){
	for(int i = 0; i < blk_cnt; i++){
		if(((opos.x <= blocks[i].x 
				&& blocks[i].x <= npos.x)
				|| (npos.x <= blocks[i].x 
					&& blocks[i].x <= opos.x))
				&& ((opos.y <= blocks[i].y 
						&& blocks[i].y <= npos.y)
					|| (npos.y <= blocks[i].y
						&& blocks[i].y <= opos.y))){
			return true;
		}
	}
	return false;
}
void dfs(int cur_dist, int dist, pt pos, int pdir){
	if(cur_dist > dist){
		if(pos.x == 0 && pos.y == 0){
			for(int i = 0; i < dist; i++){
				cout << path[i];
			}
			cout << endl;
			ans++;
		}
		return;
	}
	for(int i = 0; i < 2; i++){
		pt npos = pos;
		npos.x = npos.x + cur_dist * dir[turn_dir[pdir][i]][0];
		npos.y = npos.y + cur_dist * dir[turn_dir[pdir][i]][1];
		if(is_block(pos, npos))continue;
		path[cur_dist - 1] = cdir[turn_dir[pdir][i]];
		dfs(cur_dist + 1, dist, npos, turn_dir[pdir][i]);
	}
}

int main(){
	int k = 0;
	cin >> k;
	for(int i = 0; i < k; i++){
		int a;
		cin >> a;
		ans = 0;
		pt origin;
		origin.x = origin.y = 0;
		cin >> blk_cnt;
		for(int j = 0; j < blk_cnt; j++){
			cin >> blocks[j].x >> blocks[j].y;
		}
		for(int j = 0; j < 2; j++){
			dfs(1, a, origin, j);
		}
		cout << "Found " << ans << " golygon(s)." << endl;
	}
	return 0;
}
