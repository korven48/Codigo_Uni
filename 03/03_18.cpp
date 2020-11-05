/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          November 4, 2020
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char previous, current;
    int total = 0;
    const string FileName = "input.txt";
     
    ifstream inputFile;
    inputFile.open(FileName);

    inputFile.get(previous);
    while (previous != '*'){        
        inputFile.get(current);
        if (previous == 'x' && current == 'y')
            total++;
        previous = current;
    }

    cout << "There are " << total << " xy pairs." << endl;
    return 0;
}
