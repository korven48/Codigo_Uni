
#include <iostream>
#include <cmath>


using namespace std;

int main()
{
    double side1, side2, angle;
    cin >> side1 >> side2 >> angle;
    double area = .5 * side1 * side2 * sin(angle * M_PI / 180);
    cout << area << endl;
    return 0;
}
