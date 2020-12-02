/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>

using namespace std;

bool isPerfect(int n);
bool isTriangular(int n);

int main()
{   
    int total = 0, i = 1;
    bool hypotesis = true;
    while(hypotesis){
        if (isPerfect(i) && !isTriangular(i))
            hypotesis = false; 
        cout << i << endl;
        i++;
        if (i == 100000)
            hypotesis = false;
    }
    cout << "Hypothesis is " << boolalpha << hypotesis << endl;
    return 0;
}

bool isPerfect(int n){
    int total = 0;
    for (int i = 1; i < n; i++){
        if ((n % i) == 0)
            total += i;
    }
    return (total == n);
}

bool isTriangular(int n){
    int total = 0;
    for (int i = 1; total < n; i++){
        total += i;
    }
    return (total == n);
}
