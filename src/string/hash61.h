struct Hash61 {
    static const uint64_t MOD = (1LL << 61) - 1;
    static uint64_t BASE;
    static vector<uint64_t> pw;
    uint64_t addmod(uint64_t a, uint64_t b) const {
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    uint64_t submod(uint64_t a, uint64_t b) const {
        a += MOD - b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    uint64_t mulmod(uint64_t a, uint64_t b) const {
        uint64_t low1 = (uint32_t) a, high1 = (a >> 32);
        uint64_t low2 = (uint32_t) b, high2 = (b >> 32);

        uint64_t low = low1 * low2;
        uint64_t mid = low1 * high2 + low2 * high1;
        uint64_t high = high1 * high2;

        uint64_t ret = (low & MOD) + (low >> 61) + (high << 3) + (mid >> 29) + (mid << 35 >> 3) + 1; 
        // ret %= MOD:
        ret = (ret >> 61) + (ret & MOD);
        ret = (ret >> 61) + (ret & MOD);
        return ret - 1;
    }
    void ensure_pw(int m) {
        int sz = (int) pw.size();
        if (sz >= m) return;
        pw.resize(m);
        for (int i = sz; i < m; ++i) {
            pw[i] = mulmod(pw[i - 1], BASE);
        }
    }

    vector<uint64_t> pref;
    int n;
    template<typename T> Hash61(const T &s) { // strings or arrays. 
        n = (int) s.size();
        ensure_pw(n);
        pref.resize(n + 1);
        pref[0] = 0;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = addmod(mulmod(pref[i], BASE), s[i]);
        }
    }
    inline uint64_t operator()(const int from, const int to) const {
        assert(0 <= from && from <= to && to < n);
        // pref[to + 1] - pref[from] * pw[to - from + 1]
        return submod(pref[to + 1], mulmod(pref[from], pw[to - from + 1]));
    }
};
rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
uint64_t Hash61::BASE = (MOD >> 2) + rng() % (MOD >> 1);
vector<uint64_t> Hash61::pw = vector<uint64_t>(1, 1);