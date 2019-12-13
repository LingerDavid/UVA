#include <iostream>
#include <vector>

using namespace std;

int teams[1024][1024];

void solve(){
	int n;
	while(cin >> n){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				char c;
				cin >> c;
				teams[j][k] = c - '0';
			}
		}

		vector<int> black;
		vector<int> gray;
		bool flag[1024] = {0};

		for(int i = 1; i < n; i++){
			if(teams[0][i] == 0){
				black.push_back(i);
				flag[i] = true;
			}
		}

		for(int i = 0; i < (int)black.size(); i++){
			for(int j = 0; j < n; j++){
				int black_team = black[i];
				if(teams[black_team][j] == 0
						&& teams[0][j] == 1
						&& flag[j] == 0){
					gray.push_back(j);
					flag[j] = true;
				}

			}
		}
		
		vector<int> others;

		for(int i = 1; i < n; i++){
			if(flag[i] == false){
				others.push_back(i);
			}
		}

		int left = n - 1;

		while(left){
			vector<int> next_black, next_other, next_gray;
			//match the black
			for(int i = 0 ;i < (int)black.size(); i++){
				int black_team = black[i];
				for(int j = 0; j < (int)gray.size(); j++){
					int gray_team = gray[j];

					if(teams[black_team][gray_team] == 0){
						left--;
						next_gray.push_back(gray_team);

						black.erase(black.begin() + i);
						gray.erase(gray.begin() + j);
						i--;
						cout << black_team + 1 << ',' << gray_team + 1 << endl;
						break;
					}
				}
			}

			//unmatched black
			if(black.size()){
				
				while(black.size() >= 2){
					int tb1 = black[0],
					tb2 = black[1];
					left--;
					if(teams[tb1][tb2] == 0){
						
						next_black.push_back(tb2);
					}
					else{
						next_black.push_back(tb1);
					}
					black.erase(black.begin());
					black.erase(black.begin());

					cout << tb1 + 1 << ',' << tb2 + 1 << endl;
				}
				if(black.size() == 1){
					//left one black team
					int tb = black[0];
					left--;
					black.erase(black.begin());
					if(others.size() > 0){
						int to = others[0];
						
						if(teams[tb][to] == 0){
							next_other.push_back(to);
						}
						else{
							next_black.push_back(tb);
						}
						others.erase(others.begin());

						cout << tb + 1 << ',' << to + 1 << endl;
					}
					else{
						int tg = gray[0];
						if(teams[tb][tg] == 0){
							next_gray.push_back(tg);
						}
						else{
							next_black.push_back(tb);
						}
						gray.erase(gray.begin());

						cout << tb + 1 << ',' << tg + 1 << endl;
					}
				}
			}
			//unmatched gray
			if(gray.size()){
				while(gray.size() >= 2){
					int tg1 = gray[0],
					tg2 = gray[1];

					left--;

					if(teams[tg1][tg2] == 0){
						next_gray.push_back(tg2);
					}
					else{
						next_gray.push_back(tg1);
					}
					gray.erase(gray.begin());
					gray.erase(gray.begin());

					cout << tg1 + 1 << ',' << tg2 + 1 << endl;
				}
				if(gray.size() == 1){
					int tg = gray[0];
					gray.erase(gray.begin());
					left--;

					if(others.size() > 0){
					
						int to = others[0];
						if(teams[tg][to] == 0){
							next_other.push_back(to);
						}
						else{
							next_gray.push_back(tg);
						}
						others.erase(others.begin());
						cout << tg + 1 << ',' << to + 1 << endl;
					}
					else{
						//0-gray
						cout << 1 << ',' << tg + 1 << endl;
					}
				}
			}

			//unmatched others
			while(others.size() >= 2){
				int to1 = others[0],
				to2 = others[1];
				left--;

				if(teams[to1][to2] == 0){
					next_other.push_back(to2);
				}
				else{
					next_other.push_back(to1);
				}
				others.erase(others.begin());
				others.erase(others.begin());
				
				cout << to1 + 1 << ',' << to2 + 1 << endl;
			}
			if(others.size() == 1){
				//0-other
				int to = others[0];
				left--;
				others.erase(others.begin());

				cout << 1 << ',' << to + 1 << endl;
			}

			others = next_other;
			black = next_black;
			gray = next_gray;
		}

	}
}

int main(){
	solve();
	return 0;
}
