#include "../utilities/template.h"
#include "../../source/number-theory/segment_sieve.h"

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5, x = (int) sqrt(n); i <= x; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long N = (long long) 1e10; // 1 <= L <= N.
    const int M = (int) 1e2; // R - L + 1 <= M.
    for (int t = 0; t < (int) 100; ++t) {
        long long L = rand(1LL, N);
        long long R = L + rand(0, M - 1);
        segment_sieve(L, R);
        for (long long i = L; i <= R; ++i) {
            bool b1 = is_prime(i);
            bool b2 = prime[i - L];
            if (b1 != b2) {
                debug(L, R, b1, b2)
            }
            assert(b1 == b2);
        }
    }
    cout << "Passed all tests!" << '\n';
    return 0;
}