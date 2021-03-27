
<!--more-->

分裂：

仿照FHQ Treap的套路。

设我们现在要讲以$x$为根的树分裂成以$x,y$为根的两棵树。

以第$k$小为$x$，之后在$y$。

首先看$x$的左子树的值$v$,如果$v<k$，那么左侧仍然属于$x$，递归右侧即可，注意$k$变成$k-v$。

如果$v=k$，那么左边归$x$，右边给$y$。

如果$v>k$，那么右边给$y$，递归左边。

$x$的新权值为$k$，$y$的权值为$val[x]-k$。

```c++
const int N=222222;
int n,m;
int Rt[222222],a[222222],tot_tr=1;
int ljt[N<<5],t_p;
int Ls[N<<5],Rs[N<<5];
ll val[N<<5],tot_seg;
inline int get_NEW() {return t_p?ljt[t_p--]:++tot_seg;}
inline void DEL_poi(int x) {Ls[x]=Rs[x]=val[x]=0;ljt[++t_p]=x;}
inline void push_up(int x) {val[x]=val[Ls[x]]+val[Rs[x]];}
int bui_ld(int l,int r,int x)
{
	if(!x) x=++tot_seg;
	if(l==r) 
	{
		val[x]=a[l];
		return x;
	}
	int mid=(l+r)>>1;
	Ls[x]=bui_ld(l,mid,Ls[x]);
	Rs[x]=bui_ld(mid+1,r,Rs[x]);
	push_up(x);
	return x;
}
int spi_lt(int x,int y,int k)
{
	if(!x) return 0;
	y=get_NEW();
	int v=val[Ls[x]];
	//printf("%lld %lld %lld\n",v,k,y);
	if(k>v){Rs[y]=spi_lt(Rs[x],Rs[y],k-v);}
	else if(k==v) {Swap(Rs[x],Rs[y]);}
	else
	{
		Swap(Rs[x],Rs[y]);
		Ls[y]=spi_lt(Ls[x],Ls[y],k);
	}
	val[y]=val[x]-k;
	val[x]=k;
	return y;
}
int mer_ge(int l,int r,int x,int y)
{
	if(!x||!y) return x^y;
	if(l==r)
	{
		val[x]+=val[y];
		return x;
	}
	int mid=(l+r)>>1;
	Ls[x]=mer_ge(l,mid,Ls[x],Ls[y]);
	Rs[x]=mer_ge(mid+1,r,Rs[x],Rs[y]);
	push_up(x);
	//DEL_poi(y);
	return x;
}
ll find_kth(int k,int l,int r,int x)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(val[Ls[x]]>=k) return find_kth(k,l,mid,Ls[x]);
	else return find_kth(k-val[Ls[x]],mid+1,r,Rs[x]);
}
ll query_tot(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return val[x];
	int mid=(l+r)>>1,ret=0;
	if(L<=mid) ret+=query_tot(L,R,l,mid,Ls[x]);
	if(mid<R) ret+=query_tot(L,R,mid+1,r,Rs[x]);
	return ret;
}
int modify(int pos,int l,int r,int x,int k)
{
	if(!x) x=get_NEW();
	if(l==r) {val[x]+=k;return x;}
	int mid=(l+r)>>1;
	if(pos<=mid) Ls[x]=modify(pos,l,mid,Ls[x],k);
	else Rs[x]=modify(pos,mid+1,r,Rs[x],k);
	push_up(x);
	return x;
}

void print()
{
	puts("");
	puts("---------------open---------------");
	R(i,1,10) printf("i:%lld Rt:%lld Ls:%lld Rs:%lld val:%lld\n",i,Rt[i],Ls[i],Rs[i],val[i]);
	puts("---------------colse--------------");
	puts("");
}

signed main()
{
	n=read(),m=read();
	R(i,1,n) a[i]=read();//Rt[1]=modify(i,1,n,Rt[1],a[i]);
	Rt[1]=bui_ld(1,n,Rt[1]);
	//print();

	int opt,p,x,y,t,q,k;
	ll tot1,tot2;
	int tmp;
	while(m--)
	{
		print();
		opt=read();
		if(!opt)
		{
			p=read(),x=read(),y=read(),tmp=0;
			tot1=query_tot(1,y,1,n,1),tot2=query_tot(x,y,1,n,1);
			++tot_tr;
			//assert(0);
			//printf("%lld %lld\n",tot1,tot2);			
			//printf("ttr:%lld\n",tot_tr);
			//assert(0);
			//print();
			Rt[tot_tr]=spi_lt(Rt[p],Rt[tot_tr],tot1-tot2);	
			//print();
			//test;
			tmp=spi_lt(Rt[tot_tr],tmp,tot2);
			//printf("tmp:%lld\n",tmp);
			//print();
			//printf("Rt[p]:%lld\n",Rt[p]);
			Rt[p]=mer_ge(1,n,Rt[p],tmp);
			//print();
		}
		if(opt==1)
		{
			p=read(),t=read();
			Rt[p]=mer_ge(1,n,Rt[p],Rt[t]);
		}
		if(opt==2)
		{
			p=read(),x=read(),q=read();
			modify(q,1,n,Rt[p],x);
			//if(x==140&&q==76) print();
		}
		if(opt==3)
		{
			p=read(),x=read(),y=read();

			writeln(query_tot(x,y,1,n,Rt[p]));
		}
		if(opt==4)
		{
			p=read(),k=read();
			//printf("%lld %lld\n",val[Rt[p]],k);
			printf("%lld\n",val[Rt[p]]<k?-1:find_kth(k,1,n,Rt[p]));

		}
	}
	return 0;	
}
```

