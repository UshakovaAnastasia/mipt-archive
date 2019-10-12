#include "postfixnotation.h"
#include "StackArray.h"

#include <iostream>

int GetAnswer(std::istream & is) {
    Stack <int> st;
    char z;
    while (is >> z) {
        if (isdigit(z)) {
            st.Push(z - '0');
        } else {
            int x = st.Top();
            st.Pop();
            int y = st.Top();
            st.Pop();
            if (z == '+') {
                st.Push(x + y);
            } else if (z == '*'){
                st.Push(x * y);
            } else if (z == '-'){
                st.Push(y - x);
            }
        }
    }
    return st.Top();
}
