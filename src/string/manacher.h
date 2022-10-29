/**
 * Description: for each position, computes d[0][i] = half length of 
 longest palindrome centered on i (rounded up), d[1][i] = half length of 
 longest palindrome centered on i and i - 1.
 * Time complexity: O(N). 
 * Tested: https://judge.yosupo.jp/problem/enumerate_palindromes, stress-tested. 
 */
array<vector<int>, 2> manacher(const string &s) {
    int n = (int) s.size();
    array<vector<int>, 2> d;
    for (int z = 0; z < 2; ++z) {
        d[z].resize(n);
        int l = 0, r = 0;
        for (int i = 0; i < n; ++i) {
            int mirror = l + r - i + z;
            d[z][i] = (i > r ? 0 : min(d[z][mirror], r - i));
            int L = i - d[z][i] - z, R = i + d[z][i];
            while (L >= 0 && R < n && s[L] == s[R]) {
                d[z][i]++; L--; R++;
            }
            if (R > r) {
                l = L; r = R;
            }
        }
    }
    return d;
}