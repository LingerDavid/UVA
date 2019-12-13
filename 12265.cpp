#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;

struct ELE{
	int a;
	int b;

	ELE(int a, int b){
		this->a = a;
		this->b = b;
	}
};

void solve(){
	int k;
	cin >> k;
	char a[1000][1000];
	vector<int> height(1000), nheight(1000);
	for(int i = 0; i < k; i++){

		map<int, int> count;
		int n, m;

		cin >> n >> m;

		for(int r = 0; r < n; r++){
			for(int c = 0; c < m; c++){
				cin >> a[r][c];
			}
		}

		for(int r = 0; r < n; r++){
			
			stack<ELE> value, key_value;
			for(int c = 0; c < m; c++){
				int h = 0;
				if(a[r][c] == '#'){
					h = 0;
				}
				else{
					h = height[c] + 1;
				}
				nheight[c] = h;
				
				ELE temp(c, h);
				while(value.size() > 0 
						&& value.top().b >= h){
					temp.a = value.top().a;
					value.pop();
				}
				ELE key_temp(value.size(), h - temp.a);
				while(key_value.size() > 0
						&& key_value.top().a >= (int)value.size()){
					key_value.pop();
				}
				if(h == 0)continue;

				value.push(temp);

				if(key_value.size() == 0
						|| key_value.top().b < key_temp.b){
					key_value.push(key_temp);

				}
				int p = 2 * (key_value.top().b + c + 1);
				if(count.find(p) == count.end()){
					count[p] = 1;
				}
				else{
					count[p] += 1;
				}
				

			}
			height = nheight;

		}
		


		map<int, int>::iterator it;
		for(it = count.begin(); it != count.end(); it++){
			cout << it->second << " x " << it->first << endl;
		}
	}
}

int main(){

	solve();

	return 0;
}
