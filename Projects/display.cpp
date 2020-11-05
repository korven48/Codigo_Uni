void display(int player1, int player2, int space1, int space2) {
   char c;
   
   // Space numbers...
   cout << endl << "       ";
   for (int pos = 0; pos < NUM_SPACES; pos++) {
      cout << pos / 10;
   }
   cout << endl << "       ";
   for (int pos = 0; pos < NUM_SPACES; pos++) {
      cout << pos % 10;
   }
   cout << endl << "       ";

   // Safe spaces line...
   for (int pos = 0; pos <= 67; pos++) {
      if (isSafe(pos)) {
         cout << "o";
      }
      else {
         cout << "-";
      }
   }
   cout << endl << "STREET ";

   // Markers out of home...
   for (int pos = 0; pos < NUM_SPACES; pos++) {
      if (pos == space1)
         cout << colorToLetter(tColor(player1 - 1));
      else if (pos == space2)
         cout << colorToLetter(tColor(player2 - 1));
      else
         cout << " ";
   }
   cout << endl << "       ";

   // Other safe spaces line...
   for (int pos = 0; pos <= 67; pos++) {
      if (isSafe(pos)) {
         cout << "o";
      }
      else {
         cout << "-";
      }
   }

   // Markers at home...
   cout << endl << "HOME   ";
   for (int pos = 0; pos < NUM_SPACES; pos++) {
      c = ' ';
      if (pos == playerStart(player1)) {
         if (space1 == -1)
            c = colorToLetter(tColor(player1 - 1));
      }
      else if (pos == playerStart(player2))
         if (space2 == -1)
            c = colorToLetter(tColor(player2 - 1));
      cout << c;
   }
   cout << endl;

   system("pause");
}
