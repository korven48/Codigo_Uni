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

const string FileName = "test6.txt"; // test5 canMove test6 | .txt
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

bool displayPossibilities(tPlayers players, tColor playerTurn, int rolled, tSpaces lane1, tSpaces lane2);
bool allAtGoal(const tMarkers player);
bool isSafe(int pos);
bool bridge(const tSpaces lane1, const tSpaces lane2, int space);
bool process5(tPlayers players, tColor playerTurn, int &reward, bool &passTurn, tSpaces lane1, tSpaces lane2);
bool process6(tPlayers players, tColor playerTurn, int &reward, bool &passTurn, int &sixes, int &lastMarkerMoved, int &roll, tSpaces lane1, tSpaces lane2);
bool play(tPlayers players, tColor playerTurn, int &reward, bool &end, int &sixes, int &lastMarkerMoved, int roll, tSpaces lane1, tSpaces lane2);
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
int n_bridges(tMarkers player, int &marker1, int &marker2);

void load(tPlayers players, tColor &playerTurn, tSpaces lane1, tSpaces lane2);
void openBridge(tPlayers players, tColor playerTurn, int space, int space2, int &reward, int &lastMarkerMoved, tSpaces lane1, tSpaces lane2);
void move(tPlayers players, tColor playerTurn, int marker, int space, int &reward, tSpaces lane1, tSpaces lane2);
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
   int rolled, reward = false, next, marker, sixes = 0, lastMarkerMoved;

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
      if (reward > 0){
         cout << "The player has " << reward << " extra moves!" << endl;
         rolled = reward;
         reward = 0;
      } else {
         rolled = dice();
         cin.get();
         cout << "A " << rolled << " is rolled" << endl;
      }
      if (rolled == 0) {
         end = true;
      } else {
         if (rolled == 5){
            played = process5(players, playerTurn, reward, passTurn, lane1, lane2); 
            if (played)
               cout << "A marker gets out of home (reward: " << reward << ", passTurn: " << passTurn << ")" << endl;
            else
               cout << "No marker can get out of home" << endl;
         } else if (rolled == 6){
            played = process6(players, playerTurn, reward, passTurn, sixes, lastMarkerMoved, rolled, lane1, lane2);
         }
         if (!played){
            bool possibleMove = displayPossibilities(players, playerTurn, rolled, lane1, lane2);

            if (possibleMove){
               cout << "Marker to move: ";
               cin >> marker;
               cin.get();
               marker--;
               if (canMove(players, marker, next, playerTurn, rolled, lane1, lane2)){
                  move(players, playerTurn, marker, next, reward, lane1, lane2);
                  cout << "Reward: " << reward << endl;
                  lastMarkerMoved = marker;
               }
            }
            if ((rolled > 7) && (sixes > 0)){  //Reward after a 6
               passTurn = false;
            }
         }
         if (rolled == 0)
            end = true;
         if (passTurn){
            playerTurn = tColor((int(playerTurn) + 1) % NUM_PLAYERS);
            sixes = 0;
         } else
            passTurn = true;
         
         pause();
         display(players, lane1, lane2);
      }
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

