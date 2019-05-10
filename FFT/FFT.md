## 多项式与快速傅里叶变换

### 1. 多项式的表示
#### 1.1 系数表示
用系数向量表示，对于次数界为n的多项式 A(x) = &Sigma;<sup>n-1</sup><sub>j=0</sub> a<sub>j</sub>x<sup>j</sup>，其表示为 **a** = (a<sub>0</sub>, ..., a<sub>n-1</sub>).
+ 加法 C(x) = A(x) + B(x), 则 **c** = **a** + **b**
+ 乘法 C(x) = A(x) * B(x), 则 c<sub>j</sub> = &Sigma;<sup>j</sup><sub>k=0</sub>a<sub>k</sub>b<sub>j-k</sub>，记为 **c** = **a** &otimes; **b**, 向量 **c** 称为 **a**，**b** 的卷积


#### 1.2 点值表示
一个次数界为n（即次数做多只能为n-1）的多项式 A(x) 可以由 n 个不同的点值对唯一确定。一个多项式可以有不同的点值表达。
+ 加法，直接加y值
+ 乘法，先拓展为 2n 个点值对，再直接乘

### 2. DFT 与 FFT

#### 2.1 单位复数根
+ 消去引理
+ 折半引理
+ 求和引理

#### 2.2 离散傅里叶变换 (DFT)
多项式 A(x) 在 n 个 n 次单位复数根处 (w<sub>n</sub><sup>0</sup>, ..., w<sub>n</sub><sup>n-1</sup>) 的值向量 **y** = (y<sub>0</sub>, ..., y<sub>n-1</sub>) 就是系数向量 **a** = (a<sub>0</sub>, ..., a<sub>n-1</sub>) 的离散傅里叶变换，记为 **y** = DFT<sub>n</sub>(**a**)

#### 2.3 快速傅里叶变换 (FFT)
+ 拓展次数界 n 为2的幂，这步直接加系数为0的项即可
+ A(x) = A<sup>[0]</sup>(x<sup>2</sup>) + xA<sup>[1]</sup>(x<sup>2</sup>)
    + **a<sup>[0]</sup>** = (a<sub>0</sub>, a<sub>2</sub>, ..., a<sub>n-2</sub>)
    + **a<sup>[1]</sup>** = (a<sub>1</sub>, a<sub>3</sub>, ..., a<sub>n-1</sub>)
    + 只需要计算两个次数界为 n/2 的多项式的 n 个点值对
+ 计算子问题，两个 n/2 次数界的多项式，在 n 个点 ((w<sub>n</sub><sup>0</sup>)<sup>2</sup>, (w<sub>n</sub><sup>1</sup>)<sup>2</sup>, ..., (w<sub>n</sub><sup>n-1</sup>)<sup>2</sup>) 上的取值。
而 ((w<sub>n</sub><sup>0</sup>)<sup>2</sup>, (w<sub>n</sub><sup>1</sup>)<sup>2</sup>, ..., (w<sub>n</sub><sup>n-1</sup>)<sup>2</sup>) 中不同的值只有 n/2 个，由折半引理，这是由 n/2 个 n/2 次单位复数根组成的。故而子问题规模减小一半，由 **计算次数界为 n 的多项式在 n 个点上的值** ，变成 **计算次数界为 n/2 的多项式在 n/2 个点上的值** 。

#### 2.4 插值 IFFT
修改下 FFT 即可，将 **a** 换成 **y**，用 &omega;<sub>n</sub><sup>-1</sup> 代替 &omega;<sub>n</sub> ，并且将计算结果的每个元素除以 n 即可。

DFT<sub>n</sub><sup>-1</sup>(**y**):
> a<sub>j</sub> = 1/n &Sigma;<sub>0</sub><sup>n-1</sup> y<sub>k</sub>&omega;<sub>n</sub><sup>-kj</sup>


### 3. 有限域上的 FFT
模m下的FFT，需要m的完系有阶为n的元g<sub>n</sub>，即g<sub>n</sub>是 **Z**<sub>m</sub><sup>\*</sup> 中阶为n的元。则修改 FFT 算法，令
>&omega;<sub>n</sub> = g<sub>n</sub>,
>
>&omega;<sub>n</sub><sup>k</sup> = g<sub>n</sub><sup>k</sup> mod m

一般来说，对m的要求是，它的完系中存在阶为 1, 2, 2<sup>2</sup>, ..., n 的元素。显然，如果存在阶为 n 的元素，之前的肯定存在。故条件简化为 n | &phi;(m)，其中 n 是拓展后的次数界，为2的幂。

取m为素数，则条件变为 n | m-1. 故我们需要找到形式为 kn+1 的素数，再算出其原根g，则 g<sub>n</sub> = g<sup>(m-1)/n</sup>

[](*m可以取费马数F<sub>4</sub> = 2<sup>2<sup>4</sup></sup>+1 = 65537，原根为 3，则 N &le; 65536*)
m可取998244353ll，m-1 = 2<sup>23</sup>\*119，原根为3，则 N &le; 2<sup>23</sup> = 8388608

### 4. 多项式多点快速求值
运用 FFT 可以在 O(nlg<sup>2</sup>n) 的时间内求出一个次数界为 n 的多项式在任意 n 个点（x<sub>0</sub>, ..., x<sub>n-1</sub>）的值。

算法的核心是快速计算多项式带余除法的余式。目标多项式 A(x) 的系数表示是 **a** = (a<sub>0</sub>, ..., a<sub>n-1</sub>). 对于 0 &le; i &le; j &le; n-1，定义多项式 P<sub>ij</sub>(x) = &Pi;<sub>i</sub><sup>j</sup>(x-x<sub>k</sub>) 和多项式 Q<sub>ij</sub>(x) = A(x) mod P<sub>ij</sub>(x)
. P<sub>ij</sub>(x) 的次数为 j-i+1，故 Q<sub>ij</sub>(x) 的次数至多为 j-i. 我们有如下结论：
+ 对任意点z，A(x) mod (x-z) = A(z)
+ Q<sub>kk</sub>(x) = A(x<sub>k</sub>) 且 Q<sub>0,n-1</sub>(x) = A(x)
+ 对于 i&le;k&le;j，有
    + Q<sub>ik</sub>(x) = Q<sub>ij</sub>(x) mod P<sub>ik</sub>(x)
    + Q<sub>kj</sub>(x) = Q<sub>ij</sub>(x) mod P<sub>kj</sub>(x)

于是可以利用分治求解每个 Q<sub>kk</sub>(x):

假设 n 是2的幂，传入 Q<sub>ij</sub>(x)
+ 如果 j == i，直接求得Q<sub>ii</sub>
+ 否则，求出 Q<sub>i,(i+j)/2</sub>(x) 和 Q<sub>(i+j)/2+1,j</sub>(x)，变成两个规模减半的子问题，故总时间为 O(nlg<sup>2</sup>n)

对于如何计算多项式带余除法的余式，有如下方法：
+ 对于A(x)，求出 DFT(A)
+ 对于P<sub>ij</sub>(x)，可以在O(j-i+1)时间内求出它的系数表示，
