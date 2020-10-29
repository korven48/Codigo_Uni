
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main()
{
    const int DISCOUNT = 15, VAT = 21;

    double price;
    int units, final_diccount = 0, total_disccounted, total;
    char is_discount;
    string name, nif, address, prod_name;

    cout << "Product Price: ";
    cin >> price;
    cout << "Units: ";
    cin >> units;
    cout << "Discount (y/n): ";
    cin >> is_discount;
    is_discount = toupper(is_discount);
    cout << "Client Name: ";
    getline(cin, name);
    getline(cin, name);
    cout << "Client NIF: ";
    getline(cin, nif);
    cout << "Client Addres: ";
    getline(cin, address);
    cout << "Product Name: ";
    getline(cin, prod_name);


    cout << "Invoice:" << endl;
    cout << setw(47) << name << endl;
    cout << setw(47) << address << endl;
    cout << setw(47) << nif << endl;

    if (is_discount == 'Y'){
        final_diccount = DISCOUNT;
    }   
    total_disccounted = -(units * price * final_diccount/100);
    total = units * price + total_disccounted;

    cout << "Product: " << prod_name << endl;
    cout << left << setw(40) << "Unitary price" << right << setw(7) << price << endl;
    cout << left << setw(40) << "Units" << right << setw(7) << units << endl;
    cout << left << setw(40) << "Total" << right << setw(7) << (units * price) << endl;
    cout << left << setw(40) << "Discount" << right << setw(7-2) << final_diccount << " %" << endl;
    cout << setw(47) << total_disccounted << endl;
    cout << left << setw(40) << "Total after disccount" << right << setw(7) << total << endl;
    cout << left << setw(40) << "VAT" << right << setw(7-2) << VAT << " %" << endl;
    cout << right << setw(47) << (total * VAT/100.) << endl;
    cout << left << setw(40) << "Final Price" << right << setw(7) << (total * (1 + VAT/100)) << endl;

    return 0;
}
