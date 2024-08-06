/**
 * Description: finding primes and computing value for multiplicative function in $O(N)$.
 * Time: $O(N)$ (but the factor may be large).
 */

const int N = (int) 2e6 + 3;
bool is_prime[N + 1];
int spf[N + 1]; // smallest prime factor
int lpf[N + 1]; // largest prime factor
int cntp[N + 1]; // number of prime factor
int phi[N + 1]; // euler's totient function
int mu[N + 1]; // mobius function
int func[N + 1]; // a multiplicative function, f(p^k) = k
int k[N + 1]; // k[i] = the power of the smallest prime factor of i
int pw[N + 1]; // pw[i] = p^k[i] where p is the smallest prime factor of i
vector<int> primes;

void linear_sieve(int n = N) {
    spf[0] = spf[1] = lpf[0] = lpf[1] = -1;
    phi[1] = mu[1] = func[1] = 1;
    for (int x = 2; x <= n; ++x) {
        if (spf[x] == 0) {
            primes.push_back(x);
            is_prime[x] = true;
            spf[x] = lpf[x] = x;
            cntp[x] = 1;
            phi[x] = x - 1, mu[x] = -1, func[x] = 1;
            k[x] = 1, pw[x] = x;
        }
        for (int p : primes) {
            if (p > spf[x] || x * p > n) break;
            spf[x * p] = p, lpf[x * p] = lpf[x];
            cntp[x * p] = cntp[x] + 1;
            if (p == spf[x]) {
                phi[x * p] = phi[x] * p;
                mu[x * p] = 0;
                func[x * p] = func[x / pw[x]] * (k[x] + 1);
                k[x * p] = k[x] + 1;
                pw[x * p] = pw[x] * p;
            }
            else {
                phi[x * p] = phi[x] * phi[p];
                mu[x * p] = mu[x] * mu[p]; // or -mu[x]
                func[x * p] = func[x] * func[p];
                k[x * p] = 1;
                pw[x * p] = p;
            }
        }
    }
}
