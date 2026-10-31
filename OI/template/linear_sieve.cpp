#include <iostream>
#include <vector>

using namespace std;

vector<int> primes, is;
void sieve(int n) {
    is.assign(n + 1, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i);
        for (int p : primes) {
            if (i > n / p) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}   

int main() {
    sieve(1e7);
    for (int p : primes) {
        cout << p << "\n";
    }
}