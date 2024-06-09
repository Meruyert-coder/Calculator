#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int applyOperator(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: 
        return 0; 
    }
}

int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isspace(c)) {
            continue; 
        }
        else if (isdigit(c)) {
            int number = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            values.push(number);
            i--; 
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                if (values.size() < 2) {
                    cerr << "Ошибка: недостаточно операндов для оператора " << op << endl;
                    return 0;
                }

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }
            operators.pop(); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && operators.top() != '(' && priority(operators.top()) >= priority(c)) {
                char op = operators.top();
                operators.pop();

                if (values.size() < 2) {
                    cerr << "Ошибка: недостаточно операндов для оператора " << op << endl;
                    return 0;
                }

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }
            operators.push(c);
        }
        else {
            cerr << "Ошибка: недопустимый символ: " << c << endl;
            return 0;
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        if (values.size() < 2) {
            cerr << "Ошибка: недостаточно операндов для оператора " << op << endl;
            return 0;
        }

        int b = values.top();
        values.pop();
        int a = values.top();
        values.pop();

        values.push(applyOperator(a, b, op));
    }

    if (values.size() != 1) {
        cerr << "Ошибка: неверное количество операторов и операндов" << endl;
        return 0;
    }

    return values.top();
}

int main() {
    setlocale(LC_ALL, "Russian");
    string expression;
    char choice;

    do {
        cout << "Введите арифметическое выражение: ";
        getline(cin, expression);

        int result = evaluateExpression(expression);
        if (result != 0) {
            cout << "Результат: " << result << endl;
        }
        else {
            cout << "Вычисление выражения завершилось с ошибкой." << endl;
        }
        cout << "Хотите продолжить (y/n)? ";
        cin >> choice;
        cin.ignore(); 
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
