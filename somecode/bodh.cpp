#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
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
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int djq=998244353;
const int B=450;
const int N=2e5+10;
int bl[N],a[N],inv[N];
int n,q,lst_ans;
int mumu[N],ggd[N];
inline int gcd(int a,int b){return (!b)?a:gcd(b,a%b);}
signed main()
{
	n=read();	
	fill(mumu,mumu+n+6,1);
	inv[1]=1;R(i,2,N-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	R(i,1,n) {a[i]=read(),bl[i]=(i-1)/B+1,mumu[bl[i]]*=a[i],mumu[bl[i]]%=djq;if((i-1)%B==0)ggd[bl[i]]=a[i];else ggd[bl[i]]=gcd(ggd[bl[i]],a[i]);}
	//printf("%lld %lld\n",mumu[1],ggd[1]);
	int tmpl,tmpr,l,r;q=read();
	R(i,1,q) 
	{
		int res=1;
		tmpl=read(),tmpr=read();
		l=(tmpl+lst_ans)%n+1,r=(tmpr+lst_ans)%n+1;l>r?Swap(l,r):1;
		//printf("%lld %lld %lld\n",l,r,res);
		R(i,l,min(bl[l]*B,r)) res=(res*a[i])%mod;
		if(bl[l]!=bl[r]) R(i,(bl[r]-1)*B+1,r) res=(res*a[i])%mod; 	
		R(i,bl[l]+1,bl[r]-1) res=(res*mumu[i])%mod;
		int gdd=a[l];
		R(i,l,min(bl[l]*B,r)) gdd=gcd(gdd,a[i]); //res=(res*inv[a[i]])%mod;
		if(bl[l]!=bl[r]) R(i,(bl[r]-1)*B+1,r) gdd=gcd(gdd,a[i]); //res=(res*inv[a[i]])%mod; 	
		R(i,bl[l]+1,bl[r]-1) gdd=gcd(gdd,ggd[i]);		
		if(min(bl[l]*B,r)-l==0) gdd=1;
		res=res*inv[gdd]%mod;
		printf("%lld\n",res);
		lst_ans=res;
	}
}
/*
1
7
1
1 1









空飛ぶ羽根と引き換えに　繋ぎ合う手を選んだ僕ら
没有选择飞翔的翅膀 而是选择十指相扣的我们
それでも空に魅せられて　夢を重ねるのは罪か
却仍然向往着天空 反复做着同样的梦 这有错吗
 

夏は秋の背中を見て　その顔を思い浮かべる
夏天望着秋天的背影 心中浮现出了那面庞
憧れなのか、恋なのか　叶わぬと知っていながら
我是在期待吗 这是爱情吗 明明知道无法实现
 

通り雨が通り雨と　木漏れ日たちが木漏れ日と
阵阵骤雨过后迎来天晴 阳光从树叶的空隙间投来点点光影
名乗るずっとずっとずっと前から　あなたはあなたでいたんだろう？
在与你报名相知的很久以前开始 你便已经是个独一无二的存在了吧
 

 

重力が眠りにつく　１０００年に一度の今日
当大地渐渐失去了重力 在千年一遇的今天
太陽の死角に立ち　僕らこの星を出よう
站在阳光无法触及的边缘 我们离开这颗星球吧
 

彼が眼を覚ました時　連れ戻せない場所へ
向着在他睁开双眼之时 却再也无法返回的地方
「せーの」で大地を蹴って　ここではない星へ
齐声喊着「1、2..」脚蹬大地 向着其他行星前进
 

行こう
出发吧！
 

 

夏風邪に焦る心が　夏をさらに早送るよ
患上热伤风的我心烦意乱 心中期望夏天能够早日离开
めまぐるしい景色の中　君だけが止まって見えた
瞬息万变的景色之中 只有你保持着原样从未改变
 

君と出会ったあの日から　パタリと夜、夢は止んだよ
从与你邂逅的那天开始 黑夜中的梦境砰然而止
土の中で待ちこがれた　叶えるその時は今だ
在土壤中期盼了许久的那一刻 正是现在这梦想实现之时
 

重力が眠りにつく　１０００年に一度の今日
当大地渐渐失去了重力 在千年一遇的今天
花火の音に乗せ　僕らこの星を出よう
和着烟火之声的节奏 我们离开这颗星球吧
 

彼が眼を覚ました時　連れ戻せない場所へ
向着在他睁开双眼之时 却再也无法返回的地方
「せーの」で大地を蹴って　ここではない星へ
齐声喊着「1、2..」脚蹬大地 向着其他行星前进
 

行こう
出发吧！
 

もう少しで運命の向こう　もう少しで文明の向こう
只差一步就是命运的方向 只差一步就是文明的方向
もう少しで運命の向こう　もう少しで
只差一步就是命运的方向 只差一步...
 

 

夢に僕らで帆を張って　来たるべき日のために夜を越え
为了梦想我们扬帆起航 为了明日的到来跨越无尽黑夜
いざ期待だけ満タンで　あとはどうにかなるさと　肩を組んだ
满怀期待的上吧 我们肩并着肩 无论遇到什么困难总会有办法
 

怖くないわけない　でも止まんない
我们并非无所畏惧 而是不愿止步不前
ピンチの先回りしたって　僕らじゃしょうがない
即便危机捷足先登 我们的步伐也不受其左右
僕らの恋が言う　声が言う
我们的爱情在呼喊 我们的声音在回响
 

「行け」と言う
出发吧！
*/