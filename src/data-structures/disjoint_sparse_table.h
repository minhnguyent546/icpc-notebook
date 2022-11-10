/**
 * Description: range query on a static array. 
 * Time: O(1) per query. 
 * Tested: stress-test.
 */
const int MOD = (int) 1e9 + 7;
struct DisjointSparseTable { // product queries. 
    int n, h;
    vector<vector<int>> dst;
    vector<int> lg;
    DisjointSparseTable(int _n) : n(_n) {
        h = 1; // in case n = 1: h = 0 !!.
        int p = 1;
        while (p < n) p *= 2, h++;
        lg.resize(p); lg[1] = 0;
        for (int i = 2; i < p; ++i) {
            lg[i] = 1 + lg[i / 2];
        }
        dst.resize(h, vector<int>(n));
    }
    void build(const vector<int> &A) {
        for (int lv = 0; lv < h; ++lv) {
            int len = (1 << lv);
            for (int k = 0; k < n; k += len * 2) {
                int mid = min(k + len, n);
                dst[lv][mid - 1] = A[mid - 1] % MOD;
                for (int i = mid - 2; i >= k; --i) {
                    dst[lv][i] = 1LL * A[i] * dst[lv][i + 1] % MOD;
                }
                if (mid == n) break;
                dst[lv][mid] = A[mid] % MOD;
                for (int i = mid + 1; i < min(mid + len, n); ++i) {
                    dst[lv][i] = 1LL * A[i] * dst[lv][i - 1] % MOD;
                }
            }
        }
    }
    int get(int l, int r) {
        if (l == r) {
            return dst[0][l];
        }
        int i = lg[l ^ r];
        return 1LL * dst[i][l] * dst[i][r] % MOD;
    }
};