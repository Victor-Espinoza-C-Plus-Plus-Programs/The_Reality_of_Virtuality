#ifndef __OTHELLOVIEW_H
#define __OTHELLOVIEW_H
#include "OthelloBoard.h"
#include "GameView.h"
#include <iostream>

/*
An MVC "View" class for printing the model of the othello board. Acts as a
"wrapper" around an OthelloBoard pointer and handles requests to print that 
board to a stream by overloading operator<<. Friend of OthelloBoard.
*/
class OthelloView : public GameView {

private:
   // The actual OthelloBoard pointer.
   OthelloBoard *mOthelloBoard;

public:
   // The method that does the actual printing to a stream.
   virtual void PrintBoard(std::ostream &s) const;

   OthelloView(GameBoard *b) : mOthelloBoard((OthelloBoard *) b) {}
};
#endif