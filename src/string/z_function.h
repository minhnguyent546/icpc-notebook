/**
 * Description: for a given string `s`, z[i] = longest common prefix of `s` and suffix starting at `i`.
 *   z[0] is generally not well defined (this implementation below assume z[0] = 0).
 */

vector<int> z_function(const string &s) {
    int n = (int) s.size();
    vector<int> z(n);
    z[0] = 0;
    // [l, r)
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}