#include <iostream>

using namespace std;

struct tCoor{
    int x;
    int y;
};

bool operator == (tCoor c1, tCoor c2); 
bool operator != (tCoor c1, tCoor c2);    
tCoor operator + (tCoor c1, tCoor c2); 