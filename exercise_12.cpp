
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int capital, years, month_payment, interest_amount;
    double interest_rate;


    cout << "Please enter the Capital: ";
    cin >> capital;
    cout << endl << "Please enter the Anual Interest Rate: ";
    cin >> interest_rate;
    cout << endl << "Please enter the Years";
    cin >> years;

    interest_rate /= 12;
    month_payment = capital * interest_rate / (100 * (1 - pow(1 + interest_rate / 100, -term) ));
    return 0;
}