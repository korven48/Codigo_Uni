
#include <iostream>

using namespace std;

int main()
{
int x = 12, y = 3;
double sigma = 2.1836, lambda = 1.11695, alfa = 328.67, f;
f = 3 * ((x + sigma * y) / (x*x - y*y)) - lambda * (alfa- 13.7);
cout << "f value is: " << f << endl;  
return 0;
}
