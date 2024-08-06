#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename K, typename V, typename comp = less<K>>
using ordered_map = tree<
    K, V, comp,
    rb_tree_tag, tree_order_statistics_node_update
>;

template<typename K, typename comp = less<K>>
using ordered_set = ordered_map<K, null_type, comp>;

const int INF = 0x3f3f3f3f;
void example() {
    vector<int> nums = {1, 2, 3, 5, 10};
    ordered_set<int> st(nums.begin(), nums.end());

    cout << *st.find_by_order(0) << '\n'; // 1
    assert(st.find_by_order(-INF) == st.end());
    assert(st.find_by_order(INF) == st.end());

    cout << st.order_of_key(2) << '\n'; // 1
    cout << st.order_of_key(4) << '\n'; //  3
    cout << st.order_of_key(9) << '\n'; // 4
    cout << st.order_of_key(-INF) << '\n'; // 0 
    cout << st.order_of_key(INF) << '\n'; // 5
}
