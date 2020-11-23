#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int distance(int x, int y){
   int out; 
   if ((x - y) > 0) 
      out = x - y;
   else 
      out = 68 + x - y;
   return out;
}

int main(int argc, char const *argv[])
{
    cout << distance(59, 0) << endl;

    return 0;
}
