#include "sort.h"
#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

int main() {
    std::vector<int> v;
    int n = 18;
    for (int i = 0; i < n; ++i) {
        v.push_back(std::rand()%10 + 33);
    }
    for (int i = 0; i < n; ++i) {
        
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
    Sort<std::vector<int>::iterator>(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
    std::cout << "\n";
    std::vector<int> u;
    n = 10;
    for (int i = 0; i < n; ++i) {
        u.push_back(std::rand()%100 - 25);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << u[i] << " ";
    }
    std::cout << "\n";
    Sort<std::vector<int>::iterator>(u.begin() + 2, u.end() - 3);
    for (int i = 0; i < n; ++i) {
        std::cout << u[i] << " ";
    }
    std::cout << "\n";
    std::cout << "\n";
    std::forward_list<int> fw;
    n = 11;
    for (int i = 0; i < n; ++i) {
        fw.push_front(std::rand()%100 - 66);
    }
    for (auto const& i : fw) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    Sort<std::forward_list<int>::iterator>(fw.begin(), fw.end());
    for (auto const& i : fw) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    std::cout << "\n";
    std::list<int> l;
    n = 9;
    for (int i = 0; i < n; ++i) {
        l.push_front(std::rand()%100);
    }
    for (auto const& i : l) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    Sort<std::list<int>::iterator>(l.begin(), l.end());
    for (auto const& i : l) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    return 0;
}
