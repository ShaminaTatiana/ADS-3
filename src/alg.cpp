// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char x) {
    switch (x) {
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
    int i = 0;
    char top = 0;
    TStack <char> stackChar;
    std::string out;
    for (i ; i < inf.length() ; i++) {
        int prior;
        prior = priority(inf[i]);
        if (prior > -1) {
            if ((prior == 0 || prior > priority(top) ||
                 stackChar.isEmpty()) && inf[i] != ')') {
                if (stackChar.isEmpty())
                    top = inf[i];
                stackChar.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stackChar.get() != '(') {
                    out.push_back(stackChar.get());
                    out.push_back(' ');
                    stackChar.pop();
                }
                stackChar.pop();
                if (stackChar.isEmpty())
                    top = 0;
            } else {
                while (!stackChar.isEmpty() &&
                       priority(stackChar.get()) >= prior) {
                    out.push_back(stackChar.get());
                    out.push_back(' ');
                    stackChar.pop();
                }
                if (stackChar.isEmpty())
                    top = inf[i];
                stackChar.push(inf[i]);
            }
        } else {
            out.push_back(inf[i]);
            out.push_back(' ');
        }
    }
    while (!stackChar.isEmpty()) {
        out.push_back(stackChar.get());
        out.push_back(' ');
        stackChar.pop();
    }
    out.erase(out.end() - 1, out.end());
    return out;
}
int vichisl(char operate, int number1, int number2) {
switch (operate) {
case '+':
return number1 + number2;
break;
case '-':
return number1 - number2;
break;
case '*':
return number1 * number2;
break;
case '/':
return number1 / number2;
break;
}
}

int eval(std::string pst) {
    TStack <int> stackInt;
    int i = 0, result = 0;
    char x = pst[i];
    while (x) {
        if (x >= '0' && x <= '9') {
            int insertInt = 0;
            int dec = 1;
            while (x != ' ') {
                insertInt += (x - 48) * dec;
                dec *= 10;
                x = pst[++i];
            }
            stackInt.push(insertInt);
        } else {
            char operate = x;
            i++;
            int number2 = stackInt.get();
            stackInt.pop();
            int number1 = stackInt.get();
            stackInt.pop();
            int result = calculating(operate, number1, number2);
            stackInt.push(result);
        }
        if (i < pst.size())
            x = pst[++i];
        else
            x = 0;
    }
    result = stackInt.get();
    stackInt.pop();
    return result;
}
