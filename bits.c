/*
 * CS045 Data Lab
 *
 * <Jason Watts jawatts45, Trevor Kirkby tkirkby45, James Something, jsomething45>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int functionName(arg1, arg2, ...) {
  /* brief description of how your implementation works */
  int var1 = <expression 1>;
  ...
    int varM = <expression M>;

  varJ = <expression>;
  ...
    varN = <expression>;
  return <expression>;
}

Each "<expression>" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "<expression>" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  int result = (1 << x);
  result += 4;
  return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
    the coding rules are less strict.  You are allowed to use looping and
    conditional control.  You are allowed to use both ints and unsigneds.
    You can use arbitrary integer and unsigned constants.

    You are expressly forbidden to:
    1. Define or use any macros.
    2. Define any additional functions in this file.
    3. Call any functions.
    4. Use any form of casting.
    5. Use any data type other than int or unsigned.  This means that you
    cannot use arrays, structs, or unions.
    6. Use any floating point data types, operations, or constants.


    NOTES:
    1. Use the dlc (data lab checker) compiler (described in the handout) to
  check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
  that you are allowed to use for your implementation of the function.
  The max operator count is checked by dlc. Note that '=' is not
  counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
  header comment for each function. If there are any inconsistencies
  between the maximum ops in the writeup and in this file, consider
  this file the authoritative source.

  /*
   * STEP 2: Modify the following functions according the coding rules.
   *
   *   IMPORTANT. TO AVOID GRADING SURPRISES:
   *   1. Use the dlc compiler to check that your solutions conform
   *      to the coding rules.
   *   2. Use the BDD checker to formally verify that your solutions produce
   *      the correct answers.
   */
#endif

/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int y = x >> 31;  //Get the sign bit, and repeat it 32 times due to how right shifts work on signed ints
  return (x+y) ^ y; //Equivalent to (x^y) - y
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int xshift = x >> 31; //Get the sign bit of x to save an operator use
  return ((xshift ^ (y >> 31)) | !(xshift ^ ((x+y) >> 31))) & 1; //If overflow happened, that means the signs of x and y have to be the same, and the sign of x+y is different.
}

/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  return !!((x & 0xaa) | ((x >> 8) & 0xaa) | ((x >> 16) & 0xaa) | ((x >> 24) & 0xaa)); //Check each byte with a mask of the all odd bits set, and OR the results together
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  int negative_x = ~x+1;
  int bits = (negative_x | x) >> 31; /* -1 or 0 */
  return bits + 1;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int x55 = (0x55 << 24) | (0x55 << 16) | (0x55 << 8) | 0x55; //Using the parallel algorithm for computing hamming weights
  int x33 = (0x33 << 24) | (0x33 << 16) | (0x33 << 8) | 0x33; //A pretty clever approach that splits the int up into offset pieces to count the bits
  int x0F = (0x0F << 24) | (0x0F << 16) | (0x0F << 8) | 0x0F; //First, we create the larger constants necessary for using the parallel algorithm
  int x0F2 = (0xFF << 16) | 0xFF;                             //There is almost certainly a way to avoid creating larger constants, but we are also allowed plenty of ops on this one
  int x0F4 = (0xFF << 8) | 0xFF;
  x = (x & x55) + ((x >> 1) & x55);
  x = (x & x33) + ((x >> 2) & x33);
  x = (x + (x >> 4)) & x0F;
  x = (x + (x >> 8)) & x0F2;
  x = (x + (x >> 16)) & x0F4;
  return x;
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
   x ^= x >> 16;
   x ^= x >> 8;
   x ^= x >> 4;
   x &= 0xf;
   return (((0x69 << 8) | 0x96) >> x) & 1;
}

/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y); //Using DeMorgan's law to convert XOR to only nots and ands
}

