struct Bigraph {
    int a_size, b_size;
    vector<vector<int>> a_edge, b_edge;
    Bigraph(int asz, int bsz) : a_size(asz), b_size(bsz), a_edge(asz), b_edge(bsz) {}
    void add_edge(int a, int b) {
        a_edge[a].push_back(b);
        b_edge[b].push_back(a);
    }
    bool match_dfs(int x, vector<int> &mx, vector<int> &my, vector<bool> &walked) {
        for (auto y : a_edge[x]) {
            if (!walked[y]) {
                walked[y] = true;
                if (my[y] == -1 || match_dfs(my[y], mx, my, walked)) {
                    mx[x] = y;
                    my[y] = x;
                    return true;
                }
            }
        }
        return false;
    }
    vector<pair<int, int>> match() {
        vector<int> mx(a_size, -1);
        vector<int> my(b_size, -1);
        for (int x = 0; x < a_size; ++x) {
            vector<bool> walked(b_size, false);
            match_dfs(x, mx, my, walked);
        }
        vector<pair<int, int>> m;
        for (int x = 0; x < a_size; ++x)
            if (mx[x] != -1)
                m.push_back({x, mx[x]});
        return m;
    }
};
