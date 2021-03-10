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
const int mod=1e9+7;
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
void init()
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
const int N=1e5+10;
char s[N];
struct tri
{
    int ch[15],end;
    void clr(){
        memset(ch,0,sizeof(ch));
        end=0;
    }
}tr[N];
//27807
int tot,ok;
void ins(char *s)
{
    int now=0;
    for(int j=1;s[j];j++)
    {
        int x=s[j]-'0';
        if(!tr[now].ch[x]) tr[now].ch[x]=++tot;
        now=tr[now].ch[x]; 
    }
    tr[now].end|=1;
}
void find_s(char *s)
{
    int now=0;
    for(int j=1;s[j];j++)
    {
        int x=s[j]-'0';
        if(!tr[now].ch[x]) return;
        if(tr[tr[now].ch[x]].end) {ok=1;return;}
        now=tr[now].ch[x];
    }
    ok=1;   
}
int n;
int _;
signed main()
{
    for(_=read();_;_--)        
    {
        tot=ok=0;
        R(i,0,(int)1e5) tr[i].clr();
        n=read();
        R(i,1,n) 
        {
            scanf("%s",s+1);
            if(ok) continue;
            
            find_s(s);ins(s);
        }
        printf(ok?"NO":"YES");
        puts("");
    }
}
