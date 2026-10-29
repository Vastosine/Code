#include <bits/stdc++.h>
using namespace std;
#define For(i, a, b) for (int i = (a); i <= (b); i++)
const int N = 1e6 + 10;
int n, m, tot, last;
int rt[N << 1];
struct Node {
	int ls, rs, to, size;
} f[N << 4];
void build(int &k, int l, int r) {
	k = ++tot;
	if (l == r)
		return f[k].to = l, f[k].size = 1, void();
	int mid = (l + r) >> 1;
	build(f[k].ls, l, mid);
	build(f[k].rs, mid + 1, r);
}
void merge(int &k, int k2, int l, int r, const Node &x, const Node &y) {
	k = ++tot;
	if (l == r) {
		f[k].to = y.to;
		f[k].size = f[k2].size;
		return;
	}
	int mid = (l + r) >> 1;
	if (mid >= x.to)
		f[k].rs = f[k2].rs, merge(f[k].ls, f[k2].ls, l, mid, x, y);
	else
		f[k].ls = f[k2].ls, merge(f[k].rs, f[k2].rs, mid + 1, r, x, y);
}
void add_size(int &k, int k2, int l, int r, int y, int now) {
	k = ++tot;
	if (l == r) {
		f[k].to = f[k2].to;
		f[k].size = now;
		return;
	}
	int mid = (l + r) >> 1;
	if (mid >= y)
		f[k].rs = f[k2].rs, add_size(f[k].ls, f[k2].ls, l, mid, y, now);
	else
		f[k].ls = f[k2].ls, add_size(f[k].rs, f[k2].rs, mid + 1, r, y, now);
}
Node query(int k, int l, int r, int x, int now_rt) {
	if (l == r) {
		if (f[k].to == l || f[k].to == 0)
			return f[k];
		return query(now_rt, 1, n, f[k].to, now_rt);
	}
	int mid = (l + r) >> 1;
	if (mid >= x)
		return query(f[k].ls, l, mid, x, now_rt);
	else
		return query(f[k].rs, mid + 1, r, x, now_rt);
}
int read() {
    int x;
    cin >> x;
    return x;
}
void write(int x) {
    cout << x;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
	n = read(), m = read();
	build(rt[0], 1, n);
	For(i, 1, m) {
		int op, x, k, y;
		op = read(), k = read(), x = read();
		rt[i] = rt[k];
		if (op == 1) {
			y = read();
			Node tx = query(rt[k], 1, n, x, rt[k]);
			Node ty = query(rt[k], 1, n, y, rt[k]);
			if (tx.to == 0 || ty.to == 0 || tx.to == ty.to)
				continue;
			if (tx.size < ty.size)
				swap(tx, ty);
			merge(last, rt[k], 1, n, ty, tx), add_size(rt[i], last, 1, n, tx.to, tx.size + ty.size);
		} else if (op == 2) {
			Node tx = query(rt[k], 1, n, x, rt[k]);
			if (!tx.to)
				continue;
			Node root = query(rt[k], 1, n, tx.to, rt[k]);
			Node tmp_0;
			tmp_0.ls = tmp_0.rs = tmp_0.size = tmp_0.to = 0;
			add_size(last, rt[k], 1, n, root.to, root.size - 1);
			merge(rt[i], last, 1, n, tx, tmp_0);
		} else if (op == 3) {
			y = read();
			Node tx = query(rt[k], 1, n, x, rt[k]);
			Node ty = query(rt[k], 1, n, y, rt[k]);
			if (tx.to == 0 || ty.to == 0 || tx.to == ty.to)
				continue;
			Node root_tx = query(rt[k], 1, n, tx.to, rt[k]);
			add_size(last, rt[k], 1, n, root_tx.to, root_tx.size - 1);
			Node self;
			self.to = x;
			self.size = 1;
			merge(rt[i], last, 1, n, tx, self);
			Node cur_x = query(rt[i], 1, n, x, rt[i]);
			Node cur_ty = query(rt[i], 1, n, y, rt[i]);
			if (cur_x.to == 0 || cur_ty.to == 0 || cur_x.to == cur_ty.to)
				continue;
			if (cur_x.size < cur_ty.size)
				swap(cur_x, cur_ty);
			merge(last, rt[i], 1, n, cur_ty, cur_x);
			add_size(rt[i], last, 1, n, cur_x.to, cur_x.size + cur_ty.size);
		} else if (op == 4) {
			y = read();
			Node tx = query(rt[k], 1, n, x, rt[k]);
			Node ty = query(rt[k], 1, n, y, rt[k]);
			if (!tx.to || !ty.to)
				puts("No");
			else if (tx.to == ty.to)
				puts("Yes");
			else
				puts("No");
		} else {
			Node tx = query(rt[k], 1, n, x, rt[k]);
			if (!tx.to)
				puts("0");
			else {
				write(tx.size);
				puts("");
			}
		}
	}
	return 0;
}