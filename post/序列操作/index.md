
<!--more-->

先考虑没有一二两种操作的情况，查询区间中选$c$个数乘积所有方案的总和。由于$c$很小，所以考虑每次直接暴力算出总和。

之后考虑如何合并这些区间，仍然是暴力合并，令$x$为现在的区间，$l,r$分别为左右两个区间，合并时即$ans[x][i]=\sum\limits_{j=0}^i ans[l][j]\times ans[r][i-j]$。即大区间选$i$个数，左边选$0$个，右边选$i-0$个；左边选$1$个，右边选$i-1$个$\cdots$

之后考虑加上区间加操作，设原区间大小为$p$。

原来区间内的数为$a_1,a_2,\cdots,a_p$，加上$x$后为$a_1+x,a_2+x,\cdots,a_p+x$。

考虑对于答案的改变为多少，任取一组如$a_1a_2a_3a_4$可观察到$a_1a_2a_3a_4+(a_1a_2+a_2a_3+a_3a_4+a_2a_4)x+(a_1a_2a_3+a_2a_3a_4)x^2+(a_1+a_2+a_3+a_4)x^3+x^4$

这个式子对于答案的改变为$\sum\limits_{j=1}^i x^{i-j} \times$从$i$个数中选出$j$个数的乘积之和。

这个式子并不容易处理，但是可以去考虑计算在第$i$项答案时会出现几次。

考虑组合意义：从$p$个数中选出$i$个数，其中有$j$个数已经被钦定选了。

即已经选了$j$个数，在$p-i$个数中选$i-j$个数，即$\binom {p-j} {i-j}$。

于是可以推出式子$ans[][i]=\sum\limits_{j=0}^ix^{i-j}\times ans[][j]\times \binom{p-j}{i-j}$。

之后再考虑区间取反，打标记即可。只有奇数个 数 相乘的贡献会变成负数。

```c++
int n,q;
int a[55555];
int C[55555][25];
int la[222222],rev[222222];
ll mem[22];
char opt[22];
struct node{node(){f[0]=1;}int f[25];}t[222222];
int ans[25];
void print(int x)
{
	puts("");
	puts("-------------qwq----------");
	printf("x:%d\nrev:%d laz:%d\n",x,!rev[x]?1:-1,la[x]);
	R(i,0,10) printf("f:%d ",t[x].f[i]);
	puts("");
	puts("-------------qaq----------");
	puts("");
}
void push_up(int len,int x)
{
	ckmin(len,20ll);
	R(i,1,len) 
	{
		t[x].f[i]=0;
		R(k,0,i) t[x].f[i]=(t[x].f[i]+(1ll*t[x<<1].f[k]*t[x<<1|1].f[i-k]%mod))%mod;
	}
}
void push_add(int len,int x,int k)
{
	int qq=len;
	//if(k==96) printf("n:%d\n",qq);
	ckmin(len,20ll);
	la[x]=(la[x]+k)%mod+mod,la[x]%=mod;
	//L(i,1,len) R(j,1,i) t[x].f[i]=(t[x].f[i]+1ll*(1ll*(1ll*C[qq-(i-j)][j]*t[x].f[i-j]%mod)*mem[j]%mod))%mod;
	L(i,1,len) for(int j=1,now=k;j<=i;++j,now=1ll*now*k%mod) t[x].f[i]=(t[x].f[i]+((1ll*C[qq-(i-j)][j]*t[x].f[i-j]%mod)*now%mod))%mod;
}
void push_rev(int len,int x) 
{
	ckmin(len,20ll);
	la[x]=((mod-la[x])%mod+mod)%mod;
	for(int i=1;i<=len;i+=2) t[x].f[i]=((mod-t[x].f[i])%mod+mod)%mod;
	rev[x]^=1;
}
void push_down(int len,int x)
{
	int q=len>>1,p=len-q;
	if(rev[x]) 
	{
		//puts("forever");
		push_rev(p,x<<1),push_rev(q,x<<1|1);
		rev[x]^=1;
	}
	if(la[x])
	{
		push_add(p,x<<1,la[x]),push_add(q,x<<1|1,la[x]);
		la[x]=0;
	}
}
void build(int l,int r,int x)
{
	t[x].f[0]=1;
	if(l==r) {t[x].f[1]=a[l];return;}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up(r-l+1,x);
}
void modify_add(int L,int R,int l,int r,int x,int k)
{
	if(L<=l&&r<=R) 
	{
		//if(k==96){ 	printf("x:%d\n",x);R(i,0,10) printf("1f:%d ",t[x].f[i]);puts("");}
		push_add(r-l+1,x,k);	
		//if(k==96){ printf("x:%d\n",x);R(i,0,10) printf("2f:%d ",t[x].f[i]);puts("");}
		return;
	}
	//if(k==96){ printf("x:%d\n",x);R(i,0,10) printf("3f:%d ",t[x].f[i]);puts("");}
	push_down(r-l+1,x);
	//if(k==96){ printf("x:%d\n",x);R(i,0,10) printf("4f:%d ",t[x].f[i]);puts("");}
	int mid=(l+r)>>1;
	if(L<=mid) modify_add(L,R,l,mid,x<<1,k);
	if(mid<R) modify_add(L,R,mid+1,r,x<<1|1,k);
	//if(k==96){ printf("x:%d\n",x);R(i,0,10) printf("5f:%d ",t[x].f[i]);puts("");}
	push_up(r-l+1,x);
	//if(k==96){ printf("x:%d\n",x);R(i,0,10) printf("6f:%d ",t[x].f[i]);puts("");}
}
void modify_rev(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R)
	{
		push_rev(r-l+1,x);
		return;
	}
	push_down(r-l+1,x);
	int mid=(l+r)>>1;
	if(L<=mid) modify_rev(L,R,l,mid,x<<1);
	if(mid<R) modify_rev(L,R,mid+1,r,x<<1|1);
	push_up(r-l+1,x);
}
node query(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return t[x];
	push_down(r-l+1,x);
	int mid=(l+r)>>1,ok1=0,ok2=0;
	node ans,a,b;
	if(L<=mid) ok1=1,a=query(L,R,l,mid,x<<1);
	if(mid<R) ok2=1,b=query(L,R,mid+1,r,x<<1|1);
	int len=min(20ll,r-l+1);
	if(ok1&&ok2) 
	{
		R(i,1,len)
		{
			ans.f[i]=0;
			R(k,0,i) ans.f[i]=(ans.f[i]+1ll*a.f[k]*b.f[i-k]%mod)%mod;
		}
	}
	else if(!ok2) ans=a;
	else if(!ok1) ans=b;
	return ans;
}

signed main()
{
	//freopen("9.in","r",stdin);
	//freopen("my.out","w",stdout);
	n=read(),q=read();
	R(i,1,n) a[i]=(read()%mod+mod)%mod;
	C[0][0]=C[1][0]=C[1][1]=1;
	R(i,2,n){C[i][0]=1;R(j,1,min(i,20ll))C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;}	
	build(1,n,1);
	//R(i,1,10) print(i);
	int a,b,c;
	while(q--)
	{
		scanf("%s",opt);
		a=read(),b=read();
		if(opt[0]=='I') {c=(read()%mod+mod)%mod;mem[0]=1;mem[1]=(c%mod+mod)%mod;R(i,2,21)mem[i]=mem[i-1]*c%mod;modify_add(a,b,1,n,1,c);}
		if(opt[0]=='R') modify_rev(a,b,1,n,1);
		if(opt[0]=='Q') c=read(),writeln(query(a,b,1,n,1).f[c]);
		//R(i,80,90) print(i);
	}	
}
```

