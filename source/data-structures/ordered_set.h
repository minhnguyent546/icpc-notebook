#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename key_type>
using set_t = tree<key_type, null_type, less<key_type>, rb_tree_tag, 
    tree_order_statistics_node_update>;

void example() {
    vector<int> nums = {1, 2, 3, 5, 10};
    set_t<int> st(nums.begin(), nums.end());

    cout << *st.find_by_order(0) << '\n'; // 1
    assert(st.find_by_order(-INF) == st.end());
    assert(st.find_by_order(INF) == st.end());

    cout << st.order_of_key(2) << '\n'; // 1
    cout << st.order_of_key(4) << '\n'; //  3
    cout << st.order_of_key(9) << '\n'; // 4
    cout << st.order_of_key(-INF) << '\n'; // 0 
    cout << st.order_of_key(INF) << '\n'; // 5
}