# String
---
## 一. 字符串匹配
#### 1.1 Rabin-Karp算法
字符串和模式都当作数，模式为p%q，对应长度的字符串的数为t%q。
+ 当 p &nequiv; t (mod q) 时，显然不匹配
+ p &equiv; t (mod q) 时，可能匹配，扫描字符串检测一遍

具体实现时，可以取q为2<sup>64</sup>，利用ull自动取模，而哈希数的基可以取1e8+7;
并且当哈希值相等时，就当作匹配（近似）。

#### 1.2 有限自动机
有限自动机 M 是一个五元组 (Q, q<sub>0</sub>, A, &Sigma;, &delta;)
+ Q 是状态的有限集合
+ q<sub>0</sub>&isin;Q，是初始状态
+ A&sube;Q，是接收状态的集合
+ &Sigma; 是字母表
+ &delta; 是 Q\*&Sigma; &rarr; Q 的映射，称为转移函数

#### 1.3 KMP算法
+ 也是一种有限自动机
+ 前缀函数&pi;：&pi;[q]是P<sub>q</sub>的真后缀同时也是P的前缀的最长长度，即字符串 P[1, &pi;[q]] == P[q-&pi;[q], q]
+ 计算前缀函数：
    + &pi;[0] = 0
    + 记 k = &pi;[i-1]
        + if s[k+1] == s[i] &rArr; &pi;[i] = &pi;[i-1]+1
        + otherwise k = &pi;[k]; repeat;

#### 1.4 BM算法

#### 1.5 shift-or算法

#### 1.6. Z-function
定义函数 Z(i)，表示由 s[i] 开始的字符串和 s[0] 开始的字符串最多可以匹配多长，即：
>s[0, ..., z(i)-1] == s[i, ..., i+z(i)-1]

Z-function 可以在 O(|s|) 时间内被计算。算法维护一对值 L, R，满足：s[L, R]是s的前缀，并且 R 是 [1, i-1] 中 取到最右端的值，L是对应的起始值。即 R = L + z[L] - 1
+ z[0] = |s|
+ z[1] 暴力搜索，并且得到 L = 1, R = z[1]-1
+ 假设已经计算了z[0]，z[1]，...，z[i-1]，下面计算z[i]
    + 若 i > R，说明之前没有区间覆盖i，从i暴力搜索。此时 L = i，R = i+z[i]-1
    + 若 i &le; R，说明 s[L, R] 中有 s[i]，s[L, i]是s的前缀，记 k = i-L
        + 若 z[k] < R-i+1，则必有 z[i] = z[k]. 此时L，R不变
        + 若 z[k] &ge; R-i+1，由于我们扫描到的字符串s的最右端是R位置，对于R之后的信息是不知道的，所以我们只知道 z[i] 至少等于 R-i+1，后面的逐字比对。此时 L = i，R = i+z[i]-1

L和R遍历字符串，每个字符最多被扫描两次，故时间复杂度 O(|s|)

---
## 二. 后缀数组 Suffix
将某个字符串的所有后缀(包括空串和原串)按照字典序排序后得到的数组。
#### 2.1 计算
+ Manber-Myers
    + [./Suffix/compute_suffix.cpp](./Suffix/compute_suffix.cpp)
    + 倍增，先排序长度为2的子串，再到4、8、16...
    + rank<sub>k</sub>[i]表示从 i 开始长度为 k 的子串是第几小的，要计算rank<sub>2k</sub>[i]，只需要比较rank<sub>k</sub>[i]和rank<sub>k</sub>[i+k]的数对，和其他(j &ne; i)rank<sub>k</sub>[j]和rank<sub>k</sub>[j+k]的数对
    + 时间复杂度 O(nlog<sup>2</sup>n)，空间复杂度 O(2n)
+ SA-IS
+ Skew

#### 2.2 基于后缀数组的字符串匹配
[./Suffix/strcmp_suffix.cpp](./Suffix/strcmp_suffix.cpp)</br>
二分搜索，时间复杂度 O(|P|\* log|S|)，当|S|远大于|P|时，该算法比O(|P|+|S|)更加高效。适用于 S 不变的多次匹配。

---
## 三. 高度数组 LCP Array
高度数组，指的是由后缀数组中相邻的两个后缀的最长公共前缀(LCP，Longst Common Prefix)的长度组成的数组。lcp[i] 等于后缀 S[sa[i]...] 和 S[sa[i-1]...] 最长公共前缀的长度。
#### 3.1 计算
+ 时间复杂度 O(n)
+ 依然需要rank[i] *(rank[sa[i]] = i)*


---
## 禁止模式
#### Trie树
+ 以字符串前缀做动态规划，按照类似树的结构进行dp，数据结构并不一定是树

---
## Aho-Corasick算法（AC自动机）
AC算法主要目的是根据模式串构造一个有限状态自动机，从而实现多模式匹配。该自动机的转移函数有三种状态：成功、失败、输出。
+ 首先根据模式串构造Trie树，根节点的状态是空串
+ 为Trie树添加failure状态，即当前匹配失败时要转移到哪个节点
+ 叶子节点显然是output状态，到达叶子节点时匹配成功
+ 成功转移即沿着Trie树本来的边转移

## Wu-Manber算法
多维的BM算法


## Manacher算法
用于查找回文。

---
## Useful Function
+ reverse_copy(begin, end, \*dest);
    + 反转拷贝
