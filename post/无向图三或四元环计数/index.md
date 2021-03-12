
### 题意:

给定一个$n$个点$m$条边的简单无向图,求其三/四元环个数.

$1\leq n\leq 10^5,1\leq m\leq 2\times 10^5,1\leq u,v\leq n$.

给出的图不存在重边和子环,但不保证图联通.

<!--more-->

### 总

使用根号分治的思想.

考虑一个节点的度数,我们重新建一个新图,对于原图的每条边,建一条从度数小的点建一条从度数小的点向度数大的点的一条有向边,如果度数一样那就编号从小到大连.显然这个图为一个$DAG$(因为从一个结点出发到达的点要么度数比它大，要么结点编号比它大，所以不会回到自己).可以证明所有节点的出度是$O(\sqrt m)$的.

#### [具体证明 (来自扶苏)](https://www.luogu.com.cn/blog/fusu2333/solution-p1989)

1. 当$v$在原图(无向图)上的度数不大于$\sqrt m$时,由于新图每个节点的出度不可能小于原图的度数,所以$out_v=O(\sqrt m)$.
2. 当$v$的原图上的度数大于$\sqrt m$时,注意到它只能向原图中度数不小于它的点连边,又因为原图中所有的点的度数和为$O(m)$,所以原图中度数大于$\sqrt m$的点只有$O(\sqrt m)$个.因此$v$的出边只有$O(\sqrt m)$条,也即$out_v=O(\sqrt m) $

因此所有节点的出度均为$O(\sqrt m)$.

菜鸡的想法:

考虑度数和大约为$2m$左右,假设有点出度$\geq \sqrt m$,但是显然这些点的数量也不会超过$O(\sqrt m)$个.

### 三元环计数

#### 题解

枚举原图中的一条边,考虑两端的节点为$u$和$v$,我们需要统计新图中$u,v$连向的公共节点的个数.

先对$u$所有的出边扫一遍,给所有出点打上标记,再扫一遍$v$的所有出边,统计一下有标记的点的个数.这样子就可以了.

时间复杂度为$O(m\sqrt m)$

#### 代码:

```c++
const int N=2e5+10;
int n,m;
vector<int>g[N],e[N];
int deg[N],vis[N];
int ans;
signed main()
{	
	n=read(),m=read();
	int u,v;
	R(i,1,m) u=read(),v=read(),g[u].pb(v),g[v].pb(u),deg[u]++,deg[v]++;
	R(u,1,n) for(int v:g[u]) if((deg[u]<deg[v])||(deg[u]==deg[v]&&u<v)) e[u].pb(v);
	R(u,1,n) 
	{
		for(int v:e[u]) vis[v]=u;
		for(int v:e[u]) for(int w:e[v]) ans+=(vis[w]==u);
	}
	writeln(ans);
}
```



### 四元环计数

#### 题解

枚举原图中的一条边.考虑两端的节点为$u,v$,我们求出一个$v$连出的点$w(u<w)$,考虑一个四元环是由两条$u \to v,v\to w$和$u \to v',v'\to w$组成的(我们以度数最大的点$w$计数),所以我们维护一个$cnt$,每找到一个$w$,让$ans+=cnt[w],cnt[w]++$.每次改变$u$的时候将$cnt$清$0$即可.

时间复杂度为$O(m\sqrt m)$

[这里参照这个](https://blog.csdn.net/weixin_43466755/article/details/112985722)

搬运:按照三元环的方式建出有向图，并按照这个规则给每个结点赋一个排名$rk$如果还想按三元环的思路往下走会遇到一个问题，就是原图的四元环在新建的有向图中可能有两种形式，

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210122165855720.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzQ2Njc1NQ==,size_16,color_FFFFFF,t_70##pic_center)

所有需要使用别的枚举方法。可以发现这两种形式都可以由两条无向边+两条有向边表示，即

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021012217034387.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzQ2Njc1NQ==,size_16,color_FFFFFF,t_70##pic_center)

且两条无向边的替代位置唯一，所以我们可以把原图的四元环当成两端无向边

$(u,v)+$有向边$<v,w>$拼起来的,且无论是哪种情况,$rk_u\leq rk_v$。之后便是最上面那段

版权声明：本文为CSDN博主「恩比德爱上大帝」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_43466755/article/details/112985722

时间复杂度仍为$O(m\sqrt m)$

#### 代码

```c++
const int N=2e5+10;
int n,m;
vector<int>g[N],e[N];
int deg[N],cnt[N],id[N],rnk[N];
int ans;
inline int cmp(int u,int v) {return (deg[u]<deg[v])||(deg[u]==deg[v]&&u<v);}
signed main()
{	
	n=read(),m=read();
	int u,v;
	R(i,1,m) u=read(),v=read(),g[u].pb(v),g[v].pb(u),deg[u]++,deg[v]++;
	R(i,1,n) id[i]=i;
	sort(id+1,id+n+1,cmp);
	R(i,1,n) rnk[id[i]]=i;
	R(u,1,n) for(int v:g[u]) if(cmp(u,v)) e[u].pb(v);
	R(u,1,n) 
	{
		for(int v:g[u]) for(int w:e[v]) if(rnk[w]>rnk[u]) ans+=cnt[w]++;
		for(int v:g[u]) for(int w:e[v]) cnt[w]=0;
	}
	writeln(ans);
}
```



### 五/六元环

似乎能$O(m^2)$，但是菜鸡不会。

