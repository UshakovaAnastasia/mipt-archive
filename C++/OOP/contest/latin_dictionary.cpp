#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <exception>
#include <string>
#include <sstream>

class Dictionary {
    std::map<std::string, std::set<std::string>> dictionary;
public:
    Dictionary(){}
    void add_words(std::string line) {
        std::stringstream ss(line);
        std::string english;
        char dash;
        ss >> english >> dash;
        std::string latin;
        while(ss >> latin) {
            if (latin.back() == ',') {
                latin.pop_back();
            }
            dictionary[latin].insert(english);
        }
    }
    size_t size() const {
        return dictionary.size();
    }
    friend std::istream& operator>>(std::istream& is, Dictionary& dict) {
        std::string line;
        while (std::getline(is, line)) {
            dict.add_words(line);
        }
        return is;
    }
    void print() const {
        for (auto x = dictionary.begin(); x != dictionary.end(); ++x) {
            std::cout << x->first << " - ";
            int len = 0;
            for (auto it = (x->second).begin(); it != (x->second).end(); ++it) {
                std::cout << (*it) << (len < (x->second.size() - 1) ? ", " : "\n");
                ++len;
            }
        }
    }
    
};

int main() {
    Dictionary lat_en;
    std::cin >> lat_en;
    std::cout << lat_en.size() << "\n";
    lat_en.print();
    return 0;
}





