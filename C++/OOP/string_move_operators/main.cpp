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
    std::cout << s.Capacity() << std::endl;
    std::cout << s1.Capacity() << std::endl;
    std::cout << s2.Capacity() << std::endl;
    std::cout << s3.Capacity() << std::endl;
    std::cout << s4.Capacity() << std::endl;
    MyString s5(first);
    s1.ToUpper();
    s1.Print();
    s1.ToLower();
    s1.Print();
    s5.Capitalize();
    s5.Print();
    s5.Append(s1);
    s5.Print();
    std::cout << s5.Size() << std::endl;
    std::cout << s5.Capacity() << std::endl;
    std::cout << std::boolalpha << s1.IsSubstring(s5) << std::endl;
    std::cout << s5.At(0) << std::endl;
    std::cout << s5.At(256) << std::endl;
    MyString s6(s5);
    s6.PushBack('5');
    std::cout << s6.Size() << std::endl;
    std::cout << s6.Capacity() << std::endl;
    s6.Print();
    s5.Reverse();
    MyString s7 = MyString::Concatenate(s5, s6);
    MyString x("12345");
    MyString y("123456");
    MyString z("12345");
    std::cout << std::boolalpha << (x > y) << std::endl;
    std::cout << std::boolalpha << (x >= y) << std::endl;
    std::cout << std::boolalpha << (x < y) << std::endl;
    std::cout << std::boolalpha << (x <= y) << std::endl;
    std::cout << std::boolalpha << (x == y) << std::endl;
    std::cout << std::boolalpha << (x > z) << std::endl;
    std::cout << std::boolalpha << (x >= z) << std::endl;
    std::cout << std::boolalpha << (x < z) << std::endl;
    std::cout << std::boolalpha << (x <= z) << std::endl;
    std::cout << std::boolalpha << (x == z) << std::endl;
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
    std::cout << s2.Capacity() << std::endl;
    s2.ShrinkToFit();
    s2.Print();
    std::cout << s2.Size() << std::endl;
    std::cout << s2.Capacity() << std::endl;
    s2.Realloc(1);
    s2.Realloc(256);
    std::cout << s2.Size() << std::endl;
    std::cout << s2.Capacity() << std::endl;
    s4.Print();
    MyString str = s4 + s6;
    str.Print();
    std::cout << str.Size() << std::endl;
    std::cout << str.Capacity() << std::endl;
    str += s1;
    str.Print();
    std::cout << str.Size() << std::endl;
    std::cout << str.Capacity() << std::endl;
    std::cout << str[0] << std::endl;
    std::cout << str[256] << std::endl;
    s1 = s1 * 5;
    s1.Print();
    std::cout << s1.Size() << std::endl;
    std::cout << s1.Capacity() << std::endl;
    std::cout << x << ' ' << x + "str" << ' ' << "str" + x << std::endl;
    MyString string;
    std::cin >> string;
    std::cout << string << std::endl;
    std::cout << string.Size() << std::endl;
    std::cout << string.Capacity() << std::endl;
    std::cout << 3 * string << std::endl;
    std::cout << s << std::endl;
    s.PushBack('d');
    std::cout << s << std::endl;
    s.Clear();
    s.Append("dd");
    std::cout << s << std::endl;
    return 0;
}
