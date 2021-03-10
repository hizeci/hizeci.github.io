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
//const int mod=1e9+7;
//const int mod=10007;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
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
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ???¨·??§
printf("%lld ",dist(rand_num));
*/
/*
考虑对区间进行分块，从前往后没sqrt(n)个点，考虑其对每个询问的贡献，只需求出来符合条件的前缀长度，最长的中间串，和后缀长度即可
然后考虑每一次sqrt(n)个区间将整个数轴分成了2sqrt(n)个区间。只要对于每一个l,r求出询问左端点在第l个区间，询问右端点在第r个区间的答案即可。
具体的做法是，枚举l，当r向右扫的时候只会不断地加入可行的区间，用静态链表维护符合条件的前缀长度，最长的中间串，和后缀长度即可。求一个点在哪个区间里可以用2 pointer扫

(考虑这根号n个区间对所有询问区间的贡献
*/
const int N=55555;
const int M=222222;
const int D=1111;
const int B=200;
const int mod=173219;

int n,m;
int l1[N],r1[N],l2[M],r2[M];
int ans[M],sf[M];
int arr[D],pre[D][D],mid[D][D],suf[D][D];
int cnt,ll[D],rr[D];
int l[D],r[D];
int cp,cm,cs,ct;
//
int re[N*10],att[N*10];
int tot_inter;
std::vector<int>v[D];
struct hashtable
{
	int head[mod+10],nxt[N*10],val[N*10],cnt;
	inline void ins(int x){
		int t=x%mod;nxt[++cnt]=head[t];val[cnt]=x;head[t]=cnt;
	}
	inline int ser(int x){
		int t=x%mod;for(int i=head[t];i;i=nxt[i]) if(val[i]==x) return i;return 0;
	}
	inline void clear() {
		R(i,1,cnt) head[val[i]%mod]=nxt[i]=0;cnt=0;
	}
}mp;
void modify_add(int x){
	int L=min(l[x-1],x),R=max(r[x+1],x);
	r[L]=R,l[R]=L;
	if(L==1&&R==ct) {
		cp=cm=cs=ct;
		return;
	}
	if(L==1) cp=R;
	if(R==ct) cs=R-L+1;
	cm=max(cm,R-L+1);
}
signed main()
{
	n=read(),m=read();
	R(i,1,n) {l1[i]=read();r1[i]=read();att[++tot_inter]=l1[i];att[++tot_inter]=r1[i]+1;}
	R(i,1,m) {l2[i]=read();r2[i]=read();att[++tot_inter]=l2[i];att[++tot_inter]=r2[i];}
	sort(att+1,att+tot_inter+1);
	tot_inter=unique(att+1,att+tot_inter+1)-att-1;
	mp.clear();
	R(i,1,tot_inter) mp.ins(att[i]);
	R(i,1,n) {l1[i]=mp.ser(l1[i]);r1[i]=mp.ser(r1[i]+1);}
	R(i,1,m) {l2[i]=mp.ser(l2[i]);r2[i]=mp.ser(r2[i]);}
	for(int i=1;i<=n;i+=B) {
		int cnt=0,ct=0;cp=cm=cs=0;
		for(int j=i;j<=n&&j<i+B;j++) {
			ll[++ct]=l1[j],rr[ct]=r1[j];
			arr[++cnt]=l1[j],arr[++cnt]=r1[j];
		}
		arr[++cnt]=0;
		sort(arr+1,arr+cnt+1);
		cnt=unique(arr+1,arr+cnt+1)-arr-1;
		mp.clear();
		R(j,1,cnt) mp.ins(arr[j]);
		R(j,1,ct) ll[j]=mp.ser(ll[j]),rr[j]=mp.ser(rr[j]);
		R(j,1,cnt) v[j].clear();
		R(j,1,ct) v[ll[j]].pb(j);
		R(j,1,cnt) {
			R(k,0,ct+1) l[k]=inf,r[k]=-inf;
			cp=cm=cs=0;
			R(k,1,ct) if(ll[k]<=j&&rr[k]>j) modify_add(k);
			R(k,j,cnt) {
				pre[j][k]=cp,mid[j][k]=cm,suf[j][k]=cs;
				for(int h=0;h<(int)v[k+1].size();h++) modify_add(v[k+1][h]);
			}
		}
		int pos=1;
		R(j,1,tot_inter) {
			while(pos<=cnt&&arr[pos]<=j) pos++;
			re[j]=pos-1;
		}
		R(j,1,m) {
			int x=re[l2[j]],y=re[r2[j]];
			//printf("qwq:%d %d\n",x,y);
			ans[j]=max(ans[j],max(sf[j]+pre[x][y],mid[x][y]));
			sf[j]=(pre[x][y]==ct?sf[j]+pre[x][y]:suf[x][y]);
		}
	}
	R(i,1,m) printf("%d\n",max(ans[i],sf[i]));
}
