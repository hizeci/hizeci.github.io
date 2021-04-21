
<!--more-->

由于直接对S的所有子集求和并不是很好弄，所以考虑计算在“解码”时成为S的子集的数量。

令$f(S)$表示字符串为S时的答案。

考虑如何去计算$f$。编码字符串的第一个字符有两种选择。

- 是数字$0$或者$1$。显然这个字符与字符串其他部分的编码并没有关系，所以有$f(S_{2\ldots |S|})$种方法编码其余部分。如果$S_1=1$，则答案为这个值$\times 2$，因为编码字符串的第一个字符可以是$0$或$1$。同样，如果$S_1=0$，那么答案为$\times 1$，因为编码字符串的第一个字符串只能是$0$。
- 是一个左括号（。在此情况下，此编码字符串的开头是$(P\times K)$，其中$P$是某个字符串$A$的编码。遍历正整数$K$和$|A|$满足$K\cdot |A|\leq |S|$，同时需要$AA\ldots A$（$K$个$A$拼起来）是$S_{1\ldots K|A| }$的子集。这等价于$A$同时是$S_{1\ldots|A|},S_{|A|+1\ldots2|A|},\cdots,S_{(K-1)|A|+1\ldots K|A|}$的子串。这等价于$A$是所有这些字符串的$\wedge$。并且还有$f(S_{K|A|+1\ldots|S|})$种方法编码其余部分。

因此$f(S)$的递推式子不难推出
$$
f(S)=(1+S_1)f(S_{2\ldots |S|})+\sum_{|A|=1}^{|S|} \sum_{K=1}^{\lfloor\frac{|S|}{|A|}\rfloor} f(g(S,K,|A|))\times f(S_{K|A|+1\ldots |S|})
$$
其中$g(S,K,|A|)$表示$S_{1\ldots |A|} \wedge S_{|A|+1\ldots 2|A}  \wedge \ldots  \wedge S_{(K-1)|A|+1\ldots K|A|}$。

通过记忆化来计算$f(S)$。$f$将会调用多少个不同的参数？显然上界看上去为$O(2^{|S|})$，但事实上该解决方案十分快速。

具体证明可以查看官方题解。

下面附上感性理解：

如果字符串长度最多为12，那么不同的字符串个数为$2^{13}-2$种。可以证明对于长度$> 12$，最多有$O(n^2)$种方法调用$f$。事实上，状态数最多为$O(N^3+2^{N/8})$其中$N^3$前面有一个小常数。（其他题解有讲大概怎么推的）

```c++
#define lll __int128
map<pair<lll,int>,int>f;
char s[111];
int n;
int dfs(pair<lll,int> now)
{
	if(!now.se) return 1;
	if(f.count(now)) return f[now];
	int ans=dfs(mkp(now.fi>>1,now.se-1))*((now.fi&1)+1)%mod;
	R(A,1,now.se>>1) 
	{
		lll S=((lll)1<<A)-1,tmp=now.fi,sum=tmp&S;
		tmp>>=A;sum&=tmp&S;tmp>>=A;
		for(int K=now.se-A-A;K>=0;K-=A,sum&=tmp&S,tmp>>=A) 
			ans=(ans+1ll*dfs(mkp(sum,A))*dfs(mkp(tmp,K)))%mod;
	}
	return f[now]=ans;
}
signed main()
{
	scanf("%s",s);
	n=strlen(s);
	lll S=0;
	R(i,0,n-1) S=S<<1|(s[i]-'0');
	writeln(dfs(mkp(S,n)));
}
```

