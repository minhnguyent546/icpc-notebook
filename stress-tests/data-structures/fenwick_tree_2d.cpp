#include "../utilities/template.h"
#include "../../src/data-structures/fenwick_tree_2d.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 1e3;
    const int M = (int) 1e3;
    const int Q = (int) 1e3;
    const int VAL_MIN = 0,  VAL_MAX = (int) 1e9;
    int n = rand(1, N);
    int m = rand(1, M);
    int q = rand(1, Q);
    vector<vector<long long>> arr(n, vector<long long>(m));
    FenwickTree2D tree(n, m);
    while (q--) {
        int type = rand(0, 1);
        if (type == 0) {
            int r = rand(0, n - 1), rr = rand(0, n - 1);
            int c = rand(0, m - 1), cc = rand(0, m - 1);
            if (r > rr) swap(r, rr);
            if (c > cc) swap(c, cc);
            int amt = rand(VAL_MIN, VAL_MAX);
            for (int i = r; i <= rr; ++i) {
                for (int j = c; j <= cc; ++j) {
                    arr[i][j] += amt;
                }
            }
            tree.range_add(r, c, rr, cc, amt);
        }
        else {
            int r = rand(0, n - 1), rr = rand(0, n - 1);
            int c = rand(0, m - 1), cc = rand(0, m - 1);
            if (r > rr) swap(r, rr);
            if (c > cc) swap(c, cc);
            long long sum = 0;
            for (int i = r; i <= rr; ++i) {
                for (int j = c; j <= cc; ++j) {
                    sum += arr[i][j];
                }
            }
            long long x = tree.range_sum(r, c, rr, cc);
            // debug(sum, x)
            assert(sum == x);
        }
    }
    cout << "Passed!" << '\n';
    return 0;
}