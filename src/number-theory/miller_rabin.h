#include "modmul.h"

/**
 * Description: Miller–Rabin primality test, this algorithm works for number up to $7e^{18}$.
 * Status: tested on https://judge.yosupo.jp/problem/primality_test
 */

using num_t = long long;
int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 73, 113, 193, 311, 313, 407521, 299210837};
bool miller_rabin(num_t a, num_t d, int s, num_t mod) {
    num_t x = modpow(a, d, mod);
    if (x == mod - 1 || x == 1) return true;
    for (int i = 0; i < s - 1; ++i) {
        x = modmul(x, x, mod);
        if (x == mod - 1) return true;
    }
    return false;
}
bool is_prime(num_t n) {
    if (n < 4) return n > 1;
    num_t d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1; s++; }
    for (int a : small_primes) {
        if (n == a) return true;
        if (n % a == 0 || !miller_rabin(a, d, s, n)) return false;
    }
    return true;
}
