// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch) {
    switch (ch) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    default:
        return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string pstfx;
    int i = 0;
    char ch = inf[i];
    char top = 0;
    TStack <char> stackChar;
    while (ch) {
        int p;
        p = priority(ch);

        if (p > -1) {
            if ((p == 0 || p > priority(top) ||
                stackChar.isEmpty()) && ch != ')') {
                if (stackChar.isEmpty())
                    top = ch;
                stackChar.push(ch);
            } else if (ch == ')') {
                while (stackChar.get() != '(') {
                    pstfx.push_back(stackChar.get());
                    pstfx.push_back(' ');
                    stackChar.pop();
                }
                stackChar.pop();
                if (stackChar.isEmpty())
                    top = 0;
            } else {
                while (!stackChar.isEmpty() &&
                       priority(stackChar.get()) >= p) {
                    pstfx.push_back(stackChar.get());
                    pstfx.push_back(' ');
                    stackChar.pop();
                }
                if (stackChar.isEmpty())
                    top = ch;
                stackChar.push(ch);
            }
        } else {
            pstfx.push_back(ch);
            pstfx.push_back(' ');
        }

        ch = inf[++i];
    }
    while (!stackChar.isEmpty()) {
        pstfx.push_back(stackChar.get());
        pstfx.push_back(' ');
        stackChar.pop();
    }
    pstfx.erase(pstfx.end() - 1, pstfx.end());
    return pstfx;
}

int calculating(char oper, int num1, int num2) {
    switch (oper) {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    }
}

int eval(std::string pst) {
    TStack <int> stackInt;
    int i = 0, res = 0;
    char ch = pst[i];
    while (ch) {
        if (ch >= '0' && ch <= '9') {
            int insertInt = 0;
            int x = 1;
            while (ch != ' ') {
                insertInt += (ch - 48) * x;
                x *= 10;
                xch= pst[++i];
            }
            stackInt.push(insertInt);
        } else {
            char oper = ch;
            i++;
            int num2 = stackInt.get();
            stackInt.pop();
            int num1 = stackInt.get();
            stackInt.pop();
            int res = calculating(oper, num1, num2);
            stackInt.push(res);
        }
        if (i < pst.size())
            ch = pst[++i];
        else
            ch = 0;
    }
    res = stackInt.get();
    stackInt.pop();
    return res;
}
