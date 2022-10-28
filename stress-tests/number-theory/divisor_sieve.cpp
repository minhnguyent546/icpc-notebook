#include "../utilities/template.h"
#include "../../source/number-theory/divisor_sieve.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 1e5;
    assert(N <= MAXN);
    better_divisor_sieve(N);
    for (int i = 1; i <= N; ++i) {
        int cur = i;
        int cnt = 1;
        for (int p = 2; p <= (int) sqrt(cur); ++p) {
            int k = 0;
            while (cur % p == 0) {
                cur /= p;
                k++;
            }
            cnt *= (k + 1);
        }
        if (cur > 1) cnt *= 2;
        assert(cnt == divisor_count[i]);
    }
    cout << "Passed all tests!" << '\n';
    return 0;
}