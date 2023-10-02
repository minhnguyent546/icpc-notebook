/**
 * Description: given an unimodal function f(x), find the maximum/minimum of f(x).
 * Unimodal means The function strictly increases/decreases first,
 * reaches a maximum/minimum (at a single point or over an interval),
 * and then strictly decreases/increases.
 */
const double eps = 1e-9;
template<typename T>
inline T func(T x) { return x * x; }

// these two functions below find min, for find max: change `<` below to `>`.
double ternary_search(double l, double r) { // min
    while (r - l > eps) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if (func(mid1) < func(mid2)) r = mid2;
        else l = mid1;
    }
    return l;
}
int ternary_search(int l, int r) { // min
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (func(mid) < func(mid + 1)) r = mid;
        else l = mid + 1;
    }
    return l;
}