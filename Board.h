/*
 * Board.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Joshua Boone
 */

#ifndef BOARD_H_
#define BOARD_H_

// The size of the 2D array used for the board
const int ROWS = 8;
const int COLUMNS = 8;

// Class to represent the game board
class Board
{
public:
  // Default constructor
  Board();
  // Default destructor
  ~Board();
  // Overloaded assignment operator
  Board& operator=(const Board& copy)
  {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
          board_[i][j] = copy.board_[i][j];
        }
    }
    number_of_1_pieces_ = copy.GetNumberBlack();
    number_of_2_pieces_ = copy.GetNumberWhite();
    return *this;
  }
  // Overloaded equality operator
  bool operator==(const Board& copy)
  {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
          if (board_[i][j] != copy.board_[i][j])
          {
            return false;
          }
        }
    }
    return true;
  }
  // Function the return the piece at the passed location
  char At(int row, int col);
  // Function to print the board
  void PrintBoard() const;
  // Function the check if the game is over
  bool EndGame();
  // Returns the number of player 1 pieces on the board
  unsigned int GetTotalNumberOnePieces();
  // Returns the number of player 2 pieces on the board
  unsigned int GetTotalNumberTwoPieces();
  // Function to set the piece for the player
  bool SetPiece(int row, int column, char color);
  // Function to set the piece for the computer
  bool SetPieceForPlayer2(int row, int column, char color);
  // Function that check to see if there is a valid move from below
  bool CheckDown(int row, int column, char color);
  // Function that check to see if there is a valid move from below and left
  bool CheckDownLeft(int row, int column, char color);
  // Function that check to see if there is a valid move from below and right
  bool CheckDownRight(int row, int column, char color);
  // Function that check to see if there is a valid move from left
  bool CheckLeft(int row, int column, char color);
  // Function that check to see if there is a valid move from the right
  bool CheckRight(int row, int column, char color);
  // Function that check to see if there is a valid move from up
  bool CheckUp(int row, int column, char color);
  // Function that check to see if there is a valid move from up and left
  bool CheckUpLeft(int row, int column, char color);
  // Function that check to see if there is a valid move from up and right
  bool CheckUpRight(int row, int column, char color);
  // Function to print the winner
  void PrintWinner();
  // Function to reset the number of passes the player has made
  void PlayerOneReset();
  // Function to reset the number of passes the computer has made
  void PlayerTwoReset();
  // Function the increment the number of passes the player has made
  void PlayerOneSkip();
  // Function the increment the number of passes the computer has made
  void PlayerTwoSkip();
  // Function that returns the number of black pieces on the board
  int GetNumberBlack() const;
  // Function that returns the number of white pieces on the board
  int GetNumberWhite() const;
  // Function used to find out if a move results in someone winning
  int PlayerWin();

  // 2D array used to represent an Othello board
  char board_[ROWS][COLUMNS];
  // Number of player 1's pieces on the board
  int number_of_1_pieces_;
  // Number of player 2's pieces on the board
  int number_of_2_pieces_;
  // Number of times player 1 has passed in a row
  int number_of_1_passes_;
  // Number of times player 2 has passed in a row
  int number_of_2_passes_;
};

#endif /* BOARD_H_ */
