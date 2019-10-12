#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

class TextEditor {
    std::vector<std::string> text;
    bool newly_constructed;
    
    struct Cursor {
        size_t row;
        size_t col;
        Cursor (size_t row_ind = 0, size_t col_ind = 0) : row(row_ind), col(col_ind) {}
    };
    
    Cursor c;
    
    class Action {
    protected:
        const Cursor pos;
    public:
        Action(size_t row, size_t col) : pos(row, col) {}
        virtual void  Do(TextEditor& t) = 0;
        virtual void  Undo(TextEditor& t) = 0;
        virtual ~Action() {}
        size_t row() const {
            return pos.row;
        }
        size_t col() const {
            return pos.col;
        }
    };
    
    std::stack<Action*> Done;
    std::stack<Action*> Undone;
    
    class Insertion: public Action {
    protected:
        char symbol;
    public:
        Insertion(char s, size_t row, size_t col) : Action::Action(row, col), symbol(s) {}
        void Do(TextEditor& t) {
            if (symbol != '\n') {
                t[pos.row].insert(pos.col, std::string(1, symbol));
                t.col() = pos.col + 1;
                t.row() = pos.row;
            } else {
                std::string next = t[pos.row].substr(pos.col);
                t[pos.row].erase(pos.col);
                t.insert(t.begin() + pos.row + 1, 1, next);
                t.row() = pos.row + 1;
                t.col() = 0;
            }
        }
        void Undo(TextEditor& t) {
            if (symbol != '\n') {
                t[pos.row].erase(pos.col, 1);
            } else {
                t[pos.row] += t[pos.row + 1];
                t.erase(t.begin() + pos.row + 1);
            }
            t.col() = pos.col;
            t.row() = pos.row;
        }
    };
    
    class Deletion: public Action {
    protected:
        char symbol;
    public:
        Deletion(size_t row, size_t col) : Action::Action(row, col) {}
        void Do(TextEditor& t) {
            if (pos.col != t[pos.row].size()) {
                symbol = t(pos.row, pos.col);
                t[pos.row].erase(pos.col, 1);
            } else if (pos.row != t.size() - 1){
                t[pos.row] += t[pos.row + 1];
                t.erase(t.begin() + pos.row + 1);
                symbol = '\n';
            }
            t.row() = pos.row;
            t.col() = pos.col;
        }
        void Undo(TextEditor& t) {
            if (symbol == '\n') {
                std::string next = t[pos.row].substr(pos.col);
                t[pos.row].erase(pos.col);
                t.insert(t.begin() + pos.row + 1, 1, next);
            } else {
                t[pos.row].insert(pos.col, std::string(1, symbol));
            }
            t.row() = pos.row;
            t.col() = pos.col;
        }
    };
    
    bool ValidDelete() {
        if (c.col == text[c.row].size() && c.row == text.size() - 1) {
            return false;
        }
        return true;
    }
    char operator()(size_t row, size_t col) const {
        return text[row][col];
    }
    char& operator()(size_t row, size_t col) {
        return text[row][col];
    }
    size_t& row() {
        return c.row;
    }
    size_t& col() {
        return c.col;
    }
    std::string operator[](size_t row) const {
        return text[row];
    }
    std::string& operator[](size_t row) {
        return text[row];
    }
    size_t size() const {
        return text.size();
    }
    void erase(std::vector<std::string>::iterator it) {
        text.erase(it);
    }
    void insert(std::vector<std::string>::iterator pos, size_t number, const std::string& s) {
        text.insert(pos, number, s);
    }
    std::vector<std::string>::iterator begin() {
        return text.begin();
    }
public:
    TextEditor() {
        text.push_back("");
        newly_constructed = true;
    }
    ~TextEditor() {
        while (!Undone.empty()) {
            delete Undone.top();
            Undone.pop();
        }
        while (!Done.empty()) {
            delete Done.top();
            Done.pop();
        }
    }
    void Right() {
        if (c.col != text[c.row].size()) {
            ++c.col;
        } else if (c.row != text.size() - 1){
            c.col = 0;
            ++c.row;
        }
    }
    void Left() {
        if (c.col != 0) {
            --c.col;
        } else if (c.row != 0) {
            c.col = text[c.row - 1].size();
            --c.row;
        }
    }
    void Up() {
        if (c.row != 0) {
            if (text[c.row - 1].size() < text[c.row].size() && c.col > text[c.row - 1].size()) {
                c.col = text[c.row - 1].size();
            }
            --c.row;
        }
    }
    void Down() {
        if (c.row != text.size() - 1) {
            if (text[c.row + 1].size() < text[c.row].size() && c.col > text[c.row + 1].size()) {
                c.col = text[c.row + 1].size();
            }
            ++c.row;
        }
    }
    void Insert(char s) {
        Action* act;
        act = new Insertion(s, c.row, c.col);
        act->Do(*this);
        Done.push(act);
        while (!Undone.empty()) {
            delete Undone.top();
            Undone.pop();
        }
    }
    void Delete() {
        if (ValidDelete()) {
            Action* act;
            act = new Deletion(c.row, c.col);
            act->Do(*this);
            Done.push(act);
            while (!Undone.empty()) {
                delete Undone.top();
                Undone.pop();
            }
        }
    }
    void Undo() {
        if (!Done.empty()) {
            Done.top()->Undo(*this);
            Undone.push(Done.top());
            Done.pop();
        }
    }
    void Redo() {
        if (!Undone.empty()) {
            Undone.top()->Do(*this);
            Done.push(Undone.top());
            Undone.pop();
        }
    }
    void edit(char s) {
        if (s == '<') {
            Left();
        } else if (s == '>') {
            Right();
        } else if (s == '^') {
            Up();
        } else if (s == '|') {
            Down();
        } else if (s == '#') {
            Delete();
        } else if (s == '@') {
            Undo();
        } else if (s == '$') {
            Redo();
        } else {
            Insert(s);
        }
    }
    void print() {
        for (auto it = text.begin(); it != text.end(); ++it) {
            std::cout << *it << "\n";
        }
    }
};

int main() {
    TextEditor t;
    for(;;) {
        char symbol = std::cin.get();
        if (symbol == std::char_traits<char>::eof()) {
            break;
        }
        t.edit(symbol);
    }
    t.print();
    return 0;
}
