/*
 * Driver.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Joshua Boone
 */

#include "Driver.h"
#include <iostream>
#include <limits>
using namespace std;

// Default constructor
Driver::Driver()
: final_state_()
, exit_(false)
{
}

// Default destructor
Driver::~Driver()
{
}

// Function that gets the player's move
void Driver::GetPlayer1Move()
{
  // The row to place the piece
  int row = 0;
  // The column to place the piece
  int column = 0;
  // Bool used to get track if the player's move is valid or not
  bool valid_move = false;
  // Need to check to see if there is even a valid move for the player to take
  if (ValidMoveAvailable())
  {
    // Now we continue to get the player's move until they make a valid move
    while (!valid_move)
    {
      // Let the user know they can input their move
      cout << "Please enter the row and column you want, space between them please: ";
      // Get their move
      cin >> row >> column;
      // Check to see if they wanted to exit the program
      if (row == -1 || column == -1)
      {
        // If so set the exit variable and break out of the loop
        exit_ = true;
        break;
      }
      // This is used to handle invalid input from the user
      if (!cin)
      {
        cout << "Invalid input. Try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }
      // The -1 is used because the array indices start at 0. Attempt to make the move
      valid_move = MakeMove(row-1, column-1, 'B');

      // Check to see if the move was valid
      if (valid_move == false)
      {
        cout << "Move is invalid. Try again." << endl;
      }
    }
  }
  else
  {
    // If in here then there was no move for the player to take so their turn is skipped
    cout << "There is no valid move available. Skipping your turn." << endl;
    final_state_.PlayerOneSkip();
  }
  // Uncomment this and comment out the code above and the computer will play against itself
//  final_state_.GetPlayer1Move();
}

// Function that gets the move for player 2. In this case this is the computer's move
void Driver::GetPlayer2Move()
{
  final_state_.GetPlayer2Move();
}

// Function that attempts to make the move.
// row is the row to place the piece
// column is the column to place the piece
// color is used to represent which player is making the move. Obsolete now for the computer
// since it uses it's own move function but still required for player 1.
bool Driver::MakeMove(int row, int column, char color)
{
  return(final_state_.SetPiece(row, column, color));
}

// Function that is the main driver of the class. Gets the move from the player and the computer
void Driver::PlayGame()
{
  // Used to see whether the player wants to play a game or not
  char choice;
  // Ask the user if they want to play a game
  cout << "Would you like to play a round of Othello? Y/y for yes and anything else for no: ";
  // Get the user's choice
  cin >> choice;
  // While the player wants to play
  while (choice == 'Y' || choice == 'y')
  {
    // Create a new State
    State new_State;
    // Set the current State to the new state. This is done here in case the player plays more than 1
    // game in a row
    final_state_ = new_State;
    // Print the fresh board
    final_state_.PrintBoard();
    // While the game has not ended
    cout << "Play against NegaMax(N or n) or MiniMax(M or m): ";
    cin >> choice;
    while (choice != 'N' && choice != 'M' && choice != 'n' && choice != 'm')
    {
      cout << "Please pick NegaMax(N) or MiniMax(M): ";
      cin >> choice;
    }
    if (choice == 'N' || choice == 'n')
    {
      cout << "Going with NegaMax." << endl;
    }
    else
    {
      cout << "Going with MiniMax." << endl;
    }
    final_state_.SetAlgorithm(choice);
    while (!EndOfGame())
    {
      // Announce that it's the player's turn
      cout << "Player 1's turn." << endl;
      // Remind them on how to exit
      cout << "Remember enter \"-1 -1\" at any of your prompts to exit the game." << endl;
      // Get the player's move
      GetPlayer1Move();
      // Check to see if the player wanted to exit
      if (exit_ == true)
      {
        cout << "Exiting this game." << endl;
        break;
      }
      // Print the updated board
      final_state_.PrintBoard();
      // Check to see if that was the end of the game
      if (EndOfGame())
      {
        break;
      }
      // Announce that it's the computer's turn
      cout << "Computer's turn." << endl;
      // Get the computer's move
      GetPlayer2Move();
      // Print the updated board
      final_state_.PrintBoard();
    }
    // If the player didn't exit the game early
    if (!exit_)
    {
      // Print out the winner
      cout << "\nThe board is full so the game is over." << endl;
      final_state_.PrintWinner();
    }
    // Ask if they want to play another game
    cout << "Would you like to play another round of Othello? Y/y for yes and anything else for no: ";
    cin >> choice;
  }
}

// Function that returns if the game is over or not
bool Driver::EndOfGame()
{
  if(final_state_.EndGame())
  {
    return true;
  }
  return false;
}

// Function that returns whether there is a valid move to take or not for the player
bool Driver::ValidMoveAvailable()
{
  return(final_state_.ValidMoveAvailable());
}
