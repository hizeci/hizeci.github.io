#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
const ll inf=(1ll<<60);
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const double eps=1e-6;
inline int fpow(int a,int b=mod-2,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
struct bignum
{
    int num[111111],len;
    bignum() {memset(num,0,sizeof(num));len=1;}
    inline void get_num(int x){
        bignum();if(!x) return;len=0;
        while(x) num[len++]=x%10,x/=10; 
    }
    friend bool operator <(const bignum A,const bignum B){
        if(A.len!=B.len) return A.len<B.len;
        L(i,0,A.len-1) if(A.num[i]!=B.num[i]) return A.num[i]<B.num[i];
        return 0;
    }
    friend bignum operator + (const bignum A,const bignum B){
        bignum C;
        C.len=max(A.len,B.len)+1;
        R(i,0,C.len-1) C.num[i]=A.num[i]+B.num[i];
        R(i,0,C.len-1) C.num[i+1]+=C.num[i]/10,C.num[i]%=10;
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    friend bignum operator * (bignum A,int B){
        bignum C;
        C.len=A.len+20;
        R(i,0,C.len-1) C.num[i]=B*A.num[i];
        R(i,0,C.len-1) C.num[i+1]+=C.num[i]/10,C.num[i]%=10;
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    friend bignum operator * (bignum A,bignum B)
    {
        bignum C;
        C.len=A.len+B.len;
        R(i,0,A.len-1) R(j,0,B.len-1) C.num[i+j]+=A.num[i]*B.num[j];
        R(i,0,C.len-1) C.num[i+1]+=C.num[i]/10,C.num[i]%=10;
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    friend bignum operator / (bignum A,int B)
    {   
        bignum C;
        C.len=A.len;
        int sum=0;
        L(i,0,C.len-1) {
            sum=sum*10+A.num[i];
            C.num[i]=sum/B;
            sum%=B;
        }
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    inline void print_num(bool Entr=true){
        L(i,0,len-1) putchar('0'+num[i]);
        if(Entr) putchar('\n');
    }
}tmp1,tmp2,ans;
int n;
struct node{int a,b,ab;inline bool operator <(const node &A)const{return ab<A.ab;} }nd[1111];

signed main()
{
    n=read();
    int a,b;
    R(i,0,n) a=read(),b=read(),nd[i]=(node){a,b,a*b}; 
    sort(nd+1,nd+n+1);
    tmp1.get_num(1);
    R(i,1,n)
    {
        tmp1=tmp1*nd[i-1].a;
        tmp2=tmp1/nd[i].b;
        if(ans<tmp2) ans=tmp2; 
    }
    ans.print_num();
}