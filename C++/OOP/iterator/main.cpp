#include "vector.h"

#include <iostream>
#include <utility>
#include <stdexcept>

int main() {
    Vector<int> u;
    for (int i = 100; i < 110; ++i) {
        u.PushBack(i);
    }
    u.Print();
    Vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.PushBack(i);
    }
    v.Print();
    Vector<int>::Iterator it1 = u.begin();
    Vector<int>::Iterator it2 = v.begin();
    Vector<int>::Iterator it3 = v.begin();
    std::cout << *it1 << " " << *it2 << "\n";
    std::cout << std::boolalpha << (it2 == it3) << "\n";
    std::cout << std::boolalpha << (it1 == it2) << "\n";
    ++it2;
    std::cout << *it2 << "\n";
    std::cout << std::boolalpha << (it2 < it3) << "\n";
    std::cout << std::boolalpha << (it2 > it3) << "\n";
    std::cout << std::boolalpha << (it2 >= it3) << "\n";
    std::cout << std::boolalpha << (it2 <= it3) << "\n";
    std::cout << std::boolalpha << (it2 != it3) << "\n";
    *it2 = -1;
    v.Print();
    ++it3;
    std::cout << std::boolalpha << (it2 == it3) << "\n";
    std::cout << *it1 << " " << *it3 << "\n";
    it3.Swap(it1);
    std::cout << *it1 << " " << *it3 << "\n";
    std::cout << std::boolalpha << (it2 == it1) << "\n";
    Vector<std::pair<char, char>> c;
    c.PushBack(std::make_pair('a', 'b'));
    Vector<std::pair<char, char>>::Iterator it_c = c.end();
    --it_c;
    std::cout << it_c->first << " " << it_c->second << "\n";
    it_c->second = 'c';
    std::cout << it_c->first << " " << it_c->second << "\n";
    std::cout << *it1++ << "\n";
    std::cout << *it1 << "\n";
    std::cout << it1[2] << "\n";
    it1[2] = 42;
    v.Print();
    std::cout << *(it1 + 2) << "\n";
    it1 += 3;
    it1 -= 2;
    std::cout << *(it1) << " " << *it2 << "\n";
    std::cout << it1 - it2 << "\n";
    std::cout << *(5 + it2) << "\n";
    std::cout << *(it2 - 1) << "\n";
    Vector<int>::Iterator it4 = v.begin() + 7;
    std::cout << *(it4) << "\n";
    it4 = it1;
    std::cout << *(it4) << "\n";
    std::cout << (it4 == it1) << "\n";
    Vector<int>::Iterator it5(it4);
    std::cout << *(it5) << "\n";
    return 0;
}

