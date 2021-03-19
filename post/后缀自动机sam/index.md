
<!--more-->

## 一些前置约定/定义

记$\Sigma$为字符集，$|\Sigma|$为字符集大小。对于一个字符串$\texttt s$，记$|s|$为其长度。

## 概述

**后缀自动机**$\texttt{(suffix automaton,SAM)}$是一个能解决许多字符串相关问题的数据结构。

举个例子，以下的字符串问题都可以在线性时间内通过$\texttt{SAM}$解决。

- 在另一个字符串中搜索一个字符串的所有出现位置。
- 计算给定的字符串中有多少个不同的子串。

直观上，字符串的$\texttt{SAM}$可以理解为给定字符串的**所有子串**的压缩形式。值得注意的事实是，$\texttt{SAM}$将所有的这些信息以高度压缩的形式储存。对于一个长度为$\texttt n$的字符串，它的空间复杂度仅为$O(n)$。此外，构造$\texttt{SAM}$的时间复杂度仅为$O(n)$。准确地说，一个$\texttt{SAM}$最多有$2n-1$个节点和$3n-4$条转移边。

## SAM的定义

可以且仅可以接受母串$\texttt S$的后缀的$\texttt{DFA}$（确定性有限自动机或确定性有限状态自动机）。

换句话说：

- $\texttt{SAM}$是一张$\texttt{DAG}$。节点被称为**状态**，边被称作状态间的**转移**。
- 图存在一个源点$t_0$，称为**初始状态**，其它各节点均可从$t_0$出发到达。
- 每个**转移**都标有一些字母（？个人认为就是一个字符）。从一个节点出发的所有转移均**不同**。
- 存在一个或多个**终止状态**。如果我们从初始状态$t_0$出发，最终转移到了一个终止状态，则路径上的所有转移连接起来一定是字符串$\texttt s$的一个后缀。$\texttt s$的每个后缀均可用一条从$t_0$到某个终止状态的路径构成。
- 在所有满足上述条件的自动机中，$\texttt{SAM}$的节点是最少的。

## 子串的性质

$\texttt{SAM}$最简单、也最重要的性质是，它包含关于字符串$\texttt s$的所有子串的信息。任意从初始状态$t_0$开始的路径，如果我们将转移路径上的标号写下来，都会形成$\texttt s$的一个**子串**。反之每个$\texttt s$的子串对应从$t_0$开始的某条路径。

为了简化表达，我们称子串**对应**一条路径（从$t_0$开始、由一些标号构成这些子串）。反过来，我们说任意一条路径**对应**它的标号构成的字符串。

到达某个状态的路径可能不止一条，因此我们说一个状态对应一些字符串的集合，这个集合的每个元素对应这些路径。

## 结束位置endpos

考虑字符串$\texttt s$的任意非空子串$\texttt t$，我们记$\texttt{endpos(t)}$为在字符串$\texttt s$中$\texttt t$的所有结束位置（假设对字符串中字符的编号从零开始）。例如，对于字符串$\texttt{abcbc}$，我们有$\texttt{endpos("bc")=2,4}$。

两个子串$t_1$与$t_2$的$\texttt{endpos}$集合可能相同：$endpos(t1)=endpos(t2)$。这样所有字符串$\texttt s$的非空子串都可以根据它们的$\texttt{endpos}$集合被分为若干**等价类**。

显然，$\texttt{SAM}$中的每个状态对应一个或多个$\texttt{endpos}$相同的子串。换句话说，$\texttt{SAM}$中的状态数等于所有子串的等价类的个数，再加上初始状态。$\texttt{SAM}$的状态个数等价于$\texttt{endpos}$相同的一个或多个子串所组成的集合的个数$+1$。

我们稍后将会用这个假设来介绍构造$\texttt{SAM}$的算法。我们将发现，$\texttt{SAM}$需要满足的所有性质，除了最小性以外都满足了。由$\texttt{Nerode}$定理我们可以得出最小性（不会在这篇文章中证明）。

由$\texttt{endpos}$的值我们可以得到一些重要结论：

> **引理$\texttt 1$：** 字符串$\texttt s$的两个非空子串$\texttt u$和$\texttt w$（假设$|u|\leq |w|$）的$\texttt{endpos}$相同，当且仅当字符串$\texttt u$在$\texttt s$中的每次出现，都是以$\texttt w$后缀的形式存在的。

引理显然成立。且如果$\texttt u$为$\texttt w$的一个后缀，且只以后缀的形式在$\texttt s$中出现时，两个子串的$\texttt{endpos}$相同。

