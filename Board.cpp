/*
 * Board.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Josh
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Board.h"

using namespace std;

// Default constructor
// Initializes the board to default for Othello
Board::Board()
: number_of_1_pieces_(0)
, number_of_2_pieces_(0)
, number_of_1_passes_(0)
, number_of_2_passes_(0)
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      board_[i][j] = '.';
    }
  }
  board_[3][3] = 'W';
  board_[4][4] = 'W';
  board_[3][4] = 'B';
  board_[4][3] = 'B';
}

// Default destructor
Board::~Board()
{
}

// Returns what piece is in the spot passed
// row is the row
// column is the column
char Board::At(int row, int col)
{
  return(board_[row][col]);
}

// Prints the board and the pieces on it
void Board::PrintBoard() const
{
  cout << "  1  2  3  4  5  6  7  8" << endl;
  cout << "  ----------------------";

  for (int bRow = 0; bRow < ROWS; bRow++)
  {
    cout << "\n" << bRow+1 << "|";
    for (int bCol = 0; bCol < COLUMNS; bCol++)
    {
        cout << board_[bRow][bCol];
      cout << "  ";
    }
  }
  cout << endl;
}

// Function to return if the game is over or not
bool Board::EndGame()
{
  // Check to see if both players have passed their turn twice
  if ((number_of_1_passes_ >= 2) && (number_of_2_passes_ >= 2))
  {
    // If so count of the number of pieces for the player's on the board
    cout << "Too many passes" << endl;
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLUMNS; j++)
      {
        if (board_[i][j] == 'W')
        {
          number_of_2_pieces_++;
        }
        else if (board_[i][j] == 'B')
        {
          number_of_1_pieces_++;
        }
      }
    }
    return true;
  }
  // Count the number of pieces on the board
  number_of_2_pieces_ = 0;
  number_of_1_pieces_ = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (board_[i][j] == 'B')
      {
        number_of_1_pieces_++;
      }
      else if (board_[i][j] == 'W')
      {
        number_of_2_pieces_++;
      }
    }
  }
  // If the number of pieces on the board is equal to 64 then the board is full and the game is over
  if ((number_of_1_pieces_ + number_of_2_pieces_) >= 64)
  {
    return true;
  }
  // If not reset the number of pieces back to 0
  else
  {
    number_of_1_pieces_ = 0;
    number_of_2_pieces_ = 0;
  }
  // We are not at the end of the game yet
  return false;
}

unsigned int Board::GetTotalNumberOnePieces()
{
  unsigned int num_pieces = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (board_[i][j] == 'B')
      {
        num_pieces++;
      }
    }
  }
  return num_pieces;
}

unsigned int Board::GetTotalNumberTwoPieces()
{
  unsigned int num_pieces = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (board_[i][j] == 'W')
      {
        num_pieces++;
      }
    }
  }
  return num_pieces;
}

// Function to try and set a piece in the passed location for the passed player.
// Returns true if the move was good else returns false
bool Board::SetPiece(int row, int column, char color)
{
  bool found_valid_move = false;
  bool final_valid = false;
  // Check to see if the Row is valid
  if (row < 0 || row >> 7)
  {
    cout << "Row choice was out of bounds: " << row << endl;
    return false;
  }
  // Check to see if the column is valid
  if (column < 0 || column > 7)
  {
    cout << "Column choice was out of bounds: " << column << endl;
    return false;
  }
  // Check to make sure there isn't a piece already in the spot.
  if (board_[row][column] == 'B' || board_[row][column] == 'W')
  {
    cout << "Board spot already has a piece on it." << endl;
    return false;
  }
  // Check to the left to see if that direction makes for a good move
  found_valid_move = CheckLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the right to see if that direction makes for a good move
  found_valid_move = CheckRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up to see if that direction makes for a good move
  found_valid_move = CheckUp(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down to see if that direction makes for a good move
  found_valid_move = CheckDown(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up and left to see if that direction makes for a good move
  found_valid_move = CheckUpLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up and right to see if that direction makes for a good move
  found_valid_move = CheckUpRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down and left to see if that direction makes for a good move
  found_valid_move = CheckDownLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down and right to see if that direction makes for a good move
  found_valid_move = CheckDownRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  //  Check to see if there was indeed one good move
  if (final_valid)
  {
    // If so reset the number of passes back to 0
    PlayerOneReset();
  }
  // Returns whether the move was good or not
  return final_valid;
}

// Function that attempts to set a piece for the computer
bool Board::SetPieceForPlayer2(int row, int column, char color)
{
  bool found_valid_move = false;
  bool final_valid = false;
  // Check to see if the Row is valid
  if (row < 0 || row >> 7)
  {
    return false;
  }
  // Check to see if the column is valid
  if (column < 0 || column > 7)
  {
    return false;
  }
  // Check to make sure there isn't a piece already in the spot.
  if (board_[row][column] == 'B' || board_[row][column] == 'W')
  {
    return false;
  }
  // Check to the left to see if that direction makes for a good move
  found_valid_move = CheckLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the right to see if that direction makes for a good move
  found_valid_move = CheckRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up to see if that direction makes for a good move
  found_valid_move = CheckUp(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down to see if that direction makes for a good move
  found_valid_move = CheckDown(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up and left to see if that direction makes for a good move
  found_valid_move = CheckUpLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the up and right to see if that direction makes for a good move
  found_valid_move = CheckUpRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down and left to see if that direction makes for a good move
  found_valid_move = CheckDownLeft(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  // Check to the down and right to see if that direction makes for a good move
  found_valid_move = CheckDownRight(row, column, color);
  if (found_valid_move) {final_valid = found_valid_move;}
  //  Check to see if there was indeed one good move
  if (final_valid)
  {
    // If so reset the number of passes back to 0
    PlayerTwoReset();
  }
  // Returns whether the move was good or not
  return final_valid;
}

// Function that check to see if there is a valid move from below
bool Board::CheckDown(int row, int column, char color)
{
  // Vector used to keep track of all the spots that need to be flipped
  std::vector<int> row_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (row+1 > 7)
    {
      return false;
    }
    if (board_[row+1][column] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      // Start the search at column + 2 because we already know column + 1 is a valid piece
      row = row + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (row <= 7)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column] = 'W';
          }
          board_[original_row][column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
      }
    }
  }
  else if (color == 'B')
  {
    if (row+1 > 7)
    {
      return false;
    }
    if (board_[row+1][column] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      // Start the search at column + 2 because we already know column + 1 is a valid piece
      row = row + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (row <= 7)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column] = 'B';
          }
          board_[original_row][column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from below and left
bool Board::CheckDownLeft(int row, int column, char color)
{
  // Vectors to keep track of the spots to flip
  std::vector<int> row_slots;
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (row+1 > 7 || column-1 < 0)
    {
      return false;
    }
    if (board_[row+1][column-1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row + 2;
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0 && row <= 7)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'W';
          }
          board_[original_row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
        column--;
      }
    }
  }
  else if (color == 'B')
  {
    if (row+1 > 7 || column-1 < 0)
    {
      return false;
    }
    if (board_[row+1][column-1] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row + 2;
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0 && row <= 7)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'B';
          }
          board_[original_row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
        column--;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from below and right
bool Board::CheckDownRight(int row, int column, char color)
{
  // Vectors to keep track of the spots to flip
  std::vector<int> row_slots;
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (row+1 > 7 || column+1 > 7)
    {
      return false;
    }
    if (board_[row+1][column+1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row + 2;
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7 && row <= 7)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'W';
          }
          board_[original_row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
        column++;
      }
    }
  }
  else if (color == 'B')
  {
    if (row+1 > 7 || column+1 > 7)
    {
      return false;
    }
    if (board_[row+1][column+1] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row+1);
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row + 2;
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7 && row <= 7)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'B';
          }
          board_[original_row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row++;
        column++;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from left
bool Board::CheckLeft(int row, int column, char color)
{
  // Vector to keep track of spots to flip
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (column-1 < 0)
    {
      return false;
    }
    if (board_[row][column-1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0)
      {
        if (board_[row][column] == 'B')
        {
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < column_slots.size(); i++)
          {
            board_[row][column_slots.at(i)] = 'W';
          }
          board_[row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        column--;
      }
    }
  }
  else if (color == 'B')
  {
    if (column-1 < 0)
    {
      return false;
    }
    if (board_[row][column-1] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_column = column;
      // Check to see if there is a B piece to the left. If so we can flip the W pieces
      // Add the first column location we are to flip to the left of our new piece
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0)
      {
        if (board_[row][column] == 'W')
        {
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < column_slots.size(); i++)
          {
            board_[row][column_slots.at(i)] = 'B';
          }
          board_[row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        column--;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from the right
bool Board::CheckRight(int row, int column, char color)
{
  // Vector to keep track of the pots to flip
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (column+1 > 7)
    {
      return false;
    }
    if (board_[row][column+1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7)
      {
        if (board_[row][column] == 'B')
        {
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < column_slots.size(); i++)
          {
            board_[row][column_slots.at(i)] = 'W';
          }
          board_[row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        column++;
      }
    }
  }
  else if (color == 'B')
  {
    if (column+1 > 7)
    {
      return false;
    }
    if (board_[row][column+1] != 'W')
    {
      //      cout << "Adjacent space to the right is not a valid piece." << endl;
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_column = column;
      // Check to see if there is a B piece to the left. If so we can flip the W pieces
      // Add the first column location we are to flip to the left of our new piece
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7)
      {
        if (board_[row][column] == 'W')
        {
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < column_slots.size(); i++)
          {
            board_[row][column_slots.at(i)] = 'B';
          }
          board_[row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        column++;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from up
bool Board::CheckUp(int row, int column, char color)
{
  // Vector to keep track of the spots to flip
  std::vector<int> row_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    // Check to make sore the row is not off the board
    if (row-1 < 0)
    {
      return false;
    }
    // Check to make sure there is a black piece above us
    if (board_[row-1][column] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (row >= 0)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column] = 'W';
          }
          board_[original_row][column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
      }
    }
  }
  else if (color == 'B')
  {
    if (row-1 < 0)
    {
      return false;
    }

    if (board_[row-1][column] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (row >= 0)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column] = 'B';
          }
          board_[original_row][column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from up and left
bool Board::CheckUpLeft(int row, int column, char color)
{
  // Vectors to keep track the spots to flip
  std::vector<int> row_slots;
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    // Check to make sure the row and column are on the board
    if (row-1 < 0 || column-1 < 0)
    {
      return false;
    }
    // Check to make sure there is a black piece next to us
    if (board_[row-1][column-1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0 && row >= 0)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'W';
          }
          board_[original_row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
        column--;
      }
    }
  }
  else if (color == 'B')
  {
    if (row-1 < 0 || column-1 < 0)
    {
      return false;
    }
    if (board_[row-1][column-1] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      column_slots.push_back(column-1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      column = column - 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column >= 0 && row >= 0)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'B';
          }
          board_[original_row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
        column--;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that check to see if there is a valid move from up and right
bool Board::CheckUpRight(int row, int column, char color)
{
  // Vectors to keep track of the pots to flip
  std::vector<int> row_slots;
  std::vector<int> column_slots;
  // Find out what color piece we played
  if (color == 'W')
  {
    if (row-1 < 0 || column+1 > 7)
    {
      return false;
    }
    if (board_[row-1][column+1] != 'B')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7 && row >= 0)
      {
        if (board_[row][column] == 'B')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'W')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'W';
          }
          board_[original_row][original_column] = 'W';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
        column++;
      }
    }
  }
  else if (color == 'B')
  {
    if (row-1 < 0 || column+1 > 7)
    {
      return false;
    }
    if (board_[row-1][column+1] != 'W')
    {
      return false;
    }
    else
    {
      // Extra integer to keep track of where to place the piece if it's a valid move
      int original_row = row;
      int original_column = column;
      // Add the first column location we are to flip to the left of our new piece
      row_slots.push_back(row-1);
      column_slots.push_back(column+1);
      // Start the search at column - 2 because we already know column - 1 is a valid piece
      row = row - 2;
      column = column + 2;
      // Check to see if there is a W piece to the left. If so we can flip the B pieces
      while (column <= 7 && row >= 0)
      {
        if (board_[row][column] == 'W')
        {
          row_slots.push_back(row);
          column_slots.push_back(column);
        }
        else if (board_[row][column] == 'B')
        {
          // Loop over the vector of column spots to flip to W and flip those spots
          for (unsigned int i = 0; i < row_slots.size(); i++)
          {
            board_[row_slots.at(i)][column_slots.at(i)] = 'B';
          }
          board_[original_row][original_column] = 'B';
          // Return true
          return true;
        }
        // Check to see if we find an empty spot, If so that means there is no valid move from the left
        else if (board_[row][column] == '.')
        {
          return false;
        }
        row--;
        column++;
      }
    }
  }
  else
  {
    // Color was passed in wrong somehow
    return false;
  }
  return false;
}

// Function that prints out the winner
void Board::PrintWinner()
{
  cout << "Player 1 has " << number_of_1_pieces_ << " pieces and player 2 has " << number_of_2_pieces_ << " pieces." << endl;
  if (number_of_1_pieces_ > number_of_2_pieces_)
  {
      cout << "Player 1 has won the game." << endl;
  }
  else if (number_of_1_pieces_ < number_of_2_pieces_)
  {
    cout << "Player 2 has won the game." << endl;
  }
  else
  {
    cout << "The game is a draw so no one won." << endl;
  }
}

// Function to reset the number of passes the player has made
void Board::PlayerOneReset()
{
  number_of_1_passes_ = 0;
}

// Function to reset the number of passes the computer has made
void Board::PlayerTwoReset()
{
  number_of_2_passes_ = 0;
}

// Function the increment the number of passes the player has made
void Board::PlayerOneSkip()
{
  number_of_1_passes_++;
}

// Function the increment the number of passes the computer has made
void Board::PlayerTwoSkip()
{
  number_of_2_passes_++;
}

// Function that returns the number of black pieces on the board
int Board::GetNumberBlack() const
{
  int count = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (board_[i][j] == 'B')
      {
        count++;
      }
    }
  }
  return count;
}

// Function that returns the number of white pieces on the board
int Board::GetNumberWhite() const
{
  int count = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (board_[i][j] == 'W')
      {
        count++;
      }
    }
  }
  return count;
}

// Function used to find out if a move results in someone winning
int Board::PlayerWin()
{
  int score = 0;
  if (EndGame())
  {
    if (number_of_1_pieces_ > number_of_2_pieces_)
    {
      // Return that player 1 won
      score = -1;
    }
    else if (number_of_1_pieces_ < number_of_2_pieces_)
    {
      // Return that player 2 won
      score = 1;
    }
  }
  else
  {
    // Returns that no one has won
    score = 2;
  }
  return score;
}
