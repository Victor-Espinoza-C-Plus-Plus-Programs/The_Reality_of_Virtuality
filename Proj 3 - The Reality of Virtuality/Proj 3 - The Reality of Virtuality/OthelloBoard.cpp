#include "OthelloBoard.h"
#include "OthelloMove.h"
using namespace std;
const int BOARD_INIT_VAR1 = 3;
const int BOARD_INIT_VAR2 = 4;

// Default constructor initializes the board to its starting "new game" state
OthelloBoard::OthelloBoard() {
   //initialize the whole board to 0
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mBoard[i][j] = 0;
      }//close inner for loop
   }//close outer for loop
   //set the 4 middle pieces to their appropriate values
   mBoard[BOARD_INIT_VAR1][BOARD_INIT_VAR1] = -1;
   mBoard[BOARD_INIT_VAR1][BOARD_INIT_VAR2] =  1;
   mBoard[BOARD_INIT_VAR2][BOARD_INIT_VAR1] =  1;
   mBoard[BOARD_INIT_VAR2][BOARD_INIT_VAR2] = -1;
   //Initialize the Value, PassCount and NextPlayer of the board
   mValue = 0, mPassCount = 0;
   mNextPlayer = WHITE;
}//close OthelloBoard()


/* 
Fills in a vector with all possible moves on the current board state for
the current player. The moves should be ordered based first on row, then on
column. Example ordering: (0, 5) (0, 7) (1, 0) (2, 0) (2, 2) (7, 7)
If no moves are possible, then a single OthelloMove representing a Pass is
put in the vector.
Any code that calls ApplyMove is responsible for first checking that the
requested move is among the possible moves reported by this function.

Precondition: the vector is empty.
Postcondition: the vector contains all valid moves for the current player.
*/
void OthelloBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   //Local Variables:
   //keeps track of the current player
   char currentPlayer = (mNextPlayer == WHITE ? BLACK : WHITE);
   //these four variables are to determine whether the move is valid or if the 
   //user must pass
   bool  validMove = false, mustPass = true;
   //used to keep track of the row and column of the direction of the move
   int rowVar = 0, colVar = 0; 
   //Look through all 8 directions on every spot on the board to see if you
   //can caputure your opponent's pieces.
   for (char i = 0; i < BOARD_SIZE; i++) {
      for (char j = 0; j < BOARD_SIZE; j++) {
         for (char k = -1; k <= 1; k++) {
            for (char l = -1; l <= 1; l++) {
               rowVar = 0, colVar = 0;
               validMove = false;
               //Move one space in the designated direction (i + k), (j + l).
               //Make sure that the space is InBounds, is not empty, and is 
               //not your current location because you do not need to check 
               //this direction for opponent pieces. Also, make sure that the
               //original location was empty, otherwise this would not be a 
               //valid move.
               if (InBounds((i + k), (j + l)) && (!(k == 0 && l == 0)) 
                && (mBoard[(i + k)][(j + l)] != 0) && mBoard[i][j] == 0) {
                  //If the space is the enemy, then you set the rowVar and 
                  //colVar equal to i + k and j + l to keep track of where 
                  //you are on the gameboard. 
                  if (mBoard[(i + k)][(j + l)] == mNextPlayer) {
                     rowVar = i + k;
                     colVar = j + l;

                     //while you are InBounds of the board, the current spot 
                     //is an enemy piece, and you originally detected an enemy 
                     //piece, you go one more space in the same direction.  
                     //Repeat until the gameBoard location is no longer the 
                     //enemy. 
                     while(InBounds(rowVar, colVar) && mBoard[rowVar][colVar] 
                      == mNextPlayer) {
                        rowVar += k;
                        colVar += l;
                     }//close while loop

                     //If the current location is inbounds and is your own 
                     // piece, set the validMove variable to true and the 
                     //mustPass variable to false and then exit the inner loop.
                     if (InBounds(rowVar, colVar) && mBoard[rowVar][colVar] 
                      == currentPlayer) {	
                        validMove = true;
                        mustPass = false;
                        break;
                     }//end if
                  }//end if
               }//end if
            }//close innermost for loop
            //if it was a valid move, then push it onto the back of the list
            if (validMove) {
               OthelloMove *possibleMove = (OthelloMove *) CreateMove();
               *possibleMove = OthelloMove(i, j);
               list->push_back(possibleMove);
               break;
            }//end if
         }//close second innermost for loop
      }//close third innermost for loop
   }//close outer for loop
   //if the mustPass variable is still true, then the user must pass. We push 
   //the pass move into the back of the list.
   if (mustPass) {
      OthelloMove *passMove = (OthelloMove *) CreateMove();
      *passMove = OthelloMove();
      list->push_back(passMove);
   }//end if statement
}//close GetPossibleMoves(...) 


