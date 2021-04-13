
<!--more-->

## 原根与整数模$n$乘法群



对于一个正整数$n$，$1\sim n$有$\varphi(n)$（这里$\varphi$指欧拉函数）个与它互质的整数，形成了集合$\mathbb{Z_n^{*}}$。

如$\mathbb{Z}_{12}^*=\{1,5,7,11\}$。这就是一个群。群有一个运算叫做乘法，乘法是满足结合律的。

群有一个性质，其中两个数乘起来后的数仍然在群里面，如$5\times 7\bmod 12=11$。

以及群是有逆元的。

现在我们尝试来描述它的结构。

### 原根

原根是研究它的一个有效工具。我们考虑一个与$n$互质的整数$a$，若$a^k\bmod n$包含了$\mathbb{Z_n^*}$中的所有元素（换句话说，$a^0\sim a^{\varphi(n)-1}\bmod n$互不相同），我们称它是一个模$n$的原根。

可以证明，只有$2,4,p^k,2p^k$（这里$p$是奇素数）有原根，且若$n$有原根，那么$\mathbb{Z_n^*}$中恰好有$\varphi(\varphi(n))$个原根。

因此，原根个数非常多，寻找原根是容易的。我们只需要随机或者从小往大枚举$x$，判定$x$是否是原根。

比较快的判定是分解$\varphi(n)$，然后依次枚举$\varphi(n)$的所有不同素因子$p_k$，若$x^{\frac{\varphi(n)}{p_k}}\equiv 1\pmod n$，则$x$就是$n$的原根。

### 整数模$n$乘法群

现在，对于存在原根的整数$n$，我们就可以清晰描述$\mathbb{Z_n^*}$了：这是一个$\varphi(n)$阶循环群。

简单的说，就是取一个模$n$的原根$g$,对于$\mathbb{Z_n^*}$中的每个整数$x$，都存在唯一一个$0\sim \varphi(n)-1$间的整数$k$，使得$g^k\equiv x\pmod n$。

那么我们可以把$x$与$k$对应起来，即令$f(x)=k$。容易发现，这么对应后，原来的乘法变成了加法，求逆变为了取负，即
$$
f(x\cdot y \bmod n)=(f(x)+f(y))\bmod \varphi(n)
$$

$$
f(x^{-1}\bmod n)=(-f(x))\bmod \varphi(n)
$$

这样，对于存在原根的整数$n$，利用这个对应，我们在$\mathbb{Z_n^*}$中做的乘法运算可以完全变为简单的模$\varphi(n)$意义下的加法。对于模意义下的加法，我们已经非常详细地了解了它的性质。因此这是一个解决数论问题的利器。

一个简单的小应用是解释：为什么$n$存在原根的情况下，$1\sim n$中恰好有$\varphi(\varphi(n))$个原根

随便取一个原根$g$，那对于每一个与原根互质的整数$x$。

$x=g^{f(x)},f(g)=1$

$x^0,x^1,\dots,x^{\varphi(n)-1} \pmod n$互不相同

$0f(x),1f(x),\dots,(\varphi(n)-1)f(x) \pmod {\varphi(n)}$也都互不相同

$\gcd(f(x),\varphi(n))=1$



对于其他的整数$n$，整数模$n$乘法群的结构会更加复杂，但它仍能写成若干个循环群的直积。（在群论中是有限群的一般分解定理。）一个比较简单的理解是我们可以把每个$\mathbb{Z}_n^*$中的整数对应到一个整数向量上，每一维的值是它在那个循环群上的“坐标”。两个整数的乘法可以理解为每一维分别相加，求逆理解为每一维分别取负（当然都是在每一维不同的模数的模意义下）。

稍微举个例子，仍然是$\mathbb{Z}_{12}^*=\{1,5,7,11\}$

因为$12=3*4,\varphi(3)=2,\varphi(4)=2$，所以这是一个

$1=(0,0)$

$5=(0,1)$

$7=(1,0)$

$11=(1,1)$

$5*7=?$

$(0,1)+(1,0)=(1,1)$

$5*7=11\pmod {12}$

$7*11=?$

$(1,0)+(1,1)=(0,1)$

$7*11=5\pmod 5$

稍显考虑$n=2^k(k\ge 3)$。可以证明此时的$\mathbb{Z}_n^*$是一个$2^{k-2}$阶循环群与$2$阶群的直积，两个群的生成元（原根）分别是$5$和$-1$。

