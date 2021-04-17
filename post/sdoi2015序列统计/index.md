
<!--more-->

题意

给定一个集合$S$，$\forall x \in S,S\in [0,m-1]$求从这个集合中选取$n$个数使得乘积为$x$的方案数，答案对`1004535809`取模。

$1\leq n\leq 10^9,3\leq m\leq 8000$且$m$为质数

先考虑$n=2$，**加和**为$x$的情况：

发现$m\leq 8000$，令集合中$i$这个数字出现了$f(i)$次，则答案为
$$
\sum _i f(i)\cdot f(x-i)
$$
再来考虑$n=3$，**加和**为$x$的情况
$$
\sum_i \sum_j f(i)\cdot f(j)\cdot f(x-i-j)
$$
复杂度看上去并不优秀

而选取$3$个数可以看作在选取一个数的集合$S_1$和选取两个数的集合$S_2$中分别选取$1$个数。

可以先求出选取两个数和为$i$的方案数为$f_2(i)$，则发现答案为
$$
\sum_i f(i)\cdot f_2(x-i)
$$
然后考虑快速求出$f_2$
$$
f_2(i)=\sum f(j)\cdot f(i-j)
$$
直接做是$O(n^2)$的，但这是标准的卷积形式，可以使用`FFT/NTT`优化。时间复杂度为$O(n\log n)$

然后再考虑选取$n$个数**加和**为$x$的情况，仿照$n=3$的情况。

设$f_t(i)$表示从集合中选取$t$个数加和为$i$的方案数。
$$
f_t(i)=\sum f_{t-1}(j) \cdot f(i-j)
$$
时间复杂度为$O(xm\log m)$

再考虑倍增，设$f_t(i)$表示从集合中选取$2^t$个数加和为$i$的方案数，又有
$$
f_t(i)=\sum f_{t-1}(j)\cdot f_{j-1}(i-j)
$$
这样的时间复杂度为$O(m\log m \log x)$

然后再考虑模$m$意义下为$x$的方案数。

与上一种情况不同的是要把$\ge n$的项累加到对应模运算以后的位置。

```c++
void mul(int *f,int *g,int *ans){
	f-->tmp1
    g-->tmp2//复制两个数组，保证f,g本身对应的数组不发生改变
    ntt(tmp1,1);ntt(tmp2,1);
    for(int i=0;i<N;i++)tmp1[i]=tmp1[i]*tmp2[i]%mod;
    ntt(tmp1,-1);
	// 以上为ntt常规操作
    for(int i=0;i<n;i++)ans[i]=tmp1[i];
    for(int i=n;i<N;i++)ans[i%n]=(ans[i%n]+tmp1[i])%mod;//这就是上述的变化
}
```

然后考虑把加法变为乘法的情况.

这里我们将**乘法变成加法**！！1

有两种函数可以实现乘法与加法的互化：指数函数和对数函数。

指数函数，形如$f(x)=a^x,a\ge 0,a\neq 1$，根据幂运算性质，不难得到$f(x+y)=f(x)\cdot f(y)$

取对数运算$a^x=N$，则有$\log_a N=x$，根据$a^x\cdot a^y=a^{x+y}$得到$\log_a a^x+\log_a a^y=\log a^{x+y} =\log_a(a^x\cdot a^y)$推广可得到$\log_a x+\log_a y=\log_a(x\cdot y)$

对数函数，形如$f(x)=\log_a x,a\ge 0,a\neq 1,x>0$，根据对数运算相关性质，不难得到$f(xy)=f(x)+f(y)$。

指数函数可以使**加法转化为乘法**，对数函数可以使**乘法转化为加法**。



但是这些运算都是在实数域上的，而本题是在模意义下的。

考虑模意义下的指数和对数。

求指数还是很容易的，随便以一个数为底（设为$a$），在模意义下求出$a^x,x\in [1,m-1]$，根据对数的定义，则可令$\log_a(a^x\bmod m)=x$这样建立映射关系、

但是由于这种关系必须是一一对应的，因此并不是随便取一个数为底就可以的。

我们需要找到一个底数，满足$a^1,a^2,\ldots a^{m-1}\pmod m$互不相同。

注意这里没有包括$a^0$，因为在$\bmod m$意义下	不存在一个数$x$使得$a^x\equiv 0\pmod 	m$。实际上只有$m-1$个可对应的位置，在本题中$S$集合的$0$对答案无贡献，所以忽略$a^0$

这个东西就是原根，我们只需要遭到$m$的一个原根，就可以将乘法转化为加法。

综上本题解决方法为

1. 求出$m$的随便一个原根$g$，然后将$S$中的数$x$转化为$\log_g x$
2. 求出$f_t$，其中$f_0(i)$表示集合$S$中满足$\log_g ^x=i$数的数量。
3. 将$n$进行二进制拆分，多项式卷积。求出在取过对数的集合中选取$n$个数加和为$i$的方案数
4. 对于$x$，答案即为$ans(\log_gx)$

