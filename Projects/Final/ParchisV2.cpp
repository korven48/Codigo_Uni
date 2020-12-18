/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#undef max
#endif

using namespace std;

const string FileName = "canMove.txt"; // test5 canMove   | .txt
const bool Debug = true;
const int Goal = 108;

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


bool allAtGoal(const tMarkers player);
bool isSafe(int pos);
bool bridge(const tSpaces lane1, const tSpaces lane2, int space);
bool process5(tPlayers players, tColor playerTurn, int &award, bool &nextPlayer, tSpaces lane1, tSpaces lane2);
bool process6(tPlayers players, tColor playerTurn, int &award, bool &nextPlayer, int &sixes, int &lastMarkerMoved, int &roll, tSpaces lane1, tSpaces lane2);
bool play(tPlayers players, tColor playerTurn, int &award, bool &end, int &sixes, int &lastMarkerMoved, int roll, tSpaces lane1, tSpaces lane2);
bool canMove(const tPlayers players, int marker, int &space, tColor playerTurn, int roll, const tSpaces lane1, const tSpaces lane2);

short startSpace(tColor color);
short zanataSpace(tColor color);
short dice();
short movePlayer(short player, tColor color, short rolled);

int nextSpace(int position, tColor playerTurn);
int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);
int colorToPlayer(tColor color);

void load(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2);
void openBridge(tPlayers players, tColor playerTurn, int space, int space2, int &award, int &lastMarkerMoved, tSpaces lane1, tSpaces lane2);
void move(tPlayers players, tColor playerTurn, int marker, int space, int &award, tSpaces lane1, tSpaces lane2);
void markerOut(tPlayers players, tColor playerTurn, tSpaces lane1, tSpaces lane2);
void toHome(tPlayers players, int space, tSpaces lane1, tSpaces lane2);
void display(const tPlayers players, const tSpaces lane1, const tSpaces lane2);
void initialize(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2);
void setColor(tColor color);
void initColors();
void pause();

