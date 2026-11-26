#ifndef __INIT__
#define __INIT__

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std; 

typedef long long ll; 
typedef vector<bool> vb; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
typedef vector<ll> vll; 
typedef pair<ll, ll> pll;
typedef unsigned long long szt;
typedef vector<szt> vst;
typedef pair<szt, szt> pst;

[[maybe_unused]] const ll INF = 1ll << 60; 
[[maybe_unused]] const int inf = 0x3fffffff;

template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

#endif