#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
const int mod=1e9+7;
//const int mod=10007;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}


inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}
*/

//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
/*
题意:
给出一棵树,每次询问删掉一些子树后剩下的点到某个点P的距离 最大值/最小值/和

sol:
首先考虑good node在dfs序上一定最多是k+1个连续的区间
然后考虑对于每一个P,用segmentree维护出它与其他的点的距离的最大值/最小值/和.
考虑当P变为其的某一个儿子v时[beg[v],en[v]]的距离会减一[1,beg[v]-1],[en[v]+1,n]的距离会+1
那么根为v的线段树是由根为P的线段树修改几下得到的。于是用主席树维护即可。

时间复杂度o((n+\sum k)log n)
*/
const int N=55555;
const int M=3333333;
int n,q;
std::vector<int>e[N];
pii arr[N<<2];
int beg[N],en[N],dep[N];
int dfn_dep[N],lst_ans;
int tim,Rt[N];

struct canlongsegmentree
{
	int sum[M],MN[M],MX[M];
	int Ls[M],Rs[M];
	int lzy[M],tot_seg;
	inline void clear(){
		R(i,1,tot_seg) sum[i]=MN[i]=MX[i]=Ls[i]=Rs[i]=lzy[i]=0;
		R(i,1,n) Rt[i]=0;tot_seg=0;
	}
	inline void push_up(int x,int lsz,int rsz){
		sum[x]=sum[Ls[x]]+sum[Rs[x]]+lzy[Ls[x]]*lsz+lzy[Rs[x]]*rsz;
		MX[x]=max(MX[Ls[x]]+lzy[Ls[x]],MX[Rs[x]]+lzy[Rs[x]]);
		MN[x]=min(MN[Ls[x]]+lzy[Ls[x]],MN[Rs[x]]+lzy[Rs[x]]);
	}
	inline void build(int l,int r,int &x) {
		x=++tot_seg;
		if(l==r) {
			sum[x]=MX[x]=MN[x]=dfn_dep[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,Ls[x]),build(mid+1,r,Rs[x]);
		push_up(x,mid-l+1,r-mid);
	}
	void modify(int L,int R,int l,int r,int lst,int &x,int k){
		x=++tot_seg;
		Ls[x]=Ls[lst],Rs[x]=Rs[lst],lzy[x]=lzy[lst];
		if(L<=l&&r<=R) {
			lzy[x]=lzy[lst]+k,sum[x]=sum[lst],MN[x]=MN[lst],MX[x]=MX[lst];
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) modify(L,R,l,mid,Ls[lst],Ls[x],k);
		if(mid<R)  modify(L,R,mid+1,r,Rs[lst],Rs[x],k);
		push_up(x,mid-l+1,r-mid); 
	}
	int query_sum(int L,int R,int l,int r,int x) {
		if(l>R||r<L) return 0;
		if(L<=l&&r<=R) return sum[x]+(r-l+1)*lzy[x];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=query_sum(L,R,l,mid,Ls[x]);
		if(mid<R)  ret+=query_sum(L,R,mid+1,r,Rs[x]);
		return ret+lzy[x]*(min(r,R)-max(l,L)+1);
	}
	int query_MAX(int L,int R,int l,int r,int x) {
		if(l>R||r<L) return -inf;
		if(L<=l&&r<=R) return MX[x]+lzy[x];
		int mid=(l+r)>>1,ret=-inf;
		if(L<=mid) ret=max(ret,query_MAX(L,R,l,mid,Ls[x]));
		if(mid<R)  ret=max(ret,query_MAX(L,R,mid+1,r,Rs[x]));
		return ret+lzy[x];
	}
	int query_MIN(int L,int R,int l,int r,int x) {
		if(l>R||r<L) return inf;
		if(L<=l&&r<=R) return MN[x]+lzy[x];
		int mid=(l+r)>>1,ret=inf;
		if(L<=mid) ret=min(ret,query_MIN(L,R,l,mid,Ls[x]));
		if(mid<R) ret=min(ret,query_MIN(L,R,mid+1,r,Rs[x]));
		return ret+lzy[x];
	}
}st;

void dfs1(int u,int f){
	dep[u]=dep[f]+1,beg[u]=++tim;
	for(int v:e[u]) {
		if(v==f) continue;
		dfs1(v,u);
	}
	en[u]=tim;
}
void dfs2(int u,int f){
	for(int v:e[u]) {
		if(v==f) continue;
		int t;
		st.modify(1,n,1,n,Rt[u],t,1);
		st.modify(beg[v],en[v],1,n,t,Rt[v],-2);
		dfs2(v,u);
	}
}
/*
6 5
1 3
2 1
4 2
6 4
5 6
3 5 3
3 3 3
3 4 3
4 5 1
3 3 1
1 5 6
3 5 2
3 4 2
3 3 3
6 5 3
*/
signed main(){
	while(scanf("%d%d",&n,&q)==2) {
		R(i,1,n) e[i].clear();
		tim=0;
		R(i,2,n) {
			int u=read(),v=read();
			e[u].pb(v),e[v].pb(u);
		}
		dfs1(1,0);
		R(i,1,n) dfn_dep[beg[i]]=dep[i]-1;
		st.build(1,n,Rt[1]);
		dfs2(1,0);
		lst_ans=0;
		while(q--) {
			int k=read(),p=read(),opt=read();
			//printf("danger:%lld %lld %lld\n",k,p,opt);
			p=(p+lst_ans)%n+1;
			int ct=0;
			arr[++ct]=mkp(1,1);
			arr[++ct]=mkp(n+1,-1);
			R(i,1,k) {
				int x=read();
				arr[++ct]=mkp(beg[x],1);
				arr[++ct]=mkp(en[x]+1,-1);
			}
			sort(arr+1,arr+ct+1);
			int cur=0,flg=0;
		//	printf("duck:");
			if(opt==1) {
				lst_ans=0;
				FR(i,1,ct) {
					if(!cur) {

						lst_ans+=st.query_sum(arr[i].fi,arr[i+1].fi-1,1,n,Rt[p]);
						if(arr[i].fi<arr[i+1].fi) flg=1;
					}
					cur+=arr[i+1].se;
				}
				if(!flg){
					puts("-1");
					lst_ans=0;
				}
				else printf("%d\n",lst_ans);
			}
			if(opt==2) {
				lst_ans=inf;
				FR(i,1,ct) {
					if(!cur) {
						lst_ans=min(lst_ans,st.query_MIN(arr[i].fi,arr[i+1].fi-1,1,n,Rt[p]));
						if(arr[i].fi<arr[i+1].fi) flg=1;
					}
					cur+=arr[i+1].se;
				}
				if(!flg) {
					puts("-1");
					lst_ans=0;
				}
				else printf("%d\n",lst_ans);
			}
			if(opt==3) {
				lst_ans=-inf;
				FR(i,1,ct) {
					if(!cur) {
						//printf("%lld %lld\n",arr[i].fi,arr[i+1].fi-1);
						lst_ans=max(lst_ans,st.query_MAX(arr[i].fi,arr[i+1].fi-1,1,n,Rt[p]));
						if(arr[i].fi<arr[i+1].fi) flg=1;
					}
					cur+=arr[i+1].se;
				}
				if(!flg) {
					puts("-1");
					lst_ans=0;
				}
				else printf("%d\n",lst_ans);			
			}
		}
		st.clear();
	}
}