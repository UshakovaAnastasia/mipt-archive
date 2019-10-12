#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <sstream>
#include <string>
#include <iterator>

class Phonebook {
    std::unordered_map<std::string, std::set<std::string>> phone_names;
    std::unordered_set<std::string> names;
    std::unordered_map<std::string, std::set<std::string>> name_phone;
    std::unordered_map<std::string, std::string> name_email;
    static std::string phone_cleaned(const std::string& phone) {
        std::string result = "";
        for (int i = 0; i < phone.size(); ++i) {
            if (phone[i] != '-' && phone[i] != '(' && phone[i] != ')' && phone[i] != '+') {
                result.push_back(phone[i]);
            }
        }
        return result;
    }
public:
    Phonebook(){}
    bool add_person(const std::string& name) {
        if (names.find(name) != names.end()) {
            return false;
        }
        names.insert(name);
        return true;
    }
    bool add_person_phone(const std::string& name, const std::string& phone) {
        if (names.find(name) != names.end()) {
            return false;
        }
        names.insert(name);
        name_phone[name].insert(phone);
        phone_names[phone].insert(name);
        return true;
    }
    bool add_person_email(const std::string& name, const std::string& email) {
        if (names.find(name) != names.end()) {
            return false;
        }
        names.insert(name);
        name_email[name] = email;
        return true;
    }
    bool add_person_both(const std::string& name, const std::string& phone, const std::string& email) {
        if (names.find(name) != names.end()) {
            return false;
        }
        names.insert(name);
        name_phone[name].insert(phone);
        phone_names[phone].insert(name);
        name_email[name] = email;
        return true;
    }
    bool add_phone(const std::string& name, const std::string& phone) {
        if (names.find(name) == names.end()) {
            return false;
        }
        if (name_phone[name].find(phone) != name_phone[name].end()) {
            return false;
        }
        name_phone[name].insert(phone);
        phone_names[phone].insert(name);
        return true;
    }
    bool replace_phone(const std::string& name, const std::string& old_phone, const std::string& new_phone) {
        if (names.find(name) == names.end()) {
            return false;
        }
        if (name_phone[name].find(old_phone) == name_phone[name].end()) {
            return false;
        }
        if (name_phone[name].find(new_phone) != name_phone[name].end()) {
            return false;
        }
        name_phone[name].erase(old_phone);
        name_phone[name].insert(new_phone);
        phone_names[old_phone].erase(name);
        if (phone_names[old_phone].empty()) {
            phone_names.erase(old_phone);
        }
        phone_names[new_phone].insert(name);
        return true;
    }
    bool replace_email(const std::string& name, const std::string& email) {
        if (names.find(name) == names.end()) {
            return false;
        }
        name_email[name] = email;
        return true;
    }
    bool delete_person(const std::string& name) {
        if (names.find(name) == names.end()) {
            return false;
        }
        for (auto it = name_phone[name].begin(); it != name_phone[name].end(); ++it) {
            std::string phone = *it;
            phone_names[phone].erase(name);
            if (phone_names[phone].empty()) {
                phone_names.erase(phone);
            }
        }
        name_phone.erase(name);
        name_email.erase(name);
        names.erase(name);
        return true;
    }
    bool delete_phone(const std::string& name, const std::string& phone) {
        if (names.find(name) == names.end()) {
            return false;
        }
        if (name_phone[name].find(phone) == name_phone[name].end()) {
            return false;
        }
        name_phone[name].erase(phone);
        phone_names[phone].erase(name);
        if (phone_names[phone].empty()) {
            phone_names.erase(phone);
        }
        return true;
    }
    void print_person(const std::string& name) {
        if (names.find(name) == names.end()) {
            std::cout << "FAIL\n";
            return;
        }
        std::cout << "Name: " << name << ((name_phone[name].empty() && name_email.find(name) == name_email.end()) ? "\n" : "; ");
        if (!name_phone[name].empty()) {
            std::cout << "Phones: ";
            for (auto it = name_phone[name].begin(); it != name_phone[name].end(); ++it) {
                auto next = it;
                ++next;
                std::cout << *it << (next == name_phone[name].end() ? (name_email.find(name) == name_email.end() ? "\n" : "; ") : ", ");
            }
        }
        if (name_email.find(name) != name_email.end()) {
            std::cout << "Email: " << name_email[name] << "\n";
        }
    }
    void print_phone(const std::string& phone) {
        if (phone_names.find(phone) == phone_names.end()) {
            std::cout << "FAIL\n";
            return;
        }
        std::cout << "Names: ";
        for (auto it = phone_names[phone].begin(); it != phone_names[phone].end(); ++it) {
            auto next = it;
            ++next;
            std::cout << *it << (next == phone_names[phone].end() ? "\n" : ", ");
        }
    }
    void process_command(const std::string& line) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        std::string object;
        ss >> object;
        if (command == "add" && object == "person") {
            std::string name;
            std::string token;
            std::string phone;
            std::string email;
            bool br = false;
            ss >> name;
            while (ss >> token) {
                for (int i = 0; i < token.size(); ++i) {
                    if (std::isdigit(token[i]) || token[i] == '@') {
                        br = true;
                    }
                }
                if (!br) {
                    name += " ";
                    name += token;
                } else {
                    break;
                }
            }
            if (!br) {
                std::cout << (add_person(name) ? "DONE" : "FAIL") << std::endl;
            } else if (token.find('@') != -1) {
                email = token;
                while (ss >> phone) {
                    std::cout << (add_person_both(name, phone_cleaned(phone), email) ? "DONE" : "FAIL") << std::endl;
                    return;
                }
                std::cout << (add_person_email(name, email) ? "DONE" : "FAIL") << std::endl;
            } else {
                phone = token;
                while (ss >> email) {
                    std::cout << (add_person_both(name, phone_cleaned(phone), email) ? "DONE" : "FAIL") << std::endl;
                    return;
                }
                std::cout << (add_person_phone(name, phone_cleaned(phone)) ? "DONE" : "FAIL") << std::endl;
            }
        } else if (command == "add" && object == "phone") {
            std::string name;
            std::string token;
            std::string phone;
            bool br = false;
            ss >> name;
            while (ss >> token) {
                for (int i = 0; i < token.size(); ++i) {
                    if (std::isdigit(token[i])) {
                        br = true;
                        break;
                    }
                }
                if (!br) {
                    name += " ";
                    name += token;
                } else {
                    phone = token;
                    break;
                }
            }
            std::cout << (add_phone(name, phone_cleaned(phone)) ? "DONE" : "FAIL") << std::endl;
        } else if (command == "replace" && object == "phone") {
            std::string name;
            std::string token;
            std::string old_phone;
            std::string phone;
            bool br = false;
            ss >> name;
            while (ss >> token) {
                for (int i = 0; i < token.size(); ++i) {
                    if (std::isdigit(token[i])) {
                        br = true;
                        break;
                    }
                }
                if (!br) {
                    name += " ";
                    name += token;
                } else {
                    old_phone = token;
                    break;
                }
            }
            ss >> phone;
            std::cout << (replace_phone(name, phone_cleaned(old_phone), phone_cleaned(phone)) ? "DONE" : "FAIL") << std::endl;
        } else if (command == "replace" && object == "email") {
            std::string name;
            std::string token;
            std::string email;
            bool br = false;
            ss >> name;
            while (ss >> token) {
                for (int i = 0; i < token.size(); ++i) {
                    if (token[i] == '@') {
                        br = true;
                        break;
                    }
                }
                if (!br) {
                    name += " ";
                    name += token;
                } else {
                    email = token;
                    break;
                }
            }
            std::cout << (replace_email(name, email) ? "DONE" : "FAIL") << std::endl;
        } else if (command == "delete" && object == "person") {
            std::string name;
            std::string token;
            ss >> name;
            while (ss >> token) {
                name += " ";
                name += token;
            }
            std::cout << (delete_person(name) ? "DONE" : "FAIL") << std::endl;
        } else if (command == "delete" && object == "phone") {
            std::string name;
            std::string token;
            std::string phone;
            bool br = false;
            ss >> name;
            while (ss >> token) {
                for (int i = 0; i < token.size(); ++i) {
                    if (std::isdigit(token[i])) {
                        br = true;
                        break;
                    }
                }
                if (!br) {
                    name += " ";
                    name += token;
                } else {
                    phone = token;
                    break;
                }
            }
            std::cout << (delete_phone(name, phone_cleaned(phone)) ? "DONE" : "FAIL") << std::endl;
        } else if (command == "print" && object == "person") {
            std::string name;
            std::string token;
            ss >> name;
            while (ss >> token) {
                name += " ";
                name += token;
            }
            print_person(name);
        } else if (command == "print" && object == "phone") {
            std::string phone;
            ss >> phone;
            print_phone(phone_cleaned(phone));
        }
    }
};

int main() {
    std::string line;
    Phonebook book;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "finish") {
            break;
        }
        book.process_command(line);
    }
    return 0;
}
