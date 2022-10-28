#include "../utilities/template.h"
#include "../../source/number-theory/segment_divisor_sieve.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long N = (long long) 1e10; // L <= N.
    const int M = (int) 1e2; // R - L + 1 <= M.
    for (int t = 0; t < (int) 100; ++t) {
        long long L = rand(1LL, N);
        long long R = L + rand(0, M - 1);
        for (long long i = L; i <= R; ++i) {
            divisor_count[i - L] = 0;
        }
        segment_divisor_sieve(L, R);
        for (long long i = L; i <= R; ++i) {
            long long cur = i;
            int cnt = 1;
            for (int p = 2; p <= (int) sqrt(cur); ++p) {
                int k = 0;
                while (cur % p == 0) {
                    cur /= p;
                    k++;
                }
                cnt *= (k + 1);
            }
            if (cur > 1) {
                cnt *= 2;
            }
            if (cnt != divisor_count[i - L]) {
                debug(L, R, i, cnt, divisor_count[i-L])
            }
            assert(cnt == divisor_count[i - L]);
        }
    }
    cout << "Passed all tests!" << '\n';
    return 0;
}