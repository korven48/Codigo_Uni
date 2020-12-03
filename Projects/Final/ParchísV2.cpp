/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include<cstdlib>
#include<ctime>
#include<limits>//Forpause()

#ifdef _WIN32
#include <windows.h>
#undef max
#endif

using namespace std;

enum tColor
{
   Yellow = 0,
   Blue,
   Red,
   Green,
   Gray,
   None
};

const int NUM_PLAYERS = 4;
const int NUM_MARKERS = 4;
const int NUM_SPACES = 68;
typedef int tMarkers[NUM_MARKERS];
typedef tMarkers tPlayers[NUM_PLAYERS];
typedef tColor tSpaces[NUM_SPACES];

string colorToString(tColor color);
char colorToLetter(tColor color);
bool zanataSpace(tColor color);
int playerStart(tColor color);

void initialize(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2);
int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);

// Suyas

bool allAtGoal(const tMarkersplayer);
bool isSafe(int pos);
bool bridge(const tSpaces lane1, const tSpaces lane2, int space);
bool process5(tPlayers players, int numPlayer, int& award, bool& nextPlayer, tSpaces lane1, tSpaces lane2);
bool process6(tPlayers players, int numPlayer, int& award, bool& nextPlayer, int& sixes, int& lastMarkerMoved, int& roll, tSpaces lane1, tSpaces lane2);
bool play(tPlayers players, int numPlayer, int& award,bool& end, int& sixes, int& lastMarkerMoved, int roll, tSpaces lane1, tSpaces lane2);
bool canMove(const tPlayers players, int marker, int& space, int numPlayer, int roll, const tSpaces lane1, const tSpaces lane2);

short playerStart(tColor color);
short dice();
short movePlayer(short player, tColor color, short rolled);

int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);
int distance(int x, int y);
int colorToPlayer(tColor color); 

void openBridge(tPlayers players, int numPlayer, int space, int space2, int& award, int& lastMarkerMoved, tSpaces lane1, tSpaces lane2);
void move(tPlayers players, int numPlayer, int marker, int space, int& award, tSpaces lane1, tSpaces lane2);
void markerOut(tPlayers players, int numPlayer, tSpaces lane1, tSpaces lane2);
void toHome(tPlayers players,int space,tSpaces lane1,tSpaces lane2);
void display(const tColorArray colors, const tPositionArray positions);
void initialize(tPlayers players, int& numPlayer, tSpaces lane1, tSpaces lane2);

int main()
{


    return 0;
}

string colorToString(tColor color)
{
   string result;
   switch (color)
   {
   case Red:  
      result = "Red";
      break;
   case Green:
      result = "Green";
      break;
   case Blue:
      result = "Blue";
      break;
   case Yellow:
      result = "Yellow";
      break;
   }

   return result;
}

char colorToLetter(tColor color)
{
   return colorToString(color)[0];
}

bool isSafe(int pos)
{
   bool result = false;
   pos %= 17;
   if (pos == 0 || pos == 5 || pos == 12)
   {
      result = true;
   }

   return result;
}

bool zanataSpace(tColor color){
    return playerStart(color) - 5;
}

int playerStart(tColor color)
{
   int result;
   switch (color)
   {
   case Red:
      result = 39;
      break;
   case Green:
      result = 56;
      break;
   case Blue:
      result = 22;
      break;
   case Yellow:
      result = 5;
      break;
   }

   return result;
}

void initialize(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2);
int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);