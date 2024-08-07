vector<int> zeckendoft_theorem(int n) {
    vector<int> fibs = {1, 1};
    int sz = 2;
    while (fibs.back() <= n) {
        fibs.push_back(fibs[sz - 1] + fibs[sz - 2]);
        sz++;
    }
    fibs.pop_back();
    vector<int> nums;
    int p = sz - 1;
    while (n > 0) {
        if (n >= fibs[p]) {
            nums.push_back(fibs[p]);
            n -= fibs[p];
        }
        p--;
    }   
    return nums;
}
