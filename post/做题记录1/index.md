
<!--more-->

# 2021

## 4.16

[P3321 [SDOI2015]序列统计](https://www.luogu.com.cn/problem/P3321)

Tag：NTT 数论 

写题解了。



[P3499 [POI2010]NAJ-Divine Divisor](https://www.luogu.com.cn/problem/P3499)

Tag：数论 高精度

将所有数$\leq 10^6$的素因子先全部筛出来。

那么所有数可以被分为4类

$=1,=p,=p^2,=pq$，$p,q$均为$\ge10^6$的质数。

然后分类讨论暴力统计出现次数即可。

[P3306 [SDOI2013] 随机数生成器](https://www.luogu.com.cn/problem/P3306)

同余方程，写题解了。

[P3653 小清新数学题](https://www.luogu.com.cn/problem/P3653)

同P3499的思路，小的暴力先弄掉，然后由于区间小，剩下暴力即可。

## 4.18

[CF949C Data Center Maintenance](https://www.luogu.com.cn/problem/CF949C)

tag：图论，强连通分量

阅读理解题

题意 

$n$个点，每个点$i$有一个值$a_i$。$m$个条件，每个条件有2个点$x,y$且$a_x\neq a_y$。选择最少的$k$个点，使其值加$1$后，$m$个条件仍成立。

solution

考虑如果有一个人选了两个点$x,y$，且$(a_x+1)\bmod h=a_y$，那么就连一条从$x\to y$的有向边。表示如果选了$x$，就必须选$y$。然后将得到的图强连通缩点，容易发现一定是选最小的且出度为0的块。因为如果选了一个出度不为$0$的点，之后还要将其他出度为0的点选上，由于是DAG一定有出度为0的点

[P4782 【模板】2-SAT 问题](https://www.luogu.com.cn/problem/P4782)

tag：2-SAT

## 4.19

[loj#3101. 「JSOI2019」精准预测](https://loj.ac/p/3101)

大概算2-SAT吧

[P4882 lty loves 96！](https://www.luogu.com.cn/problem/P4882)

数位dp

[P2473 [SCOI2008] 奖励关](https://www.luogu.com.cn/problem/P2473)

菜鸡想不出的题。

令$dp[i][S]$表示在第$1$轮到第$i-1$轮内宝物是否取过的状态为$S$，第$i$轮到第$K$轮的最大期望得分，然后倒着转移。

对于第$j$个物品，$1\leq j\leq n$

1. 如果$S$包含的状态满足取第$k$中宝物的条件，则可以选择取或不取，即
   $$
   dp[i][S] +=\max(dp[i+1][S],dp[i+1][S|(1<<(j-1))]+P_k)
   $$

2. 如果不能取，那就是$dp[i][S]+=dp[i+1][S]$

以及最后是期望值，上面求的东西包括第$i$轮取了所有宝物的情况，所以在计算完之后，要将$dp[u][S]$除以$n$。

最后答案为$dp[1][0]$

```c++
int k,n,p[22],s[22];
double dp[111][1<<17];
signed main()
{
	k=read(),n=read();
	int x;
	R(i,1,n)
	{
		p[i]=read();x=read();
		while(x) s[i]=s[i]|(1<<(x-1)),x=read();
	}
	L(i,1,k) R(mask,0,1<<n)
	{
		R(j,1,n) if((mask&s[j])==s[j]) dp[i][mask]+=max(dp[i+1][mask],dp[i+1][mask|(1<<(j-1))]+p[j]);else dp[i][mask]+=dp[i+1][mask];
		dp[i][mask]/=n;
	}
	printf("%.6lf\n",dp[1][0]);
}
```

