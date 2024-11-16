/**
 * Description: Given a polynomial $f$ of degree $k$ and an array containing values
 * $f(0), f(1), \ldots, f(k)$, the calc method returns value of $f$ for a given $x$ (i.e. $f(x)$).
 * Status: need testing
 * Time: $O(N)$.
 */

#include "../modmul.h"

namespace lagrange {
const int N = (int) 1e6 + 5;
const int MOD = (int) 1e9 + 7;
int fact[N + 1], inv_fact[N + 1];
void precompute(int n = N) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }
    inv_fact[n] = modpow(fact[n], MOD - 2, MOD);
    for (int i = n; i > 0; --i) {
        inv_fact[i - 1] = 1LL * i * inv_fact[i] % MOD;
    }
}
int calc(const vector<int> &f, long long x) {
    int sz = (int) f.size();
    if (x < sz) return f[x];
    x %= MOD;
    vector<long long> pref(sz), suf(sz + 1);
    pref[0] = suf[sz] = 1;
    for (int i = 1; i < sz; ++i) {
        pref[i] = 1LL * (x - i) * pref[i - 1] % MOD;
    }
    for (int i = sz - 1; i >= 0; --i) {
        suf[i] = 1LL * (x - i) * suf[i + 1] % MOD;
    }
    int res = 0;
    for (int i = 1; i < sz; ++i) {
        int cur = 1LL * f[i] * pref[i - 1] % MOD * suf[i + 1] % MOD
                * inv_fact[sz - i - 1] % MOD * inv_fact[i - 1] % MOD;
        if ((sz - i - 1) & 1) {
            res -= cur;
        } else {
            res += cur;
        }
        if (res < 0) res += MOD;
        else if (res >= MOD) res -= MOD;
    }
    return res;
}
} // namespace lagrange