> **引理 $\texttt 2$：**考虑两个非空子串$\texttt u$和$\texttt w$（假设$|u|\leq|w|$）。那么要么$endpos(u)\cap endpos(w)=\varnothing$，要么$endpos(w)\subseteq endpos(u)$,取决于$\texttt u$是否是$\texttt w$的一个后缀：
>
> $\begin{cases} endpos(w)\subseteq  endpos(u) & \mbox{if }u\mbox{ is a suffix of w} \\ endpos(w)\cap  endpos(u)=\varnothing   & otherwise \end{cases}$

证明：如果集合$endpos(u)$与$endpos(w)$有至少一个公共元素，那么由于字符串$\texttt u$和$\texttt w$在相同位置结束，$\texttt u$是$\texttt w$是的一个后缀。所以每次$\texttt w$出现的位置，子串$\texttt u$也会出现。所以$endpos(w)\subseteq endpos(u)$。

>**引理$\texttt 3$：**考虑一个$endpos$等价类，将类中的所有子串按长度非递增的顺序排序。每个子串都不会比它前一个子串长，与此同时每个子串也是它前一个子串的后缀。换句话说，对于同一等价类的任一两子串，较短者为较长者的后缀，且该等价类中的子串长度恰好覆盖整个区间 $[x,y]$

证明：如果$endpos$等价类中只包含一个子串，引理显然成立。现在我们来讨论子串元素个数大于$\texttt 1$的等价类。

由引理$\texttt 1$，两个不同的$endpos$等价的字符串中，较短者总是较长者的真后缀。因此，等价类中没有等长的字符串。

记$\texttt w$为等价类中最长的字符串、$\texttt u$为等价类中最短的字符串。由引理$\texttt 1$，字符串$\texttt u$是字符串$\texttt w$的真后缀。现在考虑长度在区间$\texttt{[|u|,|w|]}$中的$\texttt{|w|}$的任意后缀。容易看出，这个后缀也在同一等价类中，因为这个后缀只能在字符串$\texttt s$中以$\texttt w$的一个后缀的形式存在（也因为较短的后缀$\texttt u$在$\texttt s$中只以$\texttt w$的后缀形式存在）。因此，由引理$\texttt 1$，这个后缀和字符串$\texttt w$的$\texttt{endpos}$相同。

## 后缀链接link

考虑$\texttt{SAM}$中某个不是$t_0$的状态$\texttt v$。我们已经知道，状态$\texttt v$对应于具有相同$\texttt{endpos}$的等价类。我们如果定义$\texttt w$为这些字符串中最长的一个，则所有其他的字符串都是$\texttt w$的后缀。

我们还知道字符串$\texttt w$的前几个后缀（按长度降序考虑）全部包含于这个等价类，且所有其他后缀（至少有一个——空后缀）在其他的等价类中。我们即$\texttt t$为最长的这样的后缀，然后将$\texttt v$的后缀链接到$\texttt t$上。

换句话说，一个**后缀链接$\texttt{link(v)}$**连接到对应于$\texttt w$的最长后缀的另一个$\texttt{endpos}$等价类的状态。

以下我们假设初始状态$t_0$对应与它自己这个等价类（只包含一个空字符串）。为了方便，我们规定$\operatorname {endpos}(t_0)=\{-1,0,\cdots,|S|-1\}$。

>**引理$\texttt 4$：** 所有后缀链接构成一棵根节点为$t_0$的树。

证明：考虑任意不是$t_0$的状态$\texttt v$，后缀链接$\texttt{link(v)}$连接到的状态对应严格更短的字符串（后缀链接的定义、引理$\texttt 3$）。因此，沿后缀链接移动，我们总是能到达对应空串的初始状态$t_0$。

> **引理$\texttt 5$：** 通过$\texttt{endpos}$集合构造的树（每个子节点的$\texttt{subset}$都包含在在父节点的$\texttt{subset}$中）与通过后缀链接$\texttt{link}$构造的树相同。

证明：由引理$\texttt{2}$，任意一个$\texttt{SAM}$的$\texttt{endpos}$集合形成了一棵树（因为两个集合要么完全没有交集要么一个是另一个的子集）。

我们现在考虑任意不是$t_0$的状态$\texttt v$及后缀链接$\texttt{link(v)}$，由后缀链接和引理$\texttt 2$，我们可以得到

$endpos(v)\subset endpos(link(v))$，

注意这里是真子集，因为若$\texttt{endpos(v)=endpos(link(v))}$，那么$\texttt v$和$\texttt{link(v)}$应该被合并为一个节点。

