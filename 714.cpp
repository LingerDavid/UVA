#include<iostream>
#include<map>
#include<stack>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool is_legal(int* a, int m, int k, int num){
	int tk = 0, sum = 0;
	for(int i = 0; i < m; i++){
		if(a[i] > num)return false;
		sum += a[i];
		if(sum > num){
			tk++;
			sum = a[i];
		}
	}
	tk++;
	if(tk > k)return false;
	return true;
}

void solve(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		stack<int> output;
		int k, m;
		cin >> m >> k;

		int a[100];

		for(int j = 0; j < m; j++){
			cin >> a[j];
		}

		int result = 0,
		    sum = 0,
		    max_sum = 0;
		int j = 0;
		for(j = 0; j < k - 1; j++){
			max_sum = MAX(max_sum, a[j]);
		}
		for(;j < m; j++){
			sum += a[j];
		}
		result = max_sum = MAX(max_sum, sum);

		int left = 1, 
		    right = max_sum;
		while(left < right){
			int mid = (left + right) / 2;
			if(is_legal(a, m, k, mid)){
				right = mid - 1;
				result = mid;
			}
			else{
				left = mid + 1;
			}
		}
		for(int j = m, sum = 0; j >= 0 && k >= 1; ){
			while(k <= j && sum + a[j - 1] <= result){
				j--;
				sum += a[j];
				output.push(a[j]);
			}
			if(j > 0)output.push(0);
			sum = 0;
			k -= 1;
		}
		while(output.size()){
			int v = output.top();
			if(v){
				cout << v;
			}
			else{
				cout << '/';
			}
			output.pop();
			if(output.size() > 0)cout << ' ';
		}
		cout << endl;
	}
}

int main(){
	/*
	int a[4] = {4, 5, 6, 7};
	cout << is_legal(a, 4, 2, 8) << endl;
	*/
	solve();
	return 0;
}
