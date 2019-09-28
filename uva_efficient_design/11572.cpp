#include<iostream>
#include<set>

using namespace std;

int n;
int A[1000];
void solve(){
	
	int left, right;
	int rest = 0;
	set<int> s;
	
	left = right = 0;
	
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> A[i];
	}
	while(right < n){

		while(right < n && !s.count(A[right])){
			s.insert(A[right]);
			right++;
		}
		
		if(right - left > rest)rest = right - left;
		s.erase(A[left++]);
	}
	cout << rest << endl;
}

int main(){
	int k = 0;
	cin >> k;
	for(int i = 0; i < k; i++){
		solve();
	}
	return 0;
}
