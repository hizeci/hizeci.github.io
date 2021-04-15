
<!--more-->

## 数论

### 最大公约数$(gcd)$

递归版

```c++
inline ll gcd(ll a,ll b) {return !b?a:gcd(b,a%b);}
```

迭代版

```c++
ll gcd(ll x,ll y)
{
     if(!x) return y;
    if(!y) return x;
    ll t=__builtin_ctzll(x|y);
    x>>=__builtin_ctzll(x);
    do
    {
        y>>=__builtin_ctzll(y);
        if(x>y) swap(x,y);
        y-=x;
    }while(y);
    return x<<t;
}
```

### 快速幂

```c++
ll quick_pow(ll a,ll b,ll p) {ll ans=1;while(b){if(b&1)ans=(lll)ans*a%p;a=(lll)a*a%p;b>>=1;}return ans;}
```

### 扩展欧几里得

```c++
int exgcd(int a,int b,int &x,int &y) {if(!b){x=1,y=0;return a;}int ret=exgcd(b,a%b,y,x);y-=x*(a/b);return ret;}
```

### 龟速乘和快速乘

```c++
inline ll ftimes(ull a,ull b,ull p){int ans=0;while(b){if(b&1)ans=(ans+a)%p;a=(a+a)%p;b>>=1;}return ans;}

```

```c++
inline ll ftimes(ull a,ull b,ull p)
{
    a%=p,b%=p;
    ll c=a*b-(ull)((ld)a/p*b)*p;c%=p;
    return c<0?c+p:c;
}
```

### 线性筛素数以及最小素因子

```c++
int tot_pri,pri[N/10],min_pri[N];
bool isnpr[N];
inline void euler_pri(int lim=1000000)
{
    int k;
    R(i,2,lim) 
    {
        if(!isnpr[i]) min_pri[i]=i,pri[++tot_pri]=i;
        R(j,1,tot_pri) 
        {
            k=i*pri[j];
            if(k>lim) break;
            isnpr[k]=1;min_pri[k]=pri[j];
            if(i%pri[j]==0) break;
        }
    }
}
```

### 线性筛求欧拉函数

```c++
int tot_pri,pri[N/10],phi[N];
bool isnpr[N];
inline void euler_pri(int lim=1000000)
{
    int k;
    phi[1]=1;
    R(i,2,lim) 
    {
        if(!isnpr[i]) phi[i]=i-1,pri[++tot_pri]=i;
        R(j,1,tot_pri) 
        {
            k=i*pri[j];
            if(k>lim) break;
            isnpr[k]=1;
            if(i%pri[j]==0) {phi[k]=phi[i]*pri[j];break;}
        	phi[k]=phi[i]*(pri[j]-1);
        }
    }
}
```

### 线性筛求莫比乌斯函数

```c++
int tot_pri,pri[N/10],mu[N];
bool isnpr[N];
inline void euler_pri(int lim=1000000)
{
    int k;
    mu[1]=1;
    R(i,2,lim) 
    {
        if(!isnpr[i]) mu[i]=-1,pri[++tot_pri]=i;
        R(j,1,tot_pri) 
        {
            k=i*pri[j];
            if(k>lim) break;
            isnpr[k]=1;
            if(i%pri[j]==0) {mu[k]=0;break;}
        	mu[k]=-mu[i];
        }
    }
}
```

### 线性求逆元以及组合数计算

```c++
int F[N],inv[N],Finv[N];
void init_C(int lim)
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,lim) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,lim) F[i]=(lll)F[i-1]*i%mod,Finv[i]=(lll)Finv[i-1]*inv[i]%mod;
}
inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return (lll)F[n]*Finv[m]%mod*Finv[n-m]%mod;}
```

### 求单个数的逆元

若$p$为质数，则可以直接利用费马小定理。否则使用扩展欧几里得求同余方程。

