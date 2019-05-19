#include<iostream>

using namespace std;

int N,S1,V1,S2,V2;
int result;

void solve(){
	int M1 = N / S1, M2 = N / S2;
	int T = 50;
	int res;
	if(M1 > T && M2 > T){
		//Volume:S2 * S1, S1 * S2
		//Value:S2 * V1, S1 * V2
		if(S2 * V1 < S1 * V2){
			for(int i = 0;i < S2; i++){
				res = i * V1 + (N - i * S1) / S2 * V2;
				if(result < res){
					result = res;
				}
			}
		}	
		else{
			for(int i = 0; i < S1; i++){
				res = i * V2 + (N - i * S2) / S1 * V1;
				if(result < res){
					result = res;
				}
			}
		}
	}
	else if(M1 < M2){
		//enumate the M2
		for(int i = 0; i <= M2; i++){
			res = i * V2 + (N - i * S2) / S1 * V1;
			if(result < res){
				result = res;
			}
		}
	}
	else{
		//enumate the M1
		for(int i = 0; i <= M1; i++){
			res = i * V1 + (N - i * S1) /S2 * V2;
			if(result < res){
				result = res;
			}
		}
	}
}

int main(){
	int k = 1;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> N >> S1 >> V1 >> S2 >> V2;
		solve();
		cout << "Case #" << (k++) << ": " << result << endl;
	}
	return 0;
}
