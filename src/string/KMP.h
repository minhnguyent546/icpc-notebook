/**
 * Description: searching for a sub-string in a string.
 * Time: $O(N + M)$.
 */

#include "prefix_function.h"
vector<int> KMP(const string &text, const string &pattern) {
    int n = (int) pattern.length();
    string combined = pattern + '$' + text;
    vector<int> pi = prefix_function(combined);
    vector<int> indices;
    for (int i = 0; i < (int) combined.length(); ++i) {
        if (pi[i] == n) {
            indices.push_back(i - 2 * n);
        }
    }
    return indices;
}