```c++
inline int qpow(int a,int b,int p) {int ans=1;while(b){if(b&1)ans=(lll)ans*a%p;a=(lll)a*a%p;b>>=1;}return ans;}
inline int get_inv(int a,int p) {return fpow(a,p-2,p);}
```

```c++
int exgcd(int a,int b,int &x,int &y) {if(!b){x=1,y=0;return a;}int ret=exgcd(b,a%b,y,x);y-=x*(a/b);return ret;}
inline int get_inv(int a,int p){if(!a)return 1;int x,y;exgcd(a,p,x,y);return (x+p)%p;}
```

以及oi-wiki上大概有复杂度更优的做法。

### Miller-Rabin 素数测试

```c++
ll pr[]={2,3,5,7,11,13,17,19,37};
//yhx:No pseudoprime below 2^64 to base 2, 3, 5, 7, 11, 13, 82, 373.
int Miller_Rabin(ll p)
{
    if(p<3) return p==2;
    if(p==3) return 1;
    if(!(p&1)) return 0;
    ll a=p-1,b=0;
    while(!(a&1)) a>>=1,++b;
    for(int i=0,j;i<=8;i++)
    {
        if(p==pr[i]) return 1;
        if(!(p%pr[i])) return 0;
        ll v=quick_pow(pr[i],a,p);
        if(v==1||v==p-1) continue;
        for(j=1;j<b;j++) {v=(lll)v*v%p;if(v==p-1)break;}
        if(v!=(p-1)) return 0;
    }
    return 1;
}
```

### Pollard-Rho 素因数分解

```c++
namespace por
{
    ll pr[]={2,3,5,7,11,13,17,19,37};
    int Miller_Rabin(ll p)
    {
        if(p<3) return p==2;
        if(p==3) return 1;
        if(!(p&1)) return 0;
        ll a=p-1,b=0;
        while(!(a&1)) a>>=1,++b;
        for(int i=0,j;i<=8;i++)
        {
            if(p==pr[i]) return 1;
            if(!(p%pr[i])) return 0;
            ll v=quick_pow(pr[i],a,p);
            if(v==1||v==p-1) continue;
            for(j=1;j<b;j++) {v=(lll)v*v%p;if(v==p-1)break;}
            if(v!=(p-1)) return 0;
        }
        return 1;
    }
    inline ll calc(ll x,ll c,ll p) {return ((lll)x*x+c)%p;}
    inline ll Pollard_Rho1(ll p)
    {
        ll s=0,t=0;
        ll c=(ll)rand()%(p-1)+1;
        ll val=1;
        for(int lim=1;;lim<<=1,s=t,val=1)
        {
            R(cnt,1,lim)
            {
                t=calc(t,c,p);
                val=ftimes(val,abs(t-s),p);
                if(!(cnt%127)) {ll g=gcd(val,p);if(g>1)return g;}
            }
            ll g=gcd(val,p);if(g>1)return g; 
        }
    }
    inline ll Pollard_Rho2(ll p)
    {
        ll c=rand()%(p-3)+3;
        ll t=calc(0,c,p),r=calc(calc(0,c,p),c,p);
        while(t!=r)
        {
            ll g=gcd(abs(t-r),p);
            if(g>1) return g;
            t=calc(t,c,p);
            r=calc(calc(r,c,p),c,p);
        }
        return p;
    }
    int ans;
    void solve(int n)
    {
        if(n<=ans||n<2) return;
        if(Miller_Rabin(n)){ckmax(ans,n);return;}
        int p=n;
        while(p>=n)p=Pollard_Rho1(n);
        while((n%p)==0) n/=p;
        solve(n),solve(p);
    }
    int mian(int n)
    {         
        srand(time(0));
        ans=0;
        solve(n);
        return ans;
    }
}
```

### 原根

