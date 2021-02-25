/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <ctime>

using namespace std;

enum tColor
{
   red = 0,
   green,
   blue,
   yellow
};

const short N_Players = 2;
typedef short tPositionArray[N_Players];
typedef tColor tColorArray[N_Players];
tColor chooseColor();
string colorToString(tColor color);
char colorToLetter(tColor color);
bool isSafe(int pos);
short playerStart(tColor color);
short dice();
int distance(int x, int y);

void display(const tColorArray colors, const tPositionArray positions);
short movePlayer(short player, tColor color, short rolled);

bool DEBUG = true;
const int NUM_SPACES = 68;

int main()
{
   const int ExtraMoves = 20;
   tPositionArray positions = {-1, -1};
   tColorArray colors;
   short turn = 0, space1, space2, rolled, nSixes = 0;

   srand(time(NULL));

   for (int i = 0; i < N_Players; i++)
   {
      cout << "Choose the color for the player number " << (i + 1) << "..." << endl;
      colors[i] = chooseColor();
   }


   display(colors, positions);
   while (true)
   {
      rolled = dice();
      if (rolled == 6)
         nSixes++;
      cout << "Turn for the player " << colorToString(colors[turn]) << endl;
      cout << "Rolled: " << rolled << endl;
      positions[turn] = movePlayer(positions[turn], colors[turn], rolled);

      // Check if player eats another one
      for (int i = 0; i < N_Players; i++){
         if (i != turn && positions[turn] == positions[i] && positions[turn] != -1){
            cout << colorToString(colors[turn]) << " eated " << colorToString(colors[i]) << endl;
            positions[i] = -1;
            display(colors, positions);
            positions[turn] = movePlayer(positions[turn], colors[turn], ExtraMoves);
         }
      }

      display(colors, positions);
      if (rolled != 6 || nSixes == 3){
         turn = (turn + 1) % N_Players;
         nSixes = 0;
      }
   }
   return 0;
}

short dice()
{
   short num;
   if (DEBUG)
   {
      cout << "Dice: ";
      cin >> num;
   }
   else
      num = rand() % 6 + 1;
   return num;
}

void display(const tColorArray colors, const tPositionArray positions)
{
   char c;
   bool temp;
   // Space numbers...
   cout << endl
        << "       ";
   for (int pos = 0; pos < NUM_SPACES; pos++)
   {
      cout << pos / 10;
   }
   cout << endl
        << "       ";
   for (int pos = 0; pos < NUM_SPACES; pos++)
   {
      cout << pos % 10;
   }
   cout << endl
        << "       ";

   // Safe spaces line...
   for (int pos = 0; pos <= 67; pos++)
   {
      if (isSafe(pos))
      {
         cout << "o";
      }
      else
      {
         cout << "-";
      }
   }
   cout << endl
        << "STREET ";

   // Markers out of home...
   for (int pos = 0; pos < NUM_SPACES; pos++)
   {
      temp = false;
      for (int i = 0; i < N_Players; i++)
         if (pos == positions[i]){
            cout << colorToLetter(colors[i]);
            temp = true;
         }
         if (!temp)
            cout << " ";
   }
   cout << endl
        << "       ";

   // Other safe spaces line...
   for (int pos = 0; pos <= 67; pos++)
   {
      if (isSafe(pos))
      {
         cout << "o";
      }
      else
      {
         cout << "-";
      }
   }

   // Markers at home...
   cout << endl
        << "HOME   ";
   for (int pos = 0; pos < NUM_SPACES; pos++)
   {
      c = ' ';
      for (int i = 0; i < N_Players; i++){
         if (pos == playerStart(colors[i]))
         {
            if (positions[i] == -1)
               c = colorToLetter(colors[i]);
         }
      }
      cout << c;
   }
   cout << endl;

   system("pause");
}

tColor chooseColor()
{
   short option;
   tColor result;
   cout << "Choose the color for the player 1. Red, 2. Green, 3. Blue, 4. Yellow: ";
   cin >> option;

   result = tColor(option - 1);
   return result;
}

string colorToString(tColor color)
{
   string result;
   switch (color)
   {
   case red:  
      result = "Red";
      break;
   case green:
      result = "Green";
      break;
   case blue:
      result = "Blue";
      break;
   case yellow:
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

short playerStart(tColor color)
{
   short result;
   switch (color)
   {
   case red:
      result = 39;
      break;
   case green:
      result = 56;
      break;
   case blue:
      result = 22;
      break;
   case yellow:
      result = 5;
      break;
   }

   return result;
}

short movePlayer(short player, tColor color, short rolled)
{
   short next;
   int goal = playerStart(color) - 5;
   if (player != -1)
   {
      next = (player + rolled) % 68;
      if (rolled > distance(goal, player)) 
      {
         cout << "Not a possible move (the goal is closer)!" << endl;
         next = player;
      }
      if (next == goal){
         cout << colorToString(color) << " wins!" << endl;
         cout << "Press any key to finish." << endl;
         system("pause");
         exit(0);
      }
   }
   else if (rolled == 5)
      next = playerStart(color);
   else
      next = player;

   return next;
}

int distance(int x, int y){
   int out; 
   if ((x - y) > 0) 
      out = x - y;
   else 
      out = 68 + x - y;
   return out;
}