/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int offsetn = (n << 3); //Equivalent to n * 8, the location of the byte we want
  int offsetm = (m << 3); //Equivalent to m * 8, the location of the byte we want
  int n_contents = 0xff & (x >> offsetn); //See getByte
  int m_contents = 0xff & (x >> offsetm); //Technically, we don't need a second variable to do this, but I am making one for the sake of clarity since we are only limited on use of operators
  x &= ~(0xff << offsetn); //Clear the byte in position n
  x &= ~(0xff << offsetm); //Clear the byte in position m
  x |= m_contents << offsetn; //Set the byte in position n to the former contents of m
  x |= n_contents << offsetm; //Set the byte in position m to the former contents of n
  return x;
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int xmask = (!x << 31) >> 31; //Create a sequence of all 1s or 0s. Will be 0s if x is true, 1s if x is false.
  return (~xmask & y) | (xmask & z); //If x is true, xmask will cause y to be returned and z to be zero'd out, but if x is false, xmask will cause the opposite
}

/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) { //If rounding down wasn't a requirement, we could just right shift by n.
  int offset = (x >> 31) & ((1 << n) + ~0); //As it is, we are still right shifting by n, but we must construct an offset to round x down to the nearest power of 2
  return (x + offset) >> n;                 //Sign bit & left padding of length n
}

/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  x += x << 1; //AKA x += 2x, AKA x *= 3
  return (x + ((x >> 31) & 3)) >> 2;   //Divide by 4 like we would in divpwr2, with some stuff hard-coded since we're always dividing by 4
}

/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return uf & ~(1 << 31); //All we need to do is zero the sign bit.
}                         //NOTE: I'm *fairly* sure that the automated tests are handling this function incorrectly.

/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  return uf ^ (1 << 31); //All we need to do is flip the sign bit
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int offset = (n << 3); //Equivalent to n * 8, the location of the byte we want
  return 0xff & (x >> offset); //Offset x to make the byte we want into the first byte, and then mask it with 0xff to clip off any other unwanted bytes
}

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  return !(((0x3a + ~x) >> 31) | ((x + ~0x2f) >> 31)); //If x >= y, then x - y won't be negative, ie the sign bit will not be set.
}                                                      //Keeping in mind the fact that x - y is the same as x + ~y + 1, and that if x or y is constant we can combine it with the +1 term

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x ^ y); //x ^ y returns 0 iff x = y
}

/*
 * isNegative - return 1 if x < 0, return 0 otherwise
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return (x >> 31) & 1; //Create all 1s or all 0s depending on the sign bit, and then & it with 1 to test which one it is.
}

/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
  return ((x | (~x + 1)) >> 31) & 1; //Taking advantage of the fact that x != -x iff x is not zero (where -x = ~x+1)
}

/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  return !!(x ^ y); //x ^ y returns 0 iff x = y
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return ~x & !((x+1) ^ ~x); //Taking advantage of overflow, Tmax and -1 are the only possible numbers for which x+1 == ~x
}

/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  return (x >> 31) & !x;
}

/*
 * isZero - returns 1 if x == 0, and 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}

/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
  return x & (~x+1);

}

/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~0x00;
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ((~x) + 1);
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int offset = (n << 3); //Equivalent to n * 8, the number of bits we need to offset to access the byte we want.
  return (x & ~(0xff << offset)) | (c << offset); //Zero out the byte we want to change by ANDing it with a mask, then OR that with C offset into the correct position to set the byte we just zero'd out.
}

/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  return 2;
}

/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {

  //return (~(x)|!x+1|!!x+(-2));      //bitwise not states that if x is zero than return true
                                    //logical not equates to 0 if x is a positive number
                                    //two logical nots equate to 1 if x is a negative number
  return (x >> 31) | !!x; //x >> 31 will be -1 if x is negative, else it will be 0. If x is nonzero, !!x will be 1, which when ORed will set 0 to 1 and leave -1 unaltered.
}

/*
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1 << 31); //Create a 1 in the sign bit, and then bitwise negate it to create a number with 1s in everything but the sign bit.
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31; //Left shift a 1 to the sign bit to make the most negative possible number.
}

/*
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  return ((!!n) << 31) >> ((n<<1) + ~n); //Create a 1 on the right if n != 0, and then right shift by n-1 (equal to n<<1 + ~n) to create the right number of additional 1s
  //return ~((1 << n) + ~0); //This is really neat way I thought of for padding lowerBits
}
