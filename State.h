/*
 * State.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Joshua Boone
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <vector>
#include "Board.h"

// State class. Holds the information of the current State along with a pointer that points
// to its parent State
class State
{
public:
  // Default constructor
  State();
  // Default destructor
  ~State();
  // Function to generate a vector of possible moves
  std::vector<Board> GenerateMoves(const Board& board, int color);
  int BlackTookCornerScore(Board& board);
  int WhiteTookCornerScore(Board& board);
  // Function to evaluate the board for the negamax algorithm
  int Evaluation(Board& board, int color);
  // Function to evaluate the board for the minimax algorithm
  int EvaluationMini(Board& board, int color);
  // Function that prints this State's information along with calling its parents Print function
  void PrintBoard() const;
  // Function to return if the game is over
  bool EndGame();
  // Function to call SetPiece on the board
  bool SetPiece(int row, int column, char color);
  // Function to call CheckDown on the board
  bool CheckDown(int row, int column, char color);
  // Function to call CheckDownLeft on the board
  bool CheckDownLeft(int row, int column, char color);
  // Function to call CheckDownRight on the board
  bool CheckDownRight(int row, int column, char color);
  // Function to call CheckLeft on the board
  bool CheckLeft(int row, int column, char color);
  // Function to call CheckRight on the board
  bool CheckRight(int row, int column, char color);
  // Function to call CheckUp on the board
  bool CheckUp(int row, int column, char color);
  // Function to call CheckUpLeft on the board
  bool CheckUpLeft(int row, int column, char color);
  // Function to call CheckUpRight on the board
  bool CheckUpRight(int row, int column, char color);
  // Function to call PrintWinner on the board
  void PrintWinner();
  // Function to call PlayerOneSkip on the board
  void PlayerOneSkip();
  // Function to call PlayerTwoSkip on the board
  void PlayerTwoSkip();
  // Function that searches for the best move in a game tree
  void MiniMax(Board board, int depth, int max_depth, int& chosen_score, Board& chosen_move,
      int alpha, int beta, int color);
  // Function that searches for the best move in a game tree
  void NegaMax(Board board, int depth, int max_depth, int& chosen_score, Board& chosen_move,
      int alpha, int beta, int color);
  // Function that gets the black's move when black is played by the computer
  void GetPlayer1Move();
  // Function that gets the computer's move
  void GetPlayer2Move();
  // Function that attempts to generate moves to see if there is a valid move to take
  bool ValidMoveAvailable();
  // Function that sets which algorithm to use
  void SetAlgorithm(char choice);

private:
  Board board_;
  // Used to tell when the AI cannot find a move
  Board blank_board_;
  // The current depth in the tree
  int depth_;
  // The max depth to search up to
  int max_depth_;
  // The score of the move picked by MinMax
  int chosen_score_;
  // Used with MinMax to produce the next possible move. -1 for white and 1 for black
  int next_player_;
  // Used to choose which algorithm to use
  char algorithm_;
};

#endif /* STATE_H_ */
