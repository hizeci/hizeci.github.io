#include<bits/stdc++.h>
using namespace std;
#define rp(i,n) for(int i=0;i<n;i++)
typedef long long ll;
const int MOD=1000000007;
const int M=(1<<7)+5;
ll n;
int m;
int mm; //存放2^m 
#define VACANT(i,s) ((i>=0)&&(i<m)&&(!((1<<i)&s)))//状态为S的列第i行是否为空 
int t[M][M];//转移矩阵   i,j各代表状态为j时,下一列状态为i的个数 
void dfs(int i,int state,int nex){//处理当前第i行的情况 
	if(i==m){
		t[nex][state]++;
		return; 
	}
	if(!VACANT(i,state)) dfs(i+1,state,nex); //此格子被占用 		
	if(VACANT(i,state)&&VACANT(i,nex)&&VACANT(i-1,nex)){//符合插入第一种积木的条件 	
		dfs(i+1,state,nex|(1<<i)|(1<<(i-1)));
	}
	if(VACANT(i,state)&&VACANT(i,nex)&&VACANT(i+1,nex)){//符合插入第二种积木的条件 	
		dfs(i+1,state,nex|(1<<i)|(1<<(i+1)));
	}
	if(VACANT(i,state)&&VACANT(i+1,state)&&VACANT(i+1,nex)){//符合插入第三种积木的条件 	
		dfs(i+2,state,nex|(1<<(i+1)));
	}
	if(VACANT(i,state)&&VACANT(i+1,state)&&VACANT(i,nex)){//符合插入第四种积木的条件 	
		dfs(i+2,state,nex|(1<<i));
	}
}
int temp[M][M];
void multi(int a[][M],int b[][M]){//计算矩阵(a*b)%MOD，结果存放在a中 
	memset(temp,0,sizeof(temp));//每次初始化，因为下面是+=运算符 
	rp(i,mm) rp(j,mm) rp(k,mm){
		temp[i][j]=(temp[i][j]+1ll*a[i][k]*b[k][j]%MOD)%MOD;
	}
	rp(i,mm) rp(j,mm) a[i][j]=temp[i][j];
}
int res[M][M]; 
void Pow(int a[][M],ll n){//快速幂求(a^n),结果存放在矩阵res中 
	rp(i,M) res[i][i]=1;//初始化res=1;
	while(n){
		if(n&1) multi(res,a);//n为奇数
		multi(a,a);//a=a^2;
		n>>=1; //n/=2;
	} 
}
int main(){
	cin>>n>>m;
	mm=(1<<m);
	for(int i=0;i<=mm;i++) dfs(0,i,0);//搜索状态为i的列的下一列可以是什么状态 
	Pow(t,n);	//转移矩阵自乘n次; 
	cout<<res[0][0]; //初始行列式为[1;0;0;...;0];
	return 0;
}