struct DisjointSet {
    vector<int> f, sz;
    vector<pair<int*, int>> h;
    vector<size_t> sh;
    DisjointSet(int n) {
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
        }
        sz.assign(n, 1);
    }
    void save() {
        sh.push_back(h.size());
    }
    bool undo() {
        if (sh.empty()) return false;
        size_t lsz = sh.back();
        sh.pop_back();
        while (h.size() >  lsz) {
            *(h.back().first) = h.back().second;
            h.pop_back();
        }
        return true;
    }
    void assign(int &k, int x) {
        h.push_back({&k, k});
        k = x;
    }
    int find(int x) const {
        while (f[x] != x) x = f[x];
        return x;
    }
    void uni(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        assign(sz[x], sz[x] + sz[y]);
        assign(f[y], x);
    }
};
