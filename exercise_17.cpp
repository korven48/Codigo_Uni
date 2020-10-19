#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, double> conversion_factor = {
        {"inch", 2.54}, {"mile", 1609.344}, {"gall", 4.5461},
        {"ounce", 28.349523}, {"pound", 0.45359}
    };

    map<string, string> international_unit {
        {"inch", "cm"}, {"mile", "m"}, {"gall", "kg"}, 
        {"ounce", "gr"}, {"pound", "kg"}
    };

    double measure;
    string unit;

    cout << "Enter a measure (quantity followed by value): ";
    cin >> measure;
    while (measure){
        cin >> unit;
        cout << measure * conversion_factor[unit] << international_unit[unit] << endl;
        cout << "Enter a measure (quantity followed by value): ";
        cin >> measure;
    }
    return 0;
}
