
#include <iostream>

using namespace std;

int main()
{
    double final_exam, project, activities, final_grade;
    cin >> final_exam >> project >> activities;
    final_grade = final_exam * 0.6 + project * 0.2 + activities * 0.2;
    cout << final_grade << endl;
    return 0;
}