```c++
const int N=1e6+10;
int pri[N/10],phi[N],tot_pri;
bool isnop[N],hvprt[N];
int fc[N],tot_fc;
int ans[N],tot_ans;
void init_e()
{
	int tmp;
	phi[1]=1;
	R(i,2,N-10)
	{
		if(!isnop[i]) pri[++tot_pri]=i,phi[i]=i-1;
		for(int j=1;j<=tot_pri&&(tmp=i*pri[j])<=(N-10);j++) 
		{
			isnop[tmp]=1;
			if(i%pri[j]==0) {phi[tmp]=phi[i]*pri[j];break;}
			phi[tmp]=phi[i]*(pri[j]-1);
		}
	}
	hvprt[2]=hvprt[4]=1;
	R(i,2,tot_pri) 
	{
		for(int j=1;(j*pri[i])<=(N-10);j*=pri[i]) {hvprt[j*pri[i]]=1;}
		for(int j=2;(j*pri[i])<=(N-10);j*=pri[i]) {hvprt[j*pri[i]]=1;}
	}
}
inline void get_fc(int x,int *fc,int &tot_fc)
{
	for(int i=2;i*i<=x;i++) if(x%i==0) {fc[++tot_fc]=i;while(x%i==0)x/=i;}
	if(x>1) fc[++tot_fc]=x;
}
inline int check_prt(int x,int p,int *fc,int &tot_fc)
{
	if(fpow(x,phi[p],p)^1) return 0;
	R(i,1,tot_fc) if(fpow(x,phi[p]/fc[i],p)==1) return 0;
	return 1;
}
inline int find_fprt(int p,int *fc,int &tot_fc) {R(i,1,p-1)if(check_prt(i,p,fc,tot_fc))return i;return 0;}
inline void get_allprt(int p,int x,int *ans,int &tot_ans)
{
	int prod=1;
	R(i,1,phi[p]) 
	{
		prod=(1ll*prod*x)%p;
		if(gcd(i,phi[p])==1) ans[++tot_ans]=prod;
	}
}
signed main()
{
	init_e();int n,d;
	for(int _=read();_;_--)
	{
		n=read(),d=read();
		if(hvprt[n]) 
		{
			tot_ans=tot_fc=0;
			get_fc(phi[n],fc,tot_fc);
			int mn=find_fprt(n,fc,tot_fc);
			get_allprt(n,mn,ans,tot_ans);
			sort(ans+1,ans+tot_ans+1);
			writeln(tot_ans);
			R(i,1,tot_ans/d) writesp(ans[i*d]);puts("");
		}
		else printf("0\n\n");
	}
}
```

### BSGS

```c++
int BSGS(int a,int c,int p)
{
    mp.clear();
    int sq,mu=1,ff=get_inv(a,p);
    for(sq=1;sq*sq<=p;sq++);
    R(i,0,sq-1) mp.ins(mu*c%p,i),mu=mu*ff%p;
    ff=get_inv(mu,p);mu=1;
    R(i,0,sq-1)
    {
        int pos=mp.ser(mu);
        if(pos!=-1) return i*sq+pos;
        mu=mu*ff%p;
    }
    return -1;
}
```

### EXBSGS

```c++
int BSGS(int a,int c,int p)
{
    mp.clear();
    int sq,mu=1,ff=get_inv(a,p);
    for(sq=1;sq*sq<=p;sq++);
    R(i,0,sq-1) mp.ins(mu*c%p,i),mu=mu*ff%p;
    ff=get_inv(mu,p);mu=1;
    R(i,0,sq-1)
    {
        int pos=mp.ser(mu);
        if(pos!=-1) return i*sq+pos;
        mu=mu*ff%p;
    }
    return -1;
}
int solve(int a,int c,int p)
{
    if(a==c) return 1;
    int d=gcd(a,p);
    if(d==1) return BSGS(a,c,p);
    if(c%d) return -1;
    p/=d;
    return solve(a%p,(c/d)*get_inv(a/d,p)%p,p)+1;
}
int check(int a,int c,int p)
{
    if(c==1) return 0;
    if(!a) return !c?1:-1;
    return solve(a,c,p);
}
```

### CRT

