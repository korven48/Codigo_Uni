
#include <iostream>

using namespace std;

string reverse(unsigned int num);
string digitToStr(unsigned int digit);

int main()
{
    unsigned int num;
    cout << "Introduce a number: ";
    cin >> num;
    cout << "The reverse is " << reverse(num) << endl;
    return 0;
}

string reverse(unsigned int num){
    string result = "";
    while (num){
        result += to_string(num%10);
        num /= 10;
    }
    return result;
}