（在模$2^k(k\ge 3)$时，$ord(5)=2^{k-2}$具体证明可以查数论书下面再举一个例子。）

$\mathbb{Z}_{16}^* =\{1,3,5,7,9,11,13,15\}$

$5^0\equiv 1,5^1\equiv 5,5^2\equiv 9,5^3\equiv 13, 5^4\equiv 1\cdots \pmod {16}$

$-1\equiv 15,-5\equiv 11,-9\equiv 7,-13 \equiv 3$

然后就有

$1=(0,0)$

$5=(1,0)$

$9=(2,0)$

$13=(3,0)$

$-1=(0,1)$

$-5=(1,1)$

$-9=(2,1)$

$-13=(3,1)$

这样，我们就完全解决了$n=p^k$，$p$是素数的情况。对于更一般的整数$n$，我们发现若将$n$分解为$p_1^{e_1}\cdot p_2^{e^2}\cdot \dots p_m^{e_m}$，那么模$n$意义下的乘法在每个$p_i^{e_i}$意义下是独立的（可以利用$\text{CRT}$转化）。因此，我们容易将$\mathbb{Z}_n^*$写为$\mathbb{Z}_{p_i^{e_i}}^*$的直积。

### 阶

若$\gcd(a,n)=1$，由欧拉定理（可以认为是一般有限群的拉格朗日定理的推论），物品，我们有$a^{\varphi(n)}\equiv 1 \pmod n$。

那么对满足$\gcd(a,n)=1$的$a$，我们定义$ord(a)$为最小的正整数$k$使得$a^k\equiv 1 \pmod n$，显然有$ord(a)\mid \varphi(n)$。

求阶是比较简单的：我们将$\varphi(n)$分解为$p_1^{e_1}\cdot p_2^{e_2}\cdot \ldots p_k^{e_k}$，然后初始时置$ord(a)=\varphi(n)$，每次看当前$ord(a)$除去一个$\varphi(n)$的质因子后是否仍有$x^{ord(a)}\equiv 1\pmod n$，若成立将$ord(a)$除去该质因子。



## BSGS

求方程$a^k=b$的最小非负整数解$k$，或判断无解。这里$a,b$在一个**代数结构**（不一定是数）中，且代数结构的大小$|S|$有限。（这个代数结构要满足结合律，是一个半群，不需要有逆）

考虑取$M=\lceil\sqrt{|S|} \rceil$，预处理出$a^0,a^1,\ldots,a^{M-1}$和$a^M,a^{2M},\ldots,a^{M^2}$。（这里其实和平常的BSGS不一样，因为这个原本是对半群做的，这个方法并不用求逆元）

我们将$a^0,a^M,a^{2M},\ldots,a^{M^2}$插入一个哈希表中，枚举$q(0\leq q\leq m-1)$，在哈希表中查询$b\cdot a^q$

，如果找到的话，设对应的元素是$a^{cM}$，则$k=cM-q$

是一个可能值：具体地，若$a$有逆元，$a^{cM-q}$一定为为$b$，否则还需要代入检验。

假设乘法复杂度为$O(1)$，则算法复杂度为$O(\sqrt{|S|})$。

### 离散对数

对质数$p$和某个$p$的原根$g$，对$p\not\mid x$定义$x$模$p$意义下关于$g$的离散对数$x$为最小的非负整数$k$使得$g^k\equiv x \pmod p$，显然在$[0,p-1)$间仅有唯一一个$k$满足$g^k\equiv x \pmod p$。

当$a,b$都是$\mathbb{F}_p$中元素，且$a$是模$p$意义下原根，$b\ne 0$时，这其实就是求解离散对数，直接套用上述算法即可。

由于$a$有逆元，因此可以省去检验过程。

更一般的情况是求解方程$a^k\equiv b \pmod n$的最小非负整数解，此时$a$未必有逆元，因此套用上述算法时需要检验求出$a^k$是否$\equiv b\mod n$



以下可能稍微详细一点....

求解方程$a^x=c\pmod p$

如果$p$是质数，就是经典的`BGSG`，即大步小步算法。

考虑费马小定理：若$p$为素数，$\gcd(a,p)=1$，则有$a^{p-1}\equiv 1\pmod p$

而$a^0\equiv 1\pmod p$

发现出现了一个循环节，在$x\in [0,p-2]$时就已经包含了所有结果。

直接暴力枚举是$O(p)$

考虑分块优化，将所有的$x$表示为$kT+b$,此时要求$a^{kT}\equiv ca^{-b}\pmod p$

