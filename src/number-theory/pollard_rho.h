/**
 * Description: Pollard's rho is an efficient algorithm for integer factorization.
 * The algorithm can run smoothly with $n$ upto $10^{18}$, but be careful with overflow
 * for larger $n$ (e.g. $10^{19}$).
 */

using num_t = long long;
const int PRIME_MAX = (int) 4e4; // for handle numbers <= 1e9.
const int LIMIT = (int) 1e9;
vector<int> primes;
int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 73, 113, 193, 311, 313, 407521, 299210837};
void linear_sieve(int n);
num_t mulmod(num_t a, num_t b, num_t mod);
num_t powmod(num_t a, num_t n, num_t mod);
bool miller_rabin(num_t a, num_t d, int s, num_t mod) {
    num_t x = powmod(a, d, mod);
    if (x == mod - 1 || x == 1) {
        return true;
    }
    for (int i = 0; i < s - 1; ++i) {
        x = mulmod(x, x, mod);
        if (x == mod - 1) return true;
    }
    return false;
}
bool is_prime(num_t n, int tests = 10) {
    if (n < 4) return (n > 1);
    num_t d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1; s++; }
    for (int i = 0; i < tests; ++i) {
        int a = small_primes[i];
        if (n == a) return true;
        if (n % a == 0 || !miller_rabin(a, d, s, n)) return false;
    }
    return true;
}
num_t f(num_t x, int c, num_t mod) { // f(x) = (x^2 + c) % mod.
    x = mulmod(x, x, mod);
    x += c;
    if (x >= mod) x -= mod;
    return x;
}
num_t pollard_rho(num_t n, int c) {
    // algorithm to find a random divisor of `n`.
    // using random function: f(x) = (x^2 + c) % n.
    num_t x = 2, y = x, d;
    long long p = 1;
    int dist = 0;
    while (true) {
        y = f(y, c, n); 
        dist++;
        d = __gcd(llabs(x - y), n);
        if (d > 1) break;
        if (dist == p) { dist = 0; p *= 2; x = y; }
    }
    return d;
}
void factorize(int n, vector<num_t> &factors); 
void llfactorize(num_t n, vector<num_t> &factors) {
    if (n < 2) return;
    if (is_prime(n)) {
        factors.emplace_back(n);
        return;
    }
    if (n < LIMIT) {
        factorize(n, factors);
        return;
    }
    num_t d = n;
    for (int c = 2; d == n; c++) {
        d = pollard_rho(n, c);
    }
    llfactorize(d, factors);
    llfactorize(n / d, factors);
}
vector<num_t> gen_divisors(vector<pair<num_t, int>> &factors) {
    vector<num_t> divisors = {1};
    for (auto &x : factors) {
        int sz = (int) divisors.size();
        for (int i = 0; i < sz; ++i) {
            num_t cur = divisors[i];
            for (int j = 0; j < x.second; ++j) {
                cur *= x.first;
                divisors.push_back(cur);
            }
        }
    }    
    return divisors; // this array is NOT sorted yet.
}