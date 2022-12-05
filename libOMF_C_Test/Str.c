/**************************************************************************************************
file:       Str
author:     Robbert de Groot
company:    Robbert de Grootcopyright:  2022, Robbert de Groot

description:
Simple dynamic string for testing purposes.
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "Str.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: strAppend
**************************************************************************************************/
bool strAppend(Str * const s, char const * const js)
{
   int index,
       count;

   if (!s ||
       !js)
   {
      return false;
   }

   count = (int) strlen(js);
   strGrow(s, count);
   
   for (index = 0; index < count; index++)
   {
      s->buffer[s->length + index] = js[index];
   }
   s->length += count;

   return true;
}

/**************************************************************************************************
func: strCreate
**************************************************************************************************/
Str *strCreate(size_t const reserve)
{
   Str *s;

   s = (Str *) calloc(1, sizeof(Str));
   if (!s)
   {
      return false;
   }

   s->length = 0;
   s->size   = 0;
   strGrow(s, reserve);

   return s;
}

/**************************************************************************************************
func: strDestroy
**************************************************************************************************/
void strDestroy(Str * const s)
{
   if (!s)
   {
      return;
   }

   free(s->buffer);

   s->length = 0;
   s->size   = 0;

   free(s);
}

/**************************************************************************************************
func: strGrow
**************************************************************************************************/
bool strGrow(Str * const s, size_t const count)
{
   char *stemp;

   if (s->length + count < s->size)
   {
      return true;
   }

   // What size should be our string.
   while (s->size < s->length + count + 1)
   {
      s->size += strCHUNK;
   }

   stemp = (char *) calloc(s->size, sizeof(char));
   if (!stemp)
   {
      return false;
   }

   memcpy(stemp, s->buffer, s->length);

   free(s->buffer);

   s->buffer = stemp;

   return true;
}

/**************************************************************************************************
func: strPosGetLetter
**************************************************************************************************/
char strPosGetLetter(Str * const s)
{
   if (!s ||
       s->index == s->length)
   {
      return 0;
   }

   return s->buffer[s->index];
}

/**************************************************************************************************
func: strPosNext
**************************************************************************************************/
void strPosNext(Str * const s)
{
   if (!s)
   {
      return;
   }

   s->index++;
}

/**************************************************************************************************
func: strPosReset
**************************************************************************************************/
void strPosReset(Str * const s)
{
   if (!s)
   {
      return;
   }

   s->index = 0;
}
