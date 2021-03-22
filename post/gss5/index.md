
<!--more-->

分三种情况讨论。

1. $(l2<r1)$ $rsm[l1,l2)+sum[l2,r1]+lsm(r1,r2]$
2. ($l2=r1$) $rsm[l1,l2)+lsm[r1,r2]$
3. ($l2>r1$) 这里又要分四种情况 
   1.  答案的区间两个端点在$[l2,r1]$  $mxsum[l2,r1]$。
   2. 答案的区间起点在$[l1,l2]$终点在$(l2,r1]$  $rsm[l1,l2]+lsm(l2,r1]$
   3. 答案的区间起点在[$l2,r1$]终点在$(r1,r2]$  $rsm[l2,r1]+lsm(r1,r2]$
   4. 答案的区间起点在$[l1,l2]$终点在$[r1,r2]$ $rsm[l1,l2)+sum[l2,r1]+lsm(r1,r2]$。



```c++
int a[111111],n,q;
namespace segmentree
{
	struct node{int sum,lsm,rsm,mxsum;node(int S=0,int L=0,int R=0,int M=0){sum=S,lsm=L,rsm=R,mxsum=M;}}t[444444];
	void push_up(node &x,const node &L,const node &R) 
	{
		//t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
		//t[x].lsm=max(t[x<<1].lsm,t[x<<1].sum+t[x<<1|1].lsm);
		//t[x].rsm=max(t[x<<1|1].rsm,t[x<<1].rsm+t[x<<1|1].sum);
		//t[x].mxsum=max(max(t[x<<1].mxsum,t[x<<1|1].mxsum),t[x<<1].rsm+t[x<<1].lsm);
		x.sum=L.sum+R.sum;
		x.lsm=max(L.lsm,L.sum+R.lsm);
		x.rsm=max(R.rsm,L.rsm+R.sum);
		x.mxsum=max(max(L.mxsum,R.mxsum),L.rsm+R.lsm);
	}
	void build(int l,int r,int x) 
	{
		if(l==r) 
		{
			//if(a[l]==-2) printf("f:%lld\n",x);
			t[x]=node(a[l],a[l],a[l],a[l]);
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1),build(mid+1,r,x<<1|1);
		push_up(t[x],t[x<<1],t[x<<1|1]);	
	}
	node query(int L,int R,int l,int r,int x) 
	{
		//if(L<=l&&r<=R) {printf("i:%lld sum:%lld lsm:%lld rsm:%lld mxsum:%lld\n",x,t[x].sum,t[x].lsm,t[x].rsm,t[x].mxsum);}
		if(L<=l&&r<=R) return t[x];
		int mid=(l+r)>>1,ok1=0,ok2=0;
		node ret,a,b;
		if(L<=mid) ok1=1,a=query(L,R,l,mid,x<<1);
		if(mid<R) ok2=1,b=query(L,R,mid+1,r,x<<1|1);
		if(ok1+ok2==2) push_up(ret,a,b);
		else if(!ok2) ret=a;
		else if(!ok1) ret=b;
		else ret=node(-inf,-inf,-inf,-inf);
		//printf("i:%lld sum:%lld lsm:%lld rsm:%lld mxsum:%lld\n",0ll,ret.sum,ret.lsm,ret.rsm,ret.mxsum);
		return ret;
	}
	void print()
	{
		puts("");
		puts("-------------open---------------");
		R(i,1,10) printf("i:%lld sum:%lld lsm:%lld rsm:%lld mxsum:%lld\n",i,t[i].sum,t[i].lsm,t[i].rsm,t[i].mxsum);
		puts("-------------down---------------");
		puts("");
	}
}
signed main()
{
	for(int _=read();_--;)
	{
		n=read();
		R(i,1,n) a[i]=read();
		segmentree::build(1,n,1);//segmentree::print();	
		//writeln(segmentree::query(2,2,1,n,1).lsm);
		int l1,l2,r1,r2;
		for(q=read();q--;)
		{
			l1=read(),r1=read(),l2=read(),r2=read();
			//test
			//writeln(segmentree::query(l1,r1,1,n,1).rsm);
			//writeln(segmentree::query(r1,l2,1,n,1).sum);
			//writeln(segmentree::query(l2,r2,1,n,1).lsm);
			//puts("fuck");
			//writeln(a[l2]+a[r1]);
			if(r1==l2) writeln(segmentree::query(l1,r1,1,n,1).rsm+segmentree::query(l2,r2,1,n,1).lsm-a[l2]);
			else if(r1<l2) writeln(segmentree::query(l1,r1,1,n,1).rsm+segmentree::query(r1,l2,1,n,1).sum+segmentree::query(l2,r2,1,n,1).lsm-a[l2]-a[r1]);
			else
			{
				segmentree::node A=segmentree::query(l1,l2,1,n,1),B=segmentree::query(l2,r1,1,n,1),C=segmentree::query(r1,r2,1,n,1);
				//segmentree::node A=segmentree::query(l2,r1,1,n,1),B=segmentree::query(l1,l2,1,n,1),C=segmentree::query(r1,r2,1,n,1);
				int ans=B.mxsum;
				ckmax(ans,A.rsm+B.lsm-a[l2]);
				ckmax(ans,B.rsm+C.lsm-a[r1]);
				ckmax(ans,A.rsm+B.sum+C.lsm-a[l2]-a[r1]);
				writeln(ans);
			}
		}
	}
	
}
```



