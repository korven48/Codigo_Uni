/*
   SUBMITTED BY:  Lucas Vukotic and Iván Gallego
   DATE:          April 4, 2021
*/

#include <iostream>
#include "Coordinates.h"

using namespace std;



bool operator == (tCoor c1, tCoor c2){
    bool equal = false;
    if (c1.x == c2.x && c1.y == c2.y)
        equal = true;
    return equal;
}
bool operator != (tCoor c1, tCoor c2){
    return !(c1 == c2);
} 
tCoor operator + (tCoor c1, tCoor c2){
    tCoor result;
    result.x = c1.x + c2.x;
    result.y = c1.y + c2.y;
    return result;
}