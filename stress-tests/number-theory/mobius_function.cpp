#include "../utilities/template.h"
#include "../../source/number-theory/mobius_function.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = (int) 2e5;
    assert(N <= MAXN);
    sieve(N);
    for (int i = 1; i <= N; ++i) {
        int cur = i;
        int l = 0;
        bool has_greater_than_one = false;
        for (int p = 2; p <= (int) sqrt(cur); ++p) {
            if (cur % p == 0) {
                l++;
                cur /= p;
                if (cur % p == 0) {
                    has_greater_than_one = true;
                    break;
                }
            }
        }
        if (cur > 1) l++;
        int m;
        if (has_greater_than_one) {
             m = 0;
        }
        else {
            m = (l & 1) ? -1 : 1;
        }
        assert(m == mu[i]);
    }
    cout << "Passed all tests!" << '\n';
    return 0;
}