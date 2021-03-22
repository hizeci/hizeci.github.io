
<!--more-->

题意：

给出一个序列，支持区间加等差数列，区间查询平方和。



一操作的话直接差分就好了。

假设原序列为$T$，在每个位置上进行$1$操作后的序列为$S$

$a_i^2=(T_i+S_i)^2=T_i^2 +2T_iS_i+S_i^2 $

每次一操作之后，都需要重新更新$2T_iS_i,S_i^2$。

这里假设$S_i'$为更新前的$S_i$

$2T_iS_i=2(T_i(S_i'+s+(i-l)k))$

$S_i^2=(S_i'+(s+(i-l)k))^2$

然后不是很会了，看一眼题解QAQ。



需要计算的是$\sum\limits_{i=l}^r(a_i())$

发现后一部分为等差数列平方和（这里将$S'$先略去？）

$\begin{align} \sum\limits_{i=1}^n(s+(i-1)k)^2 & = s^2+(s+k)^2+(s+2k)^2+\cdots+(s+(n-1)k)^2 \\ &= s^2+s^2+2sk+k^2+s^2+4sk+4k^2+\cdots+s^2+2(n-1)sk+(n-1)^2k^2 \\ & = ns^2+\sum\limits_{i=2}^n(2isk)+\frac{n(n-1)(2n-1)}{6}k^2(k^2\sum_{i=1}^{n-1}i^2 ) \\ \end{align}$

而$\sum\limits_{i=1}^{n-1}(2isk)=n(n-1)sk$

