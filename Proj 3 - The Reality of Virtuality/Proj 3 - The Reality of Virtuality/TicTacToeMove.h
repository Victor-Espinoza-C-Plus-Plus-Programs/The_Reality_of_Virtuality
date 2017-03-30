/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>

/*
A TicTacToeMove encapsulates a single potential move on a TicTacToeBoard. It
is represented internally by a row and column, both 0-based.
*/
class TicTacToeMove : public GameMove {
private:
   // TicTacToeBoard is a friend so it can access mRow and mCol.
   friend class TicTacToeBoard;

   int mRow, mCol;

   // KEEP THESE CONSTRUCTORS PRIVATE.
   // Default constructor: initializes this move as a PASS.
   TicTacToeMove();


   // 2-parameter constructor: initializes this move with the given 
   // row and column.
   TicTacToeMove(int row, int col);

   static int mOutstanding;


public:

   static void* operator new(std::size_t sz) {
      mOutstanding++;
      std::cout << "operator new: " << mOutstanding << " moves outstanding" 
       << std::endl;
      return ::operator new(sz);
   }//close new(...)


   static void operator delete(void* ptr, std::size_t sz) {
      mOutstanding--;
      std::cout << "operator delete: " << mOutstanding << " moves oustanding" 
       << std::endl;
      ::operator delete(ptr);
   }//close delete(...)

   virtual ~TicTacToeMove() {}

   TicTacToeMove(const TicTacToeMove &);

   TicTacToeMove& operator=(const TicTacToeMove &rhs);


   /*
   This assignment operator takes a string representation of a TicTacToeMove
   and uses it to initialize the move. The string is in the format
   (r, c); OR is the string "pass".
   */
   virtual GameMove& operator=(const std::string &);


   // Compares two TicTacToeMove objects for equality.
   virtual bool Equals(const GameMove &other) const;


   // Converts the TicTacToeMove into a string representation, one that  
   // could be used correctly with operator=(string). Returns "pass" if move 
   // is a pass.
   virtual operator std::string() const;


   // Returns true if the move represents a Pass.
   // TO DO: fill in this method.
   inline bool IsPass() const {return mRow == -1 && mCol == -1;}


   virtual GameMove *Clone() const {
      return new TicTacToeMove(*this);
   }//close *Clone()
};	//close class TicTacToeMove

#endif