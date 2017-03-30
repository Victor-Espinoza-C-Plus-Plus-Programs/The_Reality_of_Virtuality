/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
using namespace std;
const int BOARD_INIT_VAR1 = 3;
const int BOARD_INIT_VAR2 = 4;

// Default constructor initializes the board to its starting "new game" state
TicTacToeBoard::TicTacToeBoard() {
   //initialize the whole board to 0
   for (int i = 0; i < TTT_BOARD_SIZE; i++) {
      for (int j = 0; j < TTT_BOARD_SIZE; j++) {
         mBoard[i][j] = 0;
      }//close inner for loop
   }//close outer for loop
   mValue = 0, mPassCount = 0;
   mNextPlayer = O;
}//close OthelloBoard()	 default constructor


/* 
Fills in a vector with all possible moves on the current board state for
the current player. The moves should be ordered based first on row, then on
column. Example ordering: (0, 0) (0, 2) (1, 0) (2, 0) (2, 2) 
If no moves are possible, then a single TicTacToeMove representing a Pass 
is put in the vector.
Any code that calls ApplyMove is responsible for first checking that the
requested move is among the possible moves reported by this function.

Precondition: the vector is empty.
Postcondition: the vector contains all valid moves for the current player.
*/
void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   //Local Variables:
   //keeps track of the current player
   char currentPlayer = (mNextPlayer == O ? X : O);
   //this variable is to determine whether the user must pass or not
   bool  mustPass = true;
   //Look through every spot on the board to see if the user can move to the 
   //designated spot on the gameboard.
   for (char i = 0; i < TTT_BOARD_SIZE; i++) {
      for (char j = 0; j < TTT_BOARD_SIZE; j++) {
         //Move to the space occupied by (i, j). Make sure that the space is
         //InBounds and is empty, otherwise this would not be a valid move.
         if (InBounds(i, j) && mBoard[i][j] == 0) {
            //If the current location is inbounds and is empty, set the 
            //mustPass variable to false.
            mustPass = false;
            //This means that this space is a valid possible move. Push
            //the move onto the back of the list.
            TicTacToeMove *possibleMove = (TicTacToeMove *) CreateMove();
            *possibleMove = TicTacToeMove(i, j);
            list->push_back(possibleMove);
         }//end if
      }//close inner for loop
   }//close outer for loop
   //if the mustPass variable is still true, then the user must pass. We push 
   //the pass move into the back of the list.
   if (mustPass) {
      TicTacToeMove *passMove = (TicTacToeMove *) CreateMove();
      *passMove = TicTacToeMove();
      list->push_back(passMove);
   }//end if statement
}//close GetPossibleMoves(...) const


/* 
Applies a valid move to the board, updating the board state accordingly.
You may assume that this move is valid, and is consistent with the list
of possible moves returned by GetPossibleMoves. Make sure you account for 
changes to the current player, pass count, and board value.
*/
void TicTacToeBoard::ApplyMove(GameMove *move) {
   //Local Variables:
   TicTacToeMove *m = (TicTacToeMove *) move;
   //keeps track of the current player
   char currentPlayer = (mNextPlayer == O ? X : O);
   if (InBounds(m->mRow, m->mCol) && mBoard[m->mRow][m->mCol] == 0) {
      mBoard[m->mRow][m->mCol] = currentPlayer;
      mValue = UpdateBoardValue();
      mHistory.push_back(m);
   }//end if	
   //if the move is a pass, we add a flipset corresponding to a pass move
   if (m->IsPass()) {		
      mHistory.push_back(m);
   }//end if 
   //Increment the pass count if the move was a pass or set it to 0 otherwise
   mPassCount = (m->IsPass() ? mPassCount + 1 : 0);
   //change the value of mNextPlayer accordingly
   mNextPlayer = (mNextPlayer == O ? X : O);
}//close ApplyMove(...)


/*
Undoes the last move applied to the board, restoring it to the state it was
in prior to the most recent move (including whose turn it is, what the 
board value is, and what the pass count is).
*/
void TicTacToeBoard::UndoLastMove() {
   //set the currentPlayer variable with the appropriate value
   char currentPlayer = (mNextPlayer == O ? X : O);
   //set the deleteMove variable to the most recent move
   TicTacToeMove *deleteMove = (TicTacToeMove *) mHistory.back();
   //initialize the rowVar and colVar variables
   int rowVar = 0, colVar = 0;
   //only update board while deleting moves that are not passes
   if (!deleteMove->IsPass()) {
      //change the piece back to unoccupied
      mBoard[deleteMove->mRow][deleteMove->mCol] = 0;
   }//end if
   //delete the move after you are done undoing it and pop it from the back
   //of the mHistory vector
   delete deleteMove;
   mHistory.pop_back();
   //set mNextPlayer to the appropriate value and update mPassCount accordingly
   mNextPlayer = (mNextPlayer == O ? X : O);
   mPassCount = (GetMoveCount() > 0 ? (deleteMove->IsPass() ? 1: 0) : 0);
}//close UndoLastMove()


std::string TicTacToeBoard::GetPlayerString(char player) {
   return (player == 1 ? "X" : "O");
}//close GetPlayerString(...)


int TicTacToeBoard::UpdateBoardValue() {
   //Local Variables:
   //Determine the winner
   for (char i = 0; i < TTT_BOARD_SIZE; i++) {
      //check rows and columns for winning X moves. Also, check both diagonal
      //cases (we only do this once because it would be inefficient to 
      //check these cases three times).
      if ((mBoard[i][0] == X && mBoard[i][1] == X && mBoard[i][2] == X) ||
       (mBoard[0][i] == X && mBoard[1][i] == X && mBoard[2][i] == X) || (i
       == 0 && ((mBoard[0][0] == X && mBoard[1][1] == X && mBoard[2][2] == X) 
       || (mBoard[0][2] == X && mBoard[1][1] == X && mBoard[2][0] == X))))
         return 3;
      //check rows and columns for winning Y moves. Also, check both diagonal
      //cases (we only do this once because it would be inefficient to 
      //check these cases three times).
      else if ((mBoard[i][0] == O && mBoard[i][1] == O && mBoard[i][2] == O) 
       || (mBoard[0][i] == O && mBoard[1][i] == O && mBoard[2][i] == O) || (i
       == 0 && ((mBoard[0][0] == O && mBoard[1][1] == O && mBoard[2][2] == O) 
       || (mBoard[0][2] == O && mBoard[1][1] == O && mBoard[2][0] == O))))
         return -3;
   }//end for loop
   //If we reach the end of the loop, then that means that nobody has won yet.
   //We return a value of 0 to account for this.
   return 0;
}//close UpdateBoardValue()