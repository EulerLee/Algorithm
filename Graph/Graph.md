# Graph
## 一. 有向图
### 1.1 无圈图的拓扑排序
+ DFS的完成顺序，是拓扑排序的逆序
+ 若有圈，存在顶点v在完成前搜索到自己，即 vis[v] == 1 && order[v] == undefine

*处理有等于关系的拓扑序的技巧，可以优先考虑非相等的关系，在保证拓扑序的情况下尽量满足相等的条件，最后再检测一下答案是否满足条件，见 codeforces-1131D*

### 1.2 判断圈
利用拓扑排序:
+ vis[v] == 1 表示在搜索中，vis[v] == 2 表示搜索完成
+ 若有圈，存在顶点v在完成前搜索到自己，即 vis[v] == 1 返回 false
+ 若vis[v] == 2 返回 true

```cpp
int vis[MAXN];
bool DFS(int v)
{
    if(vis[v] == 2) return true;
    if(vis[v] == 1) return false;
    vis[v] = 1;
    for(auto x: E[v]) {
        if(!DFS(x)) {
            return false;
        }
    }
    vis[v] = 2;
    return true;
}
```

### 1.3 强联通分量
两遍DFS，第一遍得到一种拓扑排序，第二次将边反转，按照拓扑排序的顺序DFS，这时遍历到的都是一个强联通分量里的。
+ 注意到同一个强联通分量里的顶点，其拓扑顺序没有绝对的先后，但是不同强联通分量里的顶点有绝对的先后关系。
+ 首先第一次DFS后得到的部分拓扑排序（后序遍历），这个顺序对于同一个强联通分量里的点是可以颠倒的，但是不同scc里的点不可颠倒顺序。
+ 将边反转后，也就是拓扑排序的顺序反转，这时不同scc中的点顺序必然颠倒，故第一次顺序最前的点此时顺序最后，它能到达的顶点只有同一个scc中的顶点。**其实就是按照将scc收缩成一个顶点后得到的G<sup>SCC</sup>，这是一个有向无环图，第一次DFS得到它的拓扑排序，第二次DFS将顺序倒过来，故排在最开始的scc在边反转后没有出边，从而只能到达自己内部的顶点**

```cpp
const int MAXN = 1e5;
int n;
vector<int> E[MAXN];
vector<int> rE[MAXN];
vector<int> vs;
int vis[MAXN];
int scc[MAXN];  // 顶点所属的强联通分量标号

void DFS1(int v)
{
    if(vis[v]) return;
    vis[v] = 1;
    for(auto u: E[v]) {
        if(!vis[u]) DFS1(u);
    }
    vs.push_back(v);
}

void DFS2(int v, int k)
{
    if(vis[v]) return;
    vis[v] = 1;
    scc[v] = k;
    for(auto u: rE[v]) {
        if(!vis[u]) DFS2(u, k);
    }
}

int find_scc()
{
    memset(vis, 0, sizeof vis);
    REP(i, n) {
        if(!vis[i]) DFS1(i);
    }
    //for(auto x: vs) cout << x+1 << " "; cout << endl;
    memset(vis, 0, sizeof vis);
    int k = 0;
    for(int i = n-1; i >= 0; --i) {
        if(!vis[vs[i]]) DFS2(vs[i], k++);
    }
    return k;
}
```

### 1.4 有向图的 Euler环路 和 Euler路径
##### 1.4.1 判断
+ 有向图存在Euler环路 &iff; 图是联通的，且每个顶点的出度数等于入度数
+ 有向图存在Euler路径 &iff; 图是联通的，且 每个顶点的出度数等于入度数，或有且只有两个顶点，其中一个入度数比出度数多1,另一个出度数比入度数大1

##### 1.4.2 构造
**DFS后序遍历，再将得到的顶点序列倒过来**，证明过程与无向图的类似。

### 1.3 2-SAT问题
判断一个析取范式（只要是表达式就行）是否可满足的问题称为SAT问题，如果这个析取范式的每个合取项所包含的文字不超过两个，就称为2-SAT问题。2-SAT问题可以在线性时间内解决。
- 每个p &or; q可以表示为 (&not;p&rArr;q)&and;(&not;q&rArr;p)，将每个变量的布尔取值表示成一个顶点，得到有向图，所有的强连通分量内布尔值相同。
- 如果某个变量p,&not;p在同一个连通分量内，那么该析取范式无法满足。
- 对于每个布尔变量x，x所在强连通分量的拓扑排序在&not;x之后&hArr;x为真。按此方式得到的赋值就是使得析取范式为真的赋值。
- 对于某些项的文字只有一个的情况，说明该项一定要满足，可以在图中添加一个初始起点，指向这些顶点，DFS就从初始顶点开始，保证这些项一定为真。

