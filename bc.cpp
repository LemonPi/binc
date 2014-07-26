// Binary stack calculator
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <stack>
#include <set>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>

#define SUCCESS 0
#define FAIL -1

using namespace std;
// push if operand, pop if operator
int RPN(string& expression, unsigned int& result) {
    // main calculating function
    stringstream exp(expression);
    unsigned int token;
    stack<unsigned int> tokens;
    const set<char> operators = {'+', '-', '*', '/', '&', '|', '~', '^', '>', '<'};

    while(1) {
        // use peek to check if next word is operator or operand
        if(exp.eof()) break;
        char c = exp.peek();


        if((c >= '0') && (c <= '9')) {
            // is a digit
            exp >> token;
            tokens.push(token);
        }
        else if(isspace(c)) {
            exp.ignore();
            continue;
        }
        else if(operators.find(c) != operators.end()) {
            // is operator, so perform operation
            exp.ignore();  // skip the operator since we already have c

            if(tokens.empty()) return FAIL;  // no operator works on empty stack
            unsigned int right(tokens.top());
            tokens.pop();
            // unary operators
            if(c == '~') {
                tokens.push(~right);
                continue;  // skip popping a left
            }

            if(tokens.empty()) return FAIL;  // binary operator without second operand
            unsigned int left(tokens.top());
            tokens.pop();

            // binary operators
            switch (c) {
                case '+': tokens.push(left + right); break;
                case '-': tokens.push(left - right); break;
                case '*': tokens.push(left * right); break;
                case '/': tokens.push(left / right); break;
                case '&': tokens.push(left & right); break;
                case '|': tokens.push(left | right); break;
                case '^': tokens.push(left ^ right); break;
                case '<': tokens.push(left << right); break;
                case '>': tokens.push(left >> right); break;
                default: break;
            }
        }
        else if (c >= '!' && c <= '~') {
            // some other valid character
            token = static_cast<unsigned int>(c);
            exp.ignore();
            tokens.push(token);
        }
        else if(!exp.eof()) return FAIL;  // invalid character and not at end of stream

    }
    // whatever's left is final result
    result = tokens.top();
    tokens.pop();
    return !tokens.empty();  // if empty will return 0 (SUCCESS)
}


int main() {
    string expression;
    unsigned int result {0};
    constexpr unsigned int bit_num = 8;

    while(1){
        cout << "Expression: ";
        getline(cin, expression);

        if(expression == "quit" || expression == "q")
            break;

        else if(RPN(expression, result) == SUCCESS) {
            bitset<bit_num> bin_rep(result);
            cout << "Result: " << bin_rep << "(" << result << ")" << endl;
        }
        else
            cout << "Expression null\n";
    }
}

