#include<bits/stdc++.h>
using namespace std;
#define ll long long
//注意开long long
const int N=1e5+9,M=1e6+9;
ll a[N],b[N],h[N],w[N],f[N];
int s[M<<2],u;
inline ll g(int x,int o){return b[o]+a[o]*x;}
//对给定直线和横坐标求纵坐标
void upd(int k,int l,int r,int t){
	if(l==r){
		if(g(l,t)<g(l,s[k]))s[k]=t;
		return;
	}
	int m=l+r>>1;
	if(g(m,t)<g(m,s[k]))swap(t,s[k]);
	if(g(l,t)<g(l,s[k]))upd(k<<1,l,m,t);
	else if(g(r,t)<g(r,s[k]))upd(k<<1|1,m+1,r,t);
}//插入直线
ll qry(int k,int l,int r){
	if(l==r)return g(u,s[k]);
	int m=l+r>>1;
	return min(g(u,s[k]),u<=m?qry(k<<1,l,m):qry(k<<1|1,m+1,r));
}//查询
int main(){
	int n,i;
	scanf("%d",&n),b[0]=1e18;
	for(i=1;i<=n;++i)scanf("%lld",h+i);
	for(i=1;i<=n;++i)scanf("%lld",w+i),w[i]+=w[i-1];
	a[1]=-2*h[1],b[1]=h[1]*h[1]-w[1],upd(1,0,M,1);
	for(i=2;i<=n;++i){
		u=h[i],f[i]=h[i]*h[i]+w[i-1]+qry(1,0,M);
		a[i]=-2*h[i],b[i]=f[i]+h[i]*h[i]-w[i],upd(1,0,M,i);
	}
	printf("%lld",f[n]);
	return 0;
}