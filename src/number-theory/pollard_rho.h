/**
 * Description: Pollard's rho is an efficient algorithm for integer factorization.
 * The algorithm can run smoothly with $n$ upto $1e^{18}$, but be careful with overflow
 * for larger $n$ (e.g. $1e^{19}$).
 * Status: tested on https://judge.yosupo.jp/problem/factorize
 */

#include "modmul.h"
#include "miller_rabin.h"

uint64_t f(uint64_t x, int c, uint64_t mod) { // f(x) = (x^2 + c) % mod.
    x = modmul(x, x, mod) + c;
    if (x >= mod) x -= mod;
    return x;
}
uint64_t pollard_rho(uint64_t n, int c) {
    // algorithm to find a random divisor of `n`.
    // using random function: f(x) = (x^2 + c) % n.
    uint64_t x = 2, y = x, d;
    long long p = 1;
    int dist = 0;
    while (true) {
        y = f(y, c, n);
        dist++;
        d = __gcd(max(x, y) - min(x, y), n);
        if (d > 1) break;
        if (dist == p) { dist = 0; p *= 2; x = y; }
    }
    return d;
}
void factorize(uint64_t n, vector<uint64_t> &factors) {
    if (n < 2) return;
    if (is_prime(n)) {
        factors.emplace_back(n);
        return;
    }
    uint64_t d = n;
    for (int c = 2; d == n; c++) {
        d = pollard_rho(n, c);
    }
    factorize(d, factors); factorize(n / d, factors);
}
vector<uint64_t> gen_divisors(vector<pair<uint64_t, int>> &factors) {
    vector<uint64_t> divisors = {1};
    for (auto &x : factors) {
        int sz = (int) divisors.size();
        for (int i = 0; i < sz; ++i) {
            uint64_t cur = divisors[i];
            for (int j = 0; j < x.second; ++j) {
                cur *= x.first;
                divisors.push_back(cur);
            }
        }
    }    
    return divisors; // this array is NOT sorted yet.
}
