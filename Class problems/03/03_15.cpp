
#include <iostream>
#include <fstream>

using namespace std;

bool is_triangular(int num);

int main()
{
    int num;
    ifstream inputFile;
    inputFile.open("integers.txt");
    inputFile >> num;
    while (num){
        cout << num << ((is_triangular(num)) ? " is ": " is not ") << "triangular" << endl; 
        inputFile >> num;
    }
    return 0;
}

bool is_triangular(int num){
    bool result = false;
    int partial = 0, i = 0;
    while (partial <= num){
        if (partial == num)
            result = true;
        i++;
        partial += i;
    }
    return result;
}