鸽了

### EXCRT

```c++
inline int QuickMul(int a,int b,int mod)
{
    int c=a*b-(int)((ld)a*b/mod+0.5)*mod;
    return c<0?c+mod:c;
}
int exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);y-=x*(a/b);
	return d;
}
int excrt()
{
	int M=b[1],ans=a[1];
	int x,y,k;
	R(i,2,n) {
		int A=M,B=b[i],C=(a[i]-ans%B+B)%B;//ax \equiv c(\bmod b)
		int D=exgcd(A,B,x,y),BG=B/D;
		if(C%D) return -1;
		x=QuickMul(x,C/D,BG);
		ans+=x*M;
		M*=BG;
		ans=(ans%M+M)%M;
	}
	return ans;
}
```

## 字符串

### kmp

```c++
for(int i=2,j=0;i<=lenb;i++)
{
	while(j&&b[i]!=b[j+1]) j=nxt[j];
	if(b[i]==b[j+1]) j++;
	nxt[i]=j;
}			
for(int i=1,j=0;i<=lena;i++)
{
	while(j&&a[i]!=b[j+1]) j=nxt[j];
	if(a[i]==b[j+1]) j++;
	if(j==lenb) {printf("%lld\n",i-lenb+1);j=nxt[j];}
}
```

### [AC自动机](https://www.luogu.com.cn/problem/P3796)

```c++
const int N=5e5+10;
int n;
char a[400][500];
char s[N*50];
struct node
{
	int cnt,pos;
	inline bool operator <(const node a)const{
		if(cnt==a.cnt) return pos<a.pos;
		return cnt>a.cnt;
	}
}Ans[N];
struct AC_Automaton
{
	struct tri
	{
		int end,vis[30],fil;
	}AC_A[N];
	int cnt=0;
	void clr(int s=0)
	{
		if(!s) cnt=0;
		memset(AC_A[s].vis,0,sizeof(AC_A[s].vis));
		AC_A[s].end=AC_A[s].fil=0;
	}
	void ins(char *s,int pos)
	{
		int now=0;
		for(;*s;s++)
		{
			if(AC_A[now].vis[*s-'a']==0) 
			{
				AC_A[now].vis[*s-'a']=++cnt;
				clr(cnt);
			}
			now=AC_A[now].vis[*s-'a'];
		}
		AC_A[now].end=pos;
	}
	void build()
	{
		deque<int>q;
		for(int i=0;i<26;i++) if(AC_A[0].vis[i])
		{
			AC_A[AC_A[0].vis[i]].fil=0;
			q.pb(AC_A[0].vis[i]);
		}
		while(q.size()>0)
		{
			int u=q.front();q.pop_front();
			for(int i=0;i<26;i++)
			{
				if(AC_A[u].vis[i])
				{
					AC_A[AC_A[u].vis[i]].fil=AC_A[AC_A[u].fil].vis[i];
					//子节点的fil指针指向当前节点fil指针所指向的节点的相同子节点
					q.pb(AC_A[u].vis[i]);
				}
				else AC_A[u].vis[i]=AC_A[AC_A[u].fil].vis[i];
				//若不存在这个子节点，那么当前这个子节点指向当前节点fil指针的fil子节点
			}
		}
	}
	void frequency(char *s)
	{
		int now=0;
		for(;*s;s++)
		{
			now=AC_A[now].vis[*s-'a'];
			for(int t=now;t;t=AC_A[t].fil) ++Ans[AC_A[t].end].cnt;
		}
	}
}AC;


signed main()
{
	while(1)
	{
		n=read();
		if(!n) break;
		AC.clr();
		for(int i=1;i<=n;i++)
		{
			scanf("%s",a[i]);
			Ans[i].cnt=0,Ans[i].pos=i;
			AC.ins(a[i],i);
		}
		AC.build();
		scanf("%s",s);
		AC.frequency(s);
		sort(Ans+1,Ans+n+1);
		printf("%lld\n",Ans[1].cnt);
		for(int i=1;i<=n;i++) if(Ans[i].cnt==Ans[1].cnt) cout<<a[Ans[i].pos]<<"\n";else break;
	}
}
```

