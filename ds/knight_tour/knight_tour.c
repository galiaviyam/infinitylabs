/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Knight Tour      		*/
/*   Date:		14/02/23				*/
/*	 Reviewer:	Moriah					*/
/*										*/
/****************************************/

#include <assert.h> 		/* assert */
#include <stdio.h> 			/* printf */
#include <time.h> 			/* time_t */
#include <stdlib.h>			/* qsort */

#include "knight_tour.h"	/* knight tour header */
#include "bit_array.h"		/* bit array header */

#define SIDE_SIZE (8)
#define BOARD_SIZE ((SIDE_SIZE) * (SIDE_SIZE))
#define POSSIBLE_MOVES (8)
#define FIRST_IDX (0)
#define LAST_IDX (63)
#define MAX_TIME (300)
#define ROW_IDX (0)
#define COL_IDX (1)

typedef enum status
{
	OUT_OF_BOARD = -1,
	SUCCESS,
	FAIL,
	TIMEOUT
} status_t;

typedef struct position
{
	int square;
	size_t num_of_access;
}pos_t;

/*-------------------Static Function Declerations-----------------*/
static int Tour(size_t *path, size_t position, int next_pos_lut[][SIDE_SIZE], 
				bit_array_t board, time_t start_time);
static int WarnsdorffTour(size_t *path, size_t position, 
				int next_pos_lut[][SIDE_SIZE], bit_array_t board, 
				time_t start_time);

static int IsPosVisited(bit_array_t board, size_t position);
static int IsAllVisited(bit_array_t board);
static int IsPosInBoard(int position);
static int IsValidStep(int step, bit_array_t board);

static bit_array_t SetPosVisited(bit_array_t board, int position);
static bit_array_t SetPosNotVisited(bit_array_t board, int position);


/*------index manipulations------*/
static size_t IndexesToSquareNum(size_t row, size_t col);
static void SquareNumToIndexes(size_t num, size_t *indexes);

/*------init luts------*/
static void InitNextPositionsLUT(int next_positions_lut[][SIDE_SIZE]);
static void InitNextPossible(size_t position, pos_t *next_possible,
						   bit_array_t board, int next_pos_lut[][SIDE_SIZE]);
static size_t CalcNextPossible(int position, bit_array_t board,
						 int next_pos_lut[][SIDE_SIZE]);
static int CmpFunc(const void *square1, const void *square2);
						 
/*----------------------------Function Definitions----------------------------*/

int KnightTour(size_t *path, size_t start_position)
{
	int next_positions_lut[BOARD_SIZE][SIDE_SIZE] = {0};
	bit_array_t board = 0;
	time_t start_time = time(&start_time);
	
	assert(NULL != path);
	
	InitNextPositionsLUT(next_positions_lut);

	board = BitArrSetOn(board, start_position);

	*path = start_position;
	
	return (Tour(path + 1, start_position, next_positions_lut, board, 
				start_time));
}

int KnightTourWarnsdorff(size_t *path, size_t start_position)
{
	int next_positions_lut[BOARD_SIZE][SIDE_SIZE] = {0};
	bit_array_t board = 0;
	time_t start_time = time(&start_time);
	
	assert(NULL != path);
	
	InitNextPositionsLUT(next_positions_lut);

	board = BitArrSetOn(board, start_position);

	*path = start_position;
	
	return (WarnsdorffTour(path + 1, start_position, next_positions_lut, board, 
							start_time));
}

/*-------------------------Static Function Definitions-----------------------*/

static int Tour(size_t *path, size_t position, int next_pos_lut[][SIDE_SIZE], 
				bit_array_t board, time_t start_time)
{
	time_t curr_time = time(&curr_time);
	int direction = 0;
	int next_pos = 0;
	
	assert(NULL != path);
	
	if (MAX_TIME <= difftime(curr_time, start_time))
	{
		printf("Timeout! no solution found\n");
		return (TIMEOUT);
	}
	
	if (IsAllVisited(board))
	{
		return (SUCCESS);
	}
	
	for (direction = 0; direction < POSSIBLE_MOVES; ++direction)
	{
		next_pos = next_pos_lut[position][direction];
		if (IsValidStep(next_pos, board))
		{
			board = SetPosVisited(board, next_pos);
			*path = next_pos;
			if (SUCCESS == 
					Tour(path + 1, next_pos, next_pos_lut, board, start_time))
			{
				return SUCCESS;
			}
			else
			{
				board = SetPosNotVisited(board, next_pos);
			}
		}
	}
	
	return FAIL;
}

