
题意：

给定两个字符串，求出在两个字符串中各取出一个子串使得这两个子串相同的方案数。两个方案不同当且仅当这两个子串有一个位置不同。

<!--more-->

因为字符串所有的子串就是字符串的所有后缀的$\texttt{LCP}$的长度的和。

考虑如何很快的求出$\texttt A$和$\texttt B$的某个后缀的最长公共前缀，显然可以使用$\texttt{SA}$。

将两个字符串连接起来，中间位置随便放个分隔符隔开。求出$\texttt{height}$数组。

每一堆中不同颜色之间的$\texttt{LCP}$的长度就相当于先对于一种颜色算出在它之前出现的另外一种颜色和它的$\texttt{LCP}$，再按照另外一种颜色算一遍。

由于$lcp(i,j)=\min\left\{x|i+1\leq x \leq j,height[x]=lcp(i,j) \right\}$

也就是说排序后，一个后缀越往后的$\texttt{LCP}$越小。

所以，我们可以使用一个单调栈维护这个最小值。

我们用单调栈维护这个$\texttt{LCP}$长度，栈中分别维护$\texttt{height}$值的大小和有多少个贡献和它相同的元素。

这里只考虑$\texttt A$串插入$\texttt B$串查询

每遇到一个串，就要判断是在$\texttt A$还是在$\texttt B$，如果在$\texttt A$就直接加上前面答案之和

（每次将当前后缀$\texttt i$加入栈中，如果$sa_{i-1}$的颜色并不是要算贡献的颜色，那么它就可以对当前颜色造成贡献，$sum+=height_i$。）

然后是弹出的时候，并不是真正意义上的弹，而是与之前的东西合并，因为现在的栈顶最大$\texttt{height}$已经取不到了，所以可将它与栈中的第二个元素合并。

（这是我们将现在的$height_i$如入栈，考虑如果$height_i\leq height_{top}$，那么栈顶对答案的贡献就会变成$height_i$，所以可以将$height_i$和$height_{top}$合并，对答案的贡献是$height_i$，贡献个数是$num_i+num_{top}$。）

合并完之后如果$sa_i$的颜色是我们要算贡献的颜色就加上所有栈内的贡献。

时间复杂度为求$\texttt {SA}$的时间复杂度。

```c++
const int N=8e5+10;
char str[N];
int l1,ans;
int n,s[N],sa[N],rk[N],tp[N],pos[N],c[N],c1[N];
#define del(x) sa[c[s[x]]--]=x
#define add(x) sa[c[s[x]]++]=x
void SA_sort(int *S,int n,int m,int *s,int *tp,int tn)
{
	clr(sa,n+2),clr(c1,m+2);
	R(i,1,n) c1[s[i]]++;
	R(i,2,m) c1[i]+=c1[i-1];
	cpy(c+1,c1+1,m+2);
	L(i,1,tn) del(S[i]);
	R(i,1,m+1) c[i]=c1[i-1]+1;
	R(i,1,n) if(sa[i]>1&&tp[sa[i]-1]) add(sa[i]-1);
	cpy(c+1,c1+1,m+2);
	L(i,1,n) if(sa[i]>1&&!tp[sa[i]-1]) del(sa[i]-1);
}
void SA_IS(int n,int m,int *s,int *tp,int *pos)
{
	int tot=0,cnt=0;int *S=s+n;
	tp[n]=0;
	L(i,1,n-1) tp[i]=(s[i]!=s[i+1])?s[i]>s[i+1]:tp[i+1];
	rk[1]=0;
	R(i,2,n) if(tp[i-1]&&!tp[i]) pos[++tot]=i,rk[i]=tot;else rk[i]=0;
	SA_sort(pos,n,m,s,tp,tot);
	int u=0,p=0;
	R(i,1,n) if(rk[sa[i]])
	{
		u=rk[sa[i]];
		if(cnt<=1||pos[u+1]-pos[u]!=pos[p+1]-pos[p]) ++cnt;
		else
		{
			R(j,0,pos[u+1]-pos[u]) 
			if(s[pos[u]+j]!=s[pos[p]+j]||tp[pos[u]+j]!=tp[pos[p]+j]) {++cnt;break;}
		}
		S[u]=cnt;
		p=u;
	}
	if(tot!=cnt) SA_IS(tot,cnt,S,tp+n,pos+n);
	else R(i,1,tot) sa[S[i]]=i;
	R(i,1,tot) S[i]=pos[sa[i]];
	SA_sort(S,n,m,s,tp,tot);
}
int ht[N];
void get_ht(int n)
{
	R(i,1,n) rk[sa[i]=sa[i+1]]=i;
	int k=0;
	R(i,1,n)
	{
		k=(!k)?0:k-1;
		while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;
		ht[rk[i]]=k;
	}
}
pii stk[N];
int top,g[N];
signed main()
{
	scanf("%s",str+1);l1=strlen(str+1);str[l1+1]='z'+1;
	scanf("%s",str+l1+2);
	n=strlen(str+1);
	R(i,1,n) s[i]=str[i]-'a'+2;s[++n]=1;
	SA_IS(n--,28,s,tp,pos);
	get_ht(n);
	//R(i,1,n) printf("i:%lld ht:%lld sa:%lld rk:%lld\n",i,ht[i],sa[i],rk[i]);
	stk[0]=mkp(1,0);
	R(i,1,n) g[i]=g[i-1]+(sa[i]<=l1);
	R(i,1,n)
	{
		while(top&&ht[stk[top].fi]>ht[i]) top--;
		++top;stk[top]=mkp(i,(g[i-1]-g[stk[top-1].fi-1])*ht[i]+stk[top-1].se);
		if(sa[i]>l1+1) ans+=stk[top].se;
	}
	top=0;
	R(i,1,n) g[i]=g[i-1]+(sa[i]>l1+1);
	R(i,1,n)
	{
		while(top&&ht[stk[top].fi]>ht[i]) top--;
		++top;stk[top]=mkp(i,(g[i-1]-g[stk[top-1].fi-1])*ht[i]+stk[top-1].se);
		if(sa[i]<=l1) ans+=stk[top].se;
	} 
	writeln(ans);
}
```

