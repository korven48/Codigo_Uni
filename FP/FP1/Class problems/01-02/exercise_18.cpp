
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int number;
    do{
        cout << "Enter a number (1-100): ";
        cin >> number;
        cout << endl;
    } while (number <= 0 || number > 100);

    int i = 1;
    while (i <= 10){
        cout << setw(2) << i << setw(3) << "X" << setw(5) << number << "   =" << setw(7) << (i*number) << endl;
        i++;
    }

    return 0;
}
