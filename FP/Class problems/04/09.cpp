/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <cmath>

using namespace std;
bool isPrime(int n);

int main()
{
    for (int i = 0; i < 100; i++){
        cout << i << " --> " << boolalpha << isPrime(i) << endl;
    }
    return 0;
}

bool isPrime(int n){
    if (n == 2)
        return true;
    if (n < 2 || n % 2 == 0)
        return false;
    for (int i = 3; i <= floor(sqrt(n)) + 1; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}