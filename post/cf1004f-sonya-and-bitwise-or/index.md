
<!--more-->

![QQ图片20210329104045.png](https://i.loli.net/2021/03/29/jOkZgWiGL9upbFy.png)







先考虑只有一组查询的情况。

考虑分治，分别求出$[l,mid],[mid,r]$两个区间满足条件的区间个数，这显然可以`two pointer`扫。

然后考虑两个区间合并，即跨过中点的合法区间个数。

可以第一次枚举前者的后缀来移动后者，第二次枚举后者的前缀来枚举前者。

复杂度为$O(n\log n)$.

考虑放到线段树上，每一个节点记录前缀和后缀中与其上一个的`|`和不同的节点位置和对应`|`和，显然每一个节点上的这些东西不会超过$\log$个，所以可以直接暴力做。

```c++
int n,m,X;
int a[111111];
struct node
{
	int ans;
	int tot_l,tot_r,L,R,allo;
	pii vl[22],vr[22];
	node() {tot_l=tot_r=allo=ans=0;}
	node(int A,int B) {ans=(A<X);tot_l=tot_r=1;vl[1].fi=vr[1].fi=allo=A;vl[1].se=vr[1].se=L=R=B;}
}tr[444444];
node mer_ge(node A,node B) 
{
	node C;
	C.L=A.L,C.R=B.R;
	C.tot_l=A.tot_l,C.tot_r=B.tot_r;
	C.allo=A.allo|B.allo,C.ans=A.ans+B.ans;
	memcpy(C.vl,A.vl,sizeof(A.vl)),memcpy(C.vr,B.vr,sizeof(B.vr));
	int j=0;
	for(int i=A.tot_r;i;i--)
	{
		for(;j<B.tot_l&&(A.vr[i].fi|B.vl[j+1].fi)<X;j++);
		C.ans+=1ll*(A.vr[i].se-(i==A.tot_r?A.L-1:A.vr[i+1].se))*((j==B.tot_l?B.R+1:B.vl[j+1].se)-B.L);
	}
	for(int i=1;i<=B.tot_l;i++) if((A.allo|B.vl[i].fi)!=C.vl[C.tot_l].fi) C.vl[++C.tot_l]=mkp(A.allo|B.vl[i].fi,B.vl[i].se);
	for(int i=1;i<=A.tot_r;i++) if((B.allo|A.vr[i].fi)!=C.vr[C.tot_r].fi) C.vr[++C.tot_r]=mkp(B.allo|A.vr[i].fi,A.vr[i].se);
	return C; 
}
void build(int l,int r,int x)
{
	if(l==r) {tr[x]=node(a[l],l);return;}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	tr[x]=mer_ge(tr[x<<1],tr[x<<1|1]);
}
void modify(int pos,int l,int r,int x,int k)
{
	if(l==r) {tr[x]=node(k,l);return;}
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,x<<1,k);
	else modify(pos,mid+1,r,x<<1|1,k);
	tr[x]=mer_ge(tr[x<<1],tr[x<<1|1]);
}
void prt(node A)
{
	printf("ans:%lld aor:%lld L:%lld R:%lld tot_l:%lld tot_r:%lld\n",A.ans,A.allo,A.L,A.R,A.tot_l,A.tot_r);
	printf("vl:\n");
	printf("fi:");R(j,0,15) printf("%lld ",A.vl[j].fi);puts("");
	printf("se:");R(j,0,15) printf("%lld ",A.vl[j].se);puts("");
	printf("vr:\n");
	printf("fi:");R(j,0,15) printf("%lld ",A.vr[j].fi);puts("");
	printf("se:");R(j,0,15) printf("%lld ",A.vr[j].se);puts("");
}
node query(int L,int R,int l,int r,int x)
{
	if(L==l&&r==R) return tr[x];
	int mid=(l+r)>>1;
	if(R<=mid) return query(L,R,l,mid,x<<1);
	if(L>mid) return query(L,R,mid+1,r,x<<1|1);
	//prt(query(x,mid,l,mid,x<<1)),prt(query(mid+1,R,mid+1,r,x<<1|1));
	return mer_ge(query(L,mid,l,mid,x<<1),query(mid+1,R,mid+1,r,x<<1|1));
}
void print() 
{
	puts("");
	puts("-----------up----------");
	R(i,1,16) prt(tr[i]);
	puts("----------down---------");
	puts("");
}
signed main()
{
	n=read(),m=read(),X=read();
	R(i,1,n) a[i]=read();
	build(1,n,1);
	int opt,l,r,p,v;
	while(m--)
	{	
	//	print();
		opt=read();
		if(opt==1)
		{
			p=read(),v=read();
			modify(p,1,n,1,v);
		}
		if(opt==2)
		{
			l=read(),r=read();
			int len=r-l+1;
			//printf("l:%lld q:%lld\n",1ll*(len)*(len+1)/2,query(l,r,1,n,1).ans);
			writeln((1ll*len*(len+1)/2-query(l,r,1,n,1).ans));
		}
	}		
}	
/*
10 10 240
14 42 115 6 216 76 11 139 222 192
2 3 3
1 10 204
1 10 170
1 6 14
1 2 33
1 4 229
2 1 7
2 2 6
2 1 5
2 4 5

0
15
8
7
1
*/
```

