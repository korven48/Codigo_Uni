/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          November 11, 2020
*/

#include <iostream>

using namespace std;

double round(double n){
    n *= 100;
    n = round(n);
    return n;
}

int main()
{
    cout << round(103.3465) << endl;
    return 0;
}

