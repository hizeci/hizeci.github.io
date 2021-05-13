
<!--more-->

## Luogu 4723 求解线性递推

给定$k$阶线性递推$\{F\}$的前$k$项，$F_0,F_1,\cdots ,F_{k-1}$，以及系数$a_1,a_2,\cdots ,a_k$满足：
$$
F_n =\sum_{i=1}^k F_{n-i} \cdot a_i (n\ge k)
$$
求$F_n$，其中$n\leq 10^{18},k\leq 6\times 10^4$。

因为$n$非常大，所以之前的特征根法在这里没有什么用，因为需要解一个$10^5$阶的方程，肯定是解不出来的，所以没法求出它的通项。

首先第一想法是矩阵快速幂

设初始向量是$\overrightarrow a$然后给它乘上$M^{n-k}$

直接算复杂度就是$O(k^3 \log n)$

这个东西肯定不是非常够接受。

然后介绍一个定理：

### Cayley-Hamilton 定理

线性代数中一个非常重要的定理。这里就不证了。

首先讲一下基础概念：特征多项式。

举个例子，对于一个矩阵$M$而言，它的特征多项式是$\operatorname{char(M)}$（注意这是整体是一个多项式）

可以把$\operatorname{char}$看作一个函数，设自变量为$\lambda$，就是从$\mathbb{R}^{M\times N}\to \mathbb{R} [\lambda]$（从$M\times N$阶矩阵，映射到一个关于$\lambda$的一个多项式）

那么$\operatorname{char(M)} (\lambda) $就被定义为$\det (\lambda I-M)$（若矩阵大小为$K$，则这是一个$K$阶多项式。）

然后把它写成多项式的形式（特征多项式最高次项为$1$）：
$$
\operatorname{char(M)}(\lambda)=\lambda ^k -\sum\limits_{i=1}^k a_i \lambda ^{k-i}
$$
然后Cayley-Hamilton 定理就是说
$$
\operatorname{char(M)}(M)=0 
$$
即
$$
M^k=\sum_{i=1}^k a_i M^{k-i}
$$
然后两边同乘$M^{n-k}$，得到：
$$
M^{n-k}\cdot M^k=\sum_{i=1}^k a_i M^{n-k} M^{k-i} 
$$

$$
M^n=\sum_{i=1}^k a_i \cdot M^{n-i}
$$

所以假如知道$a_i$，考虑怎么求矩阵快速幂：

大概就是把$M^n$拆成$n-1,n-2,\cdots ,n-k$的组合。

然后$n-1$可以拆成$n-2,\cdots ,n-k-1$这样一直变，最后一叠，就变成：
$$
M^n =\sum_{i=0}^{k-1} b_i M^i
$$
因此，假如要求$M^a\cdot M^b$，就是
$$
\big(\sum\limits_{i=0}^{k-1} b_i\cdot M_i \big)\big(\sum\limits_{i=0}^{k-1} c_i\cdot M_i \big)
$$
然后对$b$和$c$进行卷积：
$$
\sum_{i=0}^{2k-1} \sum_{j=0}^{i} b_j \cdot c_{i-j} M^i
$$
多了一些项，就用类似等于$a$的方式给它搞回去。

这个东西可以在$O(k^2\log n)$的时间复杂度之内求出。

当然需要知道$a$。



然后考虑$M$长什么样子（图中的$a$为题目给出的$a$）
$$
M=\begin{bmatrix} a_1 & a_2 & a_3 &\cdots &a_k  \\1 & 0 &0 &\cdots &0\\ 0 & 1 &0 &\cdots &0\\0 & 0 &1 &\cdots &0\\ \vdots & \ddots & &\ & \vdots \\\vdots &  &\ddots & & \vdots\\ \vdots &  & &\ddots & \vdots\\ 0 & 0 & \ldots & 1 & 0
\end{bmatrix}
\begin{bmatrix} f_n\\ f_{n-1} \\f_{n-2}\\ \vdots \\ f_{n-k+1}
\end{bmatrix} 
=
\begin{bmatrix} f_{n+1}\\ f_{n} \\f_{n-1}\\ \vdots \\ f_{n-k+2}
\end{bmatrix} 
$$
我猜会崩，所以先放张图：

