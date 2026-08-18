template<typename T>
class BinaryTree {
  public:
    typedef unsigned long long int size_t;

    T &operator*() { return value; }
    const T &operator*() const { return value; }
    operator T() const { return value; }
    operator T&() { return value; }

    BinaryTree() : left(0), right(0), size(0), count(0), value() {}
    BinaryTree(const T &value) : left(0), right(0), size(1), count(1), value(value) {}

    template<typename F>
    void inorderTraversal(const F &f) const {
        if (left) left->inorderTraversal(f);
        for (int i = 0; i < count; i++) f(value);
        if (right) right->inorderTraversal(f);
    }

    BinaryTree *insert(const T &x) {
        size++;
        if (!count) return value = x, count = size = 1, this;
        if (x == value) return count++, this;
        BinaryTree *&p = x < value ? left : right;
        return p ? p->insert(x) : p = new BinaryTree(x), this;
    }

    const BinaryTree *operator[](size_t n) const {
		auto ln = left_size();
        if (n == ln) return this;
		if (n < ln) return (*left)[n];
        return (*right)[n - ln - 1];
	}

    size_t rank(const T &x) const {
        if (x == value) return left_size();
        if (x < value) return left ? left->rank(x) : 0;
        return left_size() + 1 + (right ? right->rank(x) : 0);
    }

    const BinaryTree *next(const T &x) const {
        if (value <= x) return right ? right->next(x) : 0;
        BinaryTree const *ans;
        return left && (ans = left->next(x)) ? ans : this;
    }

    const BinaryTree *pre(const T &x) const {
        if (value >= x) return left ? left->pre(x) : 0;
        BinaryTree const *ans;
        return right && (ans = right->pre(x)) ? ans : this;
    }

    // BinaryTree *begin() { return left ? left->begin() : this; }
    // BinaryTree *end() { return right ? right->end() : this; }
    // friend BinaryTree *operator++(BinaryTree *binaryTree) {}

  private:
    size_t left_size() const { return left ? left->size : 0; }
    size_t right_size() const { return right ? right->size : 0; }

    BinaryTree *left, *right;
    size_t size, count;
    T value;
};



#include <iostream>

using std::cin;
using std::cout;

int main() {
    BinaryTree<int> a;
    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
        case 1: { cout << a.rank(x) + 1 << "\n"; break; }
        case 2: { cout << **a[x - 1] << "\n"; break; }
        case 3: {
            BinaryTree<int> const* ans = a.pre(x);
            cout << (ans ? **ans : -2147483647) << "\n";
             break;
        }
        case 4: {
            BinaryTree<int> const* ans = a.next(x);
            cout << (ans ? **ans : 2147483647) << "\n";
            break;
        }
        case 5: { a.insert(x); break; }
        }
    }
}