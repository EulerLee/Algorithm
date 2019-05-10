#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstdlib>
#include <set>
#include <queue>
#include <bitset>
#include <complex>

struct Segment {
    std::complex<int> sta;
    std::complex<int> end;
    Segment(std::complex<int> s = std::complex<int>(), std::complex<int> e = std::complex<int>()) : sta(s), end(e) {}
};

bool pointOn(std::complex<int> node, const Segment &seg)
{
    int x1 = node.real() - seg.sta.real();
    int y1 = node.imag() - seg.sta.imag();
    int x2 = node.real() - seg.end.real();
    int y2 = node.imag() - seg.end.imag();
    return x1*y2 == x2*y1;
}

inline void comSwap(std::complex<int> &c)
{
    c = std::complex<int>(c.imag(), c.real());
}

bool CCW(const Segment &AB, const Segment &CD)
{
    std::complex<int> ac = CD.sta - AB.sta;
    std::complex<int> ad = CD.end - AB.sta;
    std::complex<int> bc = CD.sta - AB.end;
    std::complex<int> bd = CD.end - AB.end;
    bool ans = (ac.real()*ad.imag() - ad.real()*ac.imag())*(bc.real()*bd.imag() - bd.real()*bc.imag()) < 0;
    if(!ans) return false;
    comSwap(ac);
    comSwap(bc);
    comSwap(ad);
    comSwap(bd);
    ans = ans && ((ac.real()*bc.imag() - bc.real()*ac.imag())*(ad.real()*bd.imag() - bd.real()*ad.imag()) < 0);
    return ans;
}

bool intersect(const Segment &AB, const Segment &CD)
{
    // 判断点在直线上，包括部分重合的情况
    if(pointOn(AB.sta, CD) || pointOn(AB.end, CD)) {
        return true;
    }
    return CCW(AB, CD);
}

int main()
{
    std::vector<std::complex<int>> node(4, std::complex<int>());
    for(int i = 0; i < 4; ++i) {
        std::cin >> node[i];
    }
    Segment AB(node[0], node[1]);
    Segment CD(node[2], node[3]);
    std::cout << intersect(AB, CD) << std::endl;
}