static int WarnsdorffTour(size_t *path, size_t position, 
				int next_pos_lut[][SIDE_SIZE], bit_array_t board, 
				time_t start_time)
{
	time_t curr_time = time(&curr_time);
	int direction = 0;
	int next_pos = 0;
	pos_t next_possible[POSSIBLE_MOVES] = {0};
	
	assert(NULL != path);
	
	if (MAX_TIME <= difftime(curr_time, start_time))
	{
		printf("TIMEOUT! no solution found\n");
		return (TIMEOUT);
	}
	
	if (IsAllVisited(board))
	{
		return (SUCCESS);
	}
	
	InitNextPossible(position, next_possible, board, next_pos_lut);
	
	for (direction = 0; direction < POSSIBLE_MOVES; ++direction)
	{
		next_pos = next_possible[direction].square;
		if (IsValidStep(next_pos, board))
		{
			board = SetPosVisited(board, next_pos);
			*path = next_pos;
			if (SUCCESS == WarnsdorffTour(path + 1, next_pos, next_pos_lut, 
											board, start_time))
			{
				return SUCCESS;
			}
			else
			{
				board = SetPosNotVisited(board, next_pos);
			}
		}
	}
	
	return FAIL;
}

static void InitNextPossible(size_t position, pos_t *next_possible,
						   bit_array_t board, int next_pos_lut[][SIDE_SIZE])
{
	size_t i = 0;
	int move = 0;
	
	for (i = 0; i < POSSIBLE_MOVES; ++i)
	{
		move = next_pos_lut[position][i];
		next_possible[i].square = move;
		next_possible[i].num_of_access = 
				CalcNextPossible(move, board, next_pos_lut);
	}
	
	qsort(next_possible, POSSIBLE_MOVES, sizeof(pos_t), &CmpFunc);
}

static size_t CalcNextPossible(int position, bit_array_t board,
						 int next_pos_lut[][SIDE_SIZE])
{
	size_t i = 0;
	size_t count = 0;
	int move = 0;
	
	assert(NULL != next_pos_lut);
	
	if (IsValidStep(position, board))
	{
		for (i = 0; i < POSSIBLE_MOVES; ++i)
		{
			move = next_pos_lut[position][i];
			if (IsValidStep(move, board))
			{
				++count;
			}
		}
	}
	
	return count;
}

static int CmpFunc(const void *square1, const void *square2)
{
	assert(NULL != square1);
	assert(NULL != square2);
	
	return (((pos_t *)square1)->num_of_access - 
						((pos_t *)square2)->num_of_access);
}

static int IsAllVisited(bit_array_t board)
{
	return (0 == BitArrCountOffBits(board));
}

static size_t IndexesToSquareNum(size_t row, size_t col)
{
	return (SIDE_SIZE * row + col);
}

static void SquareNumToIndexes(size_t num, size_t *indexes)
{
	assert(NULL != indexes);
	
	indexes[ROW_IDX] = num >> 3;	/* = (num / SIDE_SIZE) */
	indexes[COL_IDX] = num & 7;		/* = (num % SIDE_SIZE) */
}

static void InitNextPositionsLUT(int next_positions_lut[][SIDE_SIZE])
{
	size_t curr_pos = 0;
	size_t direction = 0;
	size_t next_col_pos = 0;
	size_t next_row_pos = 0;
	size_t indexes[2] = {0};
	int row_moves[POSSIBLE_MOVES] = {1, 2, 2, 1, -1, -2, -2, -1};
	int col_moves[POSSIBLE_MOVES] = {2, 1, -1, -2, -2, -1, 1, 2};

	assert(NULL != next_positions_lut);
	
	for (curr_pos = 0; curr_pos < BOARD_SIZE; ++curr_pos)
	{
		SquareNumToIndexes(curr_pos, indexes);
		
		for (direction = 0; direction < POSSIBLE_MOVES; ++direction)
		{
			next_col_pos = indexes[COL_IDX] + row_moves[direction];
			next_row_pos = indexes[ROW_IDX] + col_moves[direction];
			
			if (SIDE_SIZE > next_col_pos && SIDE_SIZE > next_row_pos)
			{			
				next_positions_lut[curr_pos][direction] = 
								IndexesToSquareNum(next_row_pos, next_col_pos);
			}
			else
			{
				next_positions_lut[curr_pos][direction] = OUT_OF_BOARD;
			}
		}
	}
}

static int IsValidStep(int step, bit_array_t board)
{
	int res = 0;
	
	res = (IsPosInBoard(step) && !IsPosVisited(board, step));
	return res;
}

static int IsPosInBoard(int position)
{
	return (FIRST_IDX <= position && LAST_IDX >= position);
}

static bit_array_t SetPosVisited(bit_array_t board, int position)
{
	assert(0 <= position);
	
	return BitArrSetOn(board, position);
}

static bit_array_t SetPosNotVisited(bit_array_t board, int position)
{
	assert(0 <= position);
	
	return BitArrSetOff(board, position);
}

static int IsPosVisited(bit_array_t board, size_t position)
{
	return (bit_on == BitArrGetVal(board, position));
}
