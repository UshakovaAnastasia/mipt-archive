#include <iostream>

template <class T>
class Stack {
private:
    struct Node {
        T min;
        T value;
        T max;
        Node * next = nullptr;
    };
    Node * head_;
    int size_;
    
public:
    Stack();
    Stack(int n,
          const T & value);
    const T & Top();
    bool Empty();
    void Push(const T & value);
    void Pop();
    int Size();
    const T & Min();
    const T & Max();
    void Clear();
};

template <class T>
Stack <T>::Stack() {
    head_ = nullptr;
    size_ = 0;
}

template <class T>
Stack <T>::Stack(int n,
                 const T & data) {
    for (int i = 0; i < n; ++i) {
        Push(data);
    }
}

template <class T>
void Stack <T>::Clear() {
    while (!Empty()) {
        Pop();
    }
}

template <class T>
void Stack<T>::Push(const T & data) {
    Node * node = new Node;
    node->value = data;
    node->next = head_;
    if (size_ == 0) {
        node->max = data;
        node->min = data;
    } else {
        if (data>= head_->max) {
            node->max = data;
        } else {
            node->max = head_->max;
        }
        if (data <= head_->min) {
            node->min = data;
        } else {
            node->min = head_->min;
        }
    }
    head_ = node;
    ++size_;
}

template <class T>
const T & Stack<T>::Top() {
    if (head_ == nullptr) {
        return NULL;
    } else {
        return head_->value;
    }
}

template <class T>
void Stack<T>::Pop() {
    if (head_ != nullptr) {
        --size_;
        head_ = head_->next;
    } else {
        std::cout << "empty stack" <<std::endl;
    }
}

template <class T>
int Stack <T>::Size() {
    return size_;
}

template <class T>
const T & Stack<T>::Min() {
    return head_->min;
}

template <class T>
const T & Stack<T>::Max() {
    return head_->max;
}

template <class T>
bool Stack<T>::Empty() {
    return size_ == 0;
}

int main() {
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
    s.Clear();
    st.Clear();
    s1.Clear();
    return 0;
}
