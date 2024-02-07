
/**
 * C++ debug template for competitive programming
 * requires: c++17
 * does not support: arrays (e.g. int arr[N], vector<int> dp[N]).
 */

template<typename T, typename G>
ostream& operator<<(ostream &os, pair<T, G> p);

template<size_t N>
ostream& operator<<(ostream &os, bitset<N> bs);

template<typename... Ts>
ostream &operator<<(ostream &os, tuple<Ts...> tup);

template<typename T, typename = void>
struct iterable_std_DA : false_type {};

template<typename T>
struct iterable_std_DA<T, void_t<decltype(declval<T>().begin(), declval<T>().end())>> : true_type {};

template<typename T, typename = void>
struct non_iterable_std_DA : false_type {};

template<typename T>
struct non_iterable_std_DA<T, void_t<decltype(declval<T>().pop())>> : true_type {};

template<typename T, typename = void>
struct stack_like : false_type {};

template<typename T>
struct stack_like<T, void_t<decltype(declval<T>().top())>> : true_type {};

template<typename T, typename = void>
struct queue_like : false_type {};

template<typename T>
struct queue_like<T, void_t<decltype(declval<T>().front())>> : true_type {};

template<typename Container>
typename enable_if<iterable_std_DA<Container>::value && !is_same<Container, string>::value,ostream&>::type
operator<<(ostream &os, Container container);

template<typename Container>
typename enable_if<non_iterable_std_DA<Container>::value && !is_same<Container, string>::value,ostream&>::type
operator<<(ostream &os, Container container);

template<typename Container>
typename enable_if<iterable_std_DA<Container>::value && !is_same<Container, string>::value,ostream&>::type
operator<<(ostream &os, Container container) {
    os << "{";
    for (auto it = container.begin(); it != container.end(); ++it) {
        os << (it == container.begin() ? "" : ", ") << *it;
    }
    return os << "}";
}

template<typename Container>
typename enable_if<non_iterable_std_DA<Container>::value && !is_same<Container, string>::value,ostream&>::type
operator<<(ostream &os, Container container) {
    os << "{";
    if constexpr (stack_like<Container>::value) {
        bool first = true;
        while (!container.empty()) {
            if (!first) os << ", ";
            first = false;
            os << container.top(), container.pop();
        }
    }
    else if constexpr (queue_like<Container>::value) {
        bool first = true;
        while (!container.empty()) {
            if (!first) os << ", ";
            first = false;
            os << container.front(), container.pop();
        }
    }
    else {
        // maybe throw an error
    }
    return os << "}";
}

template<typename T, typename G>
ostream& operator<<(ostream &os, pair<T, G> p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<size_t N>
ostream& operator<<(ostream &os, bitset<N> bs) {
    for (size_t i = 0; i < N; ++i) {
        os << (char) (bs[i] + '0');
    }
    return os;
}

/**
 * https://en.cppreference.com/w/cpp/utility/integer_sequence
 */
template<typename Tup, size_t... Is>
void print_tuple_impl(ostream &os, const Tup &tup, index_sequence<Is...>) {
    ((os << (Is == 0 ? "" : ", ") << get<Is>(tup)),...);
}

template<typename... Ts>
ostream &operator<<(ostream &os, tuple<Ts...> tup) {
    os << "(";
    print_tuple_impl(os, tup, index_sequence_for<Ts...>{});
    return os << ")";
} 

/**
 * https://codeforces.com/blog/entry/125435
 */
template<typename H, typename... T>
void debug(const char *names, H &&head, T &&...tail) {
    int i = 0;
    for (size_t bracket = 0; names[i] != '\0' && (names[i] != ',' || bracket != 0); i++) {
        if (names[i] == '(' or names[i] == '<' or names[i] == '{') {
            bracket++;
        }
        else if (names[i] == ')' or names[i] == '>' or names[i] == '}') {
            bracket--;
        }
    }
    cerr << "[", cerr.write(names, i) << " = " << head << "]";
    if constexpr (sizeof...(tail)) {
        while (names[i] != '\0' && names[i + 1] == ' ') ++i;
        cerr << " "; debug(names + i + 1, tail...);
    } 
    else {
        cerr << '\n';
    }
}

using high_clock = chrono::high_resolution_clock;
auto start_time = high_clock::now();
int elapsed_time() {
    auto elapsed = high_clock::now() - start_time;
    start_time = high_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(elapsed).count();
}

#define debug(...) { \
    cerr << __FUNCTION__ << ":" << __LINE__ << ": "; \
    debug(#__VA_ARGS__, __VA_ARGS__); \
}