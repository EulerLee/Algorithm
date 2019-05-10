## 数论算法
#### 快速计算p的完系的所有逆元
对于素数m，计算m的完系[1, m-1]的所有逆元，如果每个都用 a<sup>m-2</sup> 来计算，总的复杂度是 O(mlogm).

对于素数m，求解m的完系的所有逆元，有 O(m) 时间复杂度的算法。

我们记 inv[i] 为 i 模 m 下的逆元，对于 i>1，有以下等式成立：
> **inv[i] = -⌊m/i⌋ \* inv[m%i] %m**

所以算法非常简单：
```cpp
inv[1] = 1;
for(int i = 2; i < m; ++i)
    inv[i] = (m - (m/i) * inv[m%i] % m) % m;
```

#### 计算素数的原根
对于素数p，它的原根g是满足 g<sup>0</sup>, g<sup>1</sup>, ..., g<sup>p-2</sup> 在模p意义下各不相同的元。如果g不是原根，那么必然存在 d&in;[1, p-2] 使得 g<sup>d</sup> &equiv; 1 (mod p). 而因为 g<sup>&phi;(p)</sup> &equiv; 1 (mod p)，故 d | &phi;(p)，即 d | p-1

要检测一个数 a (2 &le; a &le; p) 是否是 p 的原根，朴素的方法是检测 a 的 1 到 p-2 次幂是否有等于1的。根据上文，其实我们只需要检测 p-1 的因子次幂。更进一步，令 p-1 = q<sub>1</sub><sup>t<sub>1</sub></sup>q<sub>2</sub><sup>t<sub>2</sub></sup>...q<sub>s</sub><sup>t<sub>s</sub></sup>，其中 q<sub>i</sub> 是素数，若 a<sup>q<sub>i</sub></sup> &equiv; 1 (mod p)，则 q<sub>i</sub> 的所有倍数 kq<sub>i</sub> 也必然满足 a<sup>kq<sub>i</sub></sup> &equiv; 1 (mod p)，并且还有 a<sup>&phi;(p)/q<sub>i</sub></sup> &equiv; 1 (mod p)，所以 **检测 a<sup>&phi;(p)/q<sub>i</sub></sup> 就等于检测了 &phi;(p) 所有包含了 q<sub>i</sub> 的因子**.（证明: a<sup>kq<sub>i</sub></sup> &equiv; 1 (mod p) &rArr; a<sup>&phi;(p)/kq<sub>i</sub></sup> &equiv; 1 (mod p) &rArr; a<sup>&phi;(p)/q<sub>i</sub></sup> &equiv; 1 (mod p)）

综上所述，对于a，我们只需要检测 &phi;(p) 的所有素因子次幂，就可以判断出a是否是p的原根，而由于原根一般较小，所以从2开始遍历即可算出原根

#### 中国剩余定理 CRT
