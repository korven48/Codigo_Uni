/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 18, 2020
   
   PURPOSE:
   This program will asks the user for his or her name, surname, age, DNI (eight digits), NIF letter, as well as the capital in euros of a mortgage loan and the number of years to pay.
   It will then display the monthly payment for three possible annual interest rates: 2.25%, 2.5% and 2.75%
   
   FUNCTIONS:
   monthPayment
      Will calculate monthly payment needed given capital lent in dollars, annual interest and years of amortization.
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double monthPayment(int capital, double interest_rate, int years);

int main()
{
    string name, surname, dni;
    char nif_letter;
    int age, capital, years;
    const int N_INTERST = 3;
    const double INTERESTS[N_INTERST] = {2.25, 2.5, 2.75};

    cout << "Name: ";
    getline(cin, name);
    cout << "Surname: ";
    getline(cin, surname);
    cout << "Age: ";
    cin >> age;
    cout << "DNI (8 digits): ";
    cin >> dni;
    cout << "NIF's letter: ";
    cin >> nif_letter;
    cout << "Capital: ";
    cin >> capital;
    cout << "Years: ";
    cin >> years;
    cout << endl;

    cout << "Client: " << name << " " << surname << " " << "(" << age << " years)" << endl;
    cout << "N.I.F.: " << dni << "-" << (char)toupper(nif_letter) << endl << endl;

    cout << "Annual interest" << "    " << "Monthly payment" << endl;
    cout << fixed << setprecision(2);
    int i = 0;
    while (i < N_INTERST)       
    {
        /* 
            * foreach loop would be better if alowed *
        Prints each annual interest and its corresponding monthly payment.
        */

        double interest = INTERESTS[i];
        cout << setw(10) << interest << "          " << monthPayment(capital, interest, years) << " Eur" << endl;
        i++;
    }

    return 0;
}


double monthPayment(int capital, double interest_rate, int years){
    /* 
    PARAMETERS:
    name              type      description
    ---------------------------------------------------------------------
    capital           int       capital lent in dollars
    interest_rate     double    annual interest
    years             int       years of amortization

    RETURN VALUE:
    name              type      description
    ---------------------------------------------------------------------
    monthly_payment   double    monthly payment needed.  
    */
   
    int term; 
    double monthly_payment;

    interest_rate /= 12;
    term = years * 12;

    monthly_payment = capital * interest_rate / (100 * (1 - pow(1 + interest_rate / 100, -term) ));
    
    return monthly_payment;
}