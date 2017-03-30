#include "OthelloMove.h"
#include "GameExceptions.h"

#include <string>
#include <sstream>

#define BOARD_SIZE 8
using namespace std;

int OthelloMove::mOutstanding = 0;

// Default constructor: initializes this move as a PASS.
OthelloMove::OthelloMove() : mRow(-1), mCol(-1) {

}//close OthelloMove() default constructor


// 2-parameter constructor: initializes this move with the given 
//	row and column. 
OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col) {

}//close OthelloMove(...) 2 - parameter constructor


// Copy Constructor
OthelloMove::OthelloMove(const OthelloMove &other) : mRow(other.mRow), 
   mCol(other.mCol) {

}//close OthelloMove(...) copy constructor


// Assignment operator taking a const OthelloMove& object.
OthelloMove &OthelloMove::operator=(const OthelloMove &other) {
   if(this == &other)
      return *this;
   mRow = other.mRow;
   mCol = other.mCol;
   return *this;
}//close operator=(...)


/* 
This assignment operator takes a string representation of an Othellomove
and uses it to initialize the move. The string is in the format
(r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
anymore.]
*/
GameMove &OthelloMove::operator=(const string &string) {
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
}//close operator=(...)	 (string input)


// Compares two OthelloMove objects for equality (if rows and cols are same).
bool OthelloMove::Equals(const GameMove &other) const {
   OthelloMove &casted = (OthelloMove&) other;
   return mRow == casted.mRow && mCol == casted.mCol;
}//close Equals(...) 



/* 
Converts the OthelloMove into a string representation, one that could be
used correctly with operator=(string). Returns "pass" if move is a pass.
*/
OthelloMove::operator string() const {
   ostringstream format;
   format << "(" << mRow << "," << mCol << ")";
   return (IsPass() ? "pass" : format.str());
}//close operator string()

