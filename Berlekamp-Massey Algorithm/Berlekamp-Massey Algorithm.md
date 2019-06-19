## Berlekamp-Massey 算法
#### 线性递推关系
给定一个序列（可以是无限的）a0, a1, a2, ...，如果该序列满足：</br>
对于任意i > m, a<sub>i</sub> = &Sigma;<sup>m</sup><sub>j=1</sub> a<sub>i-j</sub>p<sub>j</sub>
</br>那么我们称该序列满足m阶线性递推关系 p1, p2, p3, ..., p<sub>m</sub>

#### 目的
计算最短线性递归关系(m最小)。最重要的部分是找到一个序列x，使得：
>在位置t之前有：&Sigma;<sup>m</sup><sub>j=1</sub> a<sub>i-j</sub>x<sub>j</sub> = 0

>位置t有：&Sigma;<sup>m</sup><sub>j=1</sub> a<sub>i-j</sub>x<sub>j</sub> = 1

这样就可以通过将原序列加减x，调整t位置上的值，从而让递推关系匹配序列。

假设某次匹配失败的位置为s，那么s之前的位置都是成功的，此时的递推关系为p，那么新序列 q = {1} &ominus; p = {1, -p1, -p2, ..., -pm} 满足：
>在位置s+1之前有：&Sigma;<sup>m</sup><sub>j=1</sub> a<sub>i-j</sub>q<sub>j</sub> = 0

>位置s+1有：&Sigma;<sup>m</sup><sub>j=1</sub> a<sub>i-j</sub>q<sub>j</sub> = a<sub>t</sub> - v<sub>t</sub>;     其中v<sub>t</sub>表示原递推序列在t位置上的值

通过在q序列的开始加上适当数量的0, 就可以得到需要位置上的x序列，0的数量为 t - s - 1


#### 算法
维护一个递推关系序列 p，最开始为空 {}。
每当递推关系与序列不匹配的时候，设位置s上不同，转而考虑上次不同发生之前的 p（不包括上一次），其不匹配的位置记为t。例如：
+ a = {1, 2, 5}     p0 = {}
    + a0不同，修改 p1 = {0}，使得a0未定义，满足
    + a1不同（递推序列的估计为0），上上次的p只有p0,故x*(a0) = {1} &ominus; p0 = {1}，位置为0，当前位置为1, 故需要加上0个0, x = {1}，则 p2 = p1 + x*(a1 - v1) = {2}
    + a2不同（估计值为4）：
        + 按照p0：x = {0, 1}, p3 = p2 + x*(a2 - v2) = {2, 1}
        + 按照p1：x*(a1 - v1) = {1} &ominus; p1 = {1, -0} = {1, 0}, p3 = p2 + x/(a1 - v1) * (a2 - v2) = {2 + 1/2, 0}
