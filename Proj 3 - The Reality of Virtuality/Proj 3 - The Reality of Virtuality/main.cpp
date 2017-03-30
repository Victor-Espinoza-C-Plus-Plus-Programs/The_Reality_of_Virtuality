/* Victor Espinoza
* CECS 282, Section 1
* Spring 2014
* Due Date: 5/15/14
* Project #3 - The Reality of Virtuality
*/

#include "GameBoard.h"
#include "GameExceptions.h"
#include "GameMove.h"
#include "GameView.h"

#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "OthelloView.h"


#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "TicTacToeView.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <regex>

const int MAX_MOVES_PER_LINE = 13;
const int MOVE_START_INDEX = 5;


using namespace std;


int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board; // the state of the game board
   GameView *v; // a View for outputting the board via operator<<
   int gameChoice=0; // a string to hold the user's game choice
   int pos=0; //used to store the starting position of undo number
   bool validGameChoice = false;
   string userInput; // a string to hold the user's command choice
   string moveUndoStr; // a string to hold the # of moves to undo
   GameMove *playerMove; //creates and holds the user's desired move
   vector<GameMove *> possMoves; // a holder for possible moves

   //find out what game the user wants to play
   do {
      //prompt user to enter what game they want to play
      cout << "What Game do you want to play? \n1) Othello \n2) Tic Tac Toe" 
       << endl;//prompt user to enter what game they want to play
      //input whole line
      getline(cin, userInput);

      //make sure user input was a digit
      if(!regex_match(userInput, regex("(\\+|-)?[[:digit:]]+")))
         cout << "You must enter a valid INTEGER NUMBER (1-2)!\n" << endl;
      else	{
         gameChoice = stoi(userInput);
         if(gameChoice < 1 || gameChoice > 2)
            cout << "You must enter a number between 1-2!\n" << endl;
      }//end else

      //end while
   } while(gameChoice < 1 || gameChoice > 2);

   //initialize the appropriate board game
   if (gameChoice == 1) {
      //User indicated that they want to play othello
      cout << "Initializing Othello Game ..." << endl;
      //Set board and view to appropriate Othello types
      board = new OthelloBoard();
      v = new OthelloView(board);
   }//end if
   else {
      //User indicated that they want to play Tic Tac Toe
      cout << "Initializing Tic Tac Toe Game ..." << endl;
      //Set board and view to appropriate TicTacToe types
      board = new TicTacToeBoard();
      v = new TicTacToeView(board);
   }//end else

   //itrIndex is for wrap around for possible moves, and userUndos and 
   //undoLimit are for the undo command
   int itrIndex, userUndos, undoLimit; 
   bool moveIsValid; //used to determine validity of move for move command

   string player; //used for showHistory
   // Main loop
   do {

      // Print the game board using the GameView object and all of the 
      //  possible moves. Max number of possible moves per line 13.	
      cout << *v << (board->GetNextPlayer() == -1 ? ((gameChoice == 1) ? 
       "\nBlack's"	: "\nX's") : ((gameChoice == 1) ? "\nWhite's" : 
       "\nO's")) << " move... " << "\n\nPossible Moves:" << endl;

      itrIndex = 1;
      board->GetPossibleMoves(&possMoves);
      for (vector<GameMove *>::iterator itr = possMoves.begin(); 
         itr != possMoves.end(); itr++, itrIndex++) {			 
            cout << "move "<< (string)(**itr) << "; ";
            if (itrIndex != 0 && itrIndex % MAX_MOVES_PER_LINE == 0)
               cout << endl;
            delete *itr;
      }//end for loop
      possMoves.clear();

      // Ask to input a command
      cout << "\nPossible commands: move (r,c) \n\t\t   undo #moves" <<
       "\n\t\t   showValue\n\t\t   showHistory\n\t\t   quit" << endl;
      cout << "\nPlease enter a command:" << endl;
      getline(cin, userInput);
      cout << endl;

      // use this inner loop so we do not have to display the  gameboard
      // and possible moves again after the user has selected the 
      // showValue and showHistory commands because it would be 
      //redundant to display the info again since it is still their turn
      while (!(userInput == "quit" || board->IsFinished())) {
         // Command loop:
         // move (r,c)	command
         if (userInput.find("move") != std::string::npos) {
            //Create a game move
            playerMove = board->CreateMove();
            try {
               //Check to see if the move is valid
               *playerMove = (string)(userInput.substr(MOVE_START_INDEX));
               board->GetPossibleMoves(&possMoves);
               moveIsValid = false;
               for (vector<GameMove *>::iterator itr = possMoves.begin(); 
                itr != possMoves.end(); itr++) {	
                  moveIsValid = ((**itr == *playerMove) ? true : moveIsValid);
                  delete *itr;
               }//end for 
               //clear possMoves since it is no longer needed
               possMoves.clear(); 

               //if move is valid, apply the move to the board
               if (moveIsValid) {
                  board->ApplyMove(playerMove);
                  break;
               }//end if
               //if not, then let the user know that the move is invalid.
               cout << "Invalid Move!" << endl;
               delete playerMove;
            }//end try
            catch(OthelloException& e) {
               //If there was an exception, display the message and 
               //delete the move.
               cout << e.GetMessage() << endl;
               delete playerMove;
            }//end catch

         }//end if (move (r,c) command) 

         // undo #moves command
         else if (userInput.find("undo") != std::string::npos) {

            //split the input to a string containing the number 
            //portion of the undo command
            pos = userInput.find_first_of(' ');
            moveUndoStr = (pos > -1) ? userInput.substr(pos+1) : 
             userInput.substr(userInput.size());

            //make sure that the movesStr is an integer
            if(!regex_match(moveUndoStr, regex("(\\+)?[[:digit:]]+")))	
               cout << "Invalid command! You must enter the command "
                << "undo followed by a positive number... (Ex: undo 1)" << endl;
            else if (board->GetMoveCount() > 0) {
               //assign user input to the userUndos variable
               userUndos = stoi(moveUndoStr);		
               undoLimit = board->GetMoveCount();

               for (int i = 0; i < userUndos; i++) {
                  // If the user enters a number that is greater than the 
                  // size of the vector, then we exit the loop right after  
                  // we reach the end of the vector.
                  if (i == undoLimit)
                     break;
                  board->UndoLastMove();
               }//end for loop
               if (userUndos > undoLimit) {
                  //Let the user know that they entered a number bigger than
                  //the size of the vector.
                  cout << "I have stopped undoing moves because we have " <<
                   "reached the beginning of the game!" << endl;
               }//end if
               break;
            }//end else if
            else
               //else, we let the user know that there are no moves to undo.
               cout << "There are no moves to undo. " << endl;		

         }// end if	(undo #moves command)

         // showValue  command
         else if (userInput == "showValue")
            //display the board value.
            cout << "Board Value: " << board->GetValue() << endl;

         // showHistory	command
         else if (userInput == "showHistory") {
            //set the player variable to the appropriate value
            player = board->GetPlayerString(board->GetNextPlayer());
            typedef vector<GameMove *>::const_reverse_iterator constItr;
            //iterate through the history vector and display the moves
            //according to the order in which they were applied
            for (constItr itr = board->GetMoveHistory()->rbegin(); 
               itr != board->GetMoveHistory()->rend(); itr++) {
                  cout << player << ": " << (string)(**itr) << endl;
                  //alternate the player
                  player = (gameChoice == 1 ? (player == "Black" ? "White" :
                   "Black") : player == "X" ? "O" : "X");
            }//close for loop
            if (board->GetMoveCount() == 0)
               //if the vector is empty, then display the appropriate message
               cout << "There are no moves to display." << endl;
         }//end if (showHistory command)

         // show which player's turn it is
         cout << (board->GetNextPlayer() == -1 ? ((gameChoice == 1) ? 
          "\nBlack's"	: "\nX's") : ((gameChoice == 1) ? 
          "\nWhite's" : "\nO's")) << " move... " << endl;

         // prompt the user to input a command
         cout << "\nPossible commands: move (r,c) \n\t\t   undo #moves" <<
          "\n\t\t   showValue\n\t\t   showHistory\n\t\t   quit" << endl;
         cout << "\nPlease enter a command:" << endl;
         getline(cin, userInput);
         cout << endl;
      }//end command loop
   } while (!(userInput == "quit" || board->IsFinished()));  

   //the game is over. Display the appropriate message / winner
   if (gameChoice == 1) {
      cout << *v << "\nGame Over. " << (board->GetValue() == 0 ? "We have a "
       "tie!" : board->GetValue() > 0 ? "Black wins!" : "White wins!") << endl;
   }//end if
   else {
      cout << *v << "\nGame Over. " << (board->GetValue() == 0 ? "We have a" 
       " tie!" : board->GetValue() > 0 ? "X wins!" : "O wins!") << endl;
   }//end else

   //now that we are done, we must delete all of the moves that are still
   //applied on the board
   undoLimit = board->GetMoveCount();
   for (int i = 0; i < undoLimit; i++) {
      board->UndoLastMove();
   }//end for loop
   //We must also delete the board and the view pointers that we put 
   //on the heap.
   delete board;
   delete v;
}//close main