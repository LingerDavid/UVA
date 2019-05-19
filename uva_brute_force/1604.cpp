#include<iostream>
#include<memory.h>

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define WHITE 0
#define RED 1
#define BLUE 2

struct Cube{
	int t;
	int f;
	int r;
	bool operator==(struct Cube& c){
		return (c.t == t && c.f == f && c.r == r);
	}
	Cube& operator=(struct Cube& c){
		t = c.t;
		f = c.f;
		r = c.r;
		return *this;
	}
	void roll(int dir){
		if(dir == WEST || dir == EAST){
			int k = t;
			t = r;
			r = k;
		}
		else{
			int k = t;
			t = f;
			f = k;
		}
	}

};

struct Board{
	Cube cube[3][3];
	int empty_pos[2];
	int step;
	bool operator==(struct Board& b){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(!(cube[i][j] == b.cube[i][j]))return false;
			}
		}
		return true;
	}

	Board& operator=(struct Board& b){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				cube[i][j] = b.cube[i][j];
			}
		}
		memcpy(empty_pos, b.empty_pos, sizeof(int) * 2);
		step = b.step;
		return *this;
	}
};

Board old_state[200000];
int count;
Board queue[10000];
int front, tail;
Board init_state;
Board target_state;

bool is_recorded(Board& b){
	for(int i = 0; i < count; i++){
		if(old_state[i] == b)return true;
	}
	return false;
}

void get_next(Board& b){
	int dds[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int roll_dir[4] = {SOUTH, WEST, NORTH, EAST};
	for(int i = 0; i < 4; i++){
		int nx = b.empty_pos[0] + dds[i][0];
		int ny = b.empty_pos[1] + dds[i][1];
		if(nx < 0 || nx > 2 
				|| ny < 0 || ny > 2)continue;

		Board nb = b;
		nb.cube[nx][ny].roll(roll_dir[i]);
		Cube t = nb.cube[nx][ny];
		nb.cube[nx][ny] = nb.cube[b.empty_pos[0]][b.empty_pos[1]];
		nb.cube[b.empty_pos[0]][b.empty_pos[1]] = t;
		nb.empty_pos[0] = nx;
		nb.empty_pos[1] = ny;
		if(is_recorded(nb))continue;
		nb.step = b.step + 1;
		queue[tail++] = nb;
		old_state[count++] = nb;
	}
}

bool is_target(Board& b){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(b.cube[i][j].t != target_state.cube[i][j].t)return false;
		}
	}
	return true;
}

void bfs(){
	int ans = 31;
	front = 0;
	tail = 1;
	count = 0;
	queue[front] = init_state;
	old_state[count++] = init_state;
	Board temp_state;
	while(front < tail){
		temp_state = queue[front++];
		if(temp_state.step >= ans)continue;
		if(is_target(temp_state)){
			if(temp_state.step < ans)ans = temp_state.step;
		}
		get_next(temp_state);
	}
	cout << ans << endl;
}

int main(){
	while(true){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				init_state.cube[i][j].t = WHITE;
				init_state.cube[i][j].f = RED;
				init_state.cube[i][j].r = BLUE;
			}
		}
		cin >> init_state.empty_pos[1] >> init_state.empty_pos[0];
		init_state.step = 0;
		if(init_state.empty_pos[0] == 0 && init_state.empty_pos[1] == 0)break;
		init_state.empty_pos[0]--;
		init_state.empty_pos[1]--;
		Cube empty_cube;
		empty_cube.t = empty_cube.f = empty_cube.r = -1;
		init_state.cube[init_state.empty_pos[0]][init_state.empty_pos[1]] = empty_cube;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				char c;
				cin >> c;
				if(c == 'W'){
					target_state.cube[i][j].t = WHITE;
				}
				else if(c == 'R'){
					target_state.cube[i][j].t = RED;
				}
				else if(c == 'B'){
					target_state.cube[i][j].t = BLUE;
				}
				else{
					target_state.cube[i][j].t = -1;
				}
			}
		}
		bfs();
	}
}