---

## 二. 无向图
### 2.1 判断圈
DFS一遍，若有后向边，则停止返回 true

### 2.2 Euler环路 和 Euler路径
##### 2.2.1 判断Euler环路与Euler路径
+ 无向图存在Euler环路 &iff; 图是联通的，且每个顶点度数为偶数
+ 无向图存在Euler路径 &iff; 图是联通的，且 每个顶点度数为偶数，或有且只有两个顶点度数为奇数

##### 2.2.2 构造一条Euler环路/Euler路径
**DFS后序遍历** 即可。下面证明这样一定能找到一条Euler路：
+ 注意到Euler路径/Euler环路的本质是一笔画完所有边
+ DFS后序遍历肯定遍历了所有边，只需要证明可以一笔画
+ 归纳法：只有一条边时显然可以一笔画，假设之前的边都一笔画了，得到了顶点的序列，序列的最后一个顶点记为 u. 当前要放入的顶点 v 是已经访问完毕的顶点（后序遍历的定义），而 u 是上一个完成访问的顶点，故 v 是 u 的父亲，u v 相邻，从而加上 v 后的序列仍然可以一笔画。

需要注意的是，如果图中存在重边或自环，需要利用 [6.1 DFS 时避免重复搜索]() 技巧

### 2.3 无向连通图的割顶
##### 2.3.1 割顶的定义
- 删除割顶后，图不连通。

##### 2.3.2 割顶的性质
DFS一遍：
- 对于根节点，如果根结点下有两棵以上子树，则该顶点是割顶。
- 对于非根结点v，v是割顶当且仅当v的儿子及其子孙没有指向v祖先的后向边。

##### 2.3.3 算法
- 根结点由其子树个数判断是否是割顶。
- 对于非根结点v：
    - 在DFS时对结点染色，未访问的顶点是白色，未完成访问的是灰色，已完成访问的是黑色。
    - v的儿子或子孙u，u相邻的白色节点都是v的子孙。和u相邻的灰色节点都是v的祖先。黑色节点不可能与u相邻。
    - 记录与v及v的子孙相邻的深度最小的祖先Ancestor[v]，若其深度小于v的深度，则存在后向边，v不是割顶，否则v是割顶。

### 2.4 无向连通图的桥
##### 2.4.1 桥的定义
- 删除这条边，图不连通。

##### 2.4.2 桥的性质
- 如果 u 是 v 的儿子，并且 Ancestor[u]>dep[v]（注意不是 >=），那么删除边(v, u)后，图将不连通。

##### 2.4.3 图的收缩
没有割顶的无向图称作2-连通分支，又称作块。把每个块收缩成一个点，得到一棵树，**它的边就是桥**。根据树的性质，从任意一个块A经过**任意一条简单路径**走到另一个块B，所经过的桥的集合是相同的。

---

## 三. 树
### 3.1 最小生成树
+ Kruskal：每次从图中取不成圈的最小边（最小安全边）
    + 并查集
+ Prim：从一个根开始构造树，每次取相邻的最小安全边
    + 优先队列
- k小生成树
    - 设G的前k小生成树构成集合S，则S的邻树中最小的一棵树可以作为G的k+1小生成树。

### 3.2 LCA（最小公共祖先）
##### 3.2.1 在线算法 RMQ
+ 记录DFS经过节点的顺序，对于每条边，其两端的节点都要经过一次（去一次，回来一次），加上开始访问的根节点，共访问了 2|E|+1 次，即 2|V|-1 次。得到数组 A[2n-1]
+ 并且得到 DFS 访问节点（第一次经过）的顺序，表示为第一次出现时在数组 A 中的下标，记为数组ind[n]。
+ 加上各个节点的深度depth[n]
+ LCA化为&plusmn;1-RMQ问题，求出深度最小的 A[ind[u]...ind[v]]之间的节点

##### 3.2.2 离线算法 Tarjan
+ 先处理所有询问，如果存在询问 LCA(u, v)，就把 v 保存在集合 Q<sub>u</sub> 里，u 保存在集合 Q<sub>v</sub> 里
+ DFS 一遍。利用并查集。
    + 如果以节点v为根的子树已经被遍历，那么就不存在 **LCA(x, y) == v** 的情况，此时将v加入他的父亲的集合，并修改 ancestor[find(v)] = par[v]
    + 对于节点v，集合Q<sub>v</sub>中被访问过的点u对应的询问 LCA(u, v) 可以直接给出答案：LCA(u, v) = ancestor[find(u)]

