/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>

using namespace std;

void load(ifstream &in){
    int z;
    in >> z;
    cout << z << endl;
}

int main()
{
    ifstream in("in");
    int x, y;
    in >> x >> y;
    cout << x << y << endl;
    load(in);
    return 0;
}