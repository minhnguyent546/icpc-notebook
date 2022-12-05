#include "../utilities/template.h"
#include "../../src/data-structures/fenwick_tree.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 1e4;
    const int Q = (int) 1e4;
    const int VAL_MIN = 0, VAL_MAX = (int) 1e9;
    int n = rand(1, N);
    int q = rand(1, Q);
    debug(n, q)
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand(VAL_MIN, VAL_MAX);
    }
    FenwickTree tree(n);
    tree.build(arr);
    while (q--) {
        int type = rand(0, 1);
        if (type == 0) {
            int l = rand(0, n - 1);
            int r = rand(l, n - 1);
            int amt = rand(VAL_MIN, VAL_MAX);
            for (int i = l; i <= r; ++i) {
                arr[i] += amt;
            }
            tree.range_add(l, r, amt);
        }
        else {
            int l = rand(0, n - 1);
            int r = rand(l, n - 1);
            long long sum = 0;
            for (int i = l; i <= r; ++i) {
                sum += arr[i];
            }
            assert(sum == tree.range_sum(l, r));
        }
    }
    cout << "Passed!" << '\n';
    return 0;
}