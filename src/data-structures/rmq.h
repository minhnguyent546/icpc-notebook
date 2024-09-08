/**
 * Description: range minimum queries on a static array.
 * Time: $<O(N\log{N}), O(1)>$.
 */

template<typename T>
struct RMQ {
    int n;
    vector<vector<T>> rmq;
    RMQ() {}
    RMQ(const vector<T> &arr) { build(arr); }
    void build(const vector<T> &arr) {
        n = (int) arr.size();
        int max_log = __lg(n) + 1;
        rmq.resize(max_log);
        rmq[0] = arr;
        for (int j = 1; j < max_log; ++j) {
            rmq[j].resize(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T get(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        int i = __lg(r - l + 1);
        return min(rmq[i][l], rmq[i][r - (1 << i) + 1]);
    }
};
