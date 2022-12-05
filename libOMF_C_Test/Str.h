/**************************************************************************************************
file:       Str
author:     Robbert de Groot
company:    Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Simple dynamic string routines.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) !!!!YEAR!!!!, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT 
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

#pragma once

/**************************************************************************************************
include:
**************************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************************************************
constant:
**************************************************************************************************/
#define strCHUNK 32

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   int    length,
          size,
          index;
   char  *buffer;
} Str;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

bool   strAppend(       Str * const s, char const * const js);
Str   *strCreate(       size_t const reserve);
void   strDestroy(      Str * const s);
bool   strGrow(         Str * const s, size_t const count);
char   strPosGetLetter( Str * const s);
void   strPosNext(      Str * const s);
void   strPosReset(     Str * const s);

#if defined(__cplusplus)
}
#endif
