/********
 *@file
 *  BoardState.h
 *
 * This is the header file for the BoardState class 
 *  The purpose of this class is to represent a single isntance of a game of tic   tac toe
 *
 * **************/

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <string>
#include <array>
#include <math.h>
#ifndef BOARD_CONSTANTS
#define BOARD_CONSTANTS 1
const short int BOARD_SIZE = 9;
const short int X_TURN = 0;
const short int O_TURN = 1;
const short int GAME_INPROGRESS = 2;
const short int GAME_WIN = 4;
const short int GAME_DRAW = 8;
const short int X_CELL = 16;
const short int O_CELL = 32;
const short int EMPTY_CELL = 64;
const short int MAX_SUM = 511;
const short int V_WINS[] = {73, 146, 292};
const short int H_WINS[] = {7, 56, 448};
const short int D_WINS[] = {84, 273};
const short int ALL_WINS[] = {73, 146, 292, 7, 56, 448, 84, 273};
#endif

class BoardState{
  private:
	short int xCount;
	short int  oCount;
	short int xSum;
	short int oSum;
	short int outcome;
  public:
	BoardState(const std::string  boardPosition);
	BoardState(short int xSum, short int oSum);

	BoardState* clone() const;

	short int getXSum() const;
	short int getOSum() const;
	short int getTurn() const;
	short int getXCount() const;
	short int getOCount() const;
	short int getOutcome() const;

	void setXSum(short int x);
	void setOSum(short int o);
	void setXCount(short int x);
	void setOCount(short int o);
	void setOutcome(short int x);
	
	//returns an array
        std::array<short int, BOARD_SIZE> toArray() const;
	//check outcome determines if the current state can continue, if it is tied, or a win
	void checkOutcome();
	void print() const;	
};
#endif
