#include<iostream>
#include<math.h>
#include<float.h>
#include<stdlib.h>

using namespace std;

#define BLACK 1
#define WHITE 0

int n;

#define PI 3.1415926

struct POINT{
	double x;
	double y;
	int c;
	double angle;
	
	double get_angle(){
		return angle;
	}
	void cal_angle(){
		double dist = sqrt(x * x + y * y);
		if(dist < 10e-10){
			this->angle = FLT_MAX;
			return;
			
		}
		double angle = asin(y / dist);
		
		if(x >= 0 && y > 0){
			//no change	
		}
		else if(x < 0 && y >= 0){
			angle = PI - angle;
		}
		else if(x <= 0 && y < 0){
			angle = PI - angle;
		}
		else{
		
			angle = 2 * PI + angle;
		}
		
		this->angle = angle;
	}
};

bool is_on_a_line(POINT* a, POINT* b){
	if(fabs(a->x * b->y - a->y * b->x) < 10e-10){
		return true;
	}
	return false;
}

POINT points[100];
POINT tpoints[100];

int cmp(const void* a, const void* b){
	POINT* pa = (POINT*)a;
	POINT* pb = (POINT*)b;
	double aa = pa->get_angle();
	double ba = pb->get_angle();
	return aa > ba ? 1 : -1;
}

