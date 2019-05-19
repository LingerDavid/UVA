#include<iostream>
#include<vector>

using namespace std;

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

struct Node{
	double l,r;
	Node(){};
	Node(double ll, double rr){l = ll; r = rr;}
};

vector<Node> rs[1 << 6];
int s,v[1 << 6];
double r, w[6], sw[1 << 6];

int bitcount(int r){
	int t = 0;
	for(int i =0 ;i < s; i++){

		if(r % 2 == 1)t++;
		r /= 2;
	}
	return t;
}

void dfs(int root){
	if(v[root])return;
	v[root] = 1;
	if(bitcount(root) == 1){
		rs[root].push_back(Node(0,0));
		return;
	}

	for(int l = (root - 1) & root; l > 0; l = (l - 1) & root){
		int r = (l ^ root) & root;
		dfs(l);dfs(r);
		double tl,tr;
		for(int i = 0; i < rs[l].size(); i++){
			for(int j = 0; j < rs[r].size(); j++){
				
				tl = min(rs[l][i].l - sw[r] / (double)(sw[l] + sw[r]), rs[r][j].l + sw[l] / (double)(sw[l] + sw[r]));
				tr = max(rs[l][i].r - sw[r] / (double)(sw[l] + sw[r]), rs[r][j].r + sw[l] / (double)(sw[l] + sw[r]));
				rs[root].push_back(Node(tl,tr));
			}
		}
	}
}

void test(){
	cin >> r >> s;
	for(int i = 0 ; i < s; i++){
		cin >> w[i];
	}
	
	for(int i = 1; i < (1 << s); i++){
		v[i] = 0;
		for(int j = 0; j < s; j++){
			if(i & (1 << j))sw[i] += w[j];
		}
	}
	int root = (1 << s) - 1;
	double ans = 0;
	dfs(root);
	for(int i = 0; i < rs[root].size(); i++){
		if(rs[root][i].r - rs[root][i].l < r){
			ans = max(ans, rs[root][i].r - rs[root][i].l);	
		}
	}

	cout << ans << endl;
}

int main(){

	test();
	return 0;
}
