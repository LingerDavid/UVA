#include<iostream>
#include<memory.h>

using namespace std;

int rect[200][16];
int rlink_cnt[200];
int mlink_cnt[41];//remain rect the match links to
int rect_size[200];
int full_rect_size[200];
int miss[41];
int min_match;
int n;
int a[4][2];
int rect_cnt = 1;
typedef int (*func)(int, int);
int match_cnt;
int remain_rect;

int rol(int x, int y){
	return (2 * n + 1) * x + y;
}
int col(int x, int y){
	return (2 * n + 1) * x + y + n;
}
func b[4] = {rol, rol, col, col};


void init(){
	rect_cnt = 1;
	match_cnt = 2 * n * (n + 1);
	memset(rlink_cnt, 0, 200 * sizeof(int));
	memset(mlink_cnt, 0, 41 * sizeof(int));
	for(int i = 1; i <= n; i++){//length
		for(int j = 0; j < n - i + 1; j++){//horizonal
			for(int k = 0; k < n - i + 1 ;k++){//vertical
				int size = 0;
				for(int m = 0; m < i; m++){
					a[0][0] = 0;a[0][1] = m;
					a[1][0] = i;a[1][1] = m;
					a[2][0] = m;a[2][1] = 0;
					a[3][0] = m;a[3][1] = i;
					for(int h = 0; h < 4; h++){
						int t = (*b[h])(j + a[h][0], k + a[h][1]) + 1;
						rect[rect_cnt][rlink_cnt[rect_cnt]] = t;
						rlink_cnt[rect_cnt] += 1;
						mlink_cnt[t] += 1;
						size++;
					}
				}
				full_rect_size[rect_cnt] = 4 * i;
				rect_size[rect_cnt] = size;
				rect_cnt++;
			}
		}
	}
	rect_cnt--;
	remain_rect = rect_cnt;
}

bool dfs(int matches){
	
	if(matches == min_match){
		if(remain_rect == 0){
			return true;
		}
		return false;
	}
	int max_index, max = 0;
	
	int i;
	for(i = 1; i <= match_cnt; i++){
		if(mlink_cnt[i] > max){
			max = mlink_cnt[i];
			max_index = i;
		}
	}
	if(max * (min_match - matches) < remain_rect)return false;//IDA*
	for(i = 1; i <= rect_cnt; i++){
		if(rect_size[i] == full_rect_size[i])break;
	}
	for(int j = 0; j < rlink_cnt[i]; j++){
		for(int k = 1; k <= rect_cnt; k++){
			for(int m = 0; m < rlink_cnt[k]; m++){
				if(rect[k][m] == rect[i][j]){
					if(rect_size[k] == full_rect_size[k]){
						for(int g = 0; g < rlink_cnt[k]; g++)
						{
							mlink_cnt[rect[k][g]]--;
						}
						remain_rect--;
					}
					rect_size[k]--;
					break;
				}
			}
		}
		miss[rect[i][j]] = true;
		if(dfs(matches + 1))return true;
		miss[rect[i][j]] = false;
		for(int k = 1; k <= rect_cnt; k++){
			for(int m = 0; m < rlink_cnt[k]; m++){
				if(rect[k][m] == rect[i][j]){
					rect_size[k]++;
					if(rect_size[k] == full_rect_size[k]){
						remain_rect++;
						for(int g = 0; g < rlink_cnt[k]; g++)
						{
							mlink_cnt[rect[k][g]]++;
						}
					}
					break;
				}
			}
		}
	}
	return false;
}


int main(){
	int c,b;
	cin >> c;
	for(int i = 0; i < c; i++){
		cin >> n;
		init();
		cin >> b;
		for(int j = 0; j < b; j++){
			int t;
			cin >> t;
			miss[t] = true;
			for(int k = 1; k <= rect_cnt; k++){
				for(int m = 0; m < rlink_cnt[k]; m++){
					if(rect[k][m] == t){
						if(rect_size[k] == full_rect_size[k]){
							for(int g = 0; g < rlink_cnt[k]; g++){
								mlink_cnt[rect[k][g]]--;
							}
							remain_rect--;	
						}
						rect_size[k]--;
						break;
					}
				}
			}
		}
		for(int i = 0; i <= n * n; i++){
			min_match = i;
			if(dfs(0)){
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}