结合前面的引理有：后缀链接构成的树本质上是由$\texttt{endpos}$集合构成的一棵树。

以下是对字符串$\texttt{"abcbc"}$构造$\texttt{SAM}$时产生的后缀链接树的一个**例子**，节点被标记为对应等价类中最长的子串。

![img](https://oi-wiki.org/string/images/SAM/SA_suffix_links.svg)

## 小结

- $\texttt s$的子串可以根据它们结束的位置$\texttt {endpos}$被划分为多个等价类；
- $\texttt{SAM}$由初始状态$t_0$和与每一个$\texttt{endpos}$等价类对应的每个状态组成；
- 对于每一个状态$\texttt v$一个或多个子串与之匹配。我们记$\texttt{longest(v)}$为其中最长的一个字符串，记$\texttt{len(v)}$为它的长度。类似地，记$\texttt{shortest(v)}$为最短的子串，它的长度为$\texttt{minlen(v)}$。那么对应这个状态的所有字符串都是字符串$\texttt{longest(v)}$的不同的后缀 ，且所有字符串的长度恰好覆盖区间$\texttt{[minlen(v),len(v)]}$中的每一个整数。
- 对于任意不是$t_0$的状态$\texttt v$，定义后缀链接为连接到对应字符串$\texttt{longest(v)}$的长度为$\texttt{minlen(v)-1}$的后缀的一条边。从根节点$t_0$出发的后缀链接可以形成一棵树。这棵树也表示$\texttt{endpos}$集合间的包含关系。
- 对于$t_0$以外的状态$\texttt v$，可用后缀链接$\texttt{link(v)}$表达$\texttt{minlen(v)}$：$\texttt{minlen(v)=len(link(v))+1}$。
- 如果我们从任意状态$v_0$开始顺着后缀链接遍历，总会到达初始状态$t_0$。这种情况下我们可以得到一个互不相交的区间$[minlen(v_i),len(v_i)]$的序列，且它们的并集形成了连续的区级$[0,len(v_0)]$。

以上内容均来自[oi-wiki](https://oi-wiki.org/string/sam/#_2)

其结构包含两部分：有向单词无环图（$\texttt{DAWG}$）以及一棵树（$\texttt{parent}$树）。

它们的节点集合相同。

目标：最小化节点集合大小！

### DAWG

$\texttt{DAWG}$是$\texttt{DAG}$，其中每个**节点**表示一个或多个$\texttt{S}$的子串。特别地，起始节点对应$\varnothing$。

每条转移边上仅有一个字符。从起始节点出发，沿着转移边移动，则每条**路径**都会唯一对应$\texttt{S}$的一个子串。

每个节点所代表的字符串是$\texttt{S}$的**某个前缀**的**长度连续的后缀**。设$\texttt u$的长度最小、最大的子串分别为$\min_u$和$\max_v$，$\max_u$在$\texttt S$中出现的位置集合为$end_u$。

#### 定理

任意两个节点的 end 集合互不相同。

### parent  树

#### 定义

定义$\texttt u$的**$\texttt{parent}$指针**指向$\texttt v$,当且仅当$|\min_u|=|\max_v|+1$，且$\texttt v$所代表的子串均为$\texttt u$子串的后缀，记作$next_u=v$。

显然，所有节点沿着**$\texttt{parent}$指针**向前走，都会走到$\texttt{DAWG}$的起始节点。因此以**$\texttt{parent}$指针**为边，所有节点组成了一棵树，称为**$\texttt{parent}$树**。

#### 定理

在**$\texttt{parent}$树**中，子节点的$end$集合一定是父亲的真子集，即$end_u \subset end_{next_u}$。

#### 简易构造SAM例子

用蓝色表示初始状态，用绿色表示终止状态。

对于字符串$s=\varnothing$

![img](https://oi-wiki.org/string/images/SAM/SA.svg)

对于字符串$s=a:$

![img](https://oi-wiki.org/string/images/SAM/SAa.svg)

对于字符串$s=aa:$

![img](https://oi-wiki.org/string/images/SAM/SAaa.svg)

对于字符串$s=ab:$

![img](https://oi-wiki.org/string/images/SAM/SAab.svg)

对于字符串$s=abb:$

![img](https://oi-wiki.org/string/images/SAM/SAabb.svg)

对于字符串$s=abbb:$

![img](https://oi-wiki.org/string/images/SAM/SAabbb.svg)

## 构建：增量法

$\texttt{SAM}$的构建使用**增量法**：通过$\texttt S$的$\texttt{SAM}$求出$\texttt{S+c}$的$\texttt{SAM}$。

