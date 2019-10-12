#include <iostream>
#include <stack>
#include <exception>
#include <cstring>
#include <utility>

class MinQueueEmptyException : public std::exception {
public:
    const char * what () const throw () {
        return "error";
    }
};


template <class T>
class MinQueue {
private:
    std::stack<std::pair<T, T>> first;
    std::stack<std::pair<T, T>> second;
public:
    size_t size() {
        return first.size() + second.size();
    }
    void clear() {
        while (!first.empty()) {
            first.pop();
        }
        while (!second.empty()) {
            second.pop();
        }
    }
    void enqueue(const T& val) {
        if (!second.empty()) {
            second.push(std::make_pair(val, std::min(val, second.top().second)));
        } else {
            second.push(std::make_pair(val, val));
        }
    }
    T front() {
        if (first.empty()) {
            while (!second.empty()) {
                std::pair<T, T> curr = second.top();
                second.pop();
                if (!first.empty()) {
                    curr.second = std::min(curr.first, first.top().second);
                } else {
                    curr.second = curr.first;
                }
                first.push(curr);
            }
        }
        if (first.empty()) {
            throw MinQueueEmptyException();
        }
        T fr = first.top().first;
        return fr;
    }
    T dequeue() {
        if (first.empty()) {
            while (!second.empty()) {
                std::pair<T, T> curr = second.top();
                second.pop();
                if (!first.empty()) {
                    curr.second = std::min(curr.first, first.top().second);
                } else {
                    curr.second = curr.first;
                }
                first.push(curr);
            }
        }
        if (first.empty()) {
            throw MinQueueEmptyException();
        }
        T val = first.top().first;
        first.pop();
        return val;
    }
    T min() {
        if (size() == 0) {
            throw MinQueueEmptyException();
        }
        if (first.empty()) {
            return second.top().second;
        }
        if (second.empty()) {
            return first.top().second;
        }
        return std::min(second.top().second, first.top().second);
    }
};

int main() {
    int n;
    std::cin >> n;
    MinQueue<int> d;
    for (int i = 0; i < n; ++i) {
        char command[20];
        std::cin >> command;
        if (!std::strcmp(command, "enqueue")) {
            int x;
            std::cin >> x;
            d.enqueue(x);
            std::cout << "ok" << std::endl;
        } else if (!std::strcmp(command, "min")) {
            try {
                int x = d.min();
                std::cout << x << std::endl;
            } catch (MinQueueEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "dequeue")) {
            try {
                int x = d.dequeue();
                std::cout << x << std::endl;
            } catch (MinQueueEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "front")) {
            try {
                int x = d.front();
                std::cout << x << std::endl;
            } catch (MinQueueEmptyException& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (!std::strcmp(command, "size")) {
            std::cout << d.size() << std::endl;
        } else {
            d.clear();
            std::cout << "ok" << std::endl;
        }
    }
    return 0;
}


