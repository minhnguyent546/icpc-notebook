/**
 * Description: acts like normal std::queue except it supports get minimum value in current queue.
 */

template <typename T>
struct MinQueue {
    vector<T> vals;
    int ptr = 0;
    vector<int> st;
    int ptr_idx = 0;
    void push(T val) {
        while ((int) st.size() > ptr_idx && vals[st.back()] >= val) {
            st.pop_back();
        }
        st.push_back((int) vals.size());
        vals.push_back(val);
    }
    void pop() {
        assert(ptr < (int) vals.size());
        if (ptr_idx < (int) st.size() && st[ptr_idx] == ptr) ptr_idx++;
        ptr++;
    }
    T get() {
        assert(ptr_idx < (int) st.size());
        return vals[st[ptr_idx]];
    }
    int front() {
        assert(!empty()); return vals[ptr];
    }
    int back() {
        assert(!empty()); return vals.back();
    }
    bool empty() {
        return (ptr == (int) vals.size());
    }
    int size() {
        return ((int) vals.size() - ptr);
    }
};