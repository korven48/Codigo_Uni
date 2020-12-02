/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          November 11, 2020
*/

#include <iostream>

using namespace std;

int readingWithLimits(int min, int max);

int main()
{
    readingWithLimits(20, 30);
    return 0;
}

int readingWithLimits(int min, int max){
    int n;
    cin >> n;
    while (n < min || n > max)
        cin >> n;
    return n;
}