##### 3.2.1 在线算法 &plusmn;1-RMQ
对RMQ的改进，利用相邻元素的值相差&plusmn;1的特点，可以得到O(n)-O(1)的算法。
- 注意到对于两个长度相同的数组A,B，如果满足对任意i，A[i]-B[i]==常数，那么A,B的最小值在同一位置。对于满足&plusmn;1性质的数组，长度为n的话，只有2<sup>n</sup>种不同的数组，他们元素的变化趋势不同。（每个位置从&plusmn;1选一个）
- 先把数组分为长度为 log<sub>2</sub>n/2 的2n/log<sub>2</sub>n 份，再进行Sparse Table的预处理，对于每个数组内部，由于本质不同的数组只有n/2个，故只需要对所有不同的n<sup>1/2</sup>/4 * log<sup>2</sup><sub>2</sub>n 种不同的询问打表，预处理的总时间为 O(n).

---

## 四. 最短路径
### 4.1 单源最短路
##### 4.1.1 Bellman-Ford
+ **条件：** 支持存在权重为负的环路的图。
+ 对每条边进行 |V|-1 次松弛操作，准确说是对整张图进行 |V|-1 次松弛操作。
+ 时间复杂度O(VE)

##### 4.1.2 Dijkstra
+ **条件：** 所有边权重非负。
+ 从根出发，将其相邻顶点的 v.d（最短路径的上界）算出，并加入优先队列，此时堆顶元素必然是最短路径，将其pop，并从对应的点继续探索。
+ 时间复杂度，用优先队列 O(ElgV)，使用斐波那契堆 O(VlgV + E)

### 4.2 所有点对的最短路径
##### 4.2.1 Floyd-Warshall
+ **条件：** 没有权重为负的环路
+ 对中间节点dp，如果中间节点只包含前k个顶点，考虑是否包含第k个顶点。dp方程如下：
> **dp[i][j][k] = w[i][j]** if k == 0
</br>**dp[i][j][k] = min(dp[i][j][k-1], dp[i][k][k-1] + dp[k][j][k-1])** if k >= 1
+ 时间复杂度 &Theta;(|V|<sup>3</sup>)

##### 4.2.2 Johnson
+ **条件：** 支持存在权重为负的环路的图。
+ 先增加一个源顶点s，s到图中每个顶点有单向边且边的权重为0. 利用 Bellman-Ford 判断是否有权重为负的环路。如果没有权重为负的环路，则利用 Bellman-Ford 得到的最短路径重新赋予边权重：**w<sup>'</sup>'[i][j] = w[i][j] + d[s][i] - d[s][j]**. 之后调用 |V| 次 dijkstra 算法计算各个点对间的最短路径，**注意得到的最短路径 d[i][j] 需要减去 (d[s][i] - d[s][j])** 。
+ 时间复杂度 O(VElgV)，若 dijkstra 使用斐波那契堆 O(V<sup>2</sup>lgV + VE)

---

## 五. 网络流

---

## 六. 技巧
### 6.1 DFS 时避免重复搜索
对于图中有重边或者环的情况，应用 DFS 时，由于没法对顶点做访问标记，只能对边做标记，可能会遇到重复判断定点是否应该被访问的情况。比如：
```cpp
void DFS(int v)
{
    for(auto u: adj[v]) {
        if(...) {
            DFS(u);
        }
    }
}
```

由于每次访问顶点都要遍历顶点v的邻接表，所以复杂度是 O(&Sigma;t<sub>i</sub>\*d<sub>i</sub>)， 其中 d<sub>i</sub> 是第i个顶点的度数， t<sub>i</sub> 是第i个顶点被访问的次数。对于简单图，有 t<sub>i</sub> == 1，故 &Sigma;d<sub>i</sub> = 2|E|. 但是对于有重边或自环的图，如果要遍历所有的边，就无法对顶点做访问标记（因为每个顶点必然要访问多次），就会导致时间复杂度爆炸。

注意到，每次访问同个顶点v，v的邻接表都没有变化（只是一些边被访问过了），所以访问的顺序是不变的。故必然是临界表中靠前的顶点先被搜索完（没有v到这个顶点的未被搜索的边了）。所以我们只要对每个顶点做个标记，记录该顶点当前访问到邻接表的哪个顶点了，在这之前的顶点都已经没有（v通向它的未被搜索的）边了。

```cpp
int sig_sta[MAXN];
void DFS(int v)
{
    for(int i = sig_sta[v]; i < adj[v].size(); i = sig_sta[i]+1) {
        if(...) {
            DFS(adj[v][i]);
        }else { // adj[v][i] 访问完毕
            sig_sta[v] = i;
        }
    }
}
```
