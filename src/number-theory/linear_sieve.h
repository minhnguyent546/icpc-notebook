/**
 * Description: finding primes and computing value for multiplicative function in $O(N)$.
 * Time: $O(N)$ (but the factor may be large).
 */

const int N = (int) 1e6;
bool is_prime[N + 1];
int spf[N + 1]; // smallest prime factor
int phi[N + 1]; // euler's totient function
int mu[N + 1]; // mobius function
int func[N + 1]; // a multiplicative function, f(p^k) = k
int cnt[N + 1]; // cnt[i] = the power of the smallest prime factor of i
int pw[N + 1]; // pw[i] = p^cnt[i] where p is the smallest prime factor of i
vector<int> primes;

void sieve(int n = N) {
    spf[0] = spf[1] = -1;
    phi[1] = mu[1] = func[1] = 1;
    for (int x = 2; x <= n; ++x) {
        if (spf[x] == 0) {
            primes.push_back(spf[x] = x);
            is_prime[x] = true;
            phi[x] = x - 1;
            mu[x] = -1;
            func[x] = 1;
            cnt[x] = 1;
            pw[x] = x;
        }
        for (int p : primes) {
            if (p > spf[x] || x * p > n) break;
            spf[x * p] = p;
            if (p == spf[x]) {
                phi[x * p] = phi[x] * p;
                mu[x * p] = 0;
                func[x * p] = func[x / pw[x]] * (cnt[x] + 1);
                cnt[x * p] = cnt[x] + 1;
                pw[x * p] = pw[x] * p;
            }
            else {
                phi[x * p] = phi[x] * phi[p];
                mu[x * p] = mu[x] * mu[p]; // or -mu[x]
                func[x * p] = func[x] * func[p];
                cnt[x * p] = 1;
                pw[x * p] = p;
            }
        }
    }
}