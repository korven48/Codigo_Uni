/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <ctime>

using namespace std;

const int NUM_MARKERS = 4;
typedef int tMarkers[NUM_MARKERS];

int n_bridges(tMarkers player){
   int bridges = 0;
   for (int i = 0; i < NUM_MARKERS; i++)
      for (int j = i + 1; j < NUM_MARKERS; j++)
         if (player[i] == player[j])
            bridges++;
   return bridges;
}

int main()
{
    tMarkers player = {1, 1, 2, 2};
    cout << n_bridges(player) << endl;
    return 0;
}