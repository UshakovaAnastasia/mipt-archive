#include "bracketseq.h"
#include "StackList.h"

char openBrackets [4]  = {'(', '[', '{'};
char closeBrackets [4] = {')', ']', '}'};

int findPositionOfOpen (char character) {
    for (int i = 0; i < std::strlen(openBrackets); ++i) {
        if (openBrackets[i] == character){
            return i;
        }
    }
    return -1;
}

int findPositionOfClose (char character) {
    for (int i = 0; i < std::strlen(closeBrackets); ++i) {
        if (closeBrackets[i] == character){
            return i;
        }
    }
    return -1;
}

bool BracketsMatch(char open, char close) {
    return findPositionOfOpen(open) == findPositionOfClose(close);
}

bool OpenBracket(char bracket) {
    if (findPositionOfOpen(bracket) == -1) {
        return false;
    }
    return true;
}

bool CloseBracket(char bracket) {
    if (findPositionOfClose(bracket) == -1) {
        return false;
    }
    return true;
}

bool CheckBracketSequence(char * s) {
    Stack<char> st;
    for (int i = 0; i < std::strlen(s); ++i) {
        if (OpenBracket(s[i])) {
            st.Push(s[i]);
        } else if (CloseBracket(s[i])) {
            if (!BracketsMatch(st.Top(), s[i])) {
                return false;
            }
            st.Pop();
        }
    }
    if (!st.Empty()) {
        return false;
    }
    return true;
}

