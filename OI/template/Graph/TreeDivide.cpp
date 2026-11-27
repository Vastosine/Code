#ifndef __TREE_DIVIDE__
#define __TREE_DIVIDE__

#include "../init.cpp"
#include <unordered_set>
#include <vector>

class TreeDivide {
  public:
    TreeDivide(szt n) : n(n), e(n), siz(n), fa(n), vis(n), dis(n) {}

    void addEdge(szt u, szt v, ll w = 1) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    szt getCentroid(szt s = 1) {
        vst o(1, s);
        fa[s] = s;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            siz[u] = 1;
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v)) {
                    o.push_back(v);
                    fa[v] = u;
                }
            }
        }
        for (szt i = o.size() - 1; i; i--) {
            szt u = o[i];
            siz[fa[u]] += siz[u];
        }
        szt N = siz[s];
        bool change;
        do {
            change = false;
            for (auto &[v, w] : e[s]) {
                if (isSon(s, v) && siz[v] > N / 2) {
                    change = true;
                    s = v;
                    break;
                }
            }
        } while (change); 
        return s;
    }
    
    szt run(szt start = 1) {
        vis.assign(n, 0);
        vst o(1, getCentroid(start));
        szt ans = 0;
        for (szt i = 0; i < o.size(); i++) {
            szt s = o[i];
            vis[s] = 1;
            ans += calculate(s);
            for (auto &[v, w] : e[s]) {
                if (!vis[v]) o.push_back(getCentroid(v));
            }
        }
        return ans;
    }

    virtual szt calculate(szt rt) {
        calcInit(rt);
        szt ans = self(rt);
        for (auto &[s, w] : e[rt]) {
            if (!vis[s]) {
                fa[s] = rt;
                ans += calcSub(s, w);
            }
        }
        return ans;
    }

    virtual void calcInit(szt) {};
    virtual szt self(szt) { return 0; }
    virtual szt calcSub(szt s, ll d) = 0;

    vst getSubOrder(szt s, ll d) {
        vst o(1, s);
        dis[s] = d;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v)) dis[v] = dis[u] + w, o.push_back(v), fa[v] = u;
            }
        }
        return o;
    }

  protected:
    bool isSon(szt u, szt v) const { return !vis[v] && fa[u] != v; }

    szt n;
    vector<vector<pair<szt, ll>>> e;
    vst siz, fa;
    vb vis;
    vll dis;
};

class Sample : public TreeDivide {
  public:
    Sample(szt n) : TreeDivide(n) {}
    void calcInit(szt) override { all.assign(3, 0), all[0] = 1; }
    szt self(szt) override { return 1; }

    szt calcSub(szt s, ll d) override {
        cur.assign(3, 0);
        vst o = getSubOrder(s, d);
        szt ans = 0;
        for (szt u : o) {
            cur[(szt) dis[u] % 3]++;
        }
        for (szt k = 0; k < 3; k++) {
            ans += all[k] * cur[(3 - (szt) k) % 3] * 2;
            all[k] += cur[k];
        }
        return ans;
    }
  private:
    vst all, cur;
};

class SampleTreeDivide : public TreeDivide {
  public:
    SampleTreeDivide(szt n) : TreeDivide(n) {}

    void calcInit(szt) override {
        has.clear();
        has.insert(0);
    }

    szt calcSub(szt s, ll d) override {
        vst o = getSubOrder(s, d);
        for (szt u : o) {
            szt x = (szt) dis[u];
            for (szt y : query) {
                if (y >= x && has.find(y - x) != has.end()) ans.insert(y);
            }
        }
        for (szt u : o) has.insert((szt) dis[u]);
        return 0;
    }

    void run() {
        TreeDivide::run();
        string res;
        for (szt x : query) cout << (ans.find(x) == ans.end() ? "NAY" : "AYE") << "\n";
    }
    vst query;
  private:
    unordered_set<szt> has, ans;
};

#endif