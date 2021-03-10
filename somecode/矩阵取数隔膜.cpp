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
const int INF=0x7f7f7f3f;
const int mod=998244353;
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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
//dp[i][j]表示某行选到区间[i,j]的max
//有dp[i][j]=max(dp[i+1][j]+2^m+i-j\times a[i],dp[i][j-1]2^m+i-j\times a[j])
//ans=dp[1][m];
const int N=233;
struct bignum
{
    int num[N],len;
    bignum() {memset(num,0,sizeof(num));len=1;}
    inline void get_num(int x){
        bignum();if(!x) return;len=0;
        while(x) num[len++]=x%10,x/=10; 
    }
    friend bool operator <(const bignum A,const bignum B){
        if(A.len!=B.len) return A.len<B.len;
        FL(i,,A.len) if(A.num[i]!=B.num[i]) return A.num[i]<B.num[i];
        return 0;
    }
    friend bignum operator + (const bignum A,const bignum B){
        bignum C;
        C.len=max(A.len,B.len)+1;
        FR(i,0,C.len) C.num[i]=A.num[i]+B.num[i];
        FR(i,0,C.len) C.num[i+1]+=C.num[i]/10,C.num[i]%=10;
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    friend bignum operator * (bignum A,int B){
        bignum C;
        C.len=A.len+20;
        FR(i,0,C.len) C.num[i]=B*A.num[i];
        FR(i,0,C.len) C.num[i+1]+=C.num[i]/10,C.num[i]%=10;
        while(C.len>1&&C.num[C.len-1]==0) C.len--;
        return C;
    }
    inline void print_num(bool Entr=true){
        FL(i,0,len) putchar('0'+num[i]);
        if(Entr) putchar('\n');
    }
}res,dp[N][N],P2P[N];
int n,m,a[N];
void solve(int x){
    R(i,1,m) dp[i][i]=P2P[m]*a[i];
   // R(i,1,m) dp[i][i].print_num();
    R(len,2,m) R(i,1,m-len+1){
        int j=len+i-1;
        dp[i][j]=max(dp[i+1][j]+P2P[m-j+i]*a[i],dp[i][j-1]+P2P[m-j+i]*a[j]);
    }
    res=res+dp[1][m];
}
int main(){
    n=read(),m=read();    
    P2P[0].get_num(1);
    R(i,1,m) P2P[i]=P2P[i-1]*2;
    //R(i,1,m) P2P[i].print_num();
    R(i,1,n){ 
        R(j,1,m) a[j]=read();
        solve(i);
    }
    res.print_num();
    return 0;
}

/*
2 3
1 2 3
3 4 2
*/