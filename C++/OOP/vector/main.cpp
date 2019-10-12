#include "vector.h"

#include <iostream>
#include <stdexcept>

int main() {
    Vector<int> v;
    Vector<int> u(5);
    Vector<int> z(6, 11);
    Vector<char> w(7, '&');
    Vector<int> a(u);
    Vector<char> b = w;
    v.Print();
    u.Clear();
    z.Print();
    u.Print();
    w.Clear();
    w.Print();
    a.Print();
    b.Print();
    std::cout << v.Capacity() << std::endl;
    std::cout << v.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    std::cout << u.Size() << std::endl;
    std::cout << w.Capacity() << std::endl;
    std::cout << w.Size() << std::endl;
    std::cout << a.Capacity() << std::endl;
    std::cout << a.Size() << std::endl;
    std::cout << b.Capacity() << std::endl;
    std::cout << b.Size() << std::endl;
    std::cout << std::boolalpha << v.Empty() << std::endl;
    std::cout << u.Empty() << std::endl;
    std::cout << w.Empty() << std::endl;
    std::cout << a.Empty() << std::endl;
    std::cout << b.Empty() << std::endl;
    b.Reserve(3);
    a.ShrinkToFit();
    w.ShrinkToFit();
    std::cout << b.Capacity() << " " << a.Capacity() << " " << w.Capacity() << std::endl;
    b.Reserve(50);
    std::cout << b.Capacity() << std::endl;
    b.Resize(4);
    b.Print();
    a.Resize(8, 1);
    a.Print();
    std::cout << a.Capacity() << std::endl;
    v.Resize(5, 1);
    v.Print();
    std::cout << v.Capacity() << std::endl;
    v.Front() = 2;
    v.Back() = 3;
    v.At(1) = 5;
    v.Print();
    w.Resize(5, ')');
    w.Print();
    std::cout << w.Capacity() << std::endl;
    try {
        w.Reserve(w.MaxSize());
    } catch (std::length_error& err) {
        std::cout << "can't reserve more than " << w.MaxSize() << std::endl;
    }
    std::cout << v.Front() << " " << v.Back() << " " << v.At(2) << " " << std::endl;
    try {
       v.At(100) = 5;
    } catch (std::out_of_range& err) {
        std::cout << "index out of range" << std::endl;
    }
    v.Print();
    w[0] = '(';
    w[4] = '(';
    w.Print();
    std::cout << w[0] << " " << w[1] << " " << w[4] << std::endl;
    std::cout << w[44] << std::endl;
    w.Print();
    int* p = v.Data();
    p[2] = 105;
    v.Print();
    for (int i = 0; i < v.Size(); ++i) {
         std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    b.Assign(2, 'a');
    b.Print();
    std::cout << b.Capacity() << std::endl;
    b.PushBack('x');
    b.Print();
    std::cout << b.Capacity() << std::endl;
    b.ShrinkToFit();
    b.PushBack('y');
    b.Print();
    std::cout << b.Capacity() << std::endl;
    w.PopBack();
    w.Print();
    std::cout << w.Size() << std::endl;
    std::cout << u.Empty() << std::endl;
    u.PopBack();
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Insert(0, 1);
    u.Print();
    u.Insert(0, 19, 3);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Insert(1, 0, 8);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Erase(10);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Erase(1, 9);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Erase(1, 3);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    u.Swap(v);
    u.Print();
    std::cout << u.Size() << std::endl;
    std::cout << u.Capacity() << std::endl;
    v.Print();
    std::cout << v.Size() << std::endl;
    std::cout << v.Capacity() << std::endl;
    Vector<char> apple;
    Vector<char> box;
    apple.PushBack('a');
    apple.PushBack('p');
    apple.PushBack('p');
    apple.PushBack('l');
    apple.PushBack('e');
    box.PushBack('b');
    box.PushBack('o');
    box.PushBack('x');
    std::cout << (apple == box) << std::endl;
    std::cout << (apple < box) << std::endl;
    std::cout << (apple > box) << std::endl;
    std::cout << (apple <= box) << std::endl;
    std::cout << (apple >= box) << std::endl;
    std::cout << (apple != box) << std::endl;
    apple.Assign(2, 'a');
    box.Assign(2, 'a');
    box.Print();
    std::cout << (apple == box) << std::endl;
    std::cout << (apple < box) << std::endl;
    std::cout << (apple > box) << std::endl;
    std::cout << (apple <= box) << std::endl;
    std::cout << (apple >= box) << std::endl;
    std::cout << (apple != box) << std::endl;
    return 0;
}

