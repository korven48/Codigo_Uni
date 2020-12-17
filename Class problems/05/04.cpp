/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          mmmmmmm dd, yyyy
*/

#include <iostream>

using namespace std;

enum tStudyLevel{
    ESO,
    Bachillerato,
    GradoMedio,
    GradoSuperior,
    Grado,
    Master,
    Doctorado
};

enum tContract{
    Permanent,
    Apprentice,
    Temporary,
    Scholarship
};

struct tEmployee{
    string name;
    int age;
    tStudyLevel studies;
    tContract contract;
};

const int NUM_EMPLOYEES = 10;
typedef tEmployee tEmployees[NUM_EMPLOYEES];

void print(const tEmployees employees);

int main()
{


    return 0;
}

void print(const tEmployees employees){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        if (employees[i].studies == Grado){
            cout << employees[i].name << endl;
            cout << employees[i].studies << endl;
        }
    }
}