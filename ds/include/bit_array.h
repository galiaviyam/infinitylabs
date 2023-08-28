/********************************************************************/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 1.12.2022                                         */
/* WORKSHEET NAME: bit array                                        */
/* Reviewer: Ariel Biton                                            */
/********************************************************************/

#ifndef __BITARR_H__
#define __BITARR_H__

#include <stddef.h>	/*size_t*/

/************************typedef*****************************/
typedef size_t bit_array_t;

typedef enum bit_val
{
	bit_off = 0,
	bit_on	= 1
}bit_val_t;

/******************Function Declarations********************/
/*---------------------------------------------------------------------------
Description:
BitArrSetOn function sets on the i'th bit in the bitarr.
i larger then bitarr's size will lead to undefined behavior
Return Value:
Returns the bitarr with the bit set on

time: o(1) / space: o(1)
---------------------------------------------------------------------------*/
bit_array_t BitArrSetOn(bit_array_t bitarr, size_t i);

/*---------------------------------------------------------------------------
Description:
BitArrSetOff function sets off the i'th bit in the bitarr.
i larger then bitarr's size will lead to undefined behavior
Return Value:
Returns the bitarr with the bit set off.

time: o(1) / space: o(1)
---------------------------------------------------------------------------*/
bit_array_t BitArrSetOff(bit_array_t bitarr, size_t i);

/*-----------------------------------------------------------------------------
Description:
BitArrFlipBit function flips the value of the i'th bit in the bitarr.
i larger then bitarr's size will lead to undefined behavior
Return Value:
Returns the bitarr with the bit flipped.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 
bit_array_t BitArrFlipBit(bit_array_t bitarr, size_t i);

/*-----------------------------------------------------------------------------
Description:
BitArrGetVal funciton checks the value of the i'th bit in the bitarr.
i larger then bitarr's size will lead to undefined behavior
Return Value:
Returns the value of the bit.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 
int BitArrGetVal(bit_array_t bitarr, size_t i);	

/*-----------------------------------------------------------------------------
Description:
BitArrSetVal function sets value to the i'th bit in the bitarr.
i larger then bitarr's size will lead to undefined behavior
Return Value:
Returns the bitarr with the chosen bit set.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	 
bit_array_t BitArrSetVal(bit_array_t bitarr, size_t i, bit_val_t value);

/*-----------------------------------------------------------------------------
Description:
BitArrFlipAll function flips the value of all bits in the bitarr.
Return Value:
Returns the flipped bitarr.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrFlipAll(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrSetAll function sets on all the bits in the bitarr.
Return Value:
Returns the bitarr set on.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrSetAll(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description 
BitArrUnsetAll function sets off all the bits in the bitarr.
Return Value:
Returns the bitarr set off.
time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrUnsetAll(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description 
BitArrRotateLeft function rotates the bitarr n times to the left.
Return Value:
Returns the bitarr rotated as requested.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrRotateLeft(bit_array_t bitarr, size_t n);

/*-----------------------------------------------------------------------------
Description:
BitArrRotateRight function rotates the bitarr n times to the right.
Return Value:
Returns the bitarr rotated as requested.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrRotateRight(bit_array_t bitarr, size_t n);

/*-----------------------------------------------------------------------------
Description:
BitArrMirror function reverses the bitarr.
Return Value:
Returns the bitarr reversed.

time: o(n) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrMirror(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrMirrorLut function reverses the bitarr.
Return Value:
Returns the bitarr reversed.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
bit_array_t BitArrMirrorLut(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrMirrorO1 function reverses the bitarr.
Return Value:
Returns the bitarr reversed.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/
bit_array_t BitArrMirrorO1(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrCountSetBits function counts the number of set bits in the bitarr.
Return Value:
Returns the number of set bits.

time: o(n) / space: o(1)
-----------------------------------------------------------------------------*/	
size_t BitArrCountSetBits(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrCountSetBitsLut function counts the number of set bits in the bitarr.
Return Value:
Returns the number of set bits.

time: o(1) / space: o(n)
-----------------------------------------------------------------------------*/	
size_t BitArrCountSetBitsLut(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrCountOffBits function counts the number of unset bits in the bitarr.
Return Value:
Returns the number of unset bits.


time: o(n) / space: o(1)
-----------------------------------------------------------------------------*/	
size_t BitArrCountOffBits(bit_array_t bitarr);

/*-----------------------------------------------------------------------------
Description:
BitArrToString function converts the bitarr into a string saved in buffer.
The buffer should be at least the bitarr's size plus one for the null-terminator.
Return Value:
Return the bitarr as a string.

time: o(1) / space: o(1)
-----------------------------------------------------------------------------*/	
char *BitArrToString(bit_array_t bitarr, char *buffer);

#endif 		/* __BITARR_H__ */
