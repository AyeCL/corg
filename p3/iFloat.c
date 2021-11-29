#include <stdio.h>
#include <stdlib.h>
#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 * 
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Aayush Lamichhane</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  int value = x;
  int mask = 0x8000;
  int result = value & mask;
  result = result >> 15;
  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
  int value = x;
  int mask = 0x7F80;
  int result = value & mask;

  // Right shift 7 to get rid of bits that contained mantissa 
  result = result >> 7;
  debug("%s\n", getBinary(result));
  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
  int value = x;
  int mask = 0x00FF;
  int result = value & mask;

  // Make the implicit 1 explicit by setting bit 7 to 1
  result = result | 0x0080;

  // If number is negative, get two's complement
  if (floatGetSign(x) == 1) {
    result = ~result + 1;
  }

  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
  *sign = floatGetSign(x);
  *exp = floatGetExp(x);
  *val = floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
  int number = bits;
  if (floatGetSign(bits) == 1) {
    return 15;
  } else {
    for (int i = 14; i > 0; i--) {
      // debug("FOR LOOP: %i\n", i);

      // debug("Number before: %s\n", getBinary(number));

      number = number >> i;

      // debug("Number is now: %s\n", getBinary(number));
      if (number == 0x1) return i;
      number = bits;
    }
  }
  return -1;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  int value = x;
  int mask = 0x7FFF;
  int result = value & mask;

  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
  if (x != 0) {
    int value = x;
    return value | 0x8000;
  } else return x;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  // debug("%s: bits of x (bfloat16)", getBinary(x)); // example only
  // debug("%s: bits of y (bfloat16)", getBinary(y)); // example only

  int xExp = floatGetExp(x);
  int yExp = floatGetExp(y);

  debug("\t\tx is: %s", getBinary(x));
  debug("\t\ty is: %s", getBinary(y));

  iFloat_t xVal = floatGetVal(x);
  iFloat_t yVal = floatGetVal(y);

  debug("\t\txVal (before equalization): %s", getBinary(xVal));
  debug("\t\tyVal (before equalization): %s", getBinary(yVal));

  // Equalize exponents if not equal.
  int diff;
  int resultExp = xExp;
  int resultSign = 0;
  if (xExp != yExp) {
    if (xExp > yExp) {
      diff = xExp - yExp;
      yVal = yVal >> diff;
      resultExp = xExp;
    } else {
      diff = yExp - xExp;
      xVal = xVal >> diff;
      resultExp = yExp;
    }
  }

  debug("\t\txVal (after equalization): %s", getBinary(xVal));
  debug("\t\tyVal (after equalization): %s", getBinary(yVal));

  // Integer Addition
  int result = xVal + yVal;

  debug("\t\tresult of intAdd: %s", getBinary(result));

  if (floatGetSign(result) == 1) {
    resultSign = 1;
    result = ~result + 1;
  }

  debug("\t\tresult of intAdd: %s", getBinary(result));

  debug("\t\tleftMost1 for result: %d", floatLeftMost1(result));
  debug("\t\texponentResult: %s or %d", getBinary(resultExp), resultExp);


  if (floatLeftMost1(result) < 7) {
    int shift = 7 - floatLeftMost1(result);
    result = result << shift;
    resultExp -= shift;
  }

  debug("\t\tresult: %s", getBinary(result));
  debug("\t\texponentResult: %s or %d", getBinary(resultExp), resultExp);

  // Combine everything into result and return it.
  int mask = 0xFF7F;

  result = result & mask;
  resultExp = resultExp << 7;

  debug("\t\tresult: %s", getBinary(result));
  debug("\t\tresultExp: %s", getBinary(resultExp));

  resultSign = resultSign << 15;

  result = resultSign | (resultExp | result);

  debug("\t\tresult: %s", getBinary(result));

  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
  return 0;
}

