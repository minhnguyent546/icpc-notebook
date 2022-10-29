const double eps = 1e-9;
double ternary_search_max(double l, double r) {
    // find x0 such that: f(x0) > f(x), \all x: l <= x <= r. 
    while (r - l > eps) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if (f(mid1) < f(mid2)) l = mid1;
        else r = mid2;
    }
    return l;
}
double ternary_search_min(double l, double r) {
    // find x0 such that: f(x0) < f(x), \all x: l <= x <= r. 
    while (r - l > eps) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if (f(mid1) > f(mid2)) l = mid1;
        else r = mid2;
    }
    return l;
}
