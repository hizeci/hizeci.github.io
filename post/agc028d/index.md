
<!--more-->

由于是一个圆不太好考虑，所以先切开这个环看作一条直线。

令$dp[i][j]$表示$i,j$在同一个连通块且满足$[i,j]$内部互相连边的方案数。

如果一定有$[i,j]$内部的点连接到$[i,j]$外部，那么$dp[i][j]=0$。

否则，令$f(i,j)$表示$[i,j]$中尚未连接到任何点的点数。

显然，若$f(i,j)$为奇数，则$dp[i][j]=0$。

否则，连接$[i,j]$中的点的方案数为$g(i,j)=(f(i,j)-1)\times (f(i,j)-3)\times \ldots \times 1$（第一个选择的点有$(f(i,j)-1)$个点可以连边，第二个选择的点有$(f(i,j)-3)$个点可以连边……）

但是此时并没有考虑$i,j$是否在同一个连通块中，考虑枚举$i$所在连通块的右端点$k$，减去$\sum dp[i][k]\times g(k+1,j) k\in [i,j)$即真正的$dp[i][j]$

时间复杂度$O(N^3)$

```c++
int dp[666][666];
int n,k;
int g[666],sum[666],to[666];
signed main()
{
	n=read(),k=read();
	g[0]=1;for(int i=2;i<=2*n;i+=2) g[i]=1ll*(i-1)*g[i-2]%mod;
	int a,b;
	R(i,1,k) a=read(),b=read(),sum[a]=sum[b]=1,to[a]=b,to[b]=a;
	R(i,1,2*n) sum[i]+=sum[i-1];
	L(i,1,2*n) R(j,i+1,2*n)
	{
		a=0;
		R(k,i,j) if(to[k]&&(to[k]<i||to[k]>j)) a=1;
		if(a) continue;
		dp[i][j]=g[(j-i+1)-(sum[j]-sum[i-1])];
		R(k,i,j-1) dp[i][j]=(dp[i][j]-1ll*dp[i][k]*g[(j-k)-(sum[j]-sum[k])]%mod+mod)%mod;
	}
	//R(i,1,2*n) {R(j,i+1,2*n) printf("%lld ",dp[i][j]);puts("");}
	int ans=0;
	R(i,1,2*n) R(j,i+1,2*n) ans=(ans+1ll*dp[i][j]*g[2*n-(j-i+1)-sum[i-1]-(sum[2*n]-sum[j])])%mod;
	writeln(ans);
}
```

