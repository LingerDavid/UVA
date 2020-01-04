#include <iostream>
#include <vector>

using namespace std;

struct POS{
	int x;
	int y;
};

void offset(POS pp, POS np, int& x, int &y){
	int px = pp.x,
	    py = pp.y,
	    npx = np.x,
	    npy = np.y;

	if(px != 0 && npy == 1){
		x += px;
	}
	else if(px != 0 && npy == -1){
		x += px;
		y -= 1;
	}
	else if(py != 0 && npx == 1){
		x += 1;
		y += (py == 1 ? 1 : 0);
	}
	else if(py != 0 && npx == -1){	
		x -= 1;
		y += (py == 1 ? 1 : 0);
	}
}

void solve(){
	while(true){
		int n;
		cin >> n;

		if(n == 0)return;

		vector<POS> angles(1);
		angles[0].x = -1;
		angles[0].y = 0;

		while(n > 0){
			int num = (int)angles.size();
			for(int i = 0; i < num; i++){
				POS tp;
				tp.x = -angles[i * 2].y;
				tp.y = angles[i * 2].x;
				angles.insert(angles.begin(), tp);
			}
			n--;
		}

		int min_x = 0,min_y = 0,max_x = 0,max_y = 0;
		int x = 0, y = 0, num = (int)angles.size();
		for(int i = 0; i < num; i++){
			if(x < min_x)min_x = x;
			else if(x > max_x)max_x = x;

			if(y < min_y)min_y = y;
			else if(y > max_y)max_y = y;

			if(i < num - 1)offset(angles[i], angles[i + 1], x, y);
		}
		
		char a[500][500] = {{'\0'}};
		x = 0;
		y = 0;
		for(int i = 0; i < num; i++){
			if(angles[i].y == 0){
				a[y - min_y][x - min_x] = '_';
			}
			else{
				a[y - min_y][x - min_x] = '|';
			}
			if(i < num - 1)offset(angles[i], angles[i + 1], x, y);

		}
		for(int r = max_y - min_y; r >= 0; r--){
			for(int c = 0; c <= max_x - min_x; c++){
				if(a[r][c] == '\0')cout << ' ';
				else cout << a[r][c];
			}
			cout << endl;
		}
		cout << '^'<< endl;
	}
}

int main(){
	solve();
	return 0;
}
