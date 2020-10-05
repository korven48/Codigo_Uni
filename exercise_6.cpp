
#include <iostream>

using namespace std;

int main()
{
    int a,b,c,d,r;
    cin >> a >> b >> c >> d >> r;
    double result = 4/(3*(r + 34)) - 9*(a+b*c) + (3 + d*(2+a)) / (a + b*d);
    cout << result << endl;
    return 0;
}
