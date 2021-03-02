
#include <iostream>


using namespace std;

unsigned long long int factorial(int n);

int main()
{   
    int n;
    cout << "Introduce a number: ";
    cin >> n;

    cout << "Factorial of " << n << " = " << factorial(n) << endl;

    return 0;
}

unsigned long long int factorial(int n){
    if (n == 0)
        return 1;
    return factorial(n-1) * n;
}
