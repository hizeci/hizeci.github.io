
<!--more-->

就线段树维护区间的连通性。

其他的也想不到什么，就写和调感觉很*。



```c++
int n,m,q;
int a[100010][7];
int f[44],tag[44],v[44];
struct node
{
	int l,r;
	int fff[14],vis[14],tot_O;
	inline int find_fff(int x){return (fff[x]==x)?x:fff[x]=find_fff(fff[x]);}
	inline void uni_fff(int x,int y){x=find_fff(x),y=find_fff(y);if(x!=y){fff[y]=x;if(vis[x]&&vis[y])tot_O--;else if(vis[y])vis[x]=1;}}
	void upd() 
	{
		int pos=l;
		tot_O=0;
		R(i,1,m<<1) fff[i]=i,vis[i]=0;
		R(i,1,m) if(a[pos][i]==4) vis[i]=1,tot_O++;
		R(i,2,m) if(a[pos][i]>1&&a[pos][i-1]>1) uni_fff(i,i-1);
		R(i,1,m-1) if(a[pos][i]>1&&a[pos][i+1]>1) uni_fff(i,i+1);
		R(i,1,m) fff[i+m]=fff[i];
	}
}t[444444];
void print(const node &t) 
{
	puts("");
	puts("----------open------------");
	printf("l:%lld r:%lld sum:%lld\n",t.l,t.r,t.tot_O);
	R(i,1,12) printf("fff:%lld vis:%lld\n",t.fff[i],t.vis[i]);
	puts("----------down------------");
	puts("");
}
inline int find_f(int x){return f[x]==x?x:f[x]=find_f(f[x]);}
inline int ga_ch(char x) {return (x=='.')?0:(x=='|')?1:(x=='-')?2:(x=='+')?3:4;}

void push_up(node &x,const node &L,const node &R)
{
	memset(x.vis,0,sizeof(x.vis));
	x.l=L.l,x.r=R.r;
	x.tot_O=L.tot_O+R.tot_O;
	R(i,1,m<<1) f[i]=L.fff[i],tag[i]=L.vis[i];
	R(i,1,m<<1) f[i+(m<<1)]=R.fff[i]+(m<<1),tag[i+(m<<1)]=R.vis[i];
	//R(i,1,m<<2) printf("f:%lld tag:%lld\n",f[i],tag[i]);
	int p=L.r,u,xx,yy;
	R(i,1,m) if(a[p][i]!=0&&a[p][i]!=2&&a[p+1][i]!=0&&a[p+1][i]!=2)//如果在中间连接的位置可以连接
	{
		xx=find_f(i+m),yy=find_f(i+(m<<1));
		if(xx!=yy) //且属于不同的连通块
		{
			f[xx]=yy;
			if(tag[xx]&&tag[yy]) x.tot_O--;//如果两连通块内都有O,那么总个数就要减一
			else if(tag[xx]) tag[yy]=1;
		}
	}
	//将并查集内的东西放到节点上
	memset(v,0,sizeof(v));
	R(i,1,m) 
	{
		u=find_f(i);
		//判断前是否出现过这个连通块
		if(!v[u]) v[u]=i,x.vis[i]=tag[u];
		u=find_f(i+m*3);
		if(!v[u]) v[u]=i+m,x.vis[i+m]=tag[u];
	}
	R(i,1,m) x.fff[i]=v[find_f(i)],x.fff[i+m]=v[find_f(i+m*3)];
}
void build(int l,int r,int x)
{
	t[x].l=l,t[x].r=r;
	if(l==r){t[x].upd();return;}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	//printf("x:%lld\n",x);
	//print(t[x]);
	push_up(t[x],t[x<<1],t[x<<1|1]);
	//printf("x:%lld\n",x);
	//print(t[x]);
}
void modify(int pos,int l,int r,int x)
{
	if(l==r) return (void)t[x].upd();
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,x<<1);
	else modify(pos,mid+1,r,x<<1|1);
	push_up(t[x],t[x<<1],t[x<<1|1]);
}
node query(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return t[x];
	int mid=(l+r)>>1,ok0=0,ok1=0;
	node ans,a,b;
	if(L<=mid) ok0=1,a=query(L,R,l,mid,x<<1);
	if(mid<R) ok1=1,b=query(L,R,mid+1,r,x<<1|1);
	if(ok1&&ok0) push_up(ans,a,b);
	else if(!ok1) ans=a;
	else if(!ok0) ans=b;
	return ans;
}
signed main()
{
	int x,y;
	char s[10];
	n=read(),m=read();
	R(i,1,n) {scanf("%s",s+1);R(j,1,m)a[i][j]=ga_ch(s[j]);}
	//R(i,1,n) {R(j,1,m) printf("%lld",a[i][j]);puts("");}
	build(1,n,1);
	//print(t[1]);
	for(q=read();q--;)
	{
		scanf("%s",s+1);
		if(s[1]=='Q')
		{
			x=read(),y=read();
			writeln(query(x,y,1,n,1).tot_O);
		}
		if(s[1]=='C')
		{
			x=read(),y=read(),scanf("%s",s+1);
			a[x][y]=ga_ch(s[1]);
			modify(x,1,n,1);
		}
	}
}
```

