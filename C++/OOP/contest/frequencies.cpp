#include <iostream>
#include <unordered_map>
#include <list>
#include <tuple>
#include <exception>
#include <string>
#include <sstream>

bool cmp (const std::tuple<int, std::string>& first, const std::tuple<int, std::string>& second) {
    if (std::get<0>(first) > std::get<0>(second)) {
        return true;
    }
    if (std::get<0>(first) < std::get<0>(second)) {
        return false;
    }
    return std::get<1>(first).compare(std::get<1>(second)) < 0;
}
        
struct Frequencies {
    std::unordered_map<std::string, int> f;
    void incr_counter(const std::string& word) {
        if (f.find(word) == f.end()) {
            f[word] = 1;
        } else {
            ++f[word];
        }
    }
};

int main() {
    Frequencies f;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string token;
        while(ss >> token) {
            f.incr_counter(token);
        }
    }
    std::list<std::tuple<int, std::string>> freq;
    for (auto const& x : f.f) {
        freq.push_back(std::make_tuple(x.second, x.first));
    }
    freq.sort(cmp);
    for (auto const& i : freq) {
        std::cout << std::get<1>(i) << std::endl;
    }
    return 0;
}





