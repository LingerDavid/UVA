#include<iostream>
#include<memory.h>
#include<stdlib.h>

using namespace std;

struct point{
	int x;
	int y;
	point(){
		x = 0;
		y = 0;
	}
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
	point& operator=(point p){
		x = p.x;
		y = p.y;
		return *this;
	}
	point operator+(int dir[2]){
		point np;
		np.x = x + dir[0];
		np.y = y + dir[1];
		return np;
	}
	friend 	ostream& operator<<(ostream& c, const point& p){
		c << p.x << ',' <<p. y;
		return c;
	}
};

int face[10][10];
point record[100][100];
int count;
int n, w, h;
bool visit[100];
int dir[4][2] = {{-1, 0},{0, 1}, {1, 0}, {0, -1}};
int mirr[2][2] = {{1, -1}, {-1, 1}};

point rotate(point& pos){
	point np;
	int t = pos.x;
	np.x = -pos.y;
	np.y = t;
	return np;
}

void rotate_gp(point* sg, point* tg){
	for(int i = 0; i < n; i++){
		tg[i] = rotate(sg[i]);
	}
}

point mirror(point pos, int dir){
	point np(pos.x * mirr[dir][0], pos.y * mirr[dir][1]);
	return np;
}

void mirror_gp(point* sg, point* tg, int dir){
	for(int i = 0; i < n; i++){
		tg[i] = mirror(sg[i], dir);	
	}
}
int comp(const void* a, const void* b){
	point* pp1 = (point*)a;
	point* pp2 = (point*)b;
	return pp1->x * w + pp1->y - (pp2->x * w + pp2->y);
}

void init_org(point& org){
	org.x = org.y = 11;
}

void print_pt(char* title, point* g){
	cout << endl;
	cout << title;
	for(int i = 0; i < n; i++){
		cout << g[i] << ' ';
	}
	cout << endl;
}

bool is_equal(point* g1, point o1, point* g2, point o2){
	for(int i = 0; i < n; i++){
		if((g1[i].x - o1.x) * 11 + (g1[i].y - o1.y) 
		!= (g2[i].x - o2.x) * 11 + (g2[i].y - o2.y))return false;
	}
	return true;
}

void find_origin(point* g, point& o){
	init_org(o);
	for(int i = 0; i < n; i++){
		if(o.x > g[i].x)o.x = g[i].x;	
		if(o.y > g[i].y)o.y = g[i].y;
	}
}

bool is_rotate_same(point* g1, point o1, point* g2){
	point o2;
	point tg2[101];
	memcpy(tg2, g2, sizeof(point) * n);
	for(int i = 0; i < 4; i++){
		rotate_gp(tg2, tg2);
		find_origin(tg2, o2);
		qsort(tg2, n, sizeof(point), comp);
		if(is_equal(g1, o1, tg2, o2))return true;
	}
	return false;
}

bool is_same(point* g1, point* g2){
	point o1;
	find_origin(g1, o1);
	point tg2[101];
	qsort(g1, n, sizeof(point), comp);

	if(is_rotate_same(g1, o1, g2))return true;
	for(int i = 0; i < 2; i++){
		memcpy(tg2, g2, sizeof(point) * n);
		mirror_gp(tg2, tg2, i);
		if(is_rotate_same(g1, o1, tg2))return true;
	}
	return false;
}

void print_graph(point* g){
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			face[i][j] = 0;	
		}
	}
	for(int i = 0; i < n ; i++){
		face[g[i].x][g[i].y] = 1;
	}
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			cout << face[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(point* graph, int index){
	if(index == n){
		int i;
		for(i = 0; i < count; i++){
			if(is_same(record[i], graph)){
				break;
			}
		}
		if(i == count){
			memcpy(record[count++], graph, sizeof(point) * n);
		}
		return;
	}
	for(int i = 0; i < index; i++){
		for(int j = 0; j < 4; j++){
			point t = graph[i] + dir[j];
			if(t.x < 0 || t.y < 0 
			||t.x >= h || t.y >= w)continue;
			int p = t.x * w + t.y;
			if(visit[p])continue;
			graph[index] = t;
			visit[p] = true;
			dfs(graph, index + 1);
			visit[p] = false;
		}
	}
}

int main(){
	point graph[101];
	point pos;
	int tcount;
	while(cin >> n >> w >> h){
		tcount = 0;
		for(int i = 0; i < h / 2; i++){
			for(int j = 0; j < w / 2; j++){
				pos.x = i; pos.y = j;
				memset(visit, 0, sizeof(bool) * w * h);
				visit[i * w + j] = true;
				count = 0;
				graph[0] = pos;
				dfs(graph, 1);
				if(count > tcount)tcount = count;
			}
		}
		cout << tcount << endl;
	}
	return 0;
}
