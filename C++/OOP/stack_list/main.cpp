#include "StackList.h"
#include "bracketseq.h"

#include <iostream>

int main() {
    char * seq = new char[100000];
    std::cin >> seq;
    std::cout << (CheckBracketSequence(seq) ? "yes" : "no") << std::endl;
    
    Stack<int> s;
    s.Push(239);
    s.Push(566);
    s.Push(105);
    s.Push(24);
    std::cout << s.Min() << std::endl;
    std::cout << s.Max() << std::endl;
    std::cout << s.Top() << std::endl;
    std::cout << s.Size() << std::endl;
    std::cout << std::boolalpha << s.Empty() << std::endl;
    
    s.Pop();
    std::cout << s.Min() << std::endl;
    std::cout << s.Max() << std::endl;
    std::cout << s.Top() << std::endl;
    std::cout << s.Size() << std::endl;
    std::cout << std::boolalpha << s.Empty() << std::endl;

    s.Clear();
    std::cout << s.Size() << std::endl;
    std::cout << std::boolalpha << s.Empty() << std::endl;
    s.Pop();
    Stack<int> st;
    st.Pop();
    s.Push(566);
    std::cout << s.Size() << std::endl;
    std::cout << std::boolalpha << s.Empty() << std::endl;
    std::cout << s.Min() << std::endl;
    std::cout << s.Max() << std::endl;
    std::cout << s.Top() << std::endl;
    Stack<int> s1(100001, 5);
    std::cout << s1.Size() << std::endl;
    s1.Push(566);
    std::cout << s1.Top() << std::endl;
    std::cout << s1.Size() << std::endl;
    std::cout << std::boolalpha << s1.Empty() << std::endl;
    std::cout << s1.Min() << std::endl;
    std::cout << s1.Max() << std::endl;
    
    return 0;
}
