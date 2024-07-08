/**
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: finds the lexicographically smallest rotation of a string.
 * Time: $O(N)$.
 * Usage: rotate(v.begin(), v.begin() + minRotation(v), v.end())
 */

#pragma once

int minRotation(string s) {
  int a = 0, N = (int) s.size(); s += s;
  rep(b, 0, N) rep(k, 0, N) {
    if (a + k == b || s[a + k] < s[b + k]) {b += max(0, k - 1); break;}
    if (s[a + k] > s[b + k]) { a = b; break; }
  }
  return a;
}