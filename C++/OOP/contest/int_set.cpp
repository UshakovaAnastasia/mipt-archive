#include <iostream>
#include <set>
#include <exception>
#include <algorithm>
#include <cstring>
#include <utility>

struct IntSet {
    std::set<int> s;
    void add(const int& val) {
        s.insert(val);
    }
    int next(const int& val){
        if (s.find(val) != s.end()) {
            return val;
        }
        if (s.upper_bound(val) == s.end()) {
            return -1;
        }
        return *s.upper_bound(val);
    }
};

int main() {
    int n;
    std::cin >> n;
    IntSet s;
    int prev_res;
    bool prev_is_next = false;
    for (int i = 0; i < n; ++i) {
        char command[5];
        std::cin >> command;
        if (!std::strcmp(command, "+")) {
            int x;
            std::cin >> x;
            if (prev_is_next == false) {
                s.add(x);
            } else {
                s.add((x + prev_res) % 1000000000);
                prev_is_next = false;
            }
        } else {
            int x;
            std::cin >> x;
            prev_res = s.next(x);
            std::cout << prev_res << std::endl;
            prev_is_next = true;
        }
    }
    return 0;
}



