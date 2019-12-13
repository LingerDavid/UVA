#include <iostream>
#include <queue>

using namespace std;

void solve(){
	priority_queue<int, vector<int>, greater<int> > q;
	
	int n;
	while(true){
		cin >> n;
		if(n == 0)break;
		int result = 0;
		for(int i = 0; i < n; i++){
			int a = 0;

			cin >> a;
			q.push(a);
		}
		while(q.size() > 1){
			int num1 = 0, num2 = 0;

			num1 = q.top();
			q.pop();
			num2 = q.top();
			q.pop();
			result += num1 + num2;
			q.push(num1 + num2);
		}
		if(q.size()){
			cout << result << endl;
			q.pop();
		}
	}
}

int main(){

	solve();

	return 0;
}
