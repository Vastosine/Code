#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Op {
    ll (*f)(ll, ll);
    ll e;
    template <class F> Op(F f, ll e = 0) : f(f), e(e) {}
    ll operator()(ll x, ll y) const { return f(x, y); }
};
static const Op MAXOP = Op([](ll x, ll y) { return max(x, y); }, -(1ll << 60));

int main(int argc, char **argv) {
    const int N = 1 << 26;
    static int a[1 << 26];
    for (int i = 0; i < N; i++) a[i] = (int)((i * 2654435761u) & 0xffff);
    ll s = -1;
    auto t0 = chrono::steady_clock::now();
    if (argv[1][0] == 'd') {
        for (int i = 0; i < N; i++) s = max(s, (ll)a[i]);
    } else {
        for (int i = 0; i < N; i++) s = MAXOP(s, (ll)a[i]);
    }
    auto t1 = chrono::steady_clock::now();
    printf("%c  %.3f ns/call  %lld\n", argv[1][0],
           chrono::duration<double, std::nano>(t1 - t0).count() / N, s);
}
