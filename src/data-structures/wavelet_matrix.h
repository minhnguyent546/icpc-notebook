/**
 * Description: an efficient, fast, and lightweight data structure supporting
 * queries like k-th smallest element in range or count lowers value in range.
 * Time: $O(\log(\max\{A_i\}))$
 * Status: tested on:
 *   - https://judge.yosupo.jp/problem/range_kth_smallest
 *   - https://judge.yosupo.jp/problem/static_range_count_distinct
 */

struct bit_vector {
    static constexpr int word_size = numeric_limits<uint64_t>::digits;
    vector<uint64_t> block;
    vector<uint32_t> pref; // pref is 1-indexed
    bit_vector() {}
    bit_vector(const vector<bool> &a) {
        int n = (int) a.size();
        block.resize(n / word_size + 1);
        pref.resize(n / word_size + 1);
        for (int i = 0; i < n; ++i) {
            block[i / word_size] |= static_cast<uint64_t>(a[i]) << (i % word_size);
        }
        for (int i = 0; i < (int) block.size() - 1; ++i) {
            pref[i + 1] = pref[i] + __builtin_popcountll(block[i]);
        }
    }
    uint32_t rank0(uint32_t i) const { return i - rank1(i); }
    uint32_t rank1(uint32_t i) const {
        return pref[i / word_size] +
                __builtin_popcountll(block[i / word_size] &
                        ~(~static_cast<uint64_t>(0) << (i % word_size)));
    }
};

template<typename key_type>
struct WaveletMatrix {
    int n, max_level;
    vector<bit_vector> mat;
    WaveletMatrix() {}
    WaveletMatrix(vector<key_type> a): n(a.size()) {
        key_type max_v = *max_element(a.begin(), a.end());
        max_level = __lg(max<key_type>(max_v, 1)) + 1;
        mat.resize(max_level);
        for (int h = max_level - 1; h >= 0; --h) {
            vector<bool> b(n);
            for (int i = 0; i < n; ++i) {
                b[i] = test(a[i], h);
            }
            mat[h] = bit_vector(b);
            vector<key_type> v0, v1;
            for (int i = 0; i < n; ++i) {
                if (test(a[i], h)) v1.emplace_back(a[i]);
                else v0.emplace_back(a[i]);
            }
            const auto iter = copy(v0.cbegin(), v0.cend(), a.begin());
            copy(v1.begin(), v1.end(), iter);
        }
    }
    static bool test(key_type mask, int i) {
        return (mask >> i) & static_cast<key_type>(1);
    }
    static void set(key_type &mask, int i) {
        mask |= static_cast<key_type>(1) << i;
    }
    key_type kth(int first, int last, int k) const {
        // return the k-th (0-indexed) smallest element in range [first, last)
        assert(0 <= first && first < last && last <= n);
        assert(k < last - first);
        key_type ret = 0;
        for (int h = max_level - 1; h >= 0; --h) {
            const bit_vector& v = mat[h];
            int cnt0 = v.rank0(last) - v.rank0(first);
            if (k < cnt0) {
                first = v.rank0(first);
                last = v.rank0(last);
            } else {
                set(ret, h);
                k -= cnt0;
                int zeros = v.rank0(n);
                first = zeros + v.rank1(first);
                last = zeros + v.rank1(last);
            }
        }
        return ret;
    }
    key_type count_lower(int first, int last, key_type val) const {
        // count first <= i < last s.t. a[i] < val
        assert(0 <= first && first < last && last <= n);
        if (val >= static_cast<key_type>(1) << max_level) return last - first;
        key_type ret = 0;
        for (int h = max_level - 1; h >= 0; --h) {
            const bit_vector& v = mat[h];
            if (!test(val, h)) {
                first = v.rank0(first);
                last = v.rank0(last);
            } else {
                ret += v.rank0(last) - v.rank0(first);
                int zeros = v.rank0(n);
                first = zeros + v.rank1(first);
                last = zeros + v.rank1(last);
            }
        }
        return ret;
    }
    key_type count_upper(int first, int last, key_type val) const {
        // count first <= i < last s.t. a[i] >= val
        return last - first - count_lower(first, last, val);
    }
    key_type range_count(int first, int last, key_type A, key_type B) const {
        // count first <= i < last s.t. A <= a[i] < B
        return count_lower(first, last, B) - count_lower(first, last, A);
    }
};
