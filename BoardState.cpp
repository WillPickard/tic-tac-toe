/************
 *@file
 *	BoardState.cpp
 *
 *
 * This file implements all the methods outlined in BoardState.h
 *
 *
 * ****************/

#include "BoardState.h"
#include <stdio.h>
#include <math.h>
#include <array>
#include <string>
using namespace std;

//This constructor is accepts a boardState of the form *****XX**0 and creates a boardState object with the appropriate variables set
BoardState::BoardState(const std::string boardPosition){ 
	size_t length;
	short int xS, oS, powResult;
	length = boardPosition.length();
	xS = 0; oS =0;
	for(std::string::size_type i=0;i<length;i++){
	  switch(boardPosition[i]){
		case 'x':
		case 'X':
		  powResult = pow(2, i);
		  xS += powResult;
		  break;
		case 'o':
		case 'O':
		  powResult = pow(2, i);
		  oS += powResult;
		  break;
		default: break;
	  };
	}
	xSum = xS;
	oSum = oS;
	outcome = GAME_INPROGRESS;
	setXCount(xS);
	setOCount(oS);
};
//This constructor is an overloaded equiavlent of the one that accepts the string.
//This constructor accepts outright values for the four short ints a single BoardSTate object keeps track of
BoardState::BoardState(short int xS, short int oS):
	xSum(xS),
 	oSum(oS),
        outcome(GAME_INPROGRESS)
{
	BoardState::setXCount(xS);
	BoardState::setOCount(oS);
};

BoardState* BoardState::clone() const{
  return new BoardState(*this);
};

/*
 *
 * GETTERS
 *	AND
 * SETTERS
 *
 *
 */

short int BoardState::getXSum() const { return xSum; }
short int BoardState::getOSum() const { return oSum; }
short int BoardState::getXCount() const { return xCount; }
short int BoardState::getOCount() const { return oCount; }
short int BoardState::getOutcome() const { return outcome; }
short int BoardState::getTurn() const {
	//prshort intf("***********************GET TURN *****************************\n");
	//prshort intf("xCount: %d\n oCount: %d\n", xCount, oCount);
	//prshort intf("***************************END GETTURN *********************\n");
	if(xCount == oCount){
	  return X_TURN;
	}  
	return O_TURN;
};

void BoardState::setXSum(short int x){ xSum = x; }
void BoardState::setOSum(short int o){ oSum = o; }
void BoardState::setXCount(short int x){
	short int lgResult;
	short int powResult;
	short int tempXCount = 0;
	while(x != 0){
	  lgResult = (short int)log2(x);
	  powResult = (short int) pow(2, lgResult);
	  x -= powResult;
	  tempXCount++;
	}
	xCount = tempXCount;
}
void BoardState::setOCount(short int o){ 
	short int lgResult;
	short int powResult;
	short int tempOCount = 0;
	while(o != 0){
	  lgResult = (short int)log2(o);
	  powResult = (short int) pow(2, lgResult);
	  o -= powResult;
	  tempOCount++;
	} 
	oCount = tempOCount;
}
void BoardState::setOutcome(short int o){ outcome = o; }

/*
 *
 * END 
 *  GETTERS AND SETTERS
 *
 *
 */
//builds an array from the boardState
void BoardState::print() const{
	array<short int, BOARD_SIZE> boardArray = toArray();
	//At this poshort int our out array will be a bunch of ints, so now we need to build a string to print with Xs, Os, and *s 
	char s [BOARD_SIZE];
	for(short int i=0; i< BOARD_SIZE; i++){
	  switch(boardArray[i]){
	    case EMPTY_CELL:	
		s[i] = '*';
		break;
	    case X_CELL:
		s[i] = 'X';
		break;
	    case O_CELL:
		s[i] = 'O';
		break;
	  };
	}
	s[BOARD_SIZE] = '\0';
	//now just prshort int it
	printf("%s\n", s);	
}
//checks to see if the game can continue, updates the boardState's outcome variable
void BoardState::checkOutcome(){
	//check to see if xCount is bigger than 3 because only then can wins occur... gotta save every picosecond... 
	if(xCount >= 3){
	  for(short int i=0;i<8;i++){
	   //to check if a win has occured, for each short int in the ALL_WINS array, we will use bit wise AND against both the xSum and oSum
	   //why? if the result of ALL_WINS[i] b-w-AND against xSum || oSum == ALL_WINS[i], then a win occured
	    short int winPoss = ALL_WINS[i];	
	    short int tx = winPoss & xSum;
	    if(tx == winPoss){
	      setOutcome(GAME_WIN);
	      return;
	    }
	    short int to = winPoss & oSum;
	    if(to == winPoss){
	      setOutcome(GAME_WIN);
	      return;
	    }
	  }
	}
	if(xCount > 4){
	  short int tempSum = xSum + oSum;
	  if(tempSum == MAX_SUM){
	    setOutcome(GAME_DRAW);
	    return;
	  }
	}
	return;
}
//prshort ints the board state
//If you take lg(xSum) || lg(oSum):
//the result will be an short integer indicating the cell position of the greatest x or o
//that's confusing, look at an example:
// 1   | x 2  | 4
//------------------
// x 8 | 16   | 32 
//------------------
// 64  | 128  | x 256
//
//	In the above example the xSum = 2+8+256 = 266
//	1)lg(266) = (short int)8
//	2)This means that there is an X in the 8th cell of the board
//	3)Now, subtract 2^8 from xSum temp
//		266 - 2^8 = 266 - 256 = 10
//	4)Current value is 9. If you notice, we have two x's left. One is in cell 1 (2^1) and the other is in cell 3 (2^3)
//		lg(10) = 3 => x is cell 3
//		10 - 2^3 = 10 - 8 = 2
//		lg(2) = 1 => x in cell 1 (2^1)
//		2 - 2^1 = 2 - 2 = 0 =====> we're done 
array<short int, BOARD_SIZE> BoardState::toArray() const{
	short int tXS = getXSum();
 	short int tOS = getOSum();
	std::array<short int, BOARD_SIZE> out;
	//set array to all EMPTY_CELL
	for(short int i=0; i<BOARD_SIZE; i++){
	  out[i] = EMPTY_CELL;
	}
	short int lgResult;
	short int powResult;
	while(tXS != 0){
	  lgResult = (short int)log2(tXS);
	  out[lgResult] = X_CELL;
	  powResult = (short int) pow(2, lgResult);
	  tXS -= powResult;
	}
	while(tOS != 0){
	  lgResult = (short int)log2(tOS);
	  out[lgResult] = O_CELL;
	  powResult = (short int) pow(2, lgResult);
	  tOS -= powResult;
	}
	return out;
}
