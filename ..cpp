#include <iostream>
#include <vector>
#define int long long

using std::cin;
using std::cout;
using std::vector;

struct SegTree {
#define ln ((size + 1) / 2)
#define rn (size / 2)
#define update data = ls->data + rs->data
	struct Node {
		int data;
		int lazy;
		int size;
		Node *ls, *rs;
		void push_down() {
			ls->data += ln * lazy;
			rs->data += rn * lazy;
			ls->lazy += lazy;
			rs->lazy += lazy;
			lazy = 0;
		}

		Node() : data(0), lazy(0), size(0), ls(nullptr), rs(nullptr) {}

		Node(const int *begin, const int *end) : Node() { build(begin, end); }
		Node(const vector<int> &data) : Node(data.begin().base(), data.end().base()) {}

		void build(const int *begin, const int *end) {
			size = end - begin;
			if (size == 1) data = *begin;
			else {
				ls = new Node(begin, begin + ln);
				rs = new Node(begin + ln, end);
				update;
			}
		}

		// [l, r)
		void add(int l, int r, int x) { 
			if (l >= size || r <= 0) return;
			if (l <= 0 && r >= size) return data += x * size, lazy += x, void();
			push_down();
			ls->add(l, r, x);
			rs->add(l - ln, r - ln, x);
			update;
		}

		int query(int l, int r) {
			if (l >= size || r <= 0) return 0;
			if (l <= 0 && r >= size) return data;
			push_down();
			return ls->query(l, r) + rs->query(l - ln, r - ln);
		}
	};
	Node root;
	SegTree(const vector<int> &data) : root(data) {}
	void add(int l, int r, int x) { root.add(l, r, x); }
	int query(int l, int r) { return root.query(l, r); }
};

signed main() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int &i : a) cin >> i;
	SegTree s(a);
	while (m--) {
		int op, l, r, x;
		cin >> op >> l >> r;
		l--;
		if (op == 1) cin >> x, s.add(l, r, x);
		else cout << s.query(l, r) << "\n";
	}
}