
#include <iostream>
#include <cmath>

using namespace std;

int sumDigits(int num);

int main()
{
    int num;
    cout << "Introduce a number: ";
    cin >> num;
    while (num > 9){
        num = sumDigits(num);
        cout << num;
    }
    cout << "The magic number is: " << num << endl;
    return 0;
}


int sumDigits(int num){
    int total = 0;
    
    while (num){
        total += num%10;
        num /= 10;
    }
    return total;
}