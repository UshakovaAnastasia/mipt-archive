#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstddef>

typedef std::size_t size_t;

class MyString {
private:
    char * buffer_;
    size_t size_;
    int capacity_;
    void CopyArray(const char * from, char * to);
    size_t Max(const size_t a, const size_t b) const;
public:
    MyString();
    MyString(const int n,
             const char symbol);
    MyString(const char * other);
    MyString(const MyString & other);
    MyString(MyString && other);
    ~MyString();
    size_t Size() const;
    int Capacity() const;
    bool Compare(const MyString & other) const;
    void ToUpper();
    void ToLower();
    void Capitalize();
    bool IsSubstring(const MyString & other) const;
    void Print() const;
    void Read();
    char & At(const int index) const;
    void Reverse();
    void Clear();
    void Append(const MyString & other);
    void PushBack(const char symbol);
    static MyString Concatenate(const MyString & first, const MyString & second);
    void ShrinkToFit();
    void Realloc(size_t size);
    
    char operator[](const int index) {
        if (index >= size_) {
            std::cout << "error" << std::endl;
        }
        return buffer_[index];
    }
    
    MyString& operator=(const MyString & other) {
        if (this == & other) {
            return *this;
        }
        delete[] buffer_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        buffer_ = new char[capacity_];
        CopyArray(other.buffer_, buffer_);
        return *this;
    }
    
    MyString& operator=(MyString && other) {
        if (this == &other) {
            return *this;
        }
        delete[] buffer_;
        buffer_ = other.buffer_;
        size_ = other.size_;
        other.size_ = 0;
        capacity_ = other.capacity_;
        other.capacity_ = 0;
        other.buffer_ = nullptr;
        return *this;
    }
    
    friend void operator+=(MyString & lhs, const MyString & rhs);
    friend MyString operator*(const MyString & string, const int multiplier);
    friend bool operator==(const MyString & lhs, const MyString & rhs);
    friend bool operator<(const MyString & lhs, const MyString & rhs);
    friend bool operator<=(const MyString & lhs, const MyString & rhs);
    friend bool operator>(const MyString & lhs, const MyString & rhs);
    friend bool operator>=(const MyString & lhs, const MyString & rhs);
    friend std::istream& operator>>(std::istream & is, MyString & string);
    friend std::ostream& operator<<(std::ostream & os, const MyString & string);
    friend MyString operator*(const int multiplier, const MyString & string);
    friend MyString operator+(const MyString & lhs, const MyString & rhs);
};

#endif
