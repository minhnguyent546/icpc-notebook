/**
 * Description: Tonelli–Shanks algorithm. For a given non-negative integer $a$
 * and a prime number $p$, find $x$ such that $x^2 \equiv a \pmod p$ or $-1$
 * if there is no such $x$.
 * Status: tested on https://judge.yosupo.jp/problem/sqrt_mod
 */
#include "./modmul.h"

int mod_sqrt(int a, int p) {
    if (a == 0) return 0;
    if (p == 2) return (a & 1 ? 1 : 0);
    if (modpow(a, (p - 1) / 2, p) != 1) return -1;

    int b = 1;
    while (modpow(b, (p - 1) / 2, p) == 1) ++b;
    int d = p - 1, e = 0; // p - 1 = d * 2^s
    while (d % 2 == 0) d /= 2, ++e;
    int64_t x = modpow(a, (d - 1) / 2, p);
    int64_t y = a * x % p * x % p;
    x = x * a % p;
    int64_t z = modpow(b, d, p);
    while (y != 1) {
        int i = 0;
        int64_t k = y;
        while (k != 1) {
            ++i;
            k = k * k % p;
        }
        z = modpow(z, 1 << (e - i - 1), p);
        x = x * z % p;
        z = z * z % p;
        y = y * z % p;
        e = i;
    }
    return x;
}
