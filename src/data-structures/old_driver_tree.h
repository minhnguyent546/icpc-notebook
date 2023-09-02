/**
 * Description: An optimized brute-force approach to deal with problem that has operation of setting an interval to the same number.
 * Note: caution TLE, only works when input is random
 */
struct ODT {
    map<int, long long> tree;
    using It = map<int, long long>::iterator;

    It split(int x) {
        It it = tree.upper_bound(x);
        assert(it != tree.begin());
        --it;
        if (it->first == x) return it;
        return tree.emplace(x, it->second).first;
    }

    void add(int l, int r, int amt) {
        It it_l = split(l);
        It it_r = split(r + 1);
        while (it_l != it_r) {
            it_l->second += amt;
            ++it_l;
        }
    }

    void set(int l, int r, int v) {
        It it_l = split(l);
        It it_r = split(r + 1);
        while (it_l != it_r) {
            tree.erase(it_l++);
        }
        tree[l] = v;
    }

    long long kth_smallest(int l, int r, int k) {
        // return the k-th smallest value in range [l..r]
        vector<pair<long long, int>> values; // pair(value, count)
        It it_l = split(l);
        It it_r = split(r + 1);
        while (it_l != it_r) {
            It prev = it_l++;
            values.emplace_back(prev->second, it_l->first - prev->first);
        }
        sort(values.begin(), values.end());
        for (auto [value, cnt] : values) {
            if (k <= cnt) return value;
            k -= cnt;
        }
        return -1;
    }
    int powmod(long long a, long long n, int mod) {}
    int sum_of_xth_power(int l, int r, int x, int mod) {
        It it_l = split(l);
        It it_r = split(r + 1);
        int res = 0;
        while (it_l != it_r) {
            It prev = it_l++;
            res = (res + 1LL * (it_l->first - prev->first) * powmod(prev->second, x, mod)) % mod;
        }
        return res;
    }
};