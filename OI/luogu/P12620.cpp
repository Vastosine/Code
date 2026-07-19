#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef long long ll;

vector<int> primes;

vector<int> getPrimes(int maxn) {
    vector<bool> isPrime(maxn + 1, 1);
    for (int i = 2; i * i <= maxn; i++) {
        if (!isPrime[i]) continue;
        for (int j = i * 2; j <= maxn; j += i) {
            isPrime[j] = 0;
        }
    }
    vector<int> prime;
    for (int i = 2; i <= maxn; i++) {
        if (isPrime[i]) {
            prime.push_back(i);
        }
    }
    return prime;
}

int main() {
    primes = getPrimes(100000);
    for (int i : primes) {
        cout << i << "\n";
    }
}