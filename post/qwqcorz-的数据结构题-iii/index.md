
<!--more-->

题意：

给定一个长为$n$的排列，两种操作

1. 使$[l,r]$区间的数降序或顺序排序。
2. 查询$k$位置的数。

$n,m\leq 3\times 10^5$

先讲一下原题查询仅一次的做法。

考虑离线，二分该位置上的答案是什么。大于该数的元素看作$1$，小于看作$0$，最后若第$k$个位置为$1$说明可行，这显然是有单调性的。

01序列排序可以用线段树实现$\log n$排序

线段树维护区间和，需要实现区间覆盖

每次排序前先查询排序一共有多少$1$

然后区间覆盖即可。

时间复杂度为$O(M \log_2 N \times \log_2N)$



然后讲一下在线的做法。

如果一个区间有序，那么顺序是唯一的，我们就可以把他们插入到权值线段树中，对于每一段有序的区间都用一棵权值线段树维护，同时记录一下是升序还是降序。可以额外用一个set标记已经有序的区间（类似ODT）。区间排序，对于所有完整的区间就变成了线段树合并。如果是不完整的区间就使用线段树分裂出完全被覆盖的区间进行合并。