int main()
{
   tPlayers players;
   tSpaces lane1, lane2;
   tColor playerTurn;
   bool forcedMove = false, passTurn = true, end = false, played;
   int rolled, reward = false, next;

   initColors();
   initialize(players, playerTurn, lane1, lane2);
   if (Debug)
      load(players, playerTurn, lane1, lane2);
   display(players, lane1, lane2);

   setColor(playerTurn);
   cout << "The " << colorToString(playerTurn) << " player starts" << endl;
   while (!end)
   {
      played = false;
      setColor(playerTurn);
      cout << "Turn for the " << colorToString(playerTurn) << " player" << endl;

      rolled = dice();
      cin.get();
      cout << "A " << rolled << " is rolled" << endl;
      if (rolled == 5){
         played = process5(players, playerTurn, reward, passTurn, lane1, lane2); 
         if (played)
            cout << "A marker gets out of home (reward: " << reward << ", passTurn: " << passTurn << ")" << endl;
         else
            cout << "No marker can get out of home" << endl;
      }
      if (!played){
         for (int m = 0; m < NUM_MARKERS ; m++) {
            cout << m + 1 << ": ";
            if (canMove(players, m, next, playerTurn, rolled, lane1, lane2))
               cout << "Can go to the space " << next << endl;
            else
               cout << "Can not be moved" << endl;
         }
      }
      if (rolled == 0)
         end = true;
      if (passTurn)
         playerTurn = tColor((int(playerTurn) + 1) % NUM_PLAYERS);
      else
         passTurn = true;
      pause();
      display(players, lane1, lane2);
   }

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

bool allAtGoal(const tMarkers player);
bool isSafe(int pos)
{
   bool result = false;
   if (pos > 100)          // Zanata (maybe not correct)
      result = true;
   pos %= 17;
   if (pos == 0 || pos == 5 || pos == 12)
   {
      result = true;
   }

   return result;
}
bool bridge(const tSpaces lane1, const tSpaces lane2, int space){
   bool out;
   // out = space >= 0 && space <= 67;                // Space must be in the street
   out = lane1[space] == lane2[space]; // && out     // If two markers of the same player in the space are
   out = out && (lane1[space] != None);              // Those are real markers not space

   return out;
}
bool process5(tPlayers players, tColor playerTurn, int &reward, bool &nextPlayer, tSpaces lane1, tSpaces lane2)
{
   // Work in progress
   bool out = false;
   int start, marker;
   start = startSpace(playerTurn);
   marker = firstAt(players[playerTurn], -1);
   if (marker != -1){
      if (lane2[start] == None) {           // Lane 2 is free 
         markerOut(players, playerTurn, lane1, lane2);
         out = true;
      } else if (lane2[start] == playerTurn){      // Two of playerTurn at start
         out = false;
      } else if (lane2[start] != playerTurn){      // One out
         toHome(players, start, lane1, lane2);
         markerOut(players, playerTurn, lane1, lane2);
         out = true;
         reward = 20;
         nextPlayer = false;
      }
   }
   return out;
}
bool process6(tPlayers players, tColor playerTurn, int &award, bool &nextPlayer, int &sixes, int &lastMarkerMoved, int &roll, tSpaces lane1, tSpaces lane2);
bool play(tPlayers players, tColor playerTurn, int &award, bool &end, int &sixes, int &lastMarkerMoved, int roll, tSpaces lane1, tSpaces lane2);
bool canMove(const tPlayers players, int marker, int &space, tColor playerTurn, int rolled, const tSpaces lane1, const tSpaces lane2){
   bool canmove = true, lastMove = false;
   int position = players[playerTurn][marker];
   if (position != -1){
      for (int i = 0; i < rolled; i++){
         position = nextSpace(position, playerTurn);        // No need to check first position
         if ((i + 1) == rolled)
            lastMove = true;
         if (lastMove && lane1[position] != None && lane2[position] != None){ // Last move is a full of players
            canmove = false;
            // cout << "Last space full" << endl; // Debug
         }
         if (position == Goal && !lastMove)
            canmove = false;
         if (bridge(lane1, lane2, position) && isSafe(position)){
            // cout << "Bridge found" << endl;  // Debug
            canmove = false;
         }
      }
      if (canmove)
         space = position;
   } else
      canmove = false;           // If player at home it can´t move (process 5 would have catch it)
   return canmove;
}

short startSpace(tColor color)
{
   short result;
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
short zanataSpace(tColor color)
{
   return startSpace(color) - 5;
}
short dice()
{
   short out;
   if (Debug)
   {
      cout << "Roll (0 to exit): ";
      cin >> out;
   }
   else
      out = rand() % 6 + 1;
   return out;
}
short movePlayer(short player, tColor color, short rolled);

int nextSpace(int position, tColor playerTurn){
   int next;
   if (position == zanataSpace(playerTurn))
      next = 101;
   else if (position == 67)
      next = 0;
   else 
      next = position + 1;
   
   return next;
}
int howMany(const tMarkers player, int space)
{
   int out = 0;
   for (int i = 0; i < NUM_MARKERS; i++)
      if (player[i] == space)
         out++;
   return out;
}
int firstAt(const tMarkers player, int space)
{
   int out = -1;
   bool found = false;
   for (int i = 0; i < NUM_MARKERS; i++)
   {
      if (player[i] == space && !found)
      {
         out = i;
         found = true;
      }
   }
   return out;
}
int secondAt(const tMarkers player, int space)
{
   int out = -1;
   for (int i = 0; i < NUM_MARKERS; i++)
      if (player[i] == space)
         out = i;
   return out;
}
int colorToPlayer(tColor color)
{
   return int(color);
}

void load(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2)
{
   ifstream file;
   int player, space;

   file.open(FileName);
   if (file.is_open())
   {
      for (int i = 0; i < NUM_PLAYERS; i++)
         for (int f = 0; f < NUM_MARKERS; f++)
         {
            file >> space;
            players[i][f] = space;
            if ((space >= 0) && (space < NUM_SPACES))
               if (lane1[space] == None)
                  lane1[space] = tColor(i);
               else
                  lane2[space] = tColor(i);
         }
      file >> player;
      playerTurn = tColor(player);
      file.close();
   }
}
void openBridge(tPlayers players, tColor playerTurn, int space, int space2, int &award, int &lastMarkerMoved, tSpaces lane1, tSpaces lane2);
void move(tPlayers players, tColor playerTurn, int marker, int space, int &award, tSpaces lane1, tSpaces lane2);

void markerOut(tPlayers players, tColor playerTurn, tSpaces lane1, tSpaces lane2)
{
   short space, markerHome;
   bool found = false;
   space = startSpace(playerTurn);
   lane2[space] = lane1[space];

   markerHome = firstAt(players[playerTurn], -1);
   players[playerTurn][markerHome] = space;
   lane1[space] = playerTurn;
}
void toHome(tPlayers players, int space, tSpaces lane1, tSpaces lane2)
{
   tColor player = lane2[space];
   int marker = secondAt(players[player], space);
   players[player][marker] = -1;
   lane2[space] = None;
}
void display(const tPlayers players, const tSpaces lane1, const tSpaces lane2)
{
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
   for (int i = 0; i < NUM_SPACES; i++)
   {
      setColor(lane2[i]);
      if (lane2[i] != None)
         cout << firstAt(players[colorToPlayer(lane2[i])], i) + 1;
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
   for (int i = 0; i < NUM_SPACES; i++)
   {
      setColor(lane1[i]);
      if (lane1[i] != None)
         cout << secondAt(players[colorToPlayer(lane1[i])], i) + 1;
      else
         cout << ' ';
      setColor(Gray);
   }
   cout << endl;

   jug = 0;
   // Lower border...
   for (int i = 0; i < NUM_SPACES; i++)
      if (i == zanataSpace(tColor(jug)))
      {
         setColor(tColor(jug));
         cout << "V";
         setColor(Gray);
      }
      else if (i == startSpace(tColor(jug)))
      {
         setColor(tColor(jug));
         cout << "^";
         setColor(Gray);
         jug++;
      }
      else
         cout << '>';
   cout << endl;

   // Goal paths and homes...
   for (int i = 0; i < NUM_MARKERS; i++)
   {
      space = 0;
      jug = 0;
      setColor(tColor(jug));
      while (space < NUM_SPACES)
      {
         if (space == zanataSpace(tColor(jug)))
         {
            marker = firstAt(players[jug], 101 + i);
            if (marker != -1)
            {
               cout << marker + 1;
               if (howMany(players[jug], 101 + i) > 1)
               {
                  marker = secondAt(players[jug], 101 + i);
                  if (marker != -1)
                  {
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
         else if (space == startSpace(tColor(jug)))
         {
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
   for (int i = 105; i <= 107; i++)
   {
      space = 0;
      jug = 0;
      setColor(tColor(jug));
      while (space < NUM_SPACES)
      {
         if (space == zanataSpace(tColor(jug)))
         {
            marker = firstAt(players[jug], i);
            if (marker != -1)
            {
               cout << marker + 1;
               if (howMany(players[jug], i) > 1)
               {
                  marker = secondAt(players[jug], i);
                  if (marker != -1)
                  {
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
   while (space < NUM_SPACES)
   {
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
   while (space < NUM_SPACES)
   {
      cout << ((players[jug][2] == 108) ? '3' : '.');
      cout << ((players[jug][3] == 108) ? '4' : '.');
      jug++;
      setColor(tColor(jug));
      cout << "               ";
      space += 17;
   }
   cout << endl
        << endl;
   setColor(Gray);
}
void setColor(tColor color)
{
   switch (color)
   {
   case Yellow:
      cout << "\x1b[33;40m";
      break;
   case Blue:
      cout << "\x1b[34;40m";
      break;
   case Red:
      cout << "\x1b[31;40m";
      break;
   case Green:
      cout << "\x1b[32;40m";
      break;
   case Gray:
   case None:
      cout << "\x1b[97;40m";    // \x1b[90;107m
      break;
   }
}
void initialize(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2)
{
   ofstream outputFile("debug.txt");
   int temp;

   srand(time(NULL));
   for (int i = 0; i < NUM_PLAYERS; i++)
   {
      for (int j = 0; j < NUM_PLAYERS; j++)
      {
         players[i][j] = -1;
      }
   }

   for (int i = 0; i < NUM_SPACES; i++)
   {
      lane1[i] = None;
      lane2[i] = None;
   }

   temp = rand();
   outputFile << temp << endl;
   temp %= NUM_PLAYERS;
   outputFile << temp << endl;
   playerTurn = tColor(temp);
   setColor(Gray);
}
void initColors()
{
#ifdef _WIN32
   for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE})
   {
      DWORD mode;
      HANDLE handle = GetStdHandle(stream);

      if (GetConsoleMode(handle, &mode))
      {
         mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
         SetConsoleMode(handle, mode);
      }
   }
#endif
}
void pause()
{
   cout << "Press Enter to continue...";
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

