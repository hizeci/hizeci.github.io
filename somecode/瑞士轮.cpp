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
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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
const int N=2e6+10;
int n,r,q;
struct node
{
    int id,s,w;
    inline bool operator <(const node a)const{
        if(s==a.s) return id<a.id;
        return s>a.s;
    }
}a[N],win[N],los[N];

signed main()
{
    freopen("swiss.in","r",stdin);
    freopen("swiss.out","w",stdout);
    n=read()*2,r=read(),q=read();
    R(i,1,n) a[i].id=i;
    R(i,1,n) a[i].s=read();
    R(i,1,n) a[i].w=read();
    sort(a+1,a+n+1);
    n/=2;
    while(r--)
    {
        R(i,1,n)
        if(a[(i<<1)-1].w<a[(i<<1)].w){
            a[(i<<1)].s++;
            win[i]=a[(i<<1)];
            los[i]=a[(i<<1)-1];
        }
        else{
            a[(i<<1)-1].s++;
            win[i]=a[(i<<1)-1];
            los[i]=a[(i<<1)];
        }
        merge(los+1,los+n+1,win+1,win+n+1,a+1);
    }
    printf("%lld\n",a[q].id);
}

/*
int tmp[N];
void gbrt(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)>>1;
    gbrt(l,mid),gbrt(mid+1,r);
    int i=l,j=mid+1,tot=l;
    while(i<=mid&&j<=r)
    {
        if(a[i]<a[j]) tmp[tot++]=a[i++];
        else tmp[tot++]=a[j++];
    }
    while(i<=mid) tmp[tot++]=a[i++];
    while(j<=r)   tmp[tot++]=a[j++];
    for(int i=l;i<=r;i++) a[i]=tmp[i];
}
*/