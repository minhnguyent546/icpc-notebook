/**
 * Description: given a string s of length n, a prefix of s is called a border of s if it is also a suffix of s.
 * Tested: https://cses.fi/problemset/task/1732
 */
#include "prefix_function.h"
vector<int> find_borders(const string &s) {
    int n = (int) s.size();
    vector<int> pi = prefix_function(s);
    vector<int> lengths;
    int i = n - 1;
    while (i >= 0) {
        if (pi[i] != 0) {
            lengths.emplace_back(pi[i]);
        }
        i = pi[i] - 1;
    }
    reverse(lengths.begin(), lengths.end());
    return lengths;
}