/*
 * Driver.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Joshua Boone
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "State.h"

// Main class that will drive and do the heavy lifting for this program
class Driver
{
public:
  // Default constructor
  Driver();
  // Default destructor
  ~Driver();
  // Gets the move from the player
  void GetPlayer1Move();
  // Gets the move from the computer
  void GetPlayer2Move();
  // Tries to makes to move for the player
  bool MakeMove(int row, int column, char color);
  // Main driver that runs the game
  void PlayGame();
  // Checks to see if the game is over
  bool EndOfGame();
  // Checks to see if there is a valid move for the player to take
  bool ValidMoveAvailable();

private:
  // State of the game
  State final_state_;
  // Used to keep track if the user wants to exit the program.
  bool exit_;
};

#endif /* DRIVER_H_ */
