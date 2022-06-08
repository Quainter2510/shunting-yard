//
// Created by User on 06.06.2022.
//
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#ifndef SHUNTING_YARD_TOKEN_H
#define SHUNTING_YARD_TOKEN_H


struct Token {

    enum class Type {
        Number = 0,
        Operator,
        Function,
        LeftBracket,
        RightBracket,
        UnaryMinus
    };
    Type type;
    const std::string token;
    Token(const std::string s, Type type):
            type(type), token(s)
    {

    }
};

int preority(Token& token);
int associavitity(Token& token);

void tokenize(const std::string& str, std::vector<Token>&);
void addToken(std::string& token, std::vector<Token>&);
bool isOperator(const std::string& oper);
bool isFunction(const std::string& func);
bool isNumber(const std::string& num);
std::queue<Token> shuntingYard(std::vector<Token>&);
double calculate(std::queue<Token>&);
double compute(const std::string& token, double one, double two);
double compute(const std::string& token, double one);
void checkCorrect(std::vector<Token> vec);



#endif //SHUNTING_YARD_TOKEN_H