bool displayPossibilities(tPlayers players, tColor playerTurn, int rolled, tSpaces lane1, tSpaces lane2){
   int next;
   bool possibleMove = false;
   for (int m = 0; m < NUM_MARKERS ; m++) {
   cout << m + 1 << ": ";
   if (canMove(players, m, next, playerTurn, rolled, lane1, lane2)){
      cout << "Can go to the space " << next << endl;
      possibleMove = true;
   }
   else
      cout << "Can not be moved" << endl;
   }
   return possibleMove;
}
bool allAtGoal(const tMarkers player){
   bool all = true;
   for (int marker = 0; marker < NUM_MARKERS; marker++)
      if (player[marker] == Goal)
         all = false;
   return all;
}
bool isSafe(int pos)
{
   bool result = false;
   if (pos > 100)          // Zanata (not sure if it should be safe)
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
bool process5(tPlayers players, tColor playerTurn, int &reward, bool &passTurn, tSpaces lane1, tSpaces lane2)
{
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
         passTurn = false;
      }
   }
   return out;
}
bool process6(tPlayers players, tColor playerTurn, int &reward, bool &passTurn, int &sixes, int &lastMarkerMoved, int &roll, tSpaces lane1, tSpaces lane2){
   int marker1 = -1, marker2 = -1, bridges, next, space;
   bool out = false;
   bridges = n_bridges(players[playerTurn], marker1, marker2);
   sixes++;
   if (firstAt(players[playerTurn], -1) == -1){    // No markers at home
      roll = 7;
      cout << "The player has no markers at home: 7 are counted!" << endl;
   }

   if (sixes == 3){
      space = players[playerTurn][lastMarkerMoved];
      cout << "Third 6 in a row...";
      if (space > 100){
         cout << "The last marker moved is beyond zanata and it is not sent home!" << endl;
      } else{  
         // It is sent home, placing it first on lane2
         cout << "The last marker moved is sent home!" << endl;
         if (lane2[space] != playerTurn){
            tColor temp = lane1[space];
            lane1[space] = lane2[space];
            lane2[space] = temp;
         }
         toHome(players, space, lane1, lane2);
      }
      passTurn = true;
      out = true;
      sixes = 0;
   } else{
      passTurn = false;
      if (bridges == 1 && canMove(players, marker1, next, playerTurn, roll, lane1, lane2)){
         space = players[playerTurn][marker1];
         openBridge(players, playerTurn, space, next, reward, lastMarkerMoved, lane1, lane2);
         out = true;
      }
      if (bridges == 2){
         bool first, second;
         int next2;
         first = canMove(players, marker1, next, playerTurn, roll, lane1, lane2);
         second = canMove(players, marker2, next2, playerTurn, roll, lane1, lane2);
         if (first && second){
            out = false;
         } else if (first){
            space = players[playerTurn][marker1];
            openBridge(players, playerTurn, space, next, reward, lastMarkerMoved, lane1, lane2);
            out = true;
         } else if (second){
            space = players[playerTurn][marker2];
            openBridge(players, playerTurn, space, next2, reward, lastMarkerMoved, lane1, lane2);
            out = true;
         } else {
            // No marker can be moved
            cout << "None of the two bridges can be opened! The roll is ignored..." << endl;
            out = true; // Suposed to be false but true makes more sense.
         }
      }
   } 
   return out;
}
bool play(tPlayers players, tColor playerTurn, int &reward, bool &end, int &sixes, int &lastMarkerMoved, int roll, tSpaces lane1, tSpaces lane2){
   // WIP
   bool passTurn = true;
   return passTurn;
}
bool canMove(const tPlayers players, int marker, int &space, tColor playerTurn, int rolled, const tSpaces lane1, const tSpaces lane2){
   bool canmove = true, lastMove = false;
   int position = players[playerTurn][marker];
   if (position != -1){
      for (int i = 0; i < rolled; i++){
         position = nextSpace(position, playerTurn);        // No need to check first position
         if ((i + 1) == rolled)
            lastMove = true;
         if (lastMove && lane1[position] != None && lane2[position] != None){ // Last move is full of players
            canmove = false;
            // cout << "Last space full" << endl; // Debug
         }
         if (position == Goal && !lastMove)
            canmove = false;
         if (bridge(lane1, lane2, position) && lastMove){
            canmove = false;
         }
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
int n_bridges(tMarkers player, int &marker1, int &marker2){
   int bridges = 0;
   for (int i = 0; i < NUM_MARKERS; i++)
      for (int j = i + 1; j < NUM_MARKERS; j++)
         if (player[i] == player[j]){
            bridges++;
            if (marker1 == -1)
               marker1 = i;
            else
               marker2 = i;
         }
   return bridges;
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
void openBridge(tPlayers players, tColor playerTurn, int space, int space2, int &reward, int &lastMarkerMoved, tSpaces lane1, tSpaces lane2){
   // ???
   int marker = secondAt(players[playerTurn], space);
   cout << "The bridge in space " << space << " is opened" << endl;
   move(players, playerTurn, marker, space2, reward, lane1, lane2);
   lastMarkerMoved = marker;
}
void move(tPlayers players, tColor playerTurn, int marker, int space, int &reward, tSpaces lane1, tSpaces lane2){
   int previous, next;
   previous = players[playerTurn][marker];
   next = space;

   lane1[previous] = lane2[previous];
   lane2[previous] = None;

   players[playerTurn][marker] = next;

   if (next == Goal){
      cout << "The players marker has arrived to the goal" << endl;
      reward = 10;
   }
   if (next >= 0 && next <= 67){
      if (lane1[next] == None)
         lane1[next] = playerTurn;
      else if (lane1[next] == playerTurn)
         lane2[next] = playerTurn;
      else if (isSafe(next))
         lane2[next] = playerTurn;
      else  // playerTurn eats lane1[next]
      {
         cout << "A marker of the " << colorToString(lane1[next]) << " player has been eaten..." << endl;
         lane2[next] = lane1[next];
         lane1[next] = playerTurn;
         toHome(players, next, lane1, lane2);
         reward = 20;
      }
   }
}

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

