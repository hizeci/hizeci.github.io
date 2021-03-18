
简要题意：

$\forall i\in [0,n)$求有多少对后缀满足$Len(lcp)\ge i$，以及满足条件的两个后缀的权值乘积的最大值

<!--more-->

由于菜鸡目前只学了$\texttt {SA}$所以先放两篇$\texttt {SA}$的题解，之后有机会补一篇后缀树的。

#### 题解1（后缀数组+并查集）：

第一问的可以转化为求有多少个区间$[l,r]$满足$min\left\{height[l\cdots r]\right\}=i$

考虑用并查集维护后缀集合，从$n-1$到$0$倒序枚举每一个可能的后缀长度$\texttt i$，

在此之前，每个集合内部的任意两个后缀的$\texttt {LCP}$都大于$\texttt i$。

这时假如有两个排名相邻并且$\texttt {LCP}$为$\texttt i$的后缀，我们就可以把它们所处的集合合并起来。

具体地，把$\texttt{height}$降序排序然后顺序插入把$\texttt{ans[height]}$的值加上当前合并的两个相邻的集合的大小乘积。然后我们可以把问题理解成：对于每次插入，我可以连接连续两堆数，然后这两堆数中每一个数值都比r大，所以我们可以把第一堆数的个数和第二堆数的个数相乘，得到的就是这两堆数对答案的贡献。

举个例子：

假设我现在的数列长这样（还未被插入的数（即比$\texttt r$小的数）为$\texttt *$）：$\texttt{5 4 * 4 5 6 7 * * 4 * 8}$

然后现在要在第三个位置插入一个$\texttt 3$

不难发现，一共有$(2+1)\times (4+1)-1=14$种方案（$+1$是因为$3$本身也可以算进来，$-1$是因为$[3,3]$不能算）。

然后合并集合，需要维护$\texttt{sz,mx,mn}$，维护$\texttt{mn}$是因为两个负数乘积可能大于两个正数的乘积

记录的时候需要注意，因为我们合并的时候都是合并排名相邻的一些后缀，所以出现在一个集合中的所有后缀必然是连续的，所以我们只需要记录每个集合的左右端点就可以了。合并的时候也只用更新端点的值就好了。

对于第二问，我们在合并的时候可以将$a_i$的值也顺路合并）

```c++
inline int find_fff(int x){return x==fff[x]?x:fff[x]=find_fff(fff[x]);}
inline void uun(int x,int y)
{
	int fx=find_fff(x),fy=find_fff(y); 
	//printf("x:%lld y:%lld fx:%lld fy:%lld\n",x,y,fx,fy);
	int i=ht[x];
	ans1[i]+=1ll*sz[fx]*sz[fy];
	ckmax(ans2[i],max(1ll*mx[fx]*mx[fy],1ll*mn[fx]*mn[fy]));
	ckmax(mx[fx],mx[fy]),ckmin(mn[fx],mn[fy]);
	fff[fy]=fx,sz[fx]+=sz[fy];
}
signed main()
{
	n=read();
	scanf("%s",str+1);
	R(i,1,n) s[i]=str[i]-'a'+2;
	R(i,1,n) a[i]=read();
	get_SA(s,sa,rk,n);get_ht(n,ht);
	R(i,1,n) id[i]=fff[i]=i,sz[i]=1;
	R(i,0,n) ans1[i]=0,ans2[i]=-inf,mx[i]=mn[i]=a[sa[i]];
	sort(id+2,id+n+1,[&](int x,int y){return ht[x]>ht[y];});
	//R(i,1,n) writeln(id[i]);
	R(i,2,n) if(find_fff(id[i])!=find_fff(id[i]-1)) uun(id[i],id[i]-1);
	L(i,0,n-2) ans1[i]+=ans1[i+1],ckmax(ans2[i],ans2[i+1]);
	R(i,0,n-1) printf("%lld %lld\n",ans1[i],!ans1[i]?0:ans2[i]);
}
```

#### 题解2（后缀数组+单调栈）：

仍然排名从小到大处理。

单调栈内存的元素不是一个后缀的开头而是一个按照排名连续的后缀开头区间。

考虑需要维护什么：

$\texttt{ST}$:区间末尾$\texttt{Ht}$值，即如果该区间后面的一个后缀开头要和该区间的任何一个元素搭配，酒都是$\texttt{ST}$相似的，即维护当前最大是$\texttt{ST}$相似。

$\texttt{sz}$：区间元素个数  $\texttt{mx}$：区间最大值  $\texttt{mn}$区间最小值 同上。

```c++
int stk[N],top;
signed main()
{
	n=read();
	scanf("%s",str+1);
	R(i,1,n) s[i]=str[i]-'a'+2;
	R(i,1,n) a[i]=read();
	get_SA(s,sa,rk,n);get_ht(n,ht);
	//R(i,1,n) writeln(sa[i]);
	R(i,0,n) ans1[i]=0,ans2[i]=-inf;
	int tsz=0,tmx=0,tmi=0;
	R(i,2,n) 
	{
		tsz=1,tmx=tmi=a[sa[i-1]];
		while(top&&stk[top]>=ht[i]) 
		{
			//printf("%lld %lld %lld %lld\n",top,stk[top],i,ht[i]);
			//printf("1:%lld %lld %lld\n",tsz,tmx,tmi);
			ans1[stk[top]]+=1ll*sz[top]*tsz;
			ckmax(ans2[stk[top]],max(1ll*mx[top]*tmx,1ll*mn[top]*tmi));
			tsz+=sz[top],ckmax(tmx,mx[top]),ckmin(tmi,mn[top]);
			//printf("2:%lld %lld %lld\n",tsz,tmx,tmi);
			top--;
		}
		++top;stk[top]=ht[i],sz[top]=tsz,mx[top]=tmx,mn[top]=tmi;
	}
	tsz=1,tmx=tmi=a[sa[n]];
	//L(w,1,top)
	//R(i,1,n) printf("%lld %lld\n",ans1[i],ans2[i]);
	L(i,1,top)
	{
		ans1[stk[i]]+=1ll*sz[i]*tsz;
		ckmax(ans2[stk[i]],max(1ll*mx[i]*tmx,1ll*mn[i]*tmi));
		tsz+=sz[i],ckmax(tmx,mx[i]),ckmin(tmi,mn[i]);
	}
	L(i,0,n-2) ans1[i]+=ans1[i+1],ckmax(ans2[i],ans2[i+1]);
	R(i,0,n-1) printf("%lld %lld\n",ans1[i],!ans1[i]?0:ans2[i]);
}
```



#### 题解3（后缀树）：

不会，先咕咕咕了