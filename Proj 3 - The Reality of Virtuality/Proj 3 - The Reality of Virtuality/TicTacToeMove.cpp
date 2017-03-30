/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#include "TicTacToeMove.h"
#include "GameExceptions.h"

#include <string>
#include <sstream>

#define BOARD_SIZE 8
using namespace std;

int TicTacToeMove::mOutstanding = 0;

// Default constructor: initializes this move as a PASS.
TicTacToeMove::TicTacToeMove() : mRow(-1), mCol(-1) {

}//close TicTacToeMove() default constructor


// 2-parameter constructor: initializes this move with the given 
//	row and column. 
TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {

}//close TicTacToeMove(...) 2-parameter constructor


// Copy Constructor
TicTacToeMove::TicTacToeMove(const TicTacToeMove &other) : mRow(other.mRow), 
   mCol(other.mCol) {

}//close TicTacToeMove(...) copy constructor


// Assignment operator taking a const OthelloMove& object.
TicTacToeMove &TicTacToeMove::operator=(const TicTacToeMove &other) {
   if(this == &other)
      return *this;
   mRow = other.mRow;
   mCol = other.mCol;
   return *this;
}//close TicTacToeMove& operator=(...);


/* 
This assignment operator takes a string representation of a TicTacToeMove
and uses it to initialize the move. The string is in the format
(r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
anymore.]
*/
GameMove &TicTacToeMove::operator=(const string &string) {
   char temp;
   if (string == "pass") {
      mRow = -1;
      mCol = -1;
   }// end if
   else {
      istringstream stringBuffer(string);
      stringBuffer >> temp >> mRow >> temp >> mCol >> temp;
      if (mRow < 0 || mRow >= BOARD_SIZE || mCol < 0 || mCol >= BOARD_SIZE)
         throw OthelloException("Invalid Move!");
   }//end else
   return *this;
}//close OthelloMove& operator=(...)  (string input)


// Compares two TicTacToeMove objects for equality 
// (if rows and cols are same).
bool TicTacToeMove::Equals(const GameMove &other) const {
   TicTacToeMove &casted = (TicTacToeMove&) other;
   return mRow == casted.mRow && mCol == casted.mCol;
}//close bool TicTacToeMove::Equals(...) const 


// Converts the TicTacToeMove into a string representation, one that could be
// used correctly with operator=(string). Returns "pass" if move is a pass.
TicTacToeMove::operator string() const {
   ostringstream format;
   format << "(" << mRow << "," << mCol << ")";
   return (IsPass() ? "pass" : format.str());
}//close operator string()

