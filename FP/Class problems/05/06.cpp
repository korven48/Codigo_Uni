/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          mmmmmmm dd, yyyy
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int M_Clients = 100;
const int M_Calls = 50;

struct tCall {
    string date;
    int duration;
    double cost;
};

typedef tCall tCalls[M_Calls];


struct tClient {
    string nif;
    int expenses;
    tCalls calls;
};

typedef tClient tClients[M_Clients];

void load(tClients clients);
int findClient(); // No me acuerdo
double totalExpense(int seconds);
void print(const tClients clients);

int main()
{
    

    return 0;
}

void print(const tClients clients);
void load(tClients clients){
    string nif, date;
    int seconds;
    ifstream inputFile("calls.txt");
    inputFile >> nif;
    while (nif != "X"){

    }
}
double totalExpense(int seconds);