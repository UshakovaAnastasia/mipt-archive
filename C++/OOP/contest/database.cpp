#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#include <sstream>

class Database {
    std::map<std::string, std::map<std::string, long long>> db;
public:
    Database(){}
    void add_info(std::string line) {
        std::stringstream ss(line);
        std::string name;
        std::string goods;
        int number;
        ss >> name >> goods >> number;
        db[name][goods] += number;
    }
    friend std::istream& operator>>(std::istream& is, Database& database) {
        std::string line;
        while (std::getline(is, line)) {
            database.add_info(line);
        }
        return is;
    }
    void print() const {
        for (auto x = db.begin(); x != db.end(); ++x) {
            std::cout << x->first << ":\n";
            for (auto it = (x->second).begin(); it != (x->second).end(); ++it) {
                std::cout << it->first << " " << it->second << "\n";
            }
        }
    }
    
};

int main() {
    Database database;
    std::cin >> database;
    database.print();
    return 0;
}





