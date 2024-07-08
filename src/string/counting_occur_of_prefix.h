/**
 * Description: count the number of occurrences of each prefix in the given string.
 * Time: $O(n)$.
 */

#include "prefix_function.h"
vector<int> count_occurrences(const string &s) {
    vector<int> pi = prefix_function(s);
    int n = (int) s.size();
    vector<int> ans(n + 1);
    for (int i = 0; i < n; ++i) {
        ans[pi[i]]++;
    }    
    for (int i = n - 1; i > 0; --i) {
        ans[pi[i - 1]] += ans[i];
    }
    for (int i = 0; i <= n; ++i) {
        ans[i]++;
    }
    return ans;
    // Input: ABACABA
    // Output: 4 2 2 1 1 1 1
}