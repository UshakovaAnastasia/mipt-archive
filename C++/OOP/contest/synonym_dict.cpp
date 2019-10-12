#include <iostream>
#include <unordered_map>
#include <string>

class SynonymDictionary {
    std::unordered_map<std::string, std::string> dict;
public:
    void add (const std::string& first, const std::string& second) {
        dict[first] = second;
        dict[second] = first;
    }
    std::string synonym(const std::string& query) {
        return dict[query];
    }
};

int main() {
    SynonymDictionary d;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string first;
        std::string second;
        std::cin >> first >> second;
        d.add(first, second);
    }
    std::string word;
    std::cin >> word;
    std::cout << d.synonym(word) << std::endl;
    return 0;
}



