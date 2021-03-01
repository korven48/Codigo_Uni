#include <iostream>

using namespace std;


const int Dim = 10;
typedef double tGrades[Dim];

double average (const tGrades grades);

int main()
{
    tGrades grades;
    int passed = 0;
    for (int i = 0; i < Dim; i++){
        cin >> grades[i];
        if (grades[i] >= 5)
            passed++;
    }
    for (int i = 0; i < Dim; i++){
        cout << grades[i] << endl;
    }

    cout << "Average is: " << average(grades) << endl;
    cout << "Number of passed exams: " << passed << endl;
    return 0;
}


double average (const tGrades grades){
    double out, total = 0;
    for (int i = 0; i < Dim; i++){
        total += grades[i];
    }

    return (total / Dim);
}