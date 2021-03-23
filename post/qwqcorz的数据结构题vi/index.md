
<!--more-->

题意：

给出一个序列，支持区间加等差数列，区间查询平方和。



原题解：

需要计算的是$\sum\limits_{i=l}^r(a_i(s+(i-l)k)+(s+(i-l)k)^2)$

发现后一部分为等差数列平方和

$\begin{align} \sum\limits_{i=1}^n(s+(i-1)k)^2 & = s^2+(s+k)^2+(s+2k)^2+\cdots+(s+(n-1)k)^2 \\&=s^2+s^2+2sk+k^2+s^2+4sk+4k^2+\cdots+s^2+2(n-1)sk+(n-1)^2k^2 \\ & = ns^2+\sum\limits_{i=2}^n(2isk)+\frac{n(n-1)(2n-1)}{6}k^2(k^2\sum_{i=1}^{n-1}i^2 ) \\ \end{align}$

其中$\sum\limits_{i=1}^{n-1}(2isk)=n(n-1)sk$（原题解写了$(skn^2)$但菜鸡认为是这个）。

考虑如何计算$\sum\limits_{i=l}^r(a_i(s+(i-l)k))$

将式子拆开得到$\sum\limits_{i=l}^r(a_i(s+(i-l)k))=\sum\limits_{i=l}^r a_is+\sum\limits_{i=l}^r(a_i(i-l)k)$(原题解第二个式子为$\sum\limits_{i=1}^r(a_i(i-1)k)$

而$\sum\limits_{i=l}^r(a_i(i-l)k)=k(\sum\limits_{i=l}^r(a_i i)-l\sum\limits_{i=l}^r a_i)$

那么可以在线段树上维护

$\texttt{sum}=\sum_{i=l}^r a_i,\texttt{sum_}=\sum_{i=l}^r(a_i(i-l+1)),\texttt{pow}=\sum_{i=l}^r a_i^2$

考虑如何修改$\texttt{sum_}$

$\texttt{sum_=sum_}+\sum_{i=l}^r((s+(i-l)k)(i-l))=\frac{len(len-1)}{2}s+(\frac{len(len-1)(2len-1)}{6}-\frac{len(len-1)}{2})k$。

以上为神<font color=#000000 size=3>L</font><font color=#FF0000 size=3>imit</font>的题解



并不是很能看懂QAQ

按个人的理解是求$\sum_{i=l}^r (a_i+(s+(i-l)k))^2$

可以拆成$\sum_{i=l}^r a_i^2+2\sum_{i=l}^r(a_i(s+(i-l)k))+\sum_{i=l}^r(s+(i-l)k)^2$

具体计算方法上面有写。

然后就是考虑如何搞区间平方和，假设这里为加上一个数$x$。

$\sum_{i=l}^r=(a_i+x)^2=(a_l^2+a_{l+1}^2+\cdots+a_{r-1}^2+a_r^2+2x(a_l+a_{l+1}+\cdots+a_{r-1}+a_r)+(r-l+1)x^2)$

所以说区间修改的时候加上$2x\sum_{i=l}^r+(r-l+1)x^2$即可。

维护的时候只要一个数组维护区间和，一个维护区间加的懒标记，一个维护区间平方和即可。

那么加上一个等差数列呢？我好像不会……

稍微推一下：$sum=(a_l+s)^2+(a_{l+1}+(s+k))^2+\cdots+(a_r+(s+(r-l)k))^2$

拆开得到：$a_l^2+a_{l+1}^2+\cdots +a_r^2+2a_l s+2a_{l+1}(s+k)+\cdots+2a_r(s+(r-l)k)+s^2+(s+k)^2+\cdots+(s+(r-l)k)^2$

仍然是拆成三部分搞$\sum_{i=l}^r a_i^2,2(s\sum_{i=l}^r a_i+k\sum_{i=l}^ra_i (i-l)),ns^2+(r-l+1)(r-l)sk+\frac{(r-l)(r-l+1)(2r-2l+1)}{6}k^2$

这些显然都是已经维护了的东西。

代码：不会。

