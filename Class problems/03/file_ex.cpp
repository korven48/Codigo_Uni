#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string nif, name, surname; 
    int age;
    double salary;
    ofstream outFile;
    ifstream inFile;

    /*
    outFile.open("company.txt");
    cout << "Inset NIF: ";
    cin >> nif;
    while (nif != "#"){
        cin.get();
        cout << "Name: ";
        getline(cin, name);
        cout << "Surname: ";
        getline(cin, surname);
        cout << "Age: ";
        cin >> age;
        cout << "Salary: ";
        cin >> salary; 

        outFile << nif << endl << name << endl;
        outFile << surname << endl << age << endl;
        outFile << salary << endl;
        
        cout << "Inset NIF: ";
        cin >> nif;
    }
    outFile << "#";
    outFile.close();
    */
    inFile.open("company.txt");
    if (inFile.is_open())
    {
        inFile >> nif;
        while (nif != "#"){
            inFile.get();
            getline(inFile, name);
            getline(inFile, surname);
            inFile >> age >> salary;
            cout << name << " " << surname << " (" << age << " years), " << salary << "$";

            inFile >> nif;
        }
    }
    
    return 0;
}
