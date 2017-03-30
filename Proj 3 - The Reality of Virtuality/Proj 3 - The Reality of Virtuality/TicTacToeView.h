/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#ifndef __TICTACTOEVIEW_H
#define __TICTACTOEVIEW_H
#include "TicTacToeBoard.h"
#include "GameView.h"
#include <iostream>

/*
An MVC "View" class for printing the model of the Tic Tac Toe board. Acts as 
a "wrapper" around a TicTacToeBoard pointer and handles requests to print that 
board to a stream by overloading operator<<. Friend of TicTacToeBoard.
*/
class TicTacToeView : public GameView {

private:
   // The actual TicTacToeBoard pointer.
   TicTacToeBoard *mTicTacToeBoard;


public:
   // The method that does the actual printing to a stream.
   virtual void PrintBoard(std::ostream &s) const;

   TicTacToeView(GameBoard *b) : mTicTacToeBoard((TicTacToeBoard *) b) {}
};	//close class TicTacToeView
#endif