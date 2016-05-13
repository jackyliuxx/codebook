struct Bigraph {
    int x_size, y_size;
    vector<vector<int>> x_edge, y_edge;
    vector<int> mx, my;
    Bigraph(int xsz, int ysz) : x_size(xsz), y_size(ysz), x_edge(xsz), y_edge(ysz), mx(xsz), my(ysz) {}
    void add_edge(int x, int y) {
        x_edge[x].push_back(y);
        y_edge[y].push_back(x);
    }
    bool match_dfs(int x, vector<bool> &walked) {
        for (auto y : x_edge[x]) {
            if (!walked[y]) {
                walked[y] = true;
                if (my[y] == -1 || match_dfs(my[y], walked)) {
                    mx[x] = y;
                    my[y] = x;
                    return true;
                }
            }
        }
        return false;
    }
    vector<pair<int, int>> match() {
        mx.assign(x_size, -1);
        my.assign(y_size, -1);
        for (int x = 0; x < x_size; ++x) {
            vector<bool> walked(y_size, false);
            match_dfs(x, walked);
        }
        vector<pair<int, int>> m;
        for (int x = 0; x < x_size; ++x)
            if (mx[x] != -1)
                m.push_back({x, mx[x]});
        return m;
    }
};
