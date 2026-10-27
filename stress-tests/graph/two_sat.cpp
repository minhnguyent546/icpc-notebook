#include "../utilities/template.h"
#include "../../src/graph/two_sat.h"

bool lit_val(int x, int mask) {
    return x >= 0 ? (mask >> x & 1) : !(mask >> ~x & 1);
}

void hand_tests() {
    {
        TwoSat ts(3);
        ts.at_most_one({0, 1, 2});
        ts.set(0); ts.set(1);
        assert(!ts.solve());
    }
    {
        TwoSat ts(3);
        ts.at_most_one({0, 1, 2});
        ts.set(1);
        assert(ts.solve());
        auto v = ts.get_vals();
        assert(!v[0] && v[1] && !v[2]);
    }
    {
        // at most one of x0, x1, x2 is false
        TwoSat ts(3);
        ts.at_most_one({~0, ~1, ~2});
        ts.set(~2);
        assert(ts.solve());
        auto v = ts.get_vals();
        assert(v[0] && v[1] && !v[2]);
    }
    {
        // lists of size 0 and 1 add no constraint
        TwoSat ts(2);
        ts.at_most_one({});
        ts.at_most_one({0});
        ts.set(0); ts.set(1);
        assert(ts.solve());
    }
    {
        // the same literal twice forces it to be false
        TwoSat ts(1);
        ts.at_most_one({0, 0});
        ts.set(0);
        assert(!ts.solve());
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    hand_tests();
    const int ITERS = (int) 2e5;
    const int N = 7;
    for (int it = 0; it < ITERS; ++it) {
        int n = rand(1, N);
        auto rand_lit = [&]() {
            int v = rand(0, n - 1);
            return rand(0, 1) ? v : ~v;
        };
        vector<pair<int, int>> clauses(rand(0, 4));
        for (auto &[a, b] : clauses) {
            a = rand_lit(); b = rand_lit();
        }
        vector<vector<int>> lists(rand(0, 3));
        for (auto &li : lists) {
            li.resize(rand(0, 6));
            for (int &x : li) x = rand_lit();
        }
        auto satisfied = [&](int mask) {
            for (auto [a, b] : clauses) {
                if (!lit_val(a, mask) && !lit_val(b, mask)) return false;
            }
            for (auto &li : lists) {
                int cnt = 0;
                for (int x : li) cnt += lit_val(x, mask);
                if (cnt > 1) return false;
            }
            return true;
        };
        bool expected = false;
        for (int mask = 0; mask < (1 << n); ++mask) {
            expected |= satisfied(mask);
        }
        // add constraints across two solve() calls to check solve() can be called again
        TwoSat ts(n);
        int half = (int) lists.size() / 2;
        for (int i = 0; i < half; ++i) ts.at_most_one(lists[i]);
        ts.solve();
        for (auto [a, b] : clauses) ts.either(a, b);
        for (int i = half; i < (int) lists.size(); ++i) ts.at_most_one(lists[i]);
        bool got = ts.solve();
        assert(got == expected);
        if (got) {
            auto v = ts.get_vals();
            int mask = 0;
            for (int i = 0; i < n; ++i) mask |= v[i] << i;
            assert(satisfied(mask));
        }
    }
    cout << "Passed!" << '\n';
    return 0;
}
