#include <iostream>
#include <deque>
#include <exception>
#include <cstring>

class DequeEmptyException : public std::exception {
public:
    const char * what () const throw () {
        return "error";
    }
};


template <class T>
class Deque {
private:
    std::deque<T> d;
public:
    void PushFront(const T& val) {
        d.push_front(val);
    }
    void PushBack(const T& val) {
        d.push_back(val);
    }
    T PopFront() {
        if (d.empty()) {
            throw DequeEmptyException();
        }
        T val = d.front();
        d.pop_front();
        return val;
    }
    T PopBack() {
        if (d.empty()) {
            throw DequeEmptyException();
        }
        T val = d.back();
        d.pop_back();
        return val;
    }
    T Front() {
        if (d.empty()) {
            throw DequeEmptyException();
        }
        return d.front();
    }
    T Back() {
        if (d.empty()) {
            throw DequeEmptyException();
        }
        return d.back();
    }
    size_t Size() {
        return d.size();
    }
    void Clear() {
        d.clear();
    }
};

int main() {
    int n;
    std::cin >> n;
    Deque<int> d;
    for (int i = 0; i < n; ++i) {
        char command[20];
        std::cin >> command;
        if (!std::strcmp(command, "push_back")) {
            int x;
            std::cin >> x;
            d.PushBack(x);
            std::cout << "ok" << std::endl;
        } else if (!std::strcmp(command, "push_front")) {
            int x;
            std::cin >> x;
            d.PushFront(x);
            std::cout << "ok" << std::endl;
        } else if (!std::strcmp(command, "back")) {
            try {
                std::cout << d.Back() << std::endl;
            } catch (DequeEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "front")) {
            try {
                std::cout << d.Front() << std::endl;
            } catch (DequeEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "pop_back")) {
            try {
                std::cout << d.PopBack() << std::endl;
            } catch (DequeEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "pop_front")) {
            try {
                std::cout << d.PopFront() << std::endl;
            } catch (DequeEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "size")) {
            std::cout << d.Size() << std::endl;
        } else {
            d.Clear();
            std::cout << "ok" << std::endl;
        }
    }
    return 0;
}


