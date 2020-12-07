#include <iostream>
#include <ctime>

using namespace std;

enum tColor
{
   Red = 0,
   Green,
   Blue,
   Yellow,
   Gray,
   None
};

const short Max_Players = 2;
const int NUM_SPACES = 68;

typedef short tPositionArray[Max_Players];
typedef tColor tColorArray[Max_Players];
typedef tColor tSpaces[NUM_SPACES];



tColor chooseColor();
string colorToString(tColor color);
char colorToLetter(tColor color);

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

bool DEBUG = true;

int main(){
   
}

void display(const tPlayers players, const tSpaces street1, const tSpaces street2) {
   int space, marker, jug;

   cout << "\x1b[2J\x1b[H"; // Go to the upper left square
   setColor(Gray);
   cout << endl;

   // Rows with space numbers...
   for (int i = 0; i < NUM_SPACES; i++)
      cout << i / 10;
   cout << endl;
   for (int i = 0; i < NUM_SPACES; i++)
      cout << i % 10;
   cout << endl;

   // Upper border...
   for (int i = 0; i < NUM_SPACES; i++)
      cout << '>';
   cout << endl;

   // Second lane of spaces...
   for (int i = 0; i < NUM_SPACES; i++) {
      setColor(street2[i]);
      if (street2[i] != None)
         cout << firstAt(players[colorToPlayer(street2[i])], i) + 1;
      else
         cout << ' ';
      setColor(Gray);
   }
   cout << endl;

   // "Median"   
   for (int i = 0; i < NUM_SPACES; i++)
      if (isSafe(i))
         cout << 'o';
      else
         cout << '-';
   cout << endl;


   // First lane of spaces...
   for (int i = 0; i < NUM_SPACES; i++) {
      setColor(street1[i]);
      if (street1[i] != None)
         cout << secondAt(players[colorToPlayer(street1[i])], i) + 1;
      else
         cout << ' ';
      setColor(Gray);
   }
   cout << endl;

   jug = 0;
   // Lower border...
   for (int i = 0; i < NUM_SPACES; i++)
      if (i == zanataSpace(jug)) {
         setColor(tColor(jug));
         cout << "V";
         setColor(Gray);
      }
      else if (i == startSpace(jug)) {
         setColor(tColor(jug));
         cout << "^";
         setColor(Gray);
         jug++;
      }
      else
         cout << '>';
   cout << endl;

   // Goal paths and homes...
   for (int i = 0; i < NUM_MARKERS; i++) {
      space = 0;
      jug = 0;
      setColor(tColor(jug));
      while (space < NUM_SPACES) {
         if (space == zanataSpace(jug)) {
            marker = firstAt(players[jug], 101 + i);
            if (marker != -1) {
               cout << marker + 1;
               if (howMany(players[jug], 101 + i) > 1) {
                  marker = secondAt(players[jug], 101 + i);
                  if (marker != -1) {
                     cout << marker + 1;
                  }
                  else
                     cout << "V";
               }
               else
                  cout << "V";
            }
            else
               cout << "VV";
            space++;
         }
         else if (space == startSpace(jug)) {
            if (players[jug][i] == -1) // En casa
               cout << i + 1;
            else
               cout << "^";
            jug++;
            setColor(tColor(jug));
         }
         else
            cout << ' ';
         space++;
      }
      cout << endl;
   }

   // More goal paths...
   for (int i = 105; i <= 107; i++) {
      space = 0;
      jug = 0;
      setColor(tColor(jug));
      while (space < NUM_SPACES) {
         if (space == zanataSpace(jug)) {
            marker = firstAt(players[jug], i);
            if (marker != -1) {
               cout << marker + 1;
               if (howMany(players[jug], i) > 1) {
                  marker = secondAt(players[jug], i);
                  if (marker != -1) {
                     cout << marker + 1;
                  }
                  else
                     cout << "V";
               }
               else
                  cout << "V";
            }
            else
               cout << "VV";
            space++;
            jug++;
            setColor(tColor(jug));
         }
         else
            cout << ' ';
         space++;
      }
      cout << endl;
   }

   space = 0;
   jug = 0;
   setColor(tColor(jug));
   while (space < NUM_SPACES) {
      cout << ((players[jug][0] == 108) ? '1' : '.');
      cout << ((players[jug][1] == 108) ? '2' : '.');
      jug++;
      setColor(tColor(jug));
      cout << "               ";
      space += 17;
   }
   cout << endl;
   space = 0;
   jug = 0;
   setColor(tColor(jug));
   while (space < NUM_SPACES) {
      cout << ((players[jug][2] == 108) ? '3' : '.');
      cout << ((players[jug][3] == 108) ? '4' : '.');
      jug++;
      setColor(tColor(jug));
      cout << "               ";
      space += 17;
   }
   cout << endl << endl;
   setColor(Gray);
}

void setColor(tColor color) {
   switch (color) {
   case Yellow:
      cout << "\x1b[33;107m";
      break;
   case Blue:
      cout << "\x1b[34;107m";
      break;
   case Red:
      cout << "\x1b[31;107m";
      break;
   case Green:
      cout << "\x1b[32;107m";
      break;
   case Gray:
   case None:
      cout << "\x1b[90;107m";
      break;
   }
}

void pause() {
   cout << "Press Enter to continue...";
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void initColors() {
#ifdef _WIN32
   for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE}) {
      DWORD mode;
      HANDLE handle = GetStdHandle(stream);

      if (GetConsoleMode(handle, &mode)) {
         mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
         SetConsoleMode(handle, mode);
      }
   }
#endif
}


int colorToPlayer(tColor color){
   // Yellow -> 0
}