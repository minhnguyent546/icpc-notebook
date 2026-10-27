#include "../utilities/template.h"
#include "../../src/data-structures/fenwick_tree.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 1e3;
    const int Q = (int) 1e4;
    // non-negative values keep prefix sums sorted, which lower_bound requires
    const int VAL_MIN = 0, VAL_MAX = (int) 1e9;
    for (int t = 0; t < 20; ++t) {
        int n = rand(1, N);
        int q = rand(1, Q);
        debug(n, q)
        vector<long long> arr(n);
        Fenwick<long long> tree(n);
        while (q--) {
            int type = rand(0, 2);
            if (type == 0) {
                int i = rand(0, n - 1);
                int amt = rand(VAL_MIN, VAL_MAX);
                arr[i] += amt;
                tree.add(i, amt);
            }
            else if (type == 1) {
                int l = rand(0, n - 1);
                int r = rand(l, n - 1);
                long long sum = 0;
                for (int i = l; i <= r; ++i) {
                    sum += arr[i];
                }
                assert(sum == tree.query(l, r));
            }
            else {
                long long total = accumulate(arr.begin(), arr.end(), 0LL);
                long long val = rand(0LL, total + 1);
                // first index whose prefix sum is >= val, or n if there is none
                int expected = n;
                long long sum = 0;
                for (int i = 0; i < n; ++i) {
                    sum += arr[i];
                    if (sum >= val) {
                        expected = i;
                        break;
                    }
                }
                assert(expected == tree.lower_bound(val));
            }
        }
    }
    cout << "Passed!" << '\n';
    return 0;
}
