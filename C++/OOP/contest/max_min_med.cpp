#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
#include <iterator>

struct StoreIntegers {
    std::set<int> s;
    std::set<int>::iterator med_it;
    size_t size() {
        return s.size();
    }
    void add(int x) {
        if (size() <= 1) {
            s.insert(x);
            med_it = s.begin();
        } else if (size() == 2) {
            s.insert(x);
            med_it = s.begin();
            ++med_it;
        } else {
            if (size() % 2 == 0) {
                if (x < *med_it) {
                    s.insert(x);
                } else {
                    s.insert(x);
                    ++med_it;
                }
            } else {
                if (x < *med_it) {
                    s.insert(x);
                    --med_it;
                } else {
                    s.insert(x);
                }
            }
        }
    }
    int min() {
        auto it = s.begin();
        int res = *(it);
        s.erase(it);
        if (size() <= 2) {
            med_it = s.begin();
        } else if ((size() + 1) % 2 == 0) {
            ++med_it;
        }
        return res;
    }
    int max() {
        auto it = s.end();
        int res = *(--it);
        s.erase(it);
        if (size() <= 2) {
            med_it = s.begin();
        } else if ((size() + 1) % 2 == 1) {
            --med_it;
        }
        return res;
    }
    int mid() {
        int res = *med_it;
        if (size() % 2 == 0) {
            ++med_it;
        } else {
            --med_it;
        }
        s.erase(res);
        return res;
    }
};

int main() {
    int n;
    std::cin >> n;
    StoreIntegers store;
    for (int i = 0; i < n; ++i) {
        char command[5];
        std::cin >> command;
        if (!std::strcmp(command, "add")) {
            int x;
            std::cin >> x;
            store.add(x);
        } else if (!std::strcmp(command, "min")) {
            std::cout << store.min() << std::endl;
        } else if (!std::strcmp(command, "max")) {
            std::cout << store.max() << std::endl;
        } else {
            std::cout << store.mid() << std::endl;
        }
    }
    return 0;
}