考虑将$ca^{-b}$放入`Hash`表中。

然后预处理出$a^{kT}$然后在`Hash`表中查询即可。

取$T=\sqrt p$得到复杂度为$O(\sqrt p)$，如果使用`map`实现多一个$\log$。

```c++
const int N=2e5+10;

const int hst_mod=173219;
struct hash_map_t
{
    int head[hst_mod+10],cnt;
    struct edge {int nxt,key,val;}e[N<<1];
    inline int ser(int key)
    {
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(key==e[i].key) return e[i].val;
        return -1;
    } 
    inline int ins(int key,int val)
    {
        if(ser(key)!=-1) return -1;
        int u=key%hst_mod;e[++cnt]=(edge){head[u],key,val};head[u]=cnt;
        return val;
    }
    inline int modify(int key,int val)
    {
        if(ser(key)==-1) return ins(key,val);
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(e[i].key==key) return e[i].val=val;
    }
    inline void clear() {R(i,1,cnt) head[e[i].key%hst_mod]=e[i].nxt=0;cnt=0;}
}mp;

//map<int,int>mp;

int p,x,y;
int sq;
int mu,ff;
signed main()
{
    p=read(),x=read(),y=read();for(;sq*sq<=p;sq++);
    mu=1;ff=fpow(x,p-2,p);
    R(i,0,sq-1) mp.ins(mu*y%p,i),mu=mu*ff%p;
    ff=fpow(mu,p-2,p);mu=1;
    R(i,0,sq-1)
    { 
        
        int pos=mp.ser(mu);
        if(pos!=-1) 
        {
            writeln(i*sq+pos);
            return 0;   
        }
        /*
        if(mp.count(mu)) 
        {
            writeln(i*sq+mp[mu]);
            return 0;
        }
        */
        mu=mu*ff%p;
    }
    puts("no solution");
}

```

