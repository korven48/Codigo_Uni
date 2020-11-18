
#include <iostream>

using namespace std;

int square(int num);

int main()
{
    int num;
    cout << "Introduce a number: ";
    cin >> num;
    while (num){
        cout << "The square of " << num << " is " << square(num) << endl; 
        cout << "Introduce a number: ";
        cin >> num;
    }
    return 0;
}

int square(int num){
    int total = 0;
    for (int i = 0; i < num; i++){
        total += 2 * i + 1; 
    }
    return total;
}