#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int TTT_BOARD_SIZE = 3;

/*
A TicTacToeBoard encapsulates data needed to represent a single game of Tic 
Tac Toe. This includes the state of the board, tracking the current player, 
and keeping a history of moves on the board.
*/
class TicTacToeBoard : public GameBoard {

public:
   enum Player {EMPTY = 0, X = 1, O = -1};

   // Default constructor initializes the board to its starting "new game" 
   // state
   TicTacToeBoard();


   /* 
   Fills in a vector with all possible moves on the current board state for
   the current player. The moves should be ordered based first on row, then on
   column. Example ordering: (0, 1) (0, 2) (1, 0) (2, 0) (2, 2) .
   If no moves are possible, then a single TicTacToeMove representing a Pass 
   is put in the vector.
   Precondition: the vector is empty.
   Postcondition: the vector contains all valid moves for the current player.
   */
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;


   /*
   Applies a valid move to the board, updating the board state accordingly.
   You may assume that this move is valid, and is consistent with the list
   of possible moves returned by GetPossibleMoves.
   */
   virtual void ApplyMove(GameMove *move);


   // Undoes the last move applied to the board, restoring it to the state it 
   // was in prior to the most recent move.
   virtual void UndoLastMove();


   /*
   Creates a TicTacToeMove object on the heap. Whoever calls this method is
   responsible for managing the move's lifetime (or transferring that task to
   someone else.)
   */
   virtual GameMove *CreateMove() const {return new TicTacToeMove;}


   inline static bool InBounds(int row, int col) {
      return row >= 0 && row < TTT_BOARD_SIZE && col >= 0 && 
       col < TTT_BOARD_SIZE;
   }//close *CreateMove()


   // Represents the player as a string
   virtual std::string GetPlayerString(char player);


   // Returns true if the game is finished.
   virtual bool IsFinished() const {
      return mPassCount == 2 || mValue == 3 || mValue == -3;
   }//close IsFinished()


   int UpdateBoardValue();


private:
   friend class TicTacToeView;

   char mBoard[TTT_BOARD_SIZE][TTT_BOARD_SIZE];
   static char mWeights[TTT_BOARD_SIZE][TTT_BOARD_SIZE];
   int mPassCount;
};	//close class TicTacToeBoard
#endif