#include "OthelloView.h"

#include <string>
#include <sstream>

using namespace std;

// The method that does the actual printing to a stream.
void OthelloView::PrintBoard(ostream &s) const {
   //Print the contents of the gameboard
   s << "\nGameboard:\n\n- 0 1 2 3 4 5 6 7";
   for (int i = 0; i < BOARD_SIZE; i++) {
      s << "\n" << i << " ";
      for (int j = 0; j < BOARD_SIZE; j++) {
         s << (mOthelloBoard->mBoard[i][j] == 0 ?  ". " : 
          mOthelloBoard->mBoard[i][j] > 0 ?  "B " : "W ");
      }//close inner for loop
   }//close outer for loop
   s << endl;
}//close PrintBoard(...)