void solve(){
		
	int rest = 0;
	for(int i = 0; i < n; i++){
		int uwhite = 0, ublack = 0;
		int bwhite = 0, bblack = 0;
		int white = 0, black = 0;

		//sort according to the angle
		int k = 0;
		for(int j = 0; j < n; j++){
			if(i == j)continue;
			tpoints[k].x = points[j].x - points[i].x;
			tpoints[k].y = points[j].y - points[i].y;
			tpoints[k].c = points[j].c;
			tpoints[k].angle = points[j].angle;
			k++;
		}
		qsort(tpoints, n - 1, sizeof(POINT), cmp);
		
		//for(int j = 0; j < n - 1; j++)	{
		//	cout << tpoints[j].get_angle() * 180 / PI << ' ';
		//}
		//cout << endl;
		int uindex = -1, bindex = -1;

		//init the number
		double uangle = 0, bangle = PI;
		for(int j = 0; j < n - 1; j++){
			double angle = tpoints[j].get_angle();
			int c = tpoints[j].c;
			if(fabs(uangle - angle) < 10E-10){
				if(c == WHITE){
					uwhite++;
				}
				else{
					ublack++;
				}
				uindex = j;
			}
			else if(uangle < angle && angle < bangle){
				if(c == WHITE){
					white++;
				}
				bindex = j;
			}
			else if(fabs(bangle - angle) < 10E-10){
				if(c == WHITE){
					bwhite++;
				}
				else{
					bblack++;
				}
				bindex = j;
			}
			else{
				if(c == BLACK){
					black++;
				}
			}
		}
		int temp = white + uwhite + ublack + bwhite + bblack + black;
		if(temp > rest)rest = temp;

		//rotate
		while(true){
			double udangle = FLT_MAX;
			double bdangle = FLT_MAX;
				
			//cout << "uindex:" << uindex << ',' << "bindex:" << bindex << endl;
			int tu = uindex + 1;
			if(tu < n - 1){
				double tuangle = tpoints[tu].get_angle();
				udangle = tuangle - uangle;
			}
			
			int tb = (bindex + 1) % (n - 1);
			double tbangle = (1 - int(tpoints[tb].get_angle() / PI)) * 2 * PI + tpoints[tb].get_angle();
			if(tbangle < 3 * PI && tbangle > bangle){
				bdangle = tbangle - bangle;
			}

			if(fabs(udangle - FLT_MAX) < 10E-10 && fabs(bdangle - FLT_MAX) < 10E-10)break;
			//cout << "tu:" << tu << ',' << "udangle:" << udangle * 180 / PI << ',' << "tb:" << tb << ',' << "tbangle:" << tbangle * 180 / PI << ',' << "bangle:" << bangle * 180 / PI << ',' << "bdangle:"	 << bdangle * 180 / PI << endl;
			if(10E-10 < bdangle - udangle){
				//cout << "rotate udangle:" << udangle * 180 / PI << endl;
				uangle += udangle;
				bangle += udangle;
				int tuwhite = 0, tublack = 0;
				while(tu < n - 1 && fabs(tpoints[tu].get_angle() - uangle) < 10E-10){
					if(tpoints[tu].c == WHITE){
						tuwhite++;
					}
					else{
						tublack++;
					}
					uindex = tu;
					tu++;
				}
				white = white + bwhite - tuwhite;
				black = black + ublack;
				uwhite = tuwhite;
				ublack = tublack;
				bblack = bwhite = 0;
				int tmp = white + black + uwhite + ublack + bwhite + bblack;
				if(tmp > rest)rest = tmp;

			}
			else if(udangle - bdangle > 10E-10){
				//cout << "rotate bdangle:" << bdangle * 180 / PI << endl;

				uangle += bdangle;
				bangle += bdangle;
				int tbwhite = 0, tbblack = 0;
				double tangle = (1 - int(tpoints[tb].get_angle() / PI)) * 2 * PI + tpoints[tb].get_angle();

				while(tb < n - 1 && fabs(tangle - bangle) < 10E-10){

					if(tpoints[tb].c == WHITE){
						tbwhite++;
					}
					else{
						tbblack++;
					}
					bindex = tb;
					tb = (tb + 1) % (n - 1);
					tangle = (1 - int(tpoints[tb].get_angle() / PI)) * 2 * PI + tpoints[tb].get_angle();
				}
				white = white + bwhite;
				black = black + ublack - tbblack;
				bwhite = tbwhite;
				bblack = tbblack;
				uwhite = ublack = 0;
				int tmp = white + black + uwhite + ublack + bwhite + bblack;
				if(tmp > rest)rest = tmp;

			}
			else{
				//cout << "rotate udangle and bdangle:" << udangle * 180 / PI << endl;

				uangle += udangle;
				bangle += bdangle;
				double tangle = (1 - int(tpoints[tb].get_angle() / PI)) * 2 * PI + tpoints[tb].get_angle();

				int tuwhite = 0, tublack = 0, tbwhite = 0, tbblack = 0;
				while(tu < n - 1 && fabs(tpoints[tu].get_angle() - uangle) < 10E-10){
					if(tpoints[tu].c == WHITE){
						tuwhite++;
					}
					else{
						tublack++;
					}
					uindex = tu;
					tu++;
				}
				while(tb < n - 1 && fabs(tangle - bangle) < 10E-10){

					if(tpoints[tb].c == WHITE){
						tbwhite++;
					}
					else{
						tbblack++;
					}
					bindex = tb;
					tb = (tb + 1) % (n - 1);
					tangle = (1 - int(tpoints[tb].get_angle() / PI)) * 2 * PI + tpoints[tb].get_angle();
				}
				white = white + bwhite - tuwhite;
				black = black + ublack - tbblack;
				uwhite = tuwhite;
				ublack = tublack;
				bwhite = tbwhite;
				bblack = tbblack;

				int tmp = white + black + uwhite + ublack + bwhite + bblack;
				//cout << "ub rotate tmp:" << tmp << ',' << "rest:" << rest <<endl;
				if(tmp > rest)rest = tmp;
			}
		}
		//cout << endl;
	
	}
	cout << rest + 1 << endl;
}

int main(){
	while(true){
		cin >> n;
		if(n == 0)break;
		for(int i = 0; i < n; i++){
			cin >> points[i].x >> points[i].y >> points[i].c;

			points[i].cal_angle();
		}
		solve();
	}
	return 0;
}
