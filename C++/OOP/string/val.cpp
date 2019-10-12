#include <iostream>
#include <cstddef>

typedef std::size_t size_t;

class MyString {
private:
    char * buffer_;
    size_t size_;
    void CopyArray(const char * from, char * to);
public:
    MyString();
    MyString(const int n,
             const char symbol);
    MyString(const char * other);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other) {
        if (this == &other) {
            return *this;
        }
        delete[] buffer_;
        size_ = other.size_;
        buffer_ = new char[other.size_ + 1];
        CopyArray(other.buffer_, buffer_);
        return *this;
    }
    ~MyString();
    size_t Size() const;
    bool Compare(const MyString& other) const;
    void ToUpper();
    void ToLower();
    void Capitalize();
    bool IsSubstring(const MyString& other) const;
    void Print() const;
    void Read();
    char& At(const int index) const;
    void Reverse();
    void Clear();
    void Append(const MyString& other);
    void PushBack(const char symbol);
    static MyString Concatenate(const MyString& first,
                                const MyString& second);
};

void MyString::CopyArray(const char * from, char * to) {
    if (from == nullptr) {
        return;
    }
    for (int j = 0; j < std::strlen(from); ++j) {
        to[j] = from[j];
    }
}

MyString::MyString() {
    buffer_ = nullptr;
    size_ = 0;
}

MyString::MyString(const int n,
                   const char symbol) {
    size_ = n;
    buffer_ = new char[n+1];
    for (int j = 0; j < n; ++j) {
        buffer_[j] = symbol;
    }
}

MyString::MyString(const char * other) {
    
    if (other != nullptr) {
        buffer_ = new char[std::strlen(other)+1];
        CopyArray(other, buffer_);
        size_ = std::strlen(other);
    } else {
        size_ = 0;
        buffer_ = nullptr;
    }
}

MyString::MyString(const MyString & other) {
    size_ = other.size_;
    buffer_ = new char[other.size_ + 1];
    CopyArray(other.buffer_, buffer_);
}

MyString::~MyString() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
}

size_t MyString::Size() const {
    return size_;
}

bool MyString::Compare(const MyString & other) const {
    return strcmp(buffer_, other.buffer_) < 0;
}

void MyString::ToUpper() {
    for (int j = 0; j < size_; ++j) {
        buffer_[j] = std::toupper(buffer_[j]);
    }
}

void MyString::ToLower() {
    for (int j = 0; j < size_; ++j) {
        buffer_[j] = std::tolower(buffer_[j]);
    }
}

void MyString::Capitalize() {
    this->ToLower();
    buffer_[0] = std::toupper(buffer_[0]);
    for (int j = 1; j < size_; ++j) {
        if (buffer_[j - 1] == ' ') {
            buffer_[j] = std::toupper(buffer_[j]);
        }
    }
}

bool MyString::IsSubstring(const MyString & other) const {
    if (other.size_ < size_) {
        return false;
    }
    for (int startPosInOther = 0; startPosInOther < other.size_ - size_ + 1; ++startPosInOther) {
        bool otherContainsThis = true;
        for (int charIndexInThis = 0; charIndexInThis < size_; ++charIndexInThis) {
            if (other.buffer_[startPosInOther + charIndexInThis] != buffer_[charIndexInThis]) {
                otherContainsThis = false;
            }
        }
        if (otherContainsThis) {
            return true;
        }
    }
    return false;
}

void MyString::Print() const {
    std::cout << ((buffer_ == nullptr) ? "" : buffer_) << std::endl;
}

void MyString::Read() {
    int inputSize = 256;
    char * data = new char[inputSize];
    std::cin.getline(data, inputSize+1);
    delete[] buffer_;
    buffer_ = new char[std::strlen(data)+1];
    CopyArray(data, buffer_);
    size_ = std::strlen(data);
    delete[] data;
}

char & MyString::At(const int index) const {
    return buffer_[index];
}

void MyString::Reverse() {
    for (int j = 0; j < size_ / 2; ++j) {
        char temp = buffer_[j];
        buffer_[j] = buffer_[size_ - j - 1];
        buffer_[size_ - j - 1] = temp;
    }
}

void MyString::Clear() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
}

void MyString::Append(const MyString & other) {
    char * temp = new char [size_ + 1];
    CopyArray(buffer_, temp);
    delete[] buffer_;
    buffer_ = new char [size_ + other.size_ + 1];
    CopyArray(temp, buffer_);
    for (int j = size_; j < other.size_ + size_; ++j) {
        buffer_[j] = other.buffer_[j - size_];
    }
    size_ += other.size_;
    delete[] temp;
}

void MyString::PushBack(const char symbol) {
    char * temp = new char [size_ + 1];
    CopyArray(buffer_, temp);
    delete[] buffer_;
    buffer_ = new char [size_ + 1 + 1];
    CopyArray(temp, buffer_);
    buffer_[size_] = symbol;
    ++size_;
    delete[] temp;
}

MyString MyString::Concatenate(const MyString & first,
                               const MyString & second) {
    MyString s = first;
    s.Append(second);
    return s;
}

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
    return 0;
}
