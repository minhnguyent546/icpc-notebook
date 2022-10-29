/**
 * Description: The prefix function of a string `s` is defined as an array pi of length n,
 *  where pi[i] is the length of the longest proper prefix of the substring
 *  s[0..i] which is also a suffix of this substring.
 * Time complexity: O(|S|).
 */
vector<int> prefix_function(const string &s) {
    int n = (int) s.length();
    vector<int> pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1]; // try length pi[i - 1] + 1.
        while (j > 0 && s[j] != s[i]) {
            j = pi[j - 1];
        }
        if (s[j] == s[i]) {
            pi[i] = j + 1;
        }
    }
    return pi;
}