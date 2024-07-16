/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/modulo.hpp
 * Description: calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Time: $O(1)$ for \texttt{modmul}, $O(\log b)$ for \texttt{modpow}.
 * Status: stress-tested, proven correct.
 * Note: this runs roughly 2x faster than the naive (\_\_int128\_t) a * b \% M.
 */

#pragma once

uint64_t modmul(uint64_t a, uint64_t b, uint64_t mod) {
    int64_t ret = a * b - mod * uint64_t(1.L / mod * a * b); // overflow is fine!
    return ret + mod * (ret < 0) - mod * (ret >= (int64_t) mod);
}
uint64_t modpow(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t ans = 1;
    while (b > 0) {
        if (b & 1) ans = modmul(ans, a, mod);
        a = modmul(a, a, mod);
        b /= 2;
    }
    return ans;
}
