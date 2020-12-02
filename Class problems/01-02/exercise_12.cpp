
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    int capital, years, interest_amount, term;
    double month_payment, interest_rate;


    cout << "Please enter the Capital: ";
    cin >> capital;
    cout << "Please enter the Anual Interest Rate: ";
    cin >> interest_rate;
    cout << "Please enter the Years: ";
    cin >> years;

    interest_rate /= 12;
    term = years * 12;

    month_payment = capital * interest_rate / (100 * (1 - pow(1 + interest_rate / 100, -term) ));

    // cout << fixed << setprecision(2); 
    cout << "Monthly Payment: " << month_payment << " $" << endl;
    cout << "Capital: " << capital << " $" << endl;
    cout << "Interests Amount: " << month_payment * 12 * years - capital << " $" << endl;

    return 0;
}