## 幂次检测
### 1. 检测完全平方数
#### 朴素算法
要判断整数N是否是完全平方数，很容易想到如下算法：
>计算 $\lfloor {\sqrt{N}} \rfloor$并判断 $\lfloor {\sqrt{N}} \rfloor^{2}$ 是否等于 N

可以通过改进Newton迭代法来优化整数开方：

```cpp
typedef long long ll;
ll nsqrt(ll N)
{
    ll x = N;
    ll y = floor((floor(N/x) + x)/2);
    while(y < x) {
        x = y;
        y = floor((floor(N/x) + x)/2);
    }
    return x;
}
```
算法得到 $\lfloor {\sqrt{N}} \rfloor$.

#### 启发算法
注意到如下事实，可以加速平方检测算法：
>如果 n 是一个平方数, 那么对任意整数 k, n 在 ${\cal Z}$ 模 k${\cal Z}$的商群中都是一个平方数.
>>其中 ${\cal Z}$ 是整数上的加法群，k${\cal Z}$ 是集合{k*g | g \in ${\cal Z}$}上的加法群

基于以上事实，我们可以通过选择合适的常数 k, 快速求出 N 在 ${\cal Z}$ / k${\cal Z}$ 中是否是完全平方数，从而快速排除 N 是非完全平方数的情况。最后再通过朴素方法检测。代码如下：
```cpp
void init_Qn(vector<ll> &Qn)
{
        int n = Qn.size();
        for(int i = 0; i < n; ++i) {
                Qn[i*i % n] = 1;
        }
}

bool square_detection(ll N)
{
        vector<ll> Q64(64, 0);
        vector<ll> Q63(63, 0);
        vector<ll> Q65(65, 0);
        vector<ll> Q11(11, 0);
        init_Qn(Q64);
        init_Qn(Q63);
        init_Qn(Q65);
        init_Qn(Q11);
        if(Q64[N%64] == 0) return false;
        ll r = N % 63*65*11; // r已经被减小到 63*65*11 的范围内，故后面的不用再减小也不要紧
        if(Q63[N%63] == 0 || Q65[N%65] == 0 || Q11[N%11] == 0) return false;
        return nsqrt(N) * nsqrt(N) == N;
}
```
以上算法通过分别取 k = 64, 63, 65, 11, 检测 N 在模 k 意义下的完全平方性，通过枚举可以得到，k 取 64, 63, 65, 11 时，模k意义下的完全平方数的占比分别为 $\frac{12}{64}$, $\frac{16}{63}$, $\frac{21}{65}$, $\frac{6}{11}$.
故理论上对于大部分的 N, 都不用进行整数开方运算，进行最后一步开方运算的概率是
$$\frac{12}{64}\cdot\frac{16}{63}\cdot\frac{21}{65}\cdot\frac{6}{11} = \frac{6}{715}$$
从而极大地减少了运算代价。
