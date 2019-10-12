#include <iostream>
#include <unordered_set>
#include <exception>
#include <algorithm>
#include <string>
#include <utility>

struct StringSet {
    std::unordered_set<std::string> s;
    void add(const std::string& c) {
        s.insert(c);
    }
    void del(const std::string& c) {
        s.erase(c);
    }
    bool contains(const std::string& c){
        return s.find(c) != s.end();
    }
};

int main() {
    StringSet s;
    for (;;) {
        char c;
        std::cin >> c;
        if (c == '+') {
            std::string str;
            std::cin >> str;
            s.add(str);
        } else if (c == '-') {
            std::string str;
            std::cin >> str;
            s.del(str);
        } else if (c == '?') {
            std::string str;
            std::cin >> str;
            std::cout << (s.contains(str) ? "YES" : "NO") << std::endl;
        } else if (c == '#') {
            break;
        }
    }
    return 0;
}



