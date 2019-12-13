#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

void flip(int* p, int left, int right){
	int i = 0;
	int mid = (left + right) / 2;
	for(i = left; i <= mid; i++){
	
		int l = i - left;
		int r = right - l;

		int temp = p[l];
		p[l] = p[r];
		p[r] = temp;
	}
}

void solve(int* p, int len){
	int max = 0;
	int max_pos = 0;
	for(int i = 0; i < len; i++){
		max = 0;
		for(int j = 0; j < len - i; j++){
			if(p[j] > max){
				max = p[j];
				max_pos = j;
			}
		}
		if(len - i - 1 == max_pos)continue;
		else if(0 == max_pos){
			flip(p, 0, len - i - 1);
			cout << i + 1 << ' ';
		}
		else{
			flip(p, 0, max_pos);
			cout << len - max_pos << ' ';
			flip(p, 0, len - i - 1);
			cout << i + 1 << ' ';
		}
	}
}

int main(){
	//test1
	/*
	int a[] = {1, 2, 3, 4, 5};
	int len = 5;
	solve(a, len);
	cout << 0 << endl;
	*/
	//test2
	/*
	int a[] = {5, 4, 3, 2, 1};
	int len = 5;
	solve(a, len);
	cout << 0 << endl;
	*/
	/*
	int a[] = {5, 1, 2, 3, 4};
	int len = 5;
	solve(a, len);
	*/
	int a[30];
	int len = 0;
	char str[3000];
	while(fgets(str, 3000, stdin)){
		if(str[0] == '\n')break;
		 len = 0;
		 int i = 0;
		 while(str[i] != '\n' && str[i] != '\0'){
		 	int num = 0;
			while('0' <= str[i] && str[i] <= '9'){
				num = num * 10 + str[i] - '0';
				i++;
			}
			a[len++] = num;
			while(str[i] == ' ')i++;
		 }
		solve(a, len);
		cout << 0 << endl;
	}

	return 0;
}
