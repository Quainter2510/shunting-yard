
#ifndef SHUNTING_YARD_TOKEN_H
#define SHUNTING_YARD_TOKEN_H

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>

struct Token {

    enum class Type {
        Number = 0,
        Operator,
        Function,
        LeftBracket,
        RightBracket,
        UnaryMinus
    };
    enum class Associativity {
        Left = 0,
        Right
    };
    Type type;
    int priority;
    Associativity associativity;
    const std::string token;
    Token(const std::string s, Type type, int priority = 0, Associativity ass = Associativity::Left):
            type(type), token(s), associativity(ass), priority(priority)
    {

    }
};
void tokenize(const std::string& str, std::vector<Token>&);
std::queue<Token> shuntingYard(std::vector<Token>&);
double calculate(std::queue<Token>&);



#endif //SHUNTING_YARD_TOKEN_H
