
#include <iostream>

using namespace std;

int main()
{
    int inp;
    do{
        cin >> inp;
        if (inp > 0){
            if (inp % 2 == 0){
                cout << "Its even" << endl;
            } else { 
                cout << "Its odd" << endl;
                }
        }
    } while (inp != 0);
    return 0;
}
