
<!--more-->

题意：

给你一个初始为$A\times B$的方格矩阵，每次往上铺一行或者往右铺一列格子，并在铺的格子上选一个涂黑，直到矩阵大小到$C\times D$为止，求最终染色的方案数，对$998244353$取模。

$1\leq A\leq C\leq 3000,1\leq B\leq D \leq 3000,A,B,C,D$均为整数。



sol：

将每种绘制网格的方式与一个操作序列相对应。如果最上面一行有多个（或没有）黑色正方形，则最后一个操作是在右边添加一列。另一方面，如果最上面行只有一个黑色正方形，可以发现从初始状态也可以到达没有最上面一行的网格。因此，从初始状态可以到达的网格的每个状态中，我们可以使用一下的算法恢复唯一的操作序列。

- 如果最上面一行有多个黑色正方形，找到导致网格不包含最右列的操作序列，并在右端添加一列。
- 否则，找到导致网格不包含最上面一行的操作序列，并在最上方添加一列。

令$dp[i][j][0/1]$表示第$i$行第$j$没有/有多个黑色正方形的列，可以在$O(CD)$时间复杂度内计算这样的操作顺序。

```C++
int dp[3333][3333][2];
int A,B,C,D;
signed main()
{
	A=read(),B=read(),C=read(),D=read();
	dp[A][B][0]=1;
	R(i,A,C) R(j,B,D)
	{
		if(i==A&&j==B) continue;
		dp[i][j][0]=(dp[i-1][j][1]+dp[i-1][j][0]*j)%mod;
		dp[i][j][1]=(dp[i][j-1][0]*i+dp[i][j-1][1]*i)%mod;
	}
	writeln((dp[C][D][0]+dp[C][D][1])%mod);
}
```

网上还有种转移是$dp[i][j]=dp[i-1][j]\cdot j+dp[i][j-1]\cdot i-dp[i-1][j-1]\cdot (i-1)(j-1)$

不过我不是很懂qwq