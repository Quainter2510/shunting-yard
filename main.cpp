#include <iostream>
#include "Token.h"

/*
 * -3 * (2 ^ 4 - 3 ^ 5) - 7 ^ 2               = 632
 * 0 - 5 * (-4) ^ (8 - 28 + (-2) * (-(-3)))   = -1.11e-15
 * cos(5 * (-sin(28^3)) - 7 / (-1)) + 25      = 25.823564
 */
int main() {
    std::vector<Token> tokensVector;
    std::string expression;
    std::cout << "to exit the loop, enter 'q'\n";
    while (true) {
        tokensVector.clear();
        getline(std::cin, expression);
        if (expression == "q") {
            break;
        }
        try {
            tokenize(expression, tokensVector);
            std::cout << "tokens:\t";
            for (int i = 0; i < tokensVector.size(); i++) {
                std::cout << tokensVector[i].token << ' ';
            }
            std::cout << '\n';
            std::cout << "RPN:\t";
            std::queue<Token> queue, show = shuntingYard(tokensVector);
            while (!show.empty()) {
                std::cout << show.front().token << ' ';
                queue.push(show.front());
                show.pop();
            }
            std::cout << '\n';
            std::cout << "Result: ";
            double res = calculate(queue);
            std::cout << res << '\n';
        }
        catch (std::runtime_error& error) {
            std::cout << error.what() << '\n';
        }
    }
    return 0;
}
