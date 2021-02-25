/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <iomanip>

using namespace std;

struct tDate {
    int day;
    int month;
    int year;
};

tDate readDate();
void print(tDate date);
bool operator==(tDate f1, tDate f2);
bool operator!=(tDate f1, tDate f2);
bool operator< (tDate f1, tDate f2);
bool operator<=(tDate f1, tDate f2);
bool operator> (tDate f1, tDate f2);
bool operator>=(tDate f1, tDate f2);

int main()
{
    tDate date;
    date = readDate();
    print(date);

    return 0;
}

tDate readDate(){
    tDate date;
    cout << "Introduce day: ";
    cin >> date.day;
    cout << "Introduce month: ";
    cin >> date.month;
    cout << "Introduce year: ";
    cin >> date.year; 

    return date;
}

void print(tDate date){
    cout << setw(2) << setfill('0') << date.day << '/'
         << setw(2) << setfill('0') << date.month << '/'
                                    << date.year; 
}

bool operator==(tDate f1, tDate f2){
    return (f1.day == f2.day && f1.month == f2.month && f1.year == f2.year);
}

bool operator!=(tDate f1, tDate f2){
    return !(f1 == f2);
}

bool operator< (tDate f1, tDate f2){
    bool out = false;
    if (f1.year < f2.year)
        out = true;
    else if (f1.year == f2.year){
        if (f1.month < f2.month)
            out = true;
        else if (f1.month == f2. month){
            if (f1.day < f2.day)
                out = true;
        }
    } 
    return out;
}

bool operator<=(tDate f1, tDate f2);
bool operator> (tDate f1, tDate f2);
bool operator>=(tDate f1, tDate f2);