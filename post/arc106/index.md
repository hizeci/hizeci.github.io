
<!--more-->

### D：

给出$N,K,A_i$

对于每个$X\in [1,k]$计算$\sum\limits_{L=1}^{N-1} \sum\limits_{R=L+1} ^N (A_i+A_j)^X $



考虑将式子改成
$$
\frac{\sum\limits_{i=1}^N \sum\limits_{j=1}^N (A_i+A_j)^X-\sum\limits_{i=1}^ N (2\cdot A_i)^X }{2}
$$
然后继续化简左边那个东西。
$$
\sum_{i=1}^N \sum_{j=1}^N (A_i+A_j) ^X=\sum_{i=1} ^N \sum_{j=1}^N \sum_{k=0}^{X} \binom X k A_j^k A_j^{X-k}
$$
然后拆开$\binom X k$
$$
\sum_{i=1} ^N \sum_{j=1}^N \sum_{k=0} ^{X} {X!}\cdot  \frac{A_j^k}{k!} \cdot \frac{A_j^{X-k}}{(X-k)!}=X! \cdot \sum_{k=0}^X \big(\sum_{i=1}^N \frac{A_i^k}{k!} \big)\cdot \big(\sum_{j=1}^N \frac{A_j^{X-k}}{(X-k)!} \big)
$$
$\sum\limits_{i=1}^N \frac{A_i^ k }{k!}$可以在$O(NK)$的时间内预处理出来。

整个式子可以在$O(k^2)$的时间复杂度算出来（也可以做到$O(k\log k)$）

### E:

你经营着一家有$N$个员工的商店，从今天开始，第$i$个员工会连续上$A_i$天班然后连续休息$A_i$天。

每一天，你都可以从所有上班的员工中选出一位，给它一枚奖章，求最少要几天每个员工获得至少$k$枚奖章。



考虑通过二分答案来找到最少的天数$D$。

考虑一个二分图拥有$N\times K +D$个点。

令$U$表示这$N\times K$个顶点的集合。

将代表每天的点与当天工作的员工相对应的点连一条边，那么满足题目条件就相当于覆盖整个$U$。

> 霍尔定理：二分图存在最大完备匹配的充要条件是与某一侧的**任意**$k$个点相连的另一侧节点$\ge k$个

考虑霍尔定理，这种情况就相当于对于每个子集$A \in U$，满足$|A|\le |\Gamma (A)|$

而$|\Gamma (A)|$只取决于关于$A$中包含的一组员工。因此对于与某个相对应的点，我们只需考虑两种情况：情况A不包含所有的点，或者包含所有的点。

因此，对于每一个包含员工的非空子集，我们可以找到子集中包含的至少一名员工开始上班的天数。

此外$|A|\leq NK \leq |\Gamma (A)|$，显然这不会超过$2NK$天。

由于这不是很说人话，搬一份别人的题解：

![QQ图片20210512085433.png](https://i.loli.net/2021/05/12/Ifhe6uYoLCD8a7N.png)

```c++
int n,k,a[22];
int popcnt1[1<<18],cnt[1<<18];
const int m=18*100000*2;
int tag[3600010];
int check(int x)
{
	//cnt[i]表示选择工人集合是i（i看成一个二进制数）的子集天数和
	memset(cnt,0,sizeof(cnt));
	R(i,0,x-1) cnt[tag[i]]++;
	R(i,0,n-1) R(j,0,(1<<n)-1) if((j>>i)&1) cnt[j]+=cnt[j^(1<<i)]; 
	R(i,0,(1<<n)-1) if(popcnt1[i]*k>x-cnt[(1<<n)-1-i]) return 0;
	return 1;
}
signed main()
{
	n=read(),k=read();
	R(i,1,(1<<n)-1) popcnt1[i]=popcnt1[i>>1]+(i&1);
	R(i,0,n-1) a[i]=read();
	R(i,0,n-1) R(j,0,m-1) if(j%(a[i]*2)<a[i]) tag[j]|=(1<<i);//选择员工的集合。
	int l=1,r=m,best=m;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) best=mid,r=mid-1;
		else l=mid+1;
	}
	writeln(best);

}
```

### F:

暂时不会，之后来做