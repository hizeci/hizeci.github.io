
<!--more-->

**求最小总距离**：

因为每个村民都需要搬到一个新的地方，考虑从叶子上开始移动。

如果当前叶子上的村民还没有移动过，就将其与他的邻居交换上，答案+2并将其从树上删除（打标记即可）。如果最后还剩下一个村民，随便找他旁边的一个邻居交换即可。

**求最大总距离**：

首先考虑每条边两个方向上有多少村民可以穿过这条边。

考虑一条边$(u,v)$，则能通过的最大人数为$\min(subtreeSize(u),subtreeSize(v))$

而理论上的最大值即对于每条边计算最大人数之和。

考虑找出树的重心，只需要排列邻居子树中的所有节点的重心本身就不会再有节点位于以前的子树中了。（具体就是将每个节点向dfs序比自己大n/2的节点移动。）因为此时因为没有一个子树大于其他子树的总和，并保证了最大数量的村民将通过每条边。

```c++
ll nebs[N];
int deg[N];
int n;
int siz[N],place[N];
int lef[N],tot_lef;
int hson[N];
namespace mindis
{
	int ans=0;
	int mian()
	{
		R(i,0,n-1)
		{
			int v=lef[i];					
			if(place[v]==v) 
			{			
				ans+=2;
				int u=nebs[v];
				if(u>0) 
				{
					place[v]=place[u];
					place[u]=v;
				}
				else
				{
					int j=i,z;
					do
					{
						j--;
						z=lef[j];
					}while(j>0&&nebs[z]^v);
					place[v]=place[z];
					place[z]=v;
				}
			} 
		}
		return ans;
	}
	inline void print() {R(i,1,n)writesp(place[i]);puts("");}
}
namespace maxdis
{
	int ans=0;
	int groupSiz[N],group[N],place2[N],cnt[N],ord[N];
	int mian() 
	{
   		R(i,1,n) ans+=2*min(siz[i],n-siz[i]);
		int u=1,uu=1;
		//R(i,1,n) printf("hson:%d\n",hson[i]);
		do
		{
			u=uu;
			if(siz[u]<(n+1)/2) uu=nebs[u];
			else if(siz[u]>n/2&&hson[u]&&siz[hson[u]]>n/2) uu=hson[u]; 
			//printf("u:%d %d\n",u,uu);
		}while(u^uu);
		//printf("u:%d uu:%d\n",u,uu);
		int nextGroup=1;
		L(i,0,n-1) 
		{
			int v=lef[i];//printf("v:%d\n",v);
			if((v==u)||(nebs[v]==u)) group[v]=++nextGroup;
			else if(nebs[v]>0) group[v]=group[nebs[v]];
			else group[v]=1;
			groupSiz[group[v]]++;
		}	
		//R(i,0,n) printf("g:%d\n",group[i]);
		R(i,1,nextGroup) groupSiz[i]+=groupSiz[i-1]/*,printf("f:%d\n",groupSiz[i])*/;
		R(i,1,n) ord[groupSiz[group[i]-1]+cnt[group[i]]]=i,cnt[group[i]]++;
		R(i,0,n-1) place2[ord[i]]=ord[(i+n/2)%n];
		return ans;
	}
	inline void print() {R(i,1,n)writesp(place2[i]);puts("");}
}
signed main()
{
	n=read();
	int u,v;
	R(i,2,n) 
	{
		u=read(),v=read();
		deg[u]++,deg[v]++;
		nebs[u]+=v,nebs[v]+=u;
	}	
	R(i,1,n) 
	{
		siz[i]=1;place[i]=i;
		if(deg[i]==1) lef[tot_lef++]=i;
	}
	siz[0]=-inf;
	for(int i=0;i<tot_lef;i++) 
	{
		int v=lef[i];
		int u=nebs[v];
		if(u>0) 
		{
			hson[u]=(siz[hson[u]]<siz[v])?v:hson[u];
			siz[u]+=siz[v];
			deg[u]--;
			nebs[u]-=v;
			if(deg[u]==1) lef[tot_lef++]=u;
		}
	}
	writesp(mindis::mian());
	writeln(maxdis::mian());
	mindis::print(),maxdis::print();
}
```