![QQ图片20210512203046.png](https://i.loli.net/2021/05/12/oSO4f23PrVjmeTc.png)

对于这个东西考虑求出特征多项式（因为稀疏，所以考虑直接手算...）

然后这个题就做完了。

现在就相当于是给一个$2k-1$次多项式（就是上面那个$b$卷$c$的多项式），这里称为$d(M)$。然后要求一个$k$次多项式$r(M)$满足$r$和$d$是一样的。

因为$\operatorname{char(M)}(M)=\sum\limits_{i=0}^{k-1} a_i M^i=0$，然后把这个写成$b(M)$

$d(M)=b(M)\cdot g(M) +r(M)$

那么$r(M)\equiv d(M) \pmod {b(M)}$

然后现在由于你给任何多项式加或减这个$b(M)$，这个值都不变，所以考虑用这个给$d(M)$降次。

可以理解为：

假如现在由$x_0$满足$x_0^3=x_0^2+2x_0+3$。

那么像$x_0^{100}$就可以拆成$x_0^{99}+2x_0^{98}+3x_0^{97}$，而$x_0^{99}$又可以拆成$x_0^{98}+2x_0^{97}+3x_0^{96}$……然后这么一直拆下去

其实这就相当于对$x^3-x^2-2x-3$取模。

由于多项式除法是$O(k\log k)$的，所以总复杂度就是$O(k\log k\log n)$，就是每一次快速幂都这样做一次多项式取模。

```c++
const int N=333333;
const int _G=3;
const int invG=332748118;
int k,n,m,K,AN;
int lim,totp;

inline int read_mod(){static int x;x=read();x%=mod;x+=x>>31&mod;return x;}
int tr[N],tf;
int inv[N];
int W[N],p[N],f[N],t[N];
int a[N],ans[N];

inline void tpre(int n)
{ 
	if(tf==n)return;tf=n;R(i,0,n-1) tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
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
void px(int *f,int *g,int *p,int n){R(i,0,n-1)p[i]=1ll*f[i]*g[i]%mod;}
void poly_inv(int *f,int *g,int m)
{
	int n=lim;
	static int w[N<<1],r[N<<1],sav[N<<1];
	w[0]=fpow(f[0]);
	//printf("f0:%d w0:%d\n",f[0],w[0]);
	for(int l=2;l<=n;l<<=1) 
	{
		R(i,0,(l>>1)-1) r[i]=w[i];
		cpy(sav,f,l);NTT(sav,1,l);
		NTT(r,1,l);px(r,sav,r,l);
		NTT(r,0,l);clr(r,l>>1);
		cpy(sav,w,l);NTT(sav,1,l);
		NTT(r,1,l);px(r,sav,r,l);
		NTT(r,0,l);
		R(i,l>>1,l-1) w[i]=(w[i]*2ll-r[i]+mod)%mod;
	}
	cpy(g,w,m+1);clr(sav,n);clr(w,n);clr(r,n);
}
void poly_times(int *f,int *g,int *p,int n,int m,int lim)
{
	static int tmpf[N<<1],tmpg[N<<1];
	for(m+=n,n=1;n<m;n<<=1);
	clr(tmpf,n),cpy(tmpf,f,n);
	clr(tmpg,n),cpy(tmpg,g,n);
	NTT(tmpf,1,n),NTT(tmpg,1,n);
	px(tmpf,tmpg,p,n),NTT(p,0,n);
	clr(p+lim,n-lim);clr(tmpf,n),clr(tmpg,n);
}
void init(int n) 
{
	for(lim=1;lim<=n;lim<<=1,++totp);
	tpre(lim);
	int tG=fpow(3,mod>>totp);W[lim>>1]=1;
	R(i,(lim>>1)+1,lim-1) W[i]=1ll*W[i-1]*tG%mod;
	L(i,1,(lim>>1)-1) W[i]=W[i<<1];
}

void times(int *f,int *g)
{
	static int sav[N<<1];
	cpy(sav,f,lim);
	NTT(sav,1,lim);NTT(g,1,lim);
	px(g,sav,g,lim);NTT(g,0,lim);
	R(i,0,lim-1) sav[i]=i>K?0:g[n-i];
	NTT(sav,1,lim);
	px(sav,t,sav,lim);NTT(sav,0,lim);
	R(i,0,lim-1) sav[i]=i>K?0:sav[i];
	reverse(sav,sav+K+1);
	NTT(sav,1,lim);
	px(sav,p,sav,lim);NTT(sav,0,lim);
	R(i,0,lim-1) g[i]=(g[i]-sav[i]+mod)%mod;
	clr(sav,lim);
}
signed main()
{
	k=read(),m=read();
	init(m<<1);n=(m-1)<<1;K=n-m;
	R(i,1,m) p[i]=read_mod();
	R(i,0,m-1) f[i]=read_mod();
	p[0]=mod-1;
	poly_inv(p,t,K);
	NTT(t,1,lim);
	reverse(p,p+m+1);NTT(p,1,lim);	
	a[1]=ans[0]=1;
	while(k) 
	{
		if(k&1) times(a,ans);
		times(a,a);
		k>>=1;
	}
	R(i,0,m-1) AN=(AN+1ll*ans[i]*f[i]%mod)%mod;
	writeln(AN);
}
```



## BZOJ 3625 小朋友与二叉树

（CF438E）

给定一棵$n$个节点的二叉树是合法的，当且仅当每个节点的权值都在给定的集合$C$中。对于每个$S\in [1,m]$，求有多少棵不同的，权值和为$S$的合法二叉树。

$n,m\leq 10^5$，$C$中的元素不超过$10^5$。

Sol：

令$f_s$表示满足条件的权重为$s$的二叉树数量

则有$f_0=1$
$$
f_s= \sum_{w\in \{c_1,\ldots,c_n \}}\sum_i f_i\times f_{s-w-i} (s>0)
$$
然后令$f$的普通生成函数为$F(x)=\sum\limits _{i=0}^{\infty} f_i x^i$

然后令$G(x)=\sum\limits_{i=1}^n x^{c_i}$

然后发现就有$F(x)=F(x)^2 G(x)+1$（$+1$是因为$f_0=1$）

然后解得：
$$
f_s=\frac{1\pm \sqrt{1-4G(x)}}{2G(x)}
$$
然后由于$f_0=1,1\leq c_i$，所以取加号时并不可能。

所以有：
$$
f_s=\frac{1-\sqrt{1-4G(x)}}{2G(x)}=\frac{4G(x)}{2G(x)(1+\sqrt{1-4G(x)})}=\frac{2}{1+\sqrt{1-4G(x)}}
$$
然后就是多项式开根+求逆了。