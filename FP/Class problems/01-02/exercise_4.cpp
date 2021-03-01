
#include <iostream>

using namespace std;

int main()
{
    int time, seconds, minutes, hours;
    cin >> time;
    seconds = time % 60;
    minutes = time / 60;
    hours = minutes / 60;
    minutes %= 60;

    cout << time << " seconds are " << hours << " hours " << minutes << " minutes " << "and " << seconds << " seconds." << endl;
    return 0;
}
