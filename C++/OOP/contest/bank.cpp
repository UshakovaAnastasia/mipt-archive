#include <iostream>
#include <map>
#include <exception>
#include <string>
#include <utility>

class KeyError : public std::exception {
public:
    const char * what () const throw () {
        return "ERROR";
    }
};

struct Clients {
    std::map<std::string, int> cl;
    void add_sum(const std::string& name, const int& sum) {
        if (cl.find(name) == cl.end()) {
            cl[name] = sum;
        } else {
            cl[name] += sum;
        }
    }
    int get_sum(const std::string& name) {
        if (cl.find(name) == cl.end()) {
            throw KeyError();
        }
        return cl[name];
    }
};

int main() {
    int n;
    std::cin >> n;
    Clients base;
    for (int i = 0; i < n; ++i) {
        int command;
        std::cin >> command;
        if (command == 1) {
            std::string name;
            int sum;
            std::cin >> name >> sum;
            base.add_sum(name, sum);
        } else {
            std::string name;
            std::cin >> name;
            try {
                std::cout << base.get_sum(name) << std::endl;
            } catch (KeyError& er) {
                std::cout << er.what() << std::endl;
            }
        }
    }
    return 0;
}




