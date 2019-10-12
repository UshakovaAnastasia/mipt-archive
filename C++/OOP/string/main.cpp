#include "MyString.h"

#include <iostream>

int main()
{
    const char * first = "tHis string, please";
    char c[7] = { 'a', 'b', 'c', 'b', 'c', 'b', '\0' };
    const char * data = c;
    MyString s;
    MyString s1(6, 'f');
    MyString s2(data);
    std::cout << std::boolalpha << (s1.Compare(s2)) << std::endl;
    MyString s3(s1);
    MyString s4 = s2;
    s.Print();
    s1.Print();
    s2.Print();
    s3.Print();
    s4.Print();
    std::cout << s.Size() << std::endl;
    std::cout << s1.Size() << std::endl;
    std::cout << s2.Size() << std::endl;
    std::cout << s3.Size() << std::endl;
    std::cout << s4.Size() << std::endl;
    MyString s5(first);
    s1.ToUpper();
    s1.Print();
    s1.ToLower();
    s1.Print();
    s5.Capitalize();
    s5.Print();
    s5.Append(s1);
    s5.Print();
    std::cout << std::boolalpha << s1.IsSubstring(s5) << std::endl;
    std::cout << s5.At(0) << std::endl;
    MyString s6(s5);
    s6.PushBack('5');
    s6.Print();
    s5.Reverse();
    MyString s7 = MyString::Concatenate(s5, s6);
    MyString x("12345");
    MyString y("123456");
    x.Reverse();
    y.Reverse();
    x.Print();
    y.Print();
    s5.Print();
    std::cout << std::boolalpha << s1.IsSubstring(s5) << std::endl;
    s5.Clear();
    s5.Print();
    s7.Print();
    std::cout << s5.Size() << std::endl;
    std::cout << std::boolalpha << s1.IsSubstring(s2) << std::endl;
    const char * second = "String";
    MyString sub(second);
    std::cout << std::boolalpha << sub.IsSubstring(s7) << std::endl;
    s2.Read();
    s2.Print();
    std::cout << s2.Size() << std::endl;
    s.PushBack('d');
    s.Print();
    s.Clear();
    s.Append("ddd");
    s.Print();
    return 0;
}
