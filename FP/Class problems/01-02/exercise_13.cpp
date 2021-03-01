
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    const int SIZE = 3;

    cout << "Introduce tres numeros separados por espacios:";
    int arr[SIZE];
    for (int i=0; i<SIZE; i++){
        cin >> arr[i];
    }

    sort(arr, arr + SIZE);

    for (int i = 0; i < SIZE; i++){
        cout << arr[i] << endl;
    }

    return 0;
}
