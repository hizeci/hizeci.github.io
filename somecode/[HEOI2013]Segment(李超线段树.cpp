#include<bits/stdc++.h>
#define ld long double
#define db double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
//const int inf=0x7f7f7f7f7f7f;
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
*/
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}

const int N=1e5+10;
const int M=39989;
int n;
int cnt_seg;
typedef pair<db,db> line;
line a[N];
inline db f(line x,int X){
	return x.first*X+x.second;
}
inline db Intersection(line x,line y){
	return (y.second-x.second)/(x.first-y.first);
}

/*
李超树并不严格，只需满足包括单点的所有线段树区间最大优势线段中含有该单点的优势最大线段即可。

加入一条新线段时：
1.如果该区间还没有线段：直接修改，让新线段为区间最大优势线段
2.新线段两端都低于当前最大优势线段，直接丢了 (都高于，替换成新线段)
3.有交点
if(新线段与区间左端点交点高于原最大优势线段)
{
	if(交点在中点及其左侧) 不更新该区间最大优势线段，用新线段更新该区间左子区间最大优势线段
	else （交点在右侧) 更新区间最大优势线段为新线段，但是用原最大优势线段更新该区间右子区间最大优势线段	
}
else (新线段与区间右端点交点高于原最大优势线段)
{
	 if(交点位于区间中点右侧) 不更新该区间最大优势线段但是用新线段更新该区间右子区间最大优势线段：
	 else 交点位于区间中点及其左侧，那么更新该区间最大优势线段为新线段但是用原最大优势线段更新该区间左子区间最大优势线段：
}
https://www.luogu.com.cn/blog/George1123/solution-p4097
*/
int ans;
int v[(N<<2)+10];
bitset<(N<<2)+10>mp;
void get_tr(int &x,int mod){
	x=(x+ans-1)%mod+1;
}
void add(int k,int L,int R,int l=1,int r=M,int x=1)
{
	int mid=(l+r)>>1;
	if(L<=l&&r<=R)
	{
		if(!mp[x]){v[x]=k,mp[x]=1;return;}
		db ly1=f(a[k],l),ry1=f(a[k],r),ly=f(a[v[x]],l),ry=f(a[v[x]],r);
		//printf("%.3f %.3f %.3f %.3f\n",ly1,ry1,ly,ry);
		if(ly1<=ly&&ry1<=ry) return;//part1
		if(ly<=ly1&&ry<=ry1) {v[x]=k;return;}
		db in=Intersection(a[v[x]],a[k]);
		if(ly1>=ly)
		{
			if(in<=mid) add(k,L,R,l,mid,x<<1);
			else add(v[x],L,R,mid+1,r,x<<1|1),v[x]=k;
		}
		else
		{
			if(in>mid) add(k,L,R,mid+1,r,x<<1|1);
			else add(v[x],L,R,l,mid,x<<1),v[x]=k;
		}
		return;
	}
	if(L<=mid) add(k,L,R,l,mid,x<<1);
	if(mid<R) add(k,L,R,mid+1,r,x<<1|1);
}
inline int lcmp(int X,int x,int y){
	return f(a[x],X)>f(a[y],X)?x:y;
}
int query(int X,int l=1,int r=M,int x=1)
{
	int res=0;
	if(mp[x]) res=lcmp(X,res,v[x]);
	if(l==r) return res;
	int mid=(l+r)>>1;
	if(X<=mid) res=lcmp(X,res,query(X,l,mid,x<<1));
	else res=lcmp(X,res,query(X,mid+1,r,x<<1|1));
	return res;
}
signed main()
{
	n=read();
	R(i,1,n)
	{
		int opt=read();
		if(opt)
		{
			int sx=read(),sy=read(),tx=read(),ty=read();
			get_tr(sx,M),get_tr(sy,1e9),get_tr(tx,M),get_tr(ty,1e9);
			//printf("%d %d %d %d\n",sx,sy,tx,ty);
			a[++cnt_seg]=tx==sx?mkp(.0,db(max(sy,ty))):mkp(db(ty-sy)/(tx-sx),-db(ty-sy)/(tx-sx)*sx+sy);
			//printf("%.4f %.4f\n",a[cnt_seg].first,a[cnt_seg].second);
			add(cnt_seg,min(sx,tx),max(sx,tx));
		}
		else
		{
			int X=read();
			get_tr(X,M);
			printf("%d\n",ans=query(X));
		}
	}
}	