### 后缀数组SA

$O(n\log n)$倍增

```c++
#define cmp(x,y,w) (ornk[x]==ornk[y]&&ornk[x+w]==ornk[y+w])
void get_SA(char *s,int *sa,int *rnk,int n)
{
	static int m,cnt[N],osa[N],ornk[N<<1],px[N];m=0;
	R(i,1,n) ++cnt[(int)s[i]],ckmax(m,(int)s[i]);
	R(i,2,m) cnt[i]+=cnt[i-1];
	L(i,1,n) sa[cnt[(int)s[i]]--]=i;
	m=0;R(i,1,n) rnk[sa[i]]=s[sa[i]]==s[sa[i-1]]?m:++m;
	for(int lim=1;m<n;lim<<=1)
	{
		clr(cnt,m+5),cpy(ornk+1,rnk+1,n+1);
		R(i,n-lim+1,n) osa[++cnt[0]]=i;
		//L(i,n-lim+1,n) osa[++cnt[0]]=i; 
		R(i,1,n) if(sa[i]>lim) osa[++cnt[0]]=sa[i]-lim;
		//R(i,1,n) ++cnt[rnk[i]];
		R(i,1,n) ++cnt[px[i]=rnk[osa[i]]];
		R(i,2,m) cnt[i]+=cnt[i-1];
		//L(i,1,n) sa[cnt[rnk[osa[i]]]--]=osa[i];
		L(i,1,n) sa[cnt[px[i]]--]=osa[i];
		m=0;R(i,1,n) rnk[sa[i]]=cmp(sa[i],sa[i-1],lim)?m:++m;
		if(m==n) {R(i,1,n)sa[rnk[i]]=i;break;}
	}
}
```

$O(n)$SA-IS

```c++
#define del(x) sa[c[s[x]]--]=x
#define add(x) sa[c[s[x]]++]=x
void SA_sort(int *S,int n,int m,int *s,int *tp,int tot)
{
	clr(sa,n+2);clr(c1,m+2);
	R(i,1,n) c1[s[i]]++;
	R(i,2,m) c1[i]+=c1[i-1];
	cpy(c+1,c1+1,m+2);
	L(i,1,tot) del(S[i]);
	R(i,1,m+1) c[i]=c1[i-1]+1;
	R(i,1,n) if(sa[i]>1&&tp[sa[i]-1]) add(sa[i]-1);
	cpy(c+1,c1+1,m+2);
	L(i,1,n) if(sa[i]>1&&!tp[sa[i]-1]) del(sa[i]-1);
}
void SA_IS(int n,int m,int *s,int *tp,int *pos)
{
	int tot=0,cnt=0;int *S=s+n;//为了减小常数，这里直接取一段没有用过的地址而不是重新申请。
	tp[n]=0;//为了方便，钦定最后一位是S型
	L(i,1,n-1) tp[i]=(s[i]!=s[i+1])?s[i]>s[i+1]:tp[i+1];
	rk[1]=0;
	R(i,2,n) if(tp[i-1]==1&&!tp[i]) pos[++tot]=i,rk[i]=tot;else rk[i]=0;//求出所有LMS子串的端点
	SA_sort(pos,n,m,s,tp,tot);//排序LMS子串
	int u=0,p=0;
	R(i,1,n) if(rk[sa[i]]) //去重，即unique
	{
		u=rk[sa[i]];
		if(cnt<=1||pos[u+1]-pos[u]!=pos[p+1]-pos[p]) ++cnt;//一个减小常数的优化：如果两个LMS子串长度不一样，显然这两个子串不同
		else
		{
			R(j,0,pos[u+1]-pos[u]) //暴力判断，注意这里如果某个字符对应的LMS后缀不同，也应当认为不同，因为如果首字母相同，L型后缀字典序一定大于S型
			if(s[pos[u]+j]!=s[pos[p]+j]||tp[pos[u]+j]!=tp[pos[p]+j]) {++cnt;break;}//因为LMS子串长度不超过$O(N)$，所以暴力扫描复杂度是对的。
		}
		S[u]=cnt;//重新标号
		p=u;
	} 
	if(tot!=cnt) SA_IS(tot,cnt,S,tp+n,pos+n);//cnt相当于不相同数字个数，如果cnt==tot相当于所有数字两两不同，直接桶排序。为了方便，tp和pos也直接取一段没有用过的地址。
	else R(i,1,tot) sa[S[i]]=i;
	R(i,1,tot) S[i]=pos[sa[i]];//得到真正的排名（之前的标号排的是LMS子串，这里的排名是LMS后缀）。
	SA_sort(S,n,m,s,tp,tot);////利用LMS子串得到真正的sa。
}
int ht[N];
void get_ht(int n)
{
	R(i,1,n) rk[sa[i]=sa[i+1]]=i;
	int k=0;
	R(i,1,n)
	{
		if(k) --k;
		while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;
		ht[rk[i]]=k;
	}
}
signed main()
{
	//fread(str+1,1,100000,stdin);n=strlen(str+1);
	//while(!isalpha(str[n])) --n;
    n=strlen(str+1);
    R(i,1,n) s[i]=str[i]-'a'+2;
	s[++n]=1;
	//writeln(n);R(i,1,n) writesp(s[i]);puts("");
	SA_IS(n--,28,s,tp,pos);
	get_ht(n);
    R(i,1,n) printf("%d ",sa[i]);cout<<endl;
	return 0;
}
```

