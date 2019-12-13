#include <iostream>
#include <map>

using namespace std;

int a[200000], ar[200000], al[200000];

bool is_unique(int index, int l, int r){
	return (ar[index] == -1 ? true : (ar[index] > r)) 
		&& (al[index] == -1 ? true : (al[index] < l));
}

bool is_boring_sequence(int l, int r){

	if(l >= r)return true;

	int tl = l,
	    tr = r,
	    ui = -1;

	while(tl <= tr){
		if(is_unique(tl, l, r)){
			ui = tl;
			break;
		}
		if(is_unique(tr, l, r)){
			ui = tr;
			break;
		}
		tl++;
		tr--;
	}
	if(ui == -1)return false;

	return is_boring_sequence(l, ui - 1) 
		&& is_boring_sequence(ui + 1, r);
}

void solve(){
	map<int, int> mapl, mapr;

	int T;
	cin >> T;
	

	for(int i = 0; i < T; i++){
		int n;
		cin >> n;
		for(int j = 0; j < n; j++){
			cin >> a[j];
		}

		for(int j = n - 1; j >= 0; j--){
			if(mapr.find(a[j]) == mapr.end()){
				//new element
				mapr[a[j]] = -1;
			}
			
			ar[j] = mapr[a[j]];
			mapr[a[j]] = j;
		}
		for(int j = 0; j < n; j++){
			if(mapl.find(a[j]) == mapl.end()){
				//new element
				mapl[a[j]] = -1;
			}
			al[j] = mapl[a[j]];
			mapl[a[j]] = j;
		}
		if(is_boring_sequence(0, n - 1)){
			cout << "non-boring" << endl;
		}
		else{
			cout << "boring" << endl;
		}
	}
}

int main(){
	solve();
	return 0;
}
