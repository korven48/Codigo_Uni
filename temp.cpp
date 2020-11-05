#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

enum tColor
{
    red = 0,
    green,
    blue,
    yellow
};

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
   }
   else if (rolled == 5)
      next = playerStart(color);
   else
      next = player;
   

   return next;
}

int main(int argc, char const *argv[])
{
    cout << movePlayer(33, red, 3) << endl;

    return 0;
}
