// 组合数模板：三种情形分开，前提写进名字 + assert，不写进注释
//
// 起因：qpow.cpp 的 Cnk(n,k,m) 只在「m 是质数 且 n < m」时正确，两个前提都没进接口。
//       帕斯卡对拍（stress/test_cnk.cpp）：
//         m = 1e9+7  bad=0
//         m = 5       bad=210   first_bad_n=5      ← 质数但 n >= m
//         m = 4       bad=203   first_bad_n=2      ← 合数
//         Cnk(7,2,5) = 0   want 1
//         Cnk(4,2,4) = 0   want 2
//
// 三条规则：
//   ① 「n < p」由 assert 保证，不由调用者记着
//   ② 「p 必须质数」由函数名保证（Prime / Lucas），不靠注释
//   ③ 拿不到的情形（任意模数）不要写半个，写占位并 assert(false)
//
// 【第二次修正】初版 CnkLucas::init(1e9+7) 会去建 1e9+6 的阶乘表（8 GB）——
//   「Lucas 的表必须装得下 p−1」这个前提没进接口。现在拆成三个函数，
//   各带自己的容量前提：
//     CnkPrime    p 质数，n < p             表到 maxN（调用者给）
//     CnkLucas    p 质数且 p <= MAXP_LUCAS  表到 p−1，内部自己建
//     CnkSmallK   p 质数且 p > k，n 可以任意大   不需要表，O(k)
//
// 对拍：stress/test_comb.cpp

// 【第三次修正】原版用了 __int128。它在 64 位目标可用，但 32 位目标没有：
//     g++ -dM -E -x c++ /dev/null | grep INT128   → 64 位有 __SIZEOF_INT128__，-m32 没有
//   CF 的 "C++17 (GCC 7-32)" 是 32 位目标 → __int128 直接编译错误。
//   ⟹ 本文件不用 __int128；代价是乘法必须保证 m * m 不溢出 ll：
//        要求 模数 m <= 3e9   （m^2 <= 9e18 < 2^63-1）
//      本文件所有模数都是这个量级，够用。
//
// 对拍：stress/test_comb.cpp / stress/test_comb_guard.cpp

#ifndef COMB_H
#define COMB_H
#include <cassert>
#include <vector>
typedef long long ll;

// 前提：m <= 3e9，保证 r * x 不溢出 ll
inline ll comb_pow(ll x, ll n, ll m) {
    x = (x % m + m) % m;
    ll r = 1;
    while (n) {
        if (n & 1) r = r * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return r % m;
}

// ---------- 情形 1：p 质数，n < p（最常用） ----------
struct CnkPrime {
    static inline int p = 0;
    static inline std::vector<ll> fac, ifac;

    // 前提：mod 是质数、maxN < mod。两者都 assert。
    static void init(int maxN, int mod) {
        assert(maxN >= 0);
        assert(mod > 1);
        assert(maxN < mod && "CnkPrime 要求 maxN < p；n 会到 p 以上时用 CnkLucas");
        p = mod;
        fac.assign(maxN + 1, 1);
        ifac.assign(maxN + 1, 1);
        for (int i = 1; i <= maxN; i++) fac[i] = fac[i - 1] * i % p;
        ifac[maxN] = comb_pow(fac[maxN], p - 2, p);
        for (int i = maxN; i >= 1; i--) ifac[i - 1] = ifac[i] * i % p;
    }

    static ll get(int n, int k) {
        assert(p && "先 init");
        assert(n >= 0 && n < (int)fac.size() && "n 超出 init 的表");
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % p * ifac[n - k] % p;
    }

    static bool fits(int n) { return p && n >= 0 && n < (int)fac.size(); }
};

// ---------- 情形 2：p 质数，p 不太大，n / k 任意 ----------
// 前提：p <= MAXP_LUCAS，否则阶乘表和内存都放不下 —— 由 init 的 assert 挡住。
struct CnkLucas {
    static constexpr int MAXP_LUCAS = 2000000;   // 表 2e6 个 ll ≈ 16 MB
    static inline int p = 0;

    static void init(int mod) {
        assert(mod > 1);
        assert(mod <= MAXP_LUCAS &&
               "CnkLucas 要求 p <= 2e6（要建到 p-1 的表）；p 很大时用 CnkPrime 或 CnkSmallK");
        p = mod;
        CnkPrime::init(mod - 1, mod);
    }

    static ll get(ll n, ll k) {
        assert(p && "先 init");
        if (k < 0 || k > n) return 0;
        ll r = 1;
        while (n || k) {
            ll ni = n % p, ki = k % p;
            if (ki > ni) return 0;
            r = r * CnkPrime::get((int)ni, (int)ki) % p;
            n /= p, k /= p;
        }
        return r;
    }
};

// ---------- 情形 3：n 任意大、k 很小、p 质数且 p > k ----------
// 不需要表：C(n,k) = n(n-1)...(n-k+1) / k!，k! 在 mod p 下可逆（前提 p > k）。
inline ll CnkSmallK(ll n, ll k, ll p) {
    if (k < 0 || k > n) return 0;
    assert(p > k && "CnkSmallK 要求 p > k，否则 k! 不可逆");
    assert(p <= 3000000000LL && "CnkSmallK 要求 p <= 3e9（不用 __int128，靠 ll）");
    ll num = 1, den = 1;
    for (ll i = 0; i < k; i++) {
        num = num * ((n - i) % p) % p;
        den = den * ((i + 1) % p) % p;
    }
    return num * comb_pow(den, p - 2, p) % p;
}

// ---------- 情形 4：模数任意（合数） ----------
// 需要 exLucas：分解 p 的质因子，每个 p^q 用「阶乘去掉 p 的因子」+ 中国剩余。
// 不实现 —— 写了半个比没写更危险。
inline ll CnkAny(ll, ll, ll) {
    assert(false && "CnkAny 未实现：合数模数要 exLucas；不要退回 qpow.cpp 的 Cnk");
    return 0;
}

#endif
