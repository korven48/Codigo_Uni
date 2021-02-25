/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>

using namespace std;

string reverse(int num);

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    int num;

    inputFile.open("input.txt");
    outputFile.open("output.txt");

    inputFile >> num;
    while (num){
        if (num < 0){
            inputFile >> num;
            continue;
        }
        outputFile << reverse(num) << endl;
        inputFile >> num;
    }

    return 0;
}

string reverse(int num){
    string output = "";
    int digit;
    while (num){
        digit = num%10;
        num /= 10;
        output = output + string(1, digit + '0');
    }
    return output;
}


