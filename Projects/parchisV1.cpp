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

tColor chooseColor();
string colorToString(tColor color);
char colorToLetter(tColor color);
bool isSafe(int pos);
short playerStart(tColor color);
short dice();

void display(tColor color1, tColor color2, short player1, short player2);
short movePlayer(short player, tColor color, short rolled);

bool DEBUG = true;
const int NUM_SPACES = 68;

int main()
{
   const int ExtraMoves = 20;
   short player1 = -1, player2 = -1, turn = 0, space1, space2, rolled, nSixes;
   tColor color1, color2;

   // safe place, goals, zanatas
   srand(time(NULL));

   cout << "Choose the color for the first player..." << endl;
   color1 = chooseColor();
   cout << "Choose the color for the second player..." << endl;
   color2 = chooseColor();

   display(color1, color2, player1, player2);
   while (true)
   {
      rolled = dice();
      switch (turn)
      {
      case 0:
         cout << "Turn for the player " << colorToString(color1) << endl;
         cout << "Rolled: " << rolled << endl;
         player1 = movePlayer(player1, color1, rolled);
         if (player1 == player2){
            cout << colorToString(color1) << " eated " << colorToString(color2) << endl;
            display(color1, color2, player1, player2);
            player2 = -1;
            player1 = movePlayer(player1, color1, ExtraMoves);
         }          
         break;
      case 1:
         cout << "Turn for the player " << colorToString(color2) << endl;
         cout << "Rolled: " << rolled << endl;
         player2 = movePlayer(player2, color2, rolled);
         if (player1 == player2){
            cout << colorToString(color1) << " eated " << colorToString(color2) << endl;
            display(color1, color2, player1, player2);
            player2 = -1;
            player1 = movePlayer(player1, color1, ExtraMoves);
         } 
         break;
      }
      if (rolled == 6)
         nSixes++;

      display(color1, color2, player1, player2);
      if (rolled != 6 && nSixes < 3){
         turn = (turn + 1) % 2;
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

void display(tColor color1, tColor color2, short player1, short player2)
{
   char c;

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
      if (pos == player1)
         cout << colorToLetter(color1);
      else if (pos == player2)
         cout << colorToLetter(color2);
      else
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
      if (pos == playerStart(color1))
      {
         if (player1 == -1)
            c = colorToLetter(color1);
      }
      else if (pos == playerStart(color2))
         if (player2 == -1)
            c = colorToLetter(color2);
      cout << c;
   }
   cout << endl;

   system("pause");
}

tColor chooseColor()
{
   int option;
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
      if (playerStart(color) >= next && next > goal)
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
