#include "Token.h"

/*
 * при токенизации унарный минус заменяется на -- для наглядности
*/
double compute(const std::string& token, double one) {
    if (token == "sin") {
        return sin(one);
    }
    else if (token == "cos") {
        return cos(one);
    }
    else if (token == "tan") {
        return tan(one);
    }
    else if (token == "ctan") {
        return cos(one) / sin(one);
    }
    else if (token == "log") {
        return log(one);
    }
    else if (token == "--") {
        return -one;
    }
    else {
        throw std::runtime_error("incorrect compute " + token);
    }
}

double compute(const std::string& token, double one, double two) {
    if (token == "-") {
        return one - two;
    }
    else if (token == "+") {
        return one + two;
    }
    else if (token == "*") {
        return one * two;
    }
    else if (token == "/") {
        return one / two;
    }
    else if (token == "^") {
        return pow(one, two);
    }
    else {
        throw std::runtime_error("incorrect compute " + token);
    }
}

void checkCorrect(std::vector<Token> vec) {
    int bracketCount = 0;

    if (vec.size() < 2) {
        throw std::runtime_error("empty expression");
    }

    if (vec[0].type == Token::Type::RightBracket ||
        vec[0].type == Token::Type::Operator) {
        throw std::runtime_error("incorrect expression: start with " + vec[0].token);
    }

    if (vec[vec.size() - 1].type != Token::Type::Number &&
        vec[vec.size() - 1].type != Token::Type::RightBracket) {
        throw std::runtime_error("incorrect expression: finish with " + vec[vec.size() - 1].token);
    }


    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i].type == Token::Type::Function) {
            if (vec[i + 1].type != Token::Type::LeftBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        else if (vec[i].type == Token::Type::Operator) {
            if (vec[i + 1].type != Token::Type::Number &&
                vec[i + 1].type != Token::Type::Function &&
                vec[i + 1].type != Token::Type::LeftBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        else if (vec[i].type == Token::Type::Number) {
            if (vec[i + 1].type != Token::Type::Operator &&
                vec[i + 1].type != Token::Type::RightBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        else if (vec[i].type == Token::Type::UnaryMinus) {
            if (vec[i + 1].type != Token::Type::Number &&
                vec[i + 1].type != Token::Type::Function &&
                vec[i + 1].type != Token::Type::LeftBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        else if (vec[i].type == Token::Type::LeftBracket) {
            bracketCount++;
            if (vec[i + 1].type != Token::Type::Number &&
                vec[i + 1].type != Token::Type::Function &&
                vec[i + 1].type != Token::Type::UnaryMinus &&
                vec[i + 1].type != Token::Type::LeftBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        else if (vec[i].type == Token::Type::RightBracket) {
            bracketCount--;
            if (vec[i + 1].type != Token::Type::Operator &&
                vec[i + 1].type != Token::Type::RightBracket) {
                throw std::runtime_error("incorrect expression: " + vec[i].token + " with " + vec[i + 1].token);
            }
        }
        if (bracketCount < 0) {
            throw std::runtime_error("negative bracket balance");
        }
    }
    if (vec[vec.size() - 1].type == Token::Type::RightBracket) {
        bracketCount--;
    }
    if (vec[vec.size() - 1].type == Token::Type::LeftBracket) {
        bracketCount++;
    }
    if (bracketCount != 0) {
        throw std::runtime_error("leftBracket != rightBracket");
    }
}

bool isNumber(const std::string& num) {
    bool point = false;
    if (num[0] == '.') {
        return false;
    }
    for (int i = 0; i < num.size(); i++) {
        if ((num[i]  < '0' || num[i] > '9') && num[i] != '.') {
            return false;
        }
        if (num[i] == '.') {
            if (point) {
                return false;
            }
            else {
                point = true;
            }
        }
    }
    return true;
}

bool isFunction(const std::string& func) {
    std::vector<std::string> s = {"sin", "cos", "tan", "ctan", "log"};
    if (std::find(s.begin(), s.end(), func) == s.end()) {
        return false;
    }
    return true;
}

bool isOperator(const std::string& oper) {
    std::vector<std::string> s = {"+", "-", "*", "/", "^"};
    if (std::find(s.begin(), s.end(), oper) != s.end()) {
        return true;
    }
    return false;
}

void addToken(std::string& token, std::vector<Token>& tokensVector) {
    if (isFunction(token)) {
        tokensVector.emplace_back(token, Token::Type::Function);
    }
    else if (isNumber(token)) {
        tokensVector.emplace_back(token, Token::Type::Number);
    }
    else if (isOperator(token)) {
        if (token == "-") {
            if (tokensVector.empty() ||
            tokensVector.back().type != Token::Type::Number &&
            tokensVector.back().type != Token::Type::RightBracket) {
                tokensVector.emplace_back("--", Token::Type::UnaryMinus);
                return;
            }
        }
        if (token == "+" || token == "-") {
            tokensVector.emplace_back(token, Token::Type::Operator, 1);
        }
        else if (token == "*" || token == "/") {
            tokensVector.emplace_back(token, Token::Type::Operator, 2);
        }
        else if (token == "^") {
            tokensVector.emplace_back(token, Token::Type::Operator, 3, Token::Associativity::Right);
        }
    }
    else {
        throw std::runtime_error("incorrect token " + token);
    }
}

void tokenize(const std::string& str, std::vector<Token>& tokensVector) {
    const std::string operators = "+-*/^";
    std::string s;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            if (!s.empty()) {
                addToken(s, tokensVector);
                s = "";
            }
        }
        else if (std::find(operators.begin(), operators.end(), str[i]) != operators.end()) {
            if (!s.empty()) {
                addToken(s, tokensVector);
                s = "";
            }
            s += str[i];
            addToken(s, tokensVector);
            s = "";
        }
        else if (str[i] == '(') {
            if (!s.empty()) {
                addToken(s, tokensVector);
                s = "";
            }
            tokensVector.emplace_back("(", Token::Type::LeftBracket);
        }
        else if (str[i] == ')') {
            if (!s.empty()) {
                addToken(s, tokensVector);
                s = "";
            }
            tokensVector.emplace_back(")", Token::Type::RightBracket);
        }
        else {
            s += str[i];
        }
    }
    if (!s.empty()) {
        addToken(s, tokensVector);
    }
    checkCorrect(tokensVector);
}

std::queue<Token> shuntingYard(std::vector<Token>& tokensVector) {
    std::queue<Token> output;
    std::stack<Token> operatorStack;
    for (auto&& token : tokensVector) {
        if (token.type == Token::Type::Number) {
            output.push(token);
        }
        if (token.type == Token::Type::Function ||
                token.type == Token::Type::UnaryMinus) {
            operatorStack.push(token);
        }
        if (token.type == Token::Type::Operator) {
            while (!operatorStack.empty() &&
            operatorStack.top().type != Token::Type::LeftBracket && (
                    operatorStack.top().type == Token::Type::Function ||
                    operatorStack.top().type == Token::Type::UnaryMinus ||
                    operatorStack.top().type == Token::Type::Operator && (
                    operatorStack.top().priority > token.priority ||
                    operatorStack.top().priority == token.priority &&
                    token.associativity == Token::Associativity::Left))) {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
             operatorStack.push(token);
        }
        if (token.type == Token::Type::LeftBracket) {
            operatorStack.push(token);
        }
        if (token.type == Token::Type::RightBracket) {
            while (!operatorStack.empty() && operatorStack.top().type != Token::Type::LeftBracket) {
                output.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop();
        }
    }
    while (!operatorStack.empty()) {
        output.push(operatorStack.top());
        operatorStack.pop();
    }
    return output;
}

double calculate(std::queue<Token>& output) {
    std::stack<double> res;
    while (!output.empty()) {
        Token token = output.front();
        if (token.type == Token::Type::Number) {
            res.push(std::stod(token.token));
        }
        else if (token.type == Token::Type::Operator) {
            if (res.size() < 2) {
                throw std::runtime_error("incorrect expression");
            }
            double first = res.top();
            res.pop();
            double second = res.top();
            res.pop();
            res.push(compute(token.token, second, first));
        }
        else if (token.type == Token::Type::Function || token.type == Token::Type::UnaryMinus) {
            if (res.empty()) {
                throw std::runtime_error("incorrect expression");
            }
            double one = res.top();
            res.pop();
            res.push(compute(token.token, one));
        }
        else {
            throw std::runtime_error("something went wrong");
        }
        output.pop();
    }
    if (res.size() != 1) {
        throw std::runtime_error("incorrect expression");
    }
    return res.top();
}