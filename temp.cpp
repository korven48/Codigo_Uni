#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;



int main(int argc, char const *argv[])
{
    int a = 2;
    int *b;

    b = &a;

    *b = -1;

    cout << a << endl;

    return 0;
}
