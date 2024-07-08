/**
 * Description: searching for a sub-string in a string.
 * Time: $O(N + M)$.
 */

#include "prefix_function.h"
vector<int> KMP(const string &text, const string &pattern) {
    int n = (int) text.length();
    int m = (int) pattern.length();
    string s = pattern + '$' + text;
    vector<int> pi = prefix_function(s);
    vector<int> indices;
    for (int i = 0; i < (int) s.length(); ++i) {
        if (pi[i] == m) {
            indices.push_back(i - 2 * m);
        }
    }
    return indices;
}