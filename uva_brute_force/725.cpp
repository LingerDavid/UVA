#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;
int N,a[2][10],C;

bool is_legal(int num){
	int t=num;
	int b[10];
	memcpy(b,a[1],sizeof(int)*10);
	for(int i=0;i<5;i++){
		if(b[t%10])return false;
		b[t%10]=1;
		t/=10;
	}
	return true;
}

void test(int n, int r){
	if(n==5){
		int l = r * N;
		if(l<1000 || l > 99999)return;
		if(is_legal(l)){
			C+=1;
			cout<<setw(5)<<setfill('0')<<l;
			cout<<'/';
			cout<<setw(5)<<setfill('0')<<r<<'='<<N<<endl;
		}
		return;
	}
	for(int i=0;i<10;i++){
		if(a[1][i])continue;
		a[1][i]=1;
		test(n+1,r*10+i);
		a[1][i]=0;
	}
}

int main(){
	for(int i=0;i<10;i++)a[0][i]=i;
	while(true){
		memset(&a[1],0,sizeof(int)*10);
		C=0;
		cin>>N;
		if(N==0)break;
		test(0,0);
		if(C==0){
			cout<<"There are no solutions for "<<N<<endl;
		}
	}
	return 0;
}
