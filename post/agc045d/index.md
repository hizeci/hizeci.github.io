
<!--more-->

题意：

给你一个长度为$N$的一个字符串$S$，初始时每个字符均为$0$。

然后给你两个数字$A,B$，你可以对这个字符串进行无限次的两个操作

- 选择连续$A$个字符将它们变成$0$
- 选择连续$B$个字符将它们变成$1$

求本质不同的字符串个数，对$10^9+7$取模。

$1\leq A, B\leq  N\leq 5000$，所有数字均为整数。

sol：

显然，我们可以使每个位置为$1$，因此，若将$0$和$1$取反，答案并不会改变，所以为了方便我们假设$A\leq B$。

考虑怎么样的字符串$x$是合法的：

- 将所有连续的长度$\ge A$的$0$变为$1$，之后存在长度$\ge B$的$1$

因为假设已经固定了一段$1$，那么由于$A\leq B$，所以可以在末端继续填充$1$。

或者直接考虑倒着的操作序列可以看出。

考虑计算最后并不合法的字符串数量。可以通过$dp$计算连续$0$长度$<A$和连续$1$长度$< B$的序列。然后考虑如何$\ge A$的连续的$0$插入连续的$1$中。

考虑预处理出将$\ge A$的连续$0$插入到一个具有$j$个连续$1$部分的方式的数量。

令$g_{i,0/1}$表示长度为$i$的连续$1$段（包含长度$\ge A$的$0$段）并且以$0/1$结尾的方案数（但是开头为$1$）

令$f_{i,0/1}$表示长度为$i$的以$0/1$结尾的不合法方案数。

时间复杂度$O(n^2)$

```c++
int n,a,b;
int f[5555][2],g[5555][2];
inline void add(int &x,const int &y) {x+=y;x>=mod?x-=mod:1;}

signed main()
{
	n=read(),a=read(),b=read();
	if(a>b) swap(a,b);
	g[1][1]=1;
	R(i,2,b-1) 
	{
		add(g[i][1],g[i-1][0]),add(g[i][1],g[i-1][1]);
		R(j,a,i-1) add(g[i][0],g[i-j][1]);
	}
	//R(i,1,b) printf("1:%lld 2:%lld\n",g[i][0],g[i][1]); 
	f[0][0]=f[0][1]=1;
	R(i,1,n) 
	{
		R(j,1,min(a,i+1)-1) add(f[i][0],f[i-j][1]);
		R(j,1,min(b,i+1)-1) 
		{
			if(i==n) add(f[i][0],1ll*f[i-j][0]*g[j][0]%mod);
			add(f[i][1],i==j?(g[j][0]+g[j][1])%mod:1ll*f[i-j][0]*g[j][1]%mod);
		}
	}
	int ans=1;
	R(i,1,n) ans*=2,ans%=mod;
	//printf("%lld %lld\n",f[n][0],f[n][1]);
	ans=(ans-(f[n][0]+f[n][1])%mod+mod)%mod;
	writeln(ans);
}
```

