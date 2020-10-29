/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 21, 2020
   
   PURPOSE:
   User interface designed to create an invoice with client and product data.
   
   FUNCTIONS:
   menu
      Prints the diferent options and recives input from the user.
*/


#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int menu();

int main()
{
    const int DISCOUNT = 15, VAT = 21;

    double price, total_disccounted, price_with_dics, total_price, taxes;
    int units, final_diccount = 0, input;
    char is_discount;
    string name, nif, address, prod_name;
    bool client, sale;

    input = menu();
    while (input != 0){
        cout << endl << endl;
        if (input == 1){
            cout << "Client Name: ";
            cin.get();
            getline(cin, name);
            cout << "Client NIF: ";
            getline(cin, nif);
            cout << "Client Addres: ";
            getline(cin, address);

            client = true;
        }

        if (input == 2){
            cout << "Product Name: ";
            cin.get();
            getline(cin, prod_name);
            cout << "Product Price: ";
            cin >> price;
            cout << "Units: ";
            cin >> units;
            cout << "Discount (y/n): ";
            cin >> is_discount;
            is_discount = toupper(is_discount);

            sale = true;
        }

        if (input == 3){
            if (!client){
                cout << "No client data!"  << endl;
            } 
            else if (!sale){
                cout << "No sale data!"  << endl;
            } else{
                cout << "Invoice:" << endl;
                cout << setw(47) << name << endl;
                cout << setw(47) << address << endl;
                cout << setw(47) << nif << endl;

                if (is_discount == 'Y'){
                    final_diccount = DISCOUNT;
                }   
                
                total_disccounted = -(units * price * final_diccount/100);
                price_with_dics = units * price + total_disccounted;
                taxes = price_with_dics * VAT/100.;
                total_price = price_with_dics + taxes;

                cout << endl << endl;
                cout << "Product: " << prod_name << endl;
                cout << left << setw(40) << "Unitary price" << right << setw(7) << price << endl;
                cout << left << setw(40) << "Units" << right << setw(7) << units << endl;
                cout << left << setw(40) << "Total" << right << setw(7) << (units * price) << endl;
                cout << left << setw(40) << "Discount" << right << setw(7-2) << final_diccount << " %" << endl;
                cout << setw(47) << total_disccounted << endl;
                cout << left << setw(40) << "Total after disccount" << right << setw(7) << price_with_dics << endl;
                cout << left << setw(40) << "VAT" << right << setw(7-2) << VAT << " %" << endl;
                cout << right << setw(47) << taxes << endl;
                cout << left << setw(40) << "Final Price" << right << setw(7) << total_price << endl;
            }
        }

        if (input == 4){
            cout << "Total sale: " << total_price << endl; 
            cout << "Total VAT: " << taxes << endl; 
        }

        if (input == 5){
            client = false;
            sale = false;
        }

        input = menu();
    }

    return 0;
}

int menu(){
    int input;
    cout << endl;
    cout << "1. Client Data" << endl;
    cout << "2. Sale Data" << endl;
    cout << "3. Invoice" << endl;
    cout << "4. Totals" << endl;
    cout << "5. Restart" << endl;
    cout << "0. Exit" << endl;

    cout << "Enter a number (0-5): ";
    cin >> input;

    return input;
}
