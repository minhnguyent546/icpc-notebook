/**
 * Description: Pollard's rho is an efficient algorithm for integer factorization.
 * The algorithm can run smoothly with $n$ upto $1e^{18}$, but be careful with overflow
 * for larger $n$ (e.g. $1e^{19}$).
 * Status: tested on https://judge.yosupo.jp/problem/factorize
 */

#include "modmul.h"
#include "miller_rabin.h"

using num_t = long long;
const int PRIME_MAX = (int) 4e4; // for handle numbers <= 1e9.
const int LIMIT = (int) 1e9;

num_t f(num_t x, int c, num_t mod) { // f(x) = (x^2 + c) % mod.
    x = modmul(x, x, mod) + c;
    if (x >= mod) x -= mod;
    return x;
}
num_t pollard_rho(num_t n, int c) {
    // algorithm to find a random divisor of `n`.
    // using random function: f(x) = (x^2 + c) % n.
    num_t x = 2, y = x, d;
    long long p = 1;
    int dist = 0;
    while (true) {
        y = f(y, c, n);
        dist++;
        d = __gcd(abs(x - y), n);
        if (d > 1) break;
        if (dist == p) { dist = 0; p *= 2; x = y; }
    }
    return d;
}
void factorize(num_t n, vector<num_t> &factors) {
    if (n < 2) return;
    if (is_prime(n)) {
        factors.emplace_back(n);
        return;
    }
    num_t d = n;
    for (int c = 2; d == n; c++) {
        d = pollard_rho(n, c);
    }
    factorize(d, factors); factorize(n / d, factors);
}
vector<num_t> gen_divisors(vector<pair<num_t, int>> &factors) {
    vector<num_t> divisors = {1};
    for (auto &x : factors) {
        int sz = (int) divisors.size();
        for (int i = 0; i < sz; ++i) {
            num_t cur = divisors[i];
            for (int j = 0; j < x.second; ++j) {
                cur *= x.first;
                divisors.push_back(cur);
            }
        }
    }    
    return divisors; // this array is NOT sorted yet.
}
