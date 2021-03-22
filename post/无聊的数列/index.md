
<!--more-->

题意：

区间加等差数列，单点查询。

根据等差数列定义有$a_n-a_{n-1}=d$，所以说可以通过差分来实现快速加等差数列。

这里假定使用$S$统计差分。

1. 对于$l$： $S_l=S_l+k$
2. 对于区间$(l,r]$：$S_i=S_i+D,l<i\leq r$
3. 对于$r+1$：$S_r=S_r-(k+(r-l)\times d)$

对于每次查询$p$的值，就是求$a_p+\sum\limits_{i=1}^p S_i$

```c++
const int N=2e5+10;
int n,m;
int a[N];
int t[N<<2],la[N<<2];
inline void push_up(int x){t[x]=(t[x<<1]+t[x<<1|1]);}
inline void push_down(int len,int x)
{
	if(!la[x]) return;
	la[x<<1]+=la[x],la[x<<1|1]+=la[x];
	t[x<<1]+=(len-(len>>1))*la[x],t[x<<1|1]+=(len>>1)*la[x];
	la[x]=0;
}
void modify(int L,int R,int l,int r,int x,int k)
{
	if(L<=l&&r<=R)
	{
		la[x]+=k;
		t[x]+=(r-l+1)*k;
		return;
	}
	push_down(r-l+1,x);
	int mid=(l+r)>>1;
	if(L<=mid) modify(L,R,l,mid,x<<1,k);
	if(mid<R) modify(L,R,mid+1,r,x<<1|1,k);
	push_up(x);
}
int query(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return t[x];
	push_down(r-l+1,x);
	int mid=(l+r)>>1,ret=0;
	if(L<=mid) ret+=query(L,R,l,mid,x<<1);
	if(mid<R) ret+=query(L,R,mid+1,r,x<<1|1);
	return ret;
}
signed main()
{
	n=read(),m=read();
	R(i,1,n) a[i]=read();
	int opt,l,r,k,d,p;
	while(m--)
	{
		opt=read();
		if(opt==1) 
		{
			l=read(),r=read(),k=read(),d=read();
			modify(l,l,1,n,1,k);
			if(l<r) modify(l+1,r,1,n,1,d);
			if(r!=n) modify(r+1,r+1,1,n,1,-(k+(r-l)*d));
		}
		if(opt==2)
		{
			p=read();
			writeln(a[p]+query(1,p,1,n,1));
		}
	}

}
```

