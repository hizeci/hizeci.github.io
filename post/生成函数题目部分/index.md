
<!--more-->

## Luogu 4723 求解线性递推

给定$k$阶线性递推$\{F\}$的前$k$项，$F_0,F_1,\cdots ,F_{k-1}$，以及系数$a_1,a_2,\cdots ,a_k$满足：
$$
F_n =\sum_{i=1}^k F_{n-i} \cdot a_i (n\ge k)
$$
求$F_n$，其中$n\leq 10^{18},k\leq 6\times 10^4$。

因为$n$非常大，所以之前的特征根法在这里没有什么用，因为需要解一个$10^5$阶的方程，肯定是解不出来的，所以没法求出它的通项。

首先第一想法是矩阵快速幂

设初始向量是$\overrightarrow a$然后给它乘上$M^{n-k}$

直接算复杂度就是$O(k^3 \log n)$

这个东西肯定不是非常够接受。

然后介绍一个定理：

### Cayley-Hamilton 定理

线性代数中一个非常重要的定理。这里就不证了。

首先讲一下基础概念：特征多项式。

举个例子，对于一个矩阵$M$而言，它的特征多项式是$\operatorname{char(M)}$（注意这是整体是一个多项式）

可以把$\operatorname{char}$看作一个函数，设自变量为$\lambda$，就是从$\mathbb{R}^{M\times N}\to \mathbb{R} [\lambda]$（从$M\times N$阶矩阵，映射到一个关于$\lambda$的一个多项式）

那么$\operatorname{char(M)} (\lambda) $就被定义为$\det (\lambda I-M)$（若矩阵大小为$K$，则这是一个$K$阶多项式。）

然后把它写成多项式的形式（特征多项式最高次项为$1$）：
$$
\operatorname{char(M)}(\lambda)=\lambda ^k -\sum\limits_{i=1}^k a_i \lambda ^{k-i}
$$
然后Cayley-Hamilton 定理就是说
$$
\operatorname{char(M)}(M)=0 
$$
即
$$
M^k=\sum_{i=1}^k a_i M^{k-i}
$$
然后两边同乘$M^{n-k}$，得到：
$$
M^{n-k}\cdot M^k=\sum_{i=1}^k a_i M^{n-k} M^{k-i} 
$$

$$
M^n=\sum_{i=1}^k a_i \cdot M^{n-i}
$$

所以假如知道$a_i$，考虑怎么求矩阵快速幂：

大概就是把$M^n$拆成$n-1,n-2,\cdots ,n-k$的组合。

然后$n-1$可以拆成$n-2,\cdots ,n-k-1$这样一直变，最后一叠，就变成：
$$
M^n =\sum_{i=0}^{k-1} b_i M^i
$$
因此，假如要求$M^a\cdot M^b$，就是
$$
\big(\sum\limits_{i=0}^{k-1} b_i\cdot M_i \big)\big(\sum\limits_{i=0}^{k-1} c_i\cdot M_i \big)
$$
然后对$b$和$c$进行卷积：
$$
\sum_{i=0}^{2k-1} \sum_{j=0}^{i} b_j \cdot c_{i-j} M^i
$$
多了一些项，就用类似等于$a$的方式给它搞回去。

这个东西可以在$O(k^2\log n)$的时间复杂度之内求出。

当然需要知道$a$。



然后考虑$M$长什么样子（图中的$a$为题目给出的$a$）
$$
M=\begin{bmatrix} a_1 & a_2 & a_3 &\cdots &a_k  \\1 & 0 &0 &\cdots &0\\ 0 & 1 &0 &\cdots &0\\0 & 0 &1 &\cdots &0\\ \vdots & \ddots & &\ & \vdots \\\vdots &  &\ddots & & \vdots\\ \vdots &  & &\ddots & \vdots\\ 0 & 0 & \ldots & 1 & 0
\end{bmatrix}
\begin{bmatrix} f_n\\ f_{n-1} \\f_{n-2}\\ \vdots \\ f_{n-k+1}
\end{bmatrix} 
=
\begin{bmatrix} f_{n+1}\\ f_{n} \\f_{n-1}\\ \vdots \\ f_{n-k+2}
\end{bmatrix} 
$$
我猜会崩，所以先放张图：

![QQ图片20210512203046.png](https://i.loli.net/2021/05/12/oSO4f23PrVjmeTc.png)

对于这个东西考虑求出特征多项式（因为稀疏，所以考虑直接手算...）

然后这个题就做完了。

现在就相当于是给一个$2k-1$次多项式（就是上面那个$b$卷$c$的多项式），这里称为$d(M)$。然后要求一个$k$次多项式$r(M)$满足$r$和$d$是一样的。

因为$\operatorname{char(M)}(M)=\sum\limits_{i=0}^{k-1} a_i M^i=0$，然后把这个写成$b(M)$

$d(M)=b(M)\cdot g(M) +r(M)$

那么$r(M)\equiv d(M) \pmod {b(M)}$

然后现在由于你给任何多项式加或减这个$b(M)$，这个值都不变，所以考虑用这个给$d(M)$降次。

可以理解为：

假如现在由$x_0$满足$x_0^3=x_0^2+2x_0+3$。

那么像$x_0^{100}$就可以拆成$x_0^{99}+2x_0^{98}+3x_0^{97}$，而$x_0^{99}$又可以拆成$x_0^{98}+2x_0^{97}+3x_0^{96}$……然后这么一直拆下去

其实这就相当于对$x^3-x^2-2x-3$取模。

由于多项式除法是$O(k\log k)$的，所以总复杂度就是$O(k\log k\log n)$，就是每一次快速幂都这样做一次多项式取模。

