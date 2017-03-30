/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#include "TicTacToeView.h"
#include <string>
#include <sstream>

using namespace std;

// The method that does the actual printing to a stream.
void TicTacToeView::PrintBoard(ostream &s) const {
   //Print the contents of the gameboard
   s << "\nGameboard:\n\n- 0 1 2";
   for (int i = 0; i < TTT_BOARD_SIZE; i++) {
      s << "\n" << i << " ";
      for (int j = 0; j < TTT_BOARD_SIZE; j++) {
         s << (mTicTacToeBoard->mBoard[i][j] == 0 ?  ". " : 
          mTicTacToeBoard->mBoard[i][j] > 0 ?  "X " : "O ");
      }//close inner for loop
   }//close outer for loop
   s << endl;
}//close PrintBoard(...)