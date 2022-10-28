#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "./debug.h"
#else
#define debug(...)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = (int) 1e9 + 7;
const int INF = 0x3f3f3f3f;

template<typename T>
T rand(T a, T b) {
	// return random integer in [a, b].
	return a + rng() % (b - a + 1);
}