#include <iostream>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::min;
typedef long long ll;

vector<int> getPrimes(int maxn) {
    vector<bool> isPrime(maxn + 1, 1);
    for (int i = 2; i * i <= maxn; i++) {
        if (!isPrime[i]) continue;
        for (int j = i * 2; j <= maxn; j += i) {
            isPrime[j] = 0;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= maxn; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

vector<int> PRIMES;

ll phi(ll x) {
    ll y = x;
    for (int p : PRIMES) {
        if (p > x) break;
        if (x % p) continue;
        y = y / p * (p - 1);
        while (!(x % p)) {
            x /= p;
        }
    }
    return y;
}

// void test() {
//     freopen("con", "r", stdin);
//     freopen("con", "w", stdout);
//     ll m, n;
//     cin >> m >> n;
//     ll x, y;
// 	x = phi(m * m);
//     y = phi(n * n);
// 	cout << x << " " << y << "\n";
// 	ll z = std::gcd(x, y);
//     cout << x / z << " " << y / z << "\n";
//     test();
// }

set<int> p_set;
vector<int> primes;

void add_to_set(int);

void add_to_set(int x) {
    for (int p : PRIMES) {
        if (p > x) break;
        if (x % p) continue;
        while (!(x % p)) {
            x /= p;
        }
        if (p_set.find(p) == p_set.end()) {
            p_set.insert(p);
            add_to_set(p - 1);
        }
    }
}

struct Number {
    vector<int> data;
    int pn;
    Number(int x = 1) {
        pn = primes.size();
        data.assign(pn, 0);
        for (int i = 0; i < pn; i++) {
            if (primes[i] > x) break;
            while (!(x % primes[i])) {
                data[i]++;
                x /= primes[i];
            }
        }
    }

    int &operator[](int i) {
        return data[i];
    }

    int operator[](int i) const {
        return data[i];
    }

    Number operator+(const Number &num) const {
        Number ans;
        for (int i = 0; i < pn; i++) {
            ans[i] = data[i] + num[i];
        }
        return ans;
    }

    Number operator+=(const Number &num) {
        return *this = *this + num;
    }

    Number operator*(int k) {
        Number ans;
        for (int i = 0; i < pn; i++) {
            ans[i] = data[i] * k;
        }
        return ans;
    }

    operator ll() {
        ll ans = 1;
        for (int i = 0; i < pn; i++) {
            for (int j = 0; j < data[i]; j++) {
                ans *= primes[i];
            }
        }
        return ans;
    }
};

vector<Number> next;

void init(int a, int b) {
    PRIMES = getPrimes(10000);
    add_to_set(a);
    add_to_set(b);
    for (int i : p_set) {
        // cout << i << "\n";
        primes.push_back(i);
    }
    for (int i : primes) {
        next.push_back(i - 1);
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    init(a, b);
    Number x(a), y(b), m, n;
    for (int i = p_set.size() - 1; i >= 0; i--) {
        int z = min(x[i], y[i]);
        x[i] -= z;
        y[i] -= z;
        if (x[i] == y[i]) continue;
        if (x[i] > 0) {
            m[i] = x[i] / 2 + 1;
            y[i] += 2 * m[i] - 1;
            y += next[i];
        } else {
            n[i] = y[i] / 2 + 1;
            x[i] += 2 * n[i] - 1;
            x += next[i];
        }
        i++;
    }
    cout << ll(m) << " " << ll(n) << "\n";
}