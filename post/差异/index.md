
题意：

给定一个长度为$n$的字符串$\texttt S$，令$T_i$表示它从第$i$个字符开始的后缀，求

$\sum\limits_{1\leq i<j\leq n} len(T_i)+len(T_j)-2\times lcp(T_i,T_j)$

<!--more-->

由于直接算答案不是很好做，考虑先求出$\sum\limits_{1\leq i < j\leq n} len(T_i)+len(T_j)$再减去后面那堆东西。

这部分答案为$\frac{n(n-1)(n+1)}{2}$（每个后缀都出现了$n-1$次，后缀总长是$\frac{n(n+1)}{2}$）

之后考虑怎么搞$lcp(i,j)$这项，我们知道$lcp(i,j)=k$等价于$\min\left\{height[i+1\cdots j] \right \} =k$

所以可以将$lcp(i,j)$记作$\min\left\{x|i+1\leq x \leq j,height[x]=lcp(i,j) \right \} $对答案的贡献。

考虑每个位置对答案的贡献是哪些后缀的$\texttt{LCP}$，其实就是从它开始向左若干个连续的$\texttt{height}$大于它的后缀选一个，再从向右若干个连续个$\texttt{height}$不小于它的后缀中选一个。这个东西可以单调栈搞。

虽然写的时候偷懒直接搞了个悬线法。

```c++
signed main()
{
	scanf("%s",str+1);
	n=strlen(str+1);ans=1ll*(n+1)*n*(n-1)/2;
	R(i,1,n) s[i]=str[i]-'a'+2;
	get_SA(s,sa,rk,n),get_ht(n,ht);ht[n+1]=-1;
	R(i,1,n) l[i]=r[i]=i;
	R(i,1,n) while(ht[l[i]-1]>ht[i]) l[i]=l[l[i]-1];
	L(i,1,n) while(ht[r[i]+1]>=ht[i]) r[i]=r[r[i]+1];
	R(i,1,n) ans-=2ll*ht[i]*(i-l[i]+1)*(r[i]-i+1);
	//L(i,1,n) printf("%lld %lld %lld %lld\n",i,i-l[i]+1,r[i]-i+1,ht[i]);
	printf("%lld\n",ans);
}
```