### 后缀自动机SAM

```c++
struct node {int len,nxt,son[26],siz;}a[N<<1];
int lst,tn;
inline void init_SAM()
{
	a[0].len=0,a[0].nxt=-1;
	tn=lst=0;
}
void extend_SAM(int c)
{
	int cur=++tn,p=lst;
	a[cur].len=a[p].len+1;
	for(;p!=-1&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
	if(p==-1) a[cur].nxt=0;
	else
	{
		int v=a[p].son[c];
		if(a[v].len==a[p].len+1) a[cur].nxt=v;
		else
		{
			int x=++tn;a[x]=a[v];
			a[x].len=a[p].len+1;
			for(;p!=-1&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
			a[cur].nxt=a[v].nxt=x;
		}
	}
	lst=cur;
}	
```

### 广义SAM

```c++
struct exSAM
{
	int tn;
	struct node {int len,nxt,son[26];}a[N<<1];
	inline void init_SAM() {tn=1;}
	inline int extend_SAM(int lst,int c)//将ch[now]接到last后面
	{
		if(a[lst].son[c])
		{
			int p=lst,v=a[p].son[c];
			if(a[p].len+1==a[v].len)return v;//最初的特判1
			else
			{
				int x=++tn;a[x]=a[v];
				a[x].len=a[p].len+1;
				for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
				a[v].nxt=x;
				return x;//即最初的特判2	
			}
		}
		int cur=++tn,p=lst;
		a[cur].len=a[p].len+1;
		for(;p&&!a[p].son[c];p=a[p].nxt)a[p].son[c]=cur;
		if(!p) a[cur].nxt=1;
		else
		{
			int v=a[p].son[c];
			if(a[v].len==a[p].len+1)a[cur].nxt=v;
			else
			{
				int x=++tn;a[x]=a[v];
				a[x].len=a[p].len+1;
				for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
				a[cur].nxt=a[v].nxt=x;
			}
		}
		return cur;
	}
}sm;
```

### 后缀树

还不会

## 数据结构

### ST表

```c++
void init()
{
	for(int j=1;j<=22;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
inline int query(int l,int r)
{
	int k=log2(r-l+1);
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
```

## 多项式

