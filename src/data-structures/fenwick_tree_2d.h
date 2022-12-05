/**
 * Description: range update and range sum query on a 2D array.
 */
using tree_type = long long;
struct FenwickTree2D {
    int n, m;
    vector<vector<tree_type> > fenw[4];
    FenwickTree2D(int _n, int _m) : n(_n), m(_m) {
        for (int i = 0; i < 4; i++) {
            fenw[i].resize(n, vector<tree_type>(m));
        }
    }
    void add(int u, int v, tree_type val) {
        for (int i = u; i < n; i |= (i + 1)) {
        	for (int j = v; j < m; j |= (j + 1)) {
        		fenw[0][i][j] += val;
        		fenw[1][i][j] += (u + 1) * val;
        		fenw[2][i][j] += (v + 1) * val;
        		fenw[3][i][j] += (u + 1) * (v + 1) * val;
        	}
        }
    }
    void range_add(int r, int c, int rr, int cc, tree_type val) { // [r, rr] x [c, cc].
        add(r, c, val);
        add(r, cc + 1, -val);
        add(rr + 1, c, -val);
        add(rr + 1, cc + 1, val);
    }
    tree_type prefix_sum(int u, int v) {
        tree_type res{};
        for (int i = u; i >= 0; i = (i & (i + 1)) - 1) {
        	for (int j = v; j >= 0; j = (j & (j + 1)) - 1) {
        		res += (u + 2) * (v + 2) * fenw[0][i][j];
        		res -= (v + 2) * fenw[1][i][j];
        		res -= (u + 2) * fenw[2][i][j];
        		res += fenw[3][i][j];
        	}
        }
        return res;
    }
    tree_type range_sum(int r, int c, int rr, int cc) { // [r, rr] x [c, cc].
        return prefix_sum(rr, cc) - prefix_sum(r - 1, cc) - prefix_sum(rr, c - 1) + prefix_sum(r - 1, c - 1);
    }
};