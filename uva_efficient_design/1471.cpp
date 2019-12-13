#include<iostream>
#include<set>

using namespace std;

int n;
int a[100];
int s[100], e[100];


int max_len_star_with(int index){
	int tail = a[index];
	int len = 0;
	index++;
	len++;
	while(index < n && a[index] > tail){
		tail = a[index];
		index++;
		len++;
	}
	return len; 
}

int max_len_end_with(int index){
	int tail = a[index];
	int len = 0;
	index--;
	len++;
	while(index >= 0 && a[index] < tail){
		tail = a[index];
		index--;
		len++;
	}
	return len; 
}



class ELE{
	public:
	ELE(int v, int l){
		value = v;
		len = l;
	}
	int value;
	int len;

	bool operator<(const ELE& a) const{
		return value < a.value;
	}
};



void get_max_len(){
	for(int i = 0; i < n; i++){
		s[i] = max_len_star_with(i);
		e[i] = max_len_end_with(i);
	}
}



void solve(){
	set<ELE> t;
	set<ELE>::iterator t_it;
	get_max_len();

	int max_len = 0;
	for(int i = 0; i < n; i++){
		ELE c(a[i], e[i]);
		if(t.size() == 0){
			t.insert(c);
		}
		else{
			t_it = t.upper_bound(c);
			if(t_it == t.end())t.insert(c);
			else{
				if(t_it->len < c.len)t.insert(c);
				else continue;
			}
		}
		for(int j = i + 1; j < n; j++){
			if(a[j] <= a[i])continue;
			if(e[i] + s[j] > max_len){
				max_len = e[i] + s[j];
			}
		}
	}
	cout << max_len << endl;
}

int main(){
	int c;
	cin >> c;
	for(int i = 0; i < c; i++){
		cin >> n;
		for(int j = 0; j < n; j++){
			cin >> a[j];
		}
		solve();
	}
	return 0;
}
