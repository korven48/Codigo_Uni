/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
   ifstream file("mine.txt");
   for (int i= 0; i < 20; i++){
      int a;
      file >> a;
      cout << a << endl;
   }
}