- [P4884 多少个1？](https://www.luogu.com.cn/problem/P4884)

$n$个$1$可以表示为$\frac{10^n-1}{9}$，所以原式可以表示为$\frac{10^n-1}{9}\equiv k\pmod m$

化简得$10^n\equiv 9k+1\pmod m$，由于$m$是质数，BGSG解出来即可。

- [P2485[SDOI2011]计算器](https://www.luogu.com.cn/problem/P2485) 

咕咕咕

接下来考虑$a,p$不一定互质的情况

当$a\perp p$时，在模$p$意义下$a$存在逆元，因此可以使用BSGS算法求解。于是我们想办法让他们变得互质。

具体地，设$d_1=\gcd(a,p)$，如果$d_1\not\mid c$则原方程无解。（$a$的幂膜$p$之后一定残余$d$的倍数。）

否则将方程同时除以$d_1$，得到
$$
\frac{a}{d_1}\cdot a^{x-1}\equiv \frac{c}{d_1} \pmod {\frac{p}{d_1}}
$$
此时有$\frac{a}{d_1}\perp \frac{p}{d_1}$，于是就可以求逆了，需要`exgcd`

如果$a$和$\frac{p}{d_1}$不互质就再除，设$d_2=\gcd(a,\frac{p}{d_1})$，同样，若$d_2\not\mid \frac{c}{d_1}$则方程无解。

否则将方程再同时除以$d_2$，得到
$$
\frac{a^2}{d_1d_2}\cdot a^{x-2}\equiv \frac{c}{d_1d_2} \pmod {\frac{p}{d_1d_2}}
$$
同理，这样不断判断下去，直到$a\perp \frac{p}{d_1d_2\cdots d_k}$或者说$d_{k+1}=1$。

令$D=\prod\limits_{i=1}^k d_i$，于是方程就变成了
$$
\frac{a^k}{D} \cdot a^{x-k}\equiv \frac{c}{D} \pmod{\frac{p}{D}}
$$
由于$a\perp \frac{p}{D}$，于是推出$\frac{a_k}{D}\perp \frac{p}{D}$。这样$\frac{a^k}{D}$就有逆元了。

将其丢到方程右边，就是一个BSGS问题了，求解$x-k$再加上$k$就是原方程的解了。

由于不排除解小于等于$k$的情况，所以在消因子之前做一下$O(k)$枚举，直接验证$a_i\equiv b\pmod p$

大概就是如果出现
$$
a^{x-1}\equiv \frac{\frac{c}{\gcd(a,p)}}{\frac{a}{\gcd(a,p)}}\equiv 1\pmod{\frac{p}{\gcd(a,p)}}
$$
的情况，也许要特判输出$k$。此时同余式左边是$a^{x-k}$，因为$a^{x-k}\equiv 1\pmod p$，所以直接输出$k$。

当然如果你的BSGS能直接判$x=0$的情况就不需要了。

在菜鸡代码中的体现就是$a=c$

```c++
int gcd(int a,int b) {return !b?a:gcd(b,a%b);}
void exgcd(int a,int b,int &x,int &y) {if(!b){x=1,y=0;return;}exgcd(b,a%b,y,x);y-=x*(a/b);}
inline int get_inv(int a,int p){int x,y;exgcd(a,p,x,y);return (x+p)%p;}
const int hst_mod=173219;
const int N=5e5+10;
struct hash_map_t
{
    int head[hst_mod+10],cnt;
    struct edge {int nxt,key,val;}e[N<<1];
    inline int ser(int key)
    {
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(key==e[i].key) return e[i].val;
        return -1;
    } 
    inline int ins(int key,int val)
    {
        if(ser(key)!=-1) return -1;
        int u=key%hst_mod;e[++cnt]=(edge){head[u],key,val};head[u]=cnt;
        return val;
    }
    inline int modify(int key,int val)
    {
        if(ser(key)==-1) return ins(key,val);
        int u=key%hst_mod;
        for(int i=head[u];i;i=e[i].nxt) if(e[i].key==key) return e[i].val=val;
    }
    inline void clear() {R(i,1,cnt) head[e[i].key%hst_mod]=e[i].nxt=0;cnt=0;}
}mp;
int BSGS(int a,int c,int p)
{
    mp.clear();
    int sq,mu=1,ff=get_inv(a,p);
    for(sq=1;sq*sq<=p;sq++);
    R(i,0,sq-1) mp.ins(mu*c%p,i),mu=mu*ff%p;
    ff=get_inv(mu,p);mu=1;
    R(i,0,sq-1)
    {
        int pos=mp.ser(mu);
        if(pos!=-1) return i*sq+pos;
        mu=mu*ff%p;
    }
    return -1;
}
int solve(int a,int c,int p)
{
    if(a==c) return 1;
    int d=gcd(a,p);
    if(d==1) return BSGS(a,c,p);
    if(c%d) return -1;
    p/=d;
    return solve(a%p,(c/d)*get_inv(a/d,p)%p,p)+1;
}
int check(int a,int c,int p)
{
    if(c==1) return 0;
    if(!a) return !c?1:-1;
    return solve(a,c,p);
}

signed main()
{
    int a,c,p;
    while(1) 
    {
        a=read(),p=read(),c=read();
        if(!p) return 0;
        a%=p,c%=p;
        int ret=check(a,c,p);
        printf(ret<0?"No Solution\n":"%lld\n",ret);
    }
}
```



### Pohlig-Hellman 算法

然后讲一下一个可以在某些情况下求$p=10^{18}$时离散对数的东西。

若我们求解$a^k=b$时，$a,b$在一个乘法群中$ord(a)=n$且$n=p_1^{e_1}\cdot p_2^{e_2}\cdot\ldots\cdot p_k^{e_k}$，则我们可以在$O(e_1\sqrt{p_1}+e_2\sqrt{p_2}+\dots + e_k\sqrt{p_k})$的时间复杂度内求出最小的$k$（若存在显然在$[0,n)$间唯一）。一个应用是求离散对数时，若$p-1$可以分解成若干小质因子乘积，则可以快速计算。

算法关键是若$n=pq$（$q$为质数），我们令

$k=qu+v(0\leq u<p,0\leq v<q)$，我们可以在$O(\sqrt{q})$的时间复杂度内求出$v$：由于$a^k=a^{qu+v}=b$，且$a$的幂形成阶数为$n=pq$的循环群，那么两边取$p$次幂就有$(a^p)^v=b^p$，而$a^p$的幂形成阶数为$q$的循环群，可以直接BSGS求解最小的$v$，不存在则无解，否则必有$0\leq v<q$，那么两边同时乘上$a^{-v}$，再取$q$次幂就可以变为一个新的方程$a'^{k'}=b'$，但此时$a'$的幂形成阶数为$p$的循环群，递归求解即可。

$a^{qu+v}=b$

$(a^{qu+v})^p=b^p$

$a^{pqu}\cdot (a^p)^v=b^p$

$(a^p)^v=b^p$

$a^{qu}=b\cdot a^{-v}$

$(a^q)^u=b\cdot a^{-v}$