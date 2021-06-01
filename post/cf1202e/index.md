
<!--more-->

由于直接计算每一对$s_i+s_j$的出现次数并不好做，考虑枚举它们分割的位置（$s_i$结束$s_j$开始处）来计算总数。

因此任何在分割处结束的$s_i$都可以与从这里开始的$s_j$配对。

所以说我们只需要对每一个后缀计算从这里开始的字符串$s_i$的数量，以及对每一个前缀计算从这里结束的字符串$s_i$的数量。计算前缀可以通过反转$t$和所有的$s_i$转化为计算后缀。

所以我们需要对于每个位置$pos$计算从$pos$开始或结束的字符串个数。个人的做法是SAM，但官方题解有一种有趣的根号分治做法。

先确定一个阙值$MAG$。然后将字符串分为长或短两类：若$|s_i|\leq MAG$就当做短的，否则当做长的。显然不会有超过$\frac{\sum|s_i|}{MAG}$个长字符串。对于这些长字符串可以用Z函数或者前缀函数找到它的所有出现。这部分的时间复杂度为$O(\frac{\sum |s_i|}{MAG}+\sum |s_i|)$。

然后对于短的字符串考虑直接建一棵Trie。这棵Trie将会有$O\left(\sum |s_i| \right)$个点，但是最大深度为$MAG$。所以可以对于每个$pos$向下移动遍历Trie，同时计算出现次数，这只使用了$s[pos\ldots (pos+MAG)]$这部分子串。所以这部分的时间复杂度为$O(|t|\cdot MAG)$。

所以当$MAG=\sqrt{\sum |s_i|}$时，总时间复杂度为$O\left(\sum |s_i|+|t|\sqrt{\sum |s_i|} \right)$。这没有使用任何字符串数据结构。



然后讲一下线性时间复杂度的SAM做法。

对于$t$和$\operatorname{reverse}(t)$建出SAM，然后对于每个$s_i$和$\operatorname{reverse}(s_i)$在SAM上跑一遍，并对于它的结束位置的整个子树打个标记。最后直接计算每个位置存在的字符串数量就可以得到答案。

```cpp
string str;
int t[222222];

int n,lent;
struct SAM
{
    struct node
    {
        int len,nxt,son[26];
    }a[444444];
    int ans[444444],edp[444444],cnt[444444];
    int lst,tn;
    vector<int>e[444444];
    inline void init_SAM()
    {
        tn=lst=1; 
    }
    void extend_SAM(int c)
    {
        int cur=++tn,p=lst;
        a[cur].len=a[p].len+1;edp[cur]=a[p].len;
        for(;p&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
        if(!p) a[cur].nxt=1;
        else
        {
            int v=a[p].son[c];
            if(a[v].len==a[p].len+1) a[cur].nxt=v;
            else
            {
                int x=++tn;a[x]=a[v];
                a[x].len=a[p].len+1;edp[x]=-1;
                for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
                a[cur].nxt=a[v].nxt=x;
            }
        } 
        lst=cur;
    }
    void solve(const string &s)
    {
        int p=1,len=(int)s.size(),x;
        R(i,0,len-1) 
        {
            x=s[i]-'a';
            if(!a[p].son[x]) return;
            p=a[p].son[x];
        }
        ++cnt[p];
    }
    void dfs(int u)
    {
        
        if(~edp[u]) ans[edp[u]]=cnt[u];
        for(int v:e[u]) cnt[v]+=cnt[u],dfs(v);
    }
    void mian()
    {
        R(i,2,tn) e[a[i].nxt].pb(i);
        dfs(1);
    }
}SAM1,SAM2;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SAM1.init_SAM(),SAM2.init_SAM();
    cin>>str>>n;lent=str.size();
    R(i,0,lent-1) t[i]=str[i]-'a';
    R(i,0,lent-1) SAM1.extend_SAM(t[i]);
    L(i,0,lent-1) SAM2.extend_SAM(t[i]);    
    R(i,1,n)
    {
        cin>>str;
        SAM1.solve(str);
        reverse(str.begin(),str.end());
        SAM2.solve(str);
    }
    SAM1.mian();
    SAM2.mian();
    ll ans=0;
    R(i,0,lent-2) ans+=1ll*SAM1.ans[i]*SAM2.ans[lent-i-2];
    cout<<ans;
}
```

