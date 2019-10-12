#include <iostream>
#include <vector>

int count(std::vector<int>::iterator begin, std::vector<int>::iterator end, const int& val) {
    int counter = 0;
    for (std::vector<int>::iterator it = begin; it != end; ++it) {
        if (*it == val) {
            ++counter;
        }
    }
    return counter;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> seq(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        seq[i] = x;
    }
    int val;
    std::cin >> val;
    std::vector<int>::iterator begin = seq.begin();
    std::vector<int>::iterator end = seq.end();
    std::cout << count(begin, end, val) << std::endl;
    return 0;
}

