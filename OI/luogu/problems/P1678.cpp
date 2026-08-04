#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::istream;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int main() {
	int m, n;
	cin >> m >> n;
	vector<int> a(m), b(n);
	cin >> a >> b;
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	long long ans = 0;
	for (int i = 0, j = 0; i < n; i++) {
		while (j + 1 < m && abs(b[i] - a[j]) >= abs(b[i] - a[j + 1])) j++;
		ans += abs(b[i] - a[j]);
	}
	cout << ans;
}