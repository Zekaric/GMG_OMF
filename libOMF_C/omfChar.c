/**************************************************************************************************
file:      OmfChar
author:    Robbert de Groot
copyright: 2022, Robbert de Groot

description:
Char routines
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
#include "pch.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfCharClone
**************************************************************************************************/
OmfChar *omfCharClone(OmfChar const * const value)
{
   returnNullIf(!value);

   return _OmfMemCloneTypeArray(omfCharGetSize(value) + 1, OmfChar, value);
}

/**************************************************************************************************
func: omfCharCreateFromWchar
**************************************************************************************************/
OmfChar *omfCharCreateFromWchar(wchar_t const * const value)
{
   OmfCount count;
   OmfChar *ctemp;

   returnNullIf(!value);
   
   // Find the number of bytes needed for the UTF8 string.  count will include
   // the null terminator.
   count = WideCharToMultiByte(CP_UTF8, 0, value, -1, NULL, 0, NULL, NULL);
   returnNullIf(!count);

   // Create the buffer for the new string.
   ctemp = _OmfMemCreateTypeArray(count, OmfChar);
   returnNullIf(!ctemp);

   // Convert the string.
   if (!WideCharToMultiByte(CP_UTF8, 0, value, -1, (LPSTR) ctemp, count, NULL, NULL))
   {
      // Something went wrong.
      _OmfMemDestroy(ctemp);
      return NULL;
   }

   return ctemp;
}

/**************************************************************************************************
func: omfCharDestroy
**************************************************************************************************/
void omfCharDestroy(OmfChar * const value)
{
   _OmfMemDestroy(value);
}

/**************************************************************************************************
func: omfCharGetSize

Get the byte count of the string.  Not necessarily the character length.
**************************************************************************************************/
OmfCount omfCharGetSize(OmfChar const * const value)
{
   OmfIndex index;

   // Find the number of bytes in the string.  Looking for the null terminator.
   forCount(index, UINT32_MAX - 1)
   {
      returnIf(!value[index], index);
   }

   // We didn't hit a null terminator.  Something dodgy is going on if we didn't
   // already crash.
   return 0;
}

/**************************************************************************************************
func: wcharCreateFromOmfChar
**************************************************************************************************/
wchar_t *wcharCreateFromOmfChar(OmfChar const * const value)
{
   OmfCount count;
   wchar_t *ctemp;

   returnNullIf(!value);

   // Find the number of wchar_t chars to use.  count will include the null
   // terminator.
   count = MultiByteToWideChar(CP_UTF8, 0, (LPCCH) value, -1, NULL, 0);
   returnNullIf(!count);
   
   // Create the buffer for the new string.
   ctemp = _OmfMemCreateTypeArray(count, wchar_t);
   returnNullIf(!ctemp);

   // Convert the string.
   if (!MultiByteToWideChar(CP_UTF8, 0, (LPCCH) value, -1, ctemp, count))
   {
      _OmfMemDestroy(ctemp);
      return NULL;
   }
   
   return ctemp;
}
