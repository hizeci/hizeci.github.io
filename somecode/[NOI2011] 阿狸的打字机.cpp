#include<bits/stdc++.h>
#define ld long double
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
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=9223372036854775807;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x) {return x % mod;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
inline void Mul(int &x, int y) {if ((x *= y) >= mod) x %= mod;}
inline int fpow(int a,int b){int res=1;while(b){if(b&1)Mul(res,a);Mul(a,a);b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
	F[0]=Finv[0]=inv[1]=1;
	R(i,2,500) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	R(i,1,500) F[i]=mul(F[i-1]*i),Finv[i]=mul(Finv[i-1]*inv[i]);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	return mul(mul(F[n]*Finv[m])*Finv[n-m]);
}
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
const int N=1e6+20;
char s[N];
struct edge
{
	int nxt,to;
}e[N<<1];
int head[N],cnt;
int dfn[N],low[N],tim;
int ql[N],qr[N];
int ch[N][30],Fa[N];
int cnt_end,End[N];
int sz[N];
int Fil[N];
int tot;
struct ques
{
	int x,y,id,res;
}qs[N];
inline int cmp1(ques a,ques b) {
	return a.y<b.y;
}
inline int cmp2(ques a,ques b){
	return a.id<b.id;
}
struct segmentree
{
	int val[N<<2],lazy[N<<2];
	void push_down(int len,int x)
	{
		if(!lazy[x]) return;
		Add(lazy[x<<1],lazy[x]);
		Add(lazy[x<<1|1],lazy[x]);
		Add(val[x<<1],(len-(len>>1))*lazy[x]);
		Add(val[x<<1|1],(len>>1)*lazy[x]);
		lazy[x]=0;
	}
	inline void push_up(int x){
		val[x]=add(val[x<<1]+val[x<<1|1]);
	}
	void modify_add(int L,int R,int l,int r,int x,int k)
	{
		//printf("L:%lld,R:%lld,l:%lld,r:%lld,x:%lld\n",L,R,l,r,x);
		if(L<=l&&r<=R) {
			Add(val[x],k*(r-l+1));
			Add(lazy[x],k);
			return;
		}
		push_down((r-l+1),x);
		int mid=(l+r)>>1;
		if(L<=mid) modify_add(L,R,l,mid,x<<1,k);
		if(mid<R)  modify_add(L,R,mid+1,r,x<<1|1,k);
		push_up(x);
	}
	int query_sum(int L,int R,int l,int r,int x)
	{
		if(L<=l&&r<=R) return val[x];
		push_down(r-l+1,x);
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) Add(ret,query_sum(L,R,l,mid,x<<1));
		if(mid<R)  Add(ret,query_sum(L,R,mid+1,r,x<<1|1));
		return ret;
	}
}st;
inline void init() {
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v){
	e[++cnt].nxt=head[u];e[cnt].to=v;head[u]=cnt;
}
struct AC_automaton
{
	void ins(char *s)
	{
		int now=0;
		for(int j=0;s[j];j++)
		{
			int x=s[j]-'a';
			if(s[j]=='B') {now=Fa[now];continue;}
			if(s[j]=='P') {End[++cnt_end]=now;continue;}
			if(!ch[now][x])
			{
				ch[now][x]=++tot;
				Fa[tot]=now;
			}
			now=ch[now][x];
		}
	}
	void get_fail()
	{
		deque<int>q;
		FR(i,0,26) if(ch[0][i]) 
		{
			Fil[ch[0][i]]=0;
			q.pb(ch[0][i]);
			add_edge(0,ch[0][i]);
		}
		while(q.size()>0)
		{
			int u=q.front();q.pop_front();
			FR(i,0,26) if(ch[u][i]) 
			{
				Fil[ch[u][i]]=ch[Fil[u]][i];
				add_edge(Fil[ch[u][i]],ch[u][i]);
				q.pb(ch[u][i]);
			}
			else ch[u][i]=ch[Fil[u]][i];
		}
	}
}AC;
void dfs(int u)
{
	dfn[u]=++tim;
	sz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		dfs(v);
		sz[u]+=sz[v];
	}
}
signed main()
{
	init();
	scanf("%s",s);
	AC.ins(s);
	AC.get_fail();
	dfs(0);
	int q=read();
	R(i,1,q) qs[i].x=read(),qs[i].y=read(),qs[i].id=i;
	sort(qs+1,qs+q+1,cmp1);
	int now=0,pos=1,cnt_work=0,len=strlen(s);
	//printf("len:%lld\n",len);
	for(int i=0;i<len;i++)
	{
		if(s[i]=='P')
		{
			cnt_work++;
			while(qs[pos].y<cnt_work&&pos<=q) pos++;
			while(qs[pos].y==cnt_work&&pos<=q)
			{
				int x=qs[pos].x;
				qs[pos].res=st.query_sum(dfn[End[x]],dfn[End[x]]+sz[End[x]]-1,1,len,1);
				pos++;
			}
			continue;	
		}
		if(s[i]=='B')
		{
			st.modify_add(dfn[now],dfn[now],1,len,1,-1);
			now=Fa[now];
			continue;
		}
		int x=s[i]-'a';
		now=ch[now][x];
		st.modify_add(dfn[now],dfn[now],1,len,1,1);		
		//printf("now:%lld,dfn[now]:%lld,sz[now]:%lld\n",now,dfn[now],sz[now]);
	}
	sort(qs+1,qs+q+1,cmp2);
	for(int i=1;i<=q;i++) printf("%lld\n",qs[i].res);
}