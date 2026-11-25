// 数位统计模板（数位和 / 数位计数）
// 核心：sd(x) = 0..x 的数位和。含 0，但 0 的数位和是 0，不影响结果。
// 推导不要临场做。这四行背下来，第 4 行四个项各自独立可验，不存在互相补偿。
//
//   sd(x)  [x >= 0]
//     d    = 10^(位数-1)              x 的最高位权
//     hi   = x / d                    最高位数字
//     rem  = x % d                    去掉最高位后的余数
//     pre  = sd(d-1) = 45*L*10^(L-1)  0..d-1 的数位和（全是 9 的那一段，闭式）
//
//   [0, d-1]                 → pre
//   [t*d, (t+1)*d-1] t=1..hi-1 → 每块 t*d + pre
//   [hi*d, hi*d+rem]         → hi*(rem+1) + sd(rem)
//
//   合并：hi*pre + hi*(hi-1)/2*d + hi*(rem+1) + sd(rem)
//
// 已对拍：x = 0..3e6 全比暴力；x = 10^1..10^15-1 全比闭式 45*L*10^(L-1)。

#ifndef DIGIT_SUM_H
#define DIGIT_SUM_H
typedef long long ll;

// [0, x] 的数位和；x < 0 返回 0
inline ll sd(ll x) {
    if (x <= 0) return 0;
    ll d = 1, L = 0;
    while (d * 10 <= x) d *= 10, L++;
    ll hi = x / d, rem = x % d;
    ll pre = 45 * L * (d / 10);  // = sd(10^L - 1) = 45*L*10^(L-1)
    return hi * pre + hi * (hi - 1) / 2 * d + hi * (rem + 1) + sd(rem);
}

// [1, x] 的数位和
inline ll sd1(ll x) { return sd(x); }

// 迭代版：同一公式，不递归。位数 <= 19，栈深可以忽略，两版都对拍过。
inline ll sd_iter(ll x) {
    ll r = 0;
    for (ll p = 1; p <= x; p *= 10) {
        ll hi = x / (p * 10), d = x / p % 10, lo = x % p;
        r += hi * 45 * p + (d * (d - 1) / 2) * p + d * (lo + 1);
    }
    return r;
}

// 1..x 里数字 c (1..9) 出现的次数；c = 0 也能用（前导零不算）
inline ll cntDigit(ll x, int c) {
    ll r = 0;
    for (ll p = 1; p <= x; p *= 10) {
        ll hi = x / (p * 10), d = x / p % 10, lo = x % p;
        if (c) r += hi * p + (d > c ? p : d == c ? lo + 1 : 0);
        else {
            if (!hi) break;
            r += (hi - 1) * p + (d > c ? p : d == c ? lo + 1 : 0);
        }
    }
    return r;
}

#endif
