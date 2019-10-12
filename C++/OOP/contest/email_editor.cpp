#include <iostream>
#include <list>
#include <algorithm>
#include <sstream>
#include <iterator>

class Text {
    std::list<char> text;
    std::list<char>::iterator position = text.begin();
public:
    Text(){}
    void edit(std::string seq) {
        for (int i = 0; i < seq.size(); ++i) {
            if (seq[i] == '<') {
                if (position != text.begin()) {
                    --position;
                }
            } else if (seq[i] == '>') {
                if (position != text.end()) {
                    ++position;
                }
            } else if (seq[i] == '#') {
                if (position != text.end()) {
                    std::list<char>::iterator del = position;
                    ++position;
                    text.erase(del);
                }
            } else if (seq[i] == '@') {
                if (position != text.begin()) {
                    //gg
                    std::list<char>::iterator del = --position;
                    ++position;
                    text.erase(del);
                }
            } else if (seq[i] == '^') {
                position = text.begin();
            } else if (seq[i] == '$') {
                position = text.end();
            } else if (seq[i] != '\n'){
                text.insert(position, seq[i]);
            }
        }
    }
    void print() {
        for (std::list<char>::iterator it = text.begin(); it != text.end(); ++it) {
            std::cout << *it;
        }
        std::cout << "\n";
    }
};

int main() {
    std::string line;
    std::getline(std::cin, line);
    Text t;
    t.edit(line);
    t.print();
    return 0;
}







