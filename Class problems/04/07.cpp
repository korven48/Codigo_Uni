/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>

using namespace std;

bool isPerfect(int n);

int main()
{   
    int n, total = 0;
    ifstream inputFile("data.txt");
    if (inputFile.is_open()){
        inputFile >> n;
        while (n != 0){
            if (isPerfect(n))
                total++;
            inputFile >> n;
        }
        cout << "Total: " << total << endl;
    }
    else
    {
        cout << "No File" << endl;
    }
    
    return 0;
}

bool isPerfect(int n){
    int total = 0;
    for (int i = 0; i < n; i++){
        if (i % n == 0)
            total += i;
    }
    return (total == n);
}
