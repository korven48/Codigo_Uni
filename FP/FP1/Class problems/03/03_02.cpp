
#include <iostream>

using namespace std;

typedef enum { aprobado, suspenso, bien, notable, matricula } tGrade;

int main()
{
    tGrade score = aprobado;

    cout << score << endl;

    return 0;
}