时间复杂度为$O(m\log m \log n)$

```c++
const int N=1e6+10;
int n,m,gg,X,S;
int tot[N];
int f[44][N],g[N];
int dtol[N],ltod[N];

namespace find_prt
{
	int tot_pri,pri[N/10],phi[N];
	bool isnpr[N];
	void init_phi(int lim=1000000)
	{
		int k;
		phi[1]=1;
		R(i,2,lim) 
		{
			if(!isnpr[i]) pri[++tot_pri]=i,phi[i]=i-1;
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
	inline void div_num(int p,vector<int>&v)
	{
		R(i,1,tot_pri) 
		{
			if(pri[i]>p) break;
			if(p%pri[i]==0) 
			{
				v.pb(pri[i]);
				while(p%pri[i]==0)p/=pri[i];
			}
		}
		if(p^1) v.pb(p);
		//for(int qwq:v) printf("p:%lld\n",qwq);
	}
	inline int check(int x,int p,vector<int>v) 
	{
		if(fpow(x,phi[p],p)^1) return 0;
		for(int qwq:v) if(fpow(x,phi[p]/qwq,p)==1) return 0;
		return 1;
	}
	int find_prt(int p,vector<int>v)
	{	
		R(i,1,p-1) if(check(i,p,v)) return i;return 0;
	}
	int mian(int p) {if(!tot_pri)init_phi();vector<int>v;div_num(phi[p],v);return find_prt(p,v);}
}	
namespace poly
{
	const int _G=3,invG=334845270;
	int tr[N<<1],tf;
	void tpre(int n){
		if(tf==n) return;tf=n;
		R(i,0,n-1) tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	}
	void NTT(int *g,int rev,int n)
	{
		tpre(n);
		static ull f[N<<1],w[N<<1];w[0]=1;
		R(i,0,n-1) f[i]=(((ll)mod<<5)+g[tr[i]])%mod;
		for(int l=1;l<n;l<<=1)
		{
			ull tG=fpow(rev?_G:invG,(mod-1)/(l+l));
			R(i,1,l-1) w[i]=w[i-1]*tG%mod;
			for(int k=0;k<n;k+=l+l)
			{
				R(p,0,l-1) 
				{
					int tt=w[p]*f[k|l|p]%mod;
					f[k|l|p]=f[k|p]+mod-tt;
					f[k|p]+=tt;
				}
			}
			if(l==(1<<10)) R(i,0,n-1) f[i]%=mod;
		}
		if(!rev) 
		{
			ull invn=fpow(n);
			R(i,0,n-1) g[i]=f[i]%mod*invn%mod;
		}
		else R(i,0,n-1) g[i]=f[i]%mod;
	}
	inline void px(int *f,int *g,int n){R(i,0,n-1)f[i]=1ll*f[i]*g[i]%mod;}
	void times(int *f,int *g,int *sav,int n,int m,int mod2)
	{
		static int a[N<<1],b[N<<1];
		int N=1;for(N=1;N<(n+m-1);N<<=1);
		//clr(sav,N);
		cpy(a,f,n);clr(a+n+1,N-n);
		cpy(b,g,m);clr(b+m+1,N-m);
		//R(i,0,n-1) a[i]=f[i];R(i,n,N-1)a[i]=0;
		//R(i,0,m-1) b[i]=g[i];R(i,m,N-1)b[i]=0;
		NTT(a,1,N);NTT(b,1,N);
		px(a,b,N);NTT(a,0,N);
		R(i,0,mod2-1) sav[i]=a[i];
		R(i,mod2,N-1) sav[i%n]=(sav[i%n]+a[i])%mod,sav[i]=0;
		clr(a,N),clr(b,N);
	}
}	

void solve(int p) 
{
	g[0]=1;
	L(i,0,32){if(p&(1ll<<i)){/*printf("i:%lld\n",i);*/poly::times(f[i],g,g,m-1,m-1,m-1);}/*printf("i:%lld\n",i); R(j,0,12)printf("%lld ",g[j]);puts("");*/}
}

signed main()
{

	n=read(),m=read(),X=read(),S=read();
	gg=find_prt::mian(m);
	for(int i=0,mu=1;i<(m-1);i++,mu=mu*gg%m) {dtol[mu]=i,ltod[i]=mu;}
	//printf("%lld\n",gg);
	int x;R(i,1,S) x=read(),x?tot[dtol[x]]++:1;
	R(i,0,m-1) f[0][i]=tot[i];
	//printf("%lld\n",m);
	R(i,1,32) poly::times(f[i-1],f[i-1],f[i],m-1,m-1,m-1);
	/*
	R(i,0,32)
	{
		printf("i:%lld\n",i);
		R(j,0,12) printf("%lld ",f[i][j]);
		puts("");
	} 
	*/
	solve(n);
	writeln(g[dtol[X]]);
}	
```

