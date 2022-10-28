#include "../utilities/template.h"
#include "../../source/number-theory/phi_euler_totient_function.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 2e5;
    assert(N <= MAXN);
    sieve(N);
    for (int i = 1; i <= N; ++i) {
        int cur = i;
        int ret = cur;
        for (int p = 2; p <= (int) sqrt(cur); ++p) {
            if (cur % p == 0) {
                ret -= ret / p;
                while (cur % p == 0) {
                    cur /= p;
                }
            }
        }
        if (cur > 1) ret -= ret / cur;
        assert(ret == etf[i]);
    }
    cout << "Passed all tests!" << '\n';
    return 0;
}