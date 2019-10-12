#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <cstring>
#include <iterator>

class Cache {
    std::unordered_map<int, std::list<int>::iterator> db;
    std::list<int> queue;
    size_t max_size;
public:
    Cache() {}
    void set_size(size_t m) {
        max_size = m;
    }
    int get_user(int x) {
        if (db.find(x) != db.end()) {
            queue.erase(db[x]);
            queue.push_front(x);
            db[x] = queue.begin();
            return 0;
        }
        if (db.size() == max_size) {
            db.erase(queue.back());
            queue.pop_back();
        }
        queue.push_front(x);
        db[x] = queue.begin();
        return 1;
    }
};

int main() {
    int m;
    std::cin >> m;
    Cache c;
    c.set_size(m);
    int x;
    while (std::cin >> x) {
        std::cout << c.get_user(x) << " ";
    }
    std::cout << "\n";
    return 0;
}






