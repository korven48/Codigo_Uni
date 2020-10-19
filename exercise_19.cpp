#include <iostream>

using namespace std;


double operate(double x, double y, char operand);

int main()
{
    double x, y, result;
    char operand;

    cout << "Operand Operator Operand (0 to end): ";
    cin >> x;
    while (x != 0){
        cin >> operand >> y;
        cout << x << " " << operand << " " << y << " = " << operate(x, y, operand) << endl;
        cout << "Operand Operator Operand (0 to end): ";
        cin >> x;
    }


    return 0;
}


double operate(double x, double y, char operand){
    double result;

    switch (operand){
        case '+':
            result = x + y;
            break; 
        case '-':
            result = x - y;
            break;
        case '/':
            result = x / y;
            break;
        case '*':
            result = x * y;
            break;
    }

    return result;
}
