
#include <iostream>

using namespace std;

int main()
{
    string name, surname, dni, nif_letter;
    int age, capital, years;

    cout << "Name: ";
    cin >> name;
    cout << endl << "Surname: ";
    cin >> surname;
    cout << endl << "DNI (8 digits): ";
    cin >> dni;
    cout << endl << "NIF's letter: ";
    cin >> nif_letter;
    cout << endl << "Capital: ";
    cin >> capital;
    cout << endl << "Years: " << endl;
    cin >> years;

    cout << "Client: " << name << surname << "(" << years << " years)" << endl;
    cout << "N.I.F.: " << dni << "-" << nif_letter;


    return 0;
}
