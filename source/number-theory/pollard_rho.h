const int PRIME_MAX = (int) 4e4; // for handle numbers <= 1e9.
const int LIMIT = (int) 1e9;
vector<int> primes;

void linear_sieve(int n);
num_type mulmod(num_type a, num_type b, num_type mod);
num_type powmod(num_type a, num_type n, num_type mod);

bool miller_rabin(num_type a, num_type d, int s, num_type mod) {
    // mod - 1 = a ^ (d * 2^s).
    num_type x = powmod(a, d, mod);
    if (x == 1 || x == mod - 1) return true;
    for (int i = 1; i <= s - 1; ++i) {
        x = mulmod(x, x, mod);
        if (x == mod - 1) return true;
    }
    return false;
}
bool is_prime(num_type n, int ITERATION = 10) {
    if (n < 4) return (n == 2 || n == 3);
    if (n % 2 == 0 || n % 3 == 0) return false;
    num_type d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (int i = 0; i < ITERATION; ++i) {
        num_type a = (num_type) (rand() % (n - 2)) + 2;
        if (miller_rabin(a, d, s, n) == false) {
            return false;
        }
    }
    return true;
}
num_type f(num_type x, int c, num_type mod) { // f(x) = (x^2 + c) % mod.
    x = mulmod(x, x, mod);
    x += c;
    if (x >= mod) x -= mod;
    return x;
}
num_type pollard_rho(num_type n, int c) {
    // algorithm to find a random divisor of `n`.
    // using random function: f(x) = (x^2 + c) % n.

    // **************** Floyd's cycle detection algorithm **************** 
    // move 1 step and 2 steps.
    // num_type x = 2, y = 2, d;
    // while (true) {
    //     x = f(x, c, n);
    //     y = f(y, c, n);
    //     y = f(y, c, n);
    //     d = __gcd(llabs(x - y), n);
    //     if (d > 1) break;
    // }
    // return d;

    // **************** Brent's cycle detection algorithm **************** 
    // move power of two steps.
    num_type x = 2, y = x, d;
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
void factorize(int n, vector<num_type> &factors);
void llfactorize(num_type n, vector<num_type> &factors) {
    if (n < 2) return;
    if (n < LIMIT) {
        factorize(n, factors);
        return;
    }
    if (is_prime(n)) {
        factors.emplace_back(n);
        return;
    }
    num_type d = n;
    for (int c = 2; d == n; c++) {
        d = pollard_rho(n, c);
    }
    llfactorize(d, factors);
    llfactorize(n / d, factors);
}
vector<num_type> gen_divisors(vector<pair<num_type, int>> &factors) {
    vector<num_type> divisors = {1};
    for (auto &x : factors) {
        int sz = (int) divisors.size();
        for (int i = 0; i < sz; ++i) {
            num_type cur = divisors[i];
            for (int j = 0; j < x.second; ++j) {
                cur *= x.first;
                divisors.push_back(cur);
            }
        }
    }    
    return divisors; // this array is NOT sorted yet.
}