/*
 * State.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Joshua Boone
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include "State.h"

using namespace std;

// Default constructor
State::State()
: depth_(0)
, max_depth_(5)
, next_player_(1)
{
}

// Destructor
State::~State()
{
}

// Purpose: To set a State to the goal State
std::vector<Board> State::GenerateMoves(const Board& board, int color)
{
  // Board to set to the current board so we don't change the current board needlessly
  Board new_move;
  // Vector to hold generated moves
  vector<Board> moves;
  // Check to see whose turn it is
  if (color == -1)
  {
    // If black's turn
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLUMNS; j++)
      {
        // Set the local board to the game board and try to set a move
        new_move = board;
        if (new_move.SetPieceForPlayer2(i, j, 'B'))
        {
          // If good add it to the vector
          moves.push_back(new_move);
        }
      }
    }
  }
  else
  {
    // If white's turn
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLUMNS; j++)
      {
        // Set the local board to the game board and try to set a move
        new_move = board;
        if (new_move.SetPieceForPlayer2(i, j, 'W'))
        {
          // If good add it to the vector
          moves.push_back(new_move);
        }
      }
    }
  }
  // Return the vector
  return moves;
}

// Function to evaluate the board for the minimax algorithm
int State::EvaluationMini(Board& board, int color)
{
  // The score of the move
  int score = 0;
  // Find out if this move is a winning move and if so which color is it for
  score = board.PlayerWin();
  // -1 is player 1
  if (score == -1)
  {
    score = 9999999;
  }
  // 1 is player 2
  else if (score == 1)
  {
    score = -9999999;
  }
  // 2 means a even number of pieces on the board
  else if (score == 2)
  {
    // Check to see if any of the corners were taken. If so find out by who and set the score
//    if ((board_.At(0,0) == '.' && board.At(0,0) == 'B') ||
//        (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'B') ||
//        (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'B')||
//        (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'B'))
//    {
//      // Black took a corner
//      score = score + 15;
//    }
    score = BlackTookCornerScore(board);
    if ((board_.At(1,1) == '.' && board.At(1,1) == 'B') ||
        (board_.At(1,COLUMNS-2) == '.' && board.At(1,COLUMNS-2) == 'B') ||
        (board_.At(ROWS-2,1) == '.' && board.At(ROWS-2,1) == 'B')||
        (board_.At(ROWS-2,COLUMNS-2) == '.' && board.At(ROWS-2,COLUMNS-2) == 'B'))
    {
      // Black made the corner easier for white to get
      score = score - 15;
    }
//    if ((board_.At(0,0) == '.' && board.At(0,0) == 'W') ||
//        (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'W') ||
//        (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'W')||
//        (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'W'))
//    {
//      // White took a corner
//      score = score - 15;
//    }
    score = score + WhiteTookCornerScore(board);
    if ((board_.At(1,1) == '.' && board.At(1,1) == 'W') ||
        (board_.At(1,COLUMNS-2) == '.' && board.At(1,COLUMNS-2) == 'W') ||
        (board_.At(ROWS-2,1) == '.' && board.At(ROWS-2,1) == 'W')||
        (board_.At(ROWS-2,COLUMNS-2) == '.' && board.At(ROWS-2,COLUMNS-2) == 'W'))
    {
      // White made the corner easier for black to get
      score = score + 15;
    }
    // We are simple looking for more black pieces than white pieces
    score = score + board.GetNumberBlack() - board.GetNumberWhite();
  }
  // Return the score of this move
  return score;
}

int State::BlackTookCornerScore(Board& board)
{
  int score = 0;
  if ((board_.At(0,0) == '.' && board.At(0,0) == 'B') ||
      (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'B') ||
      (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'B')||
      (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'B'))
  {
    score = 15;
  }
  return score;
}

int State::WhiteTookCornerScore(Board& board)
{
  int score = 0;
  if ((board_.At(0,0) == '.' && board.At(0,0) == 'W') ||
      (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'W') ||
      (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'W')||
      (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'W'))
  {
    score = -15;
  }
  return score;
}

// Function to evaluate the board for the negamax algorithm
int State::Evaluation(Board& board, int color)
{
  // The score of the move
  int score = 0;
  // Find out if this move is a winning move and if so which color is it for
  score = board.PlayerWin();
  // -1 is player 1
  if (score == -1)
  {
    score = 9999999;
  }
  // 1 is player 2
  else if (score == 1)
  {
    score = 9999999;
  }
  else
  {
    // Check to see whose move it is
    if (color == -1)
    {
      // Check to see if any of the corners were taken
      if ((board_.At(0,0) == '.' && board.At(0,0) == 'B') ||
          (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'B') ||
          (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'B')||
          (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'B'))
      {
        // Black took a corner
        score = score + 5;
      }
      if ((board_.At(1,1) == '.' && board.At(1,1) == 'B') ||
          (board_.At(1,COLUMNS-2) == '.' && board.At(1,COLUMNS-2) == 'B') ||
          (board_.At(ROWS-2,1) == '.' && board.At(ROWS-2,1) == 'B')||
          (board_.At(ROWS-2,COLUMNS-2) == '.' && board.At(ROWS-2,COLUMNS-2) == 'B'))
      {

        // Black made the corner easier for white to get
        score = score - 5;
      }
      // We are simple looking for more black pieces than white pieces
      score = score + board.GetNumberBlack() - board.GetNumberWhite();
    }
    else
    {
      // Check to see if any of the corners were taken
      if ((board_.At(0,0) == '.' && board.At(0,0) == 'W') ||
          (board_.At(0,COLUMNS-1) == '.' && board.At(0,COLUMNS-1) == 'W') ||
          (board_.At(ROWS-1,0) == '.' && board.At(ROWS-1,0) == 'W')||
          (board_.At(ROWS-1,COLUMNS-1) == '.' && board.At(ROWS-1,COLUMNS-1) == 'W'))
      {
        // White took a corner
        score = score + 5;
      }
      if ((board_.At(1,1) == '.' && board.At(1,1) == 'W') ||
          (board_.At(1,COLUMNS-2) == '.' && board.At(1,COLUMNS-2) == 'W') ||
          (board_.At(ROWS-2,1) == '.' && board.At(ROWS-2,1) == 'W')||
          (board_.At(ROWS-2,COLUMNS-2) == '.' && board.At(ROWS-2,COLUMNS-2) == 'W'))
      {
        // White made the corner easier for black to get
        score = score - 5;
      }
      // We are simple looking for more white pieces than black pieces
      score = score + board.GetNumberWhite() - board.GetNumberBlack();
    }
  }
  // Return the moves scores
  return score;
}

// Prints the board and the pieces on it
void State::PrintBoard() const
{
  board_.PrintBoard();
}

// Function to return if the game is over
bool State::EndGame()
{
  return(board_.EndGame());
}

// Function to call SetPiece on the board
bool State::SetPiece(int row, int column, char color)
{
  return(board_.SetPiece(row, column, color));
}

// Function to call CheckDown on the board
bool State::CheckDown(int row, int column, char color)
{
  return(board_.CheckDown(row, column, color));
}

// Function to call CheckDownLeft on the board
bool State::CheckDownLeft(int row, int column, char color)
{
  return(board_.CheckDownLeft(row, column, color));
}

// Function to call CheckDownRight on the board
bool State::CheckDownRight(int row, int column, char color)
{
  return(board_.CheckDownRight(row, column, color));
}

// Function to call CheckLeft on the board
bool State::CheckLeft(int row, int column, char color)
{
  return(board_.CheckLeft(row, column, color));
}

// Function to call CheckRight on the board
bool State::CheckRight(int row, int column, char color)
{
  return(board_.CheckRight(row, column, color));
}

// Function to call CheckUp on the board
bool State::CheckUp(int row, int column, char color)
{
  return(board_.CheckUp(row, column, color));
}

// Function to call CheckUpLeft on the board
bool State::CheckUpLeft(int row, int column, char color)
{
  return(board_.CheckUpLeft(row, column, color));
}

// Function to call CheckUpRight on the board
bool State::CheckUpRight(int row, int column, char color)
{
  return(board_.CheckUpRight(row, column, color));
}

// Function to call PrintWinner on the board
void State::PrintWinner()
{
  board_.PrintWinner();
}

// Function to call PlayerOneSkip on the board
void State::PlayerOneSkip()
{
  board_.PlayerOneSkip();
}

// Function to call PlayerTwoSkip on the board
void State::PlayerTwoSkip()
{
  board_.PlayerTwoSkip();
}

// Function that searches for the best move in a game tree.
// Returns the best move and its score by reference
void State::MiniMax(Board board, int depth, int max_depth, int& chosen_score, Board& chosen_move, int alpha, int beta, int color)
{
  Board the_move;
  // Check to see if the max depth is reached or if the board is the end of the game
  if (depth == max_depth || board.EndGame())
  {
    // If so evaluate the board
    chosen_score = EvaluationMini(board, -color);
  }
  else
  {
    // If not generate a vector of moves
    vector<Board> moves_list = GenerateMoves(board, color);
    // If there is no move the from this position
    if (moves_list.size() == 0)
    {
      // If so evaluate the board
      chosen_score = EvaluationMini(board, -color);
    }
    else
    {
      // Variable to hold the score
      int the_score = -9999999;
      // Board to hold the move so we don't mess up the current board
      Board new_board;
      // Check to see whose turn it is
      if (color == -1)
      {
        // If black's turn. Loop until we cover all the moves generated at this level
        for (unsigned int i = 0; i < moves_list.size(); i++)
        {
          // Set the safe board to the first new move
          new_board = moves_list.at(i);
          // Call minimax again on it
          MiniMax(new_board, depth+1, max_depth, the_score, the_move, alpha, beta, -color);
          // If the score found is better than the alpha
          if (the_score > alpha)
          {
            // Set alpha to the new score
            alpha = the_score;
            chosen_score = alpha;
            chosen_move = new_board;
          }
          // Check to see if alpha is equal to or greater than beta
          if (alpha >= beta)
          {
            // If so we found the best move we are getting down this path
            chosen_score = alpha;
            chosen_move = new_board;
            return;
          }
        }
        // If we make it here we didn't run across the best move we can get yet
//        chosen_score = the_score;
//        chosen_move = new_board;
      }
      else
      {
        // If white's turn. Loop until we cover all the moves generated at this level
        for (unsigned int i = 0; i < moves_list.size(); i++)
        {
          // Set the safe board to the first new move
          new_board = moves_list.at(i);
          // Call minimax again on it
          MiniMax(new_board, depth+1, max_depth, the_score, the_move, alpha, beta, -color);
          // If the score found is less than beta
          if (the_score < beta)
          {
            // Set beta to the new score
            beta = the_score;
            chosen_score = beta;
            chosen_move = new_board;
          }
          // Check to see if alpha is equal to or greater than beta
          if (alpha >= beta)
          {
            // If so we found the best move we are getting down this path
            chosen_score = beta;
            chosen_move = new_board;
            return;
          }
        }
        // If we make it here we didn't run across the best move we can get yet
//        chosen_score = beta;
//        chosen_move = new_board;
      }
    }
  }
}

// Function that searches for the best move in a game tree.
// Returns the best move and its score by reference
void State::NegaMax(Board board, int depth, int max_depth, int& chosen_score, Board& chosen_move, int alpha, int beta, int color)
{
  Board the_move;
  // Check to see if the max depth is reached or if the board is the end of the game
  if (depth == max_depth)
  {
    // If so evaluate the board
    chosen_score = Evaluation(board, -color) * (-color);
  }
  else
  {
    // If not generate a vector of moves
    vector<Board> moves_list = GenerateMoves(board, color);
    // If there is no move the from this position
    if (moves_list.size() == 0)
    {
      // If so evaluate the board
      chosen_score = Evaluation(board, -color) * (-color);
    }
    else
    {
      // Board to hold the move so we don't mess up the current board
      Board new_board = board;
      // Loop until all moves are gone through
      for (unsigned int i = 0; i < moves_list.size(); i++)
      {
        // The score
        int the_score = -9999;
        // Get the first move from the vector
        new_board = moves_list.at(i);
        // Call Negamax on it
        NegaMax(new_board, depth+1, max_depth, the_score, the_move, -beta, -alpha, -color);
        // Reverse the score
        int val = -the_score;
        // Check to see if val is greater than beta
        if (val >= beta)
        {
          chosen_score = val;
          chosen_move = new_board;
          return;
        }
        // Check to see if val is greater than alpha
        if (val > alpha)
        {
          alpha = val;
          chosen_score = alpha;
          chosen_move = new_board;
        }
      }
      // If we make it here we didn't run across the best move we can get yet
//      chosen_score = alpha;
//      chosen_move = new_board;
    }
  }
}

// Function that gets the black's move when black is played by the computer
void State::GetPlayer1Move()
{
  // Make sure the player was set right. Was having an issue where the next player to play wasn't being flipped correctly
  // This is used to make sure it is until the other stuff is fixed
  if (next_player_ == 1)
  {
    next_player_ = -1;
  }
  // The new board of the game
  Board update;
  // The score of the move picked
  int chosen_score = 0;
  // Used for alpha beta pruning
  int alpha = -99999990;
  // Used for alpha beta pruning
  int beta = 99999990;
  if (algorithm_ == 'N' || algorithm_ == 'n')
  {
    NegaMax(board_, depth_, max_depth_, chosen_score, update, alpha, beta, next_player_);
  }
  else
  {
    MiniMax(board_, depth_, max_depth_, chosen_score, update, alpha, beta, next_player_);
  }
  // Check to see if a move was found
  if (blank_board_ == update || board_ == update)
  {
    // If not skip this turn
    cout << "No move was found. Passing turn" << endl;
    PlayerOneSkip();
  }
  else
  {
    // If so update the board
    board_ = update;
    // Reset the number of passes to 0
    board_.PlayerOneReset();
  }
  // Flip to the next player
  next_player_ = -next_player_;
}

// Function that gets the computer's move
void State::GetPlayer2Move()
{
  // Make sure the player was set right. Was having an issue where the next player to play wasn't being flipped correctly
  // This is used to make sure it is until the other stuff is fixed
  if (next_player_ == -1)
  {
    next_player_ = 1;
  }
  // The new board of the game
  Board update;
  // The score of the move picked
  int chosen_score = 0;
  // Used for alpha beta pruning
  int alpha = -99999990;
  // Used for alpha beta pruning
  int beta = 99999990;
  if (algorithm_ == 'N' || algorithm_ == 'n')
  {
    NegaMax(board_, depth_, max_depth_, chosen_score, update, alpha, beta, next_player_);
  }
  else
  {
    MiniMax(board_, depth_, max_depth_, chosen_score, update, alpha, beta, next_player_);
  }
  // Check to see if a move was found
  if (blank_board_ == update || board_ == update)
  {
    // If not skip this turn
    cout << "No move was found. Passing turn" << endl;
    PlayerTwoSkip();
  }
  else
  {
    // If so update the board
    board_ = update;
    // Reset the number of passes to 0
    board_.PlayerTwoReset();
  }
  // Flip to the next player
  next_player_ = -next_player_;
}

// Function that attempts to generate moves to see if there is a valid move to take
// Returns true if a move is found else returns false
bool State::ValidMoveAvailable()
{
  Board new_move;
  new_move = board_;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (new_move.SetPieceForPlayer2(i, j, 'B'))
      {
        return true;
      }
    }
  }
  return false;
}

// Function to set the algorithm to use
void State::SetAlgorithm(char choice)
{
  algorithm_ = choice;
}