/* 
Applies a valid move to the board, updating the board state accordingly.
You may assume that this move is valid, and is consistent with the list
of possible moves returned by GetAllMoves. Make sure you account for 
changes to the current player, pass count, and board value.
*/
void OthelloBoard::ApplyMove(GameMove *move) {
   //Local Variables:
   OthelloMove *m = (OthelloMove *) move;
   //keeps track of the current player
   char currentPlayer = (mNextPlayer == WHITE ? BLACK : WHITE);
   //used to keep track of whether the move is valid or not
   bool validMove = false;
   //used to keep track of the row and column of the direction of the move
   int rowVar = 0, colVar = 0;
   //keeps track of the number of pieces that were switched per flipset
   char switchedPieces = 0;
   //Look through all 8 directions to see if you can caputure your 
   //opponents pieces.
   for (char i = -1; i <= 1; i++) {
      //If the move was a pass, then we do not need to execute any of the
      //following logic. Exit the loop immediately!
      if (m->IsPass())
         break;
      for (char j = -1; j <= 1; j++) {
         switchedPieces = 0;
         //Move one space in the designated direction (row + i), (col + j).
         //Make sure that the space is InBounds, is not empty, and is not
         //your current location because you do not need to check this
         //direction for opponent pieces being that it will always be you.
         if (InBounds((m->mRow + i), (m->mCol + j)) && (!(i == 0 && 
          j == 0)) && (mBoard[(m->mRow + i)][(m->mCol + j)] != 0)) {
            //If the space is the enemy, then you set the rowVar and colVar
            //equal to row + i and col + j to keep track of where you are
            //on the gameboard.
            if (mBoard[(m->mRow + i)][(m->mCol + j)] == mNextPlayer) {
               rowVar = m->mRow + i;
               colVar = m->mCol + j;
            }//end if

            //while you are InBounds of the board and the current spot is an
            //enemy piece, you go one more space in the same direction. Repeat
            //until the gameBoard location is no longer the enemy.
            while(InBounds(rowVar, colVar) && mBoard[rowVar][colVar] == 
             mNextPlayer) {
               rowVar += i;
               colVar += j;
            }//close while loop

            //If your current location is your own piece, then you go back in
            //the opposite direction and set the enemy's pieces to your own.
            //You also update the total value of the board, increment the 
            //switched pieces, set the validMove variable to true, and
            //add the flipset to the move's vector of flipsets.
            if (InBounds(rowVar, colVar) && mBoard[rowVar][colVar] == 
             currentPlayer) {
               while (mBoard[rowVar -= i][colVar -= j] == mNextPlayer) {	
                  mValue -= mNextPlayer;
                  mBoard[rowVar][colVar] = currentPlayer;
                  switchedPieces+= 1;
                  mValue += currentPlayer;
               }//close while loop
               
               validMove = true;
               m->AddFlipSet(OthelloMove::FlipSet(switchedPieces, i, j));
            }//end if
         }//end if
      }//close inner for loop
   }//close outer for loop

   //if it was a valid move, then we push the move onto the back of the 
   //mHistory vector
   if (validMove)
      mHistory.push_back(m);
   //if the move is a pass, we add a flipset corresponding to a pass move
   if (m->IsPass()) {		
      m->AddFlipSet(OthelloMove::FlipSet(0, 0, 0));
      mHistory.push_back(m);
   }//end if

   //If it was a valid move, then change the board location (board[row][col]) 
   //to your own piece, otherwise, keep the board location at 0, indicating  
   //an invalid move.
   mBoard[m->mRow][m->mCol] = (validMove ? currentPlayer : 0);
   //update the value of the board accordingly
   mValue += (validMove ? currentPlayer : 0);
   //Increment the pass count if the move was a pass or set it to 0 otherwise
   mPassCount = (m->IsPass() ? mPassCount + 1 : 0);
   //change the value of mNextPlayer accordingly
   mNextPlayer = (mNextPlayer == WHITE ? BLACK : WHITE);
}//close ApplyMove(...)


/*
Undoes the last move applied to the board, restoring it to the state it was
in prior to the most recent move (including whose turn it is, what the 
board value is, and what the pass count is).
*/
void OthelloBoard::UndoLastMove() {
   //set the currentPlayer variable with the appropriate value
   char currentPlayer = (mNextPlayer == WHITE ? BLACK : WHITE);
   //set the deleteMove variable to the most recent move
   OthelloMove *deleteMove = (OthelloMove *) mHistory.back();
   //initialize the rowVar and colVar variables
   int rowVar = 0, colVar = 0;
   //only delete moves that are not passes
   if (!deleteMove->IsPass()) {
      //change the piece back to unoccupied
      mBoard[deleteMove->mRow][deleteMove->mCol] = 0;
      //decrement the board value according to the player
      mValue -= mNextPlayer;

      //while there are flipsets in the move's flipset vector, iterate 
      //through them and change the pieces back to their original values
      for (vector<OthelloMove::FlipSet>::iterator itr = deleteMove->
       mFlips.begin(); itr != deleteMove->mFlips.end(); itr++) {
         //set the rowVar and colVar variables to their appropriate values
         rowVar = itr->rowDelta + deleteMove->mRow;
         colVar = itr->colDelta + deleteMove->mCol;

         //while there are still pieces that were switched, go one more 
         //space in that direction and flip the pieces back to their 
         //original values and update the board value at the same time
         for (itr->switched; itr->switched != 0; itr->switched--) {				
            mValue -= mNextPlayer;
            mBoard[rowVar][colVar] = currentPlayer;
            mValue += currentPlayer;
            rowVar += itr->rowDelta;
            colVar += itr->colDelta;
         }//close inner for loop	
      }//end for loop
   }//end if

   //delete the move after you are done undoing it and pop it from the back
   //of the mHistory vector
   delete deleteMove;
   mHistory.pop_back();
   //set mNextPlayer to the appropriate value and update mPassCount accordingly
   mNextPlayer = (mNextPlayer == WHITE ? BLACK : WHITE);
   mPassCount = (GetMoveCount() > 0 ? (deleteMove->IsPass() ? 1: 0) : 0);
}//close UndoLastMove()


std::string OthelloBoard::GetPlayerString(char player) {
   return (player == 1 ? "Black" : "White");
}//close GetPlayerString(...)