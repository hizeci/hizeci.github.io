
<!--more-->

注意到一个$1\times 1$的格子的凌乱度为$0$

而每次将整个矩阵每次从中间劈开，最多只能劈$\log_2 H+\log_2 W$次，所以说整个矩阵的混乱度是$O(\log H+\log W)$级别的。

现在，考虑$dp$计算以下值：

- 混乱值为$i$的子矩阵的最大水平长度，其左上角和左下角的坐标分别为$(r,c)$和$(r',c)$

- 混乱值为$i$的子矩阵的最大垂直长度，其左上角和右上角的坐标分别为$(r,c)$和$(r,c')$

令$dp[v][i][l][r]$表示凌乱度为$v$，在$l$行到$r$行时之间第$i$列开始向右延伸最多能延伸到第几列。

转移讨论下一刀横着还是竖着。

如果是竖着：$dp[v][i][l][r]=dp[v-1][dp[v-1][l][r][i]+1][l][r]$

否则$dp[v][i][l][r]=\max(\min(dp[v][i][l][k],dp[v][i][k+1][r])),k\in [l,d-1]$

然后使用双指针把循环$k$给优化掉

时间复杂度$O(HW(H+W)\log HW)$。

```c++
short dp[20][200][200][200];
int n,m;
char a[200][200];

signed main()
{
	n=read(),m=read();
	R(i,1,n) scanf("%s",a[i]+1);
	R(i,1,n) R(j,1,n) R(k,0,18) dp[k][m+1][i][j]=m;
	L(i,1,m) 
	{
		R(j,1,n)
		{
			if(a[j][i]==a[j][i+1]) dp[0][i][j][j]=dp[0][i+1][j][j];
			else dp[0][i][j][j]=i;
		}	
		R(l,1,n) R(r,l+1,n) 
		{
			if(a[r][i]==a[r-1][i]) dp[0][i][l][r]=min(dp[0][i][l][r-1],dp[0][i][r][r]);
			else dp[0][i][l][r]=i-1;
		}
	}
	R(v,1,18) R(i,1,m) 
	{
		R(l,1,n)
		{
			dp[v][i][l][l]=dp[v-1][dp[v-1][i][l][l]+1][l][l];
			int now=l;
			R(r,l+1,n) 
			{
				while(now<=r&&min(dp[v-1][i][l][now],dp[v-1][i][now+1][r])<=min(dp[v-1][i][l][now+1],dp[v-1][i][now+2][r])) now++;
                dp[v][i][l][r]=max(min(dp[v-1][i][l][now],dp[v-1][i][now+1][r]),dp[v-1][dp[v-1][i][l][r]+1][l][r]);
			}
		}
	}
	R(i,0,18) if(dp[i][1][1][n]==m) return printf("%lld\n",i)&0;
}

```

