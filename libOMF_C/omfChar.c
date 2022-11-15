/******************************************************************************
file: OmfChar
author: Robbert de Groot
copyright: 2022, Robbert de Groot

description:
Char routines
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pch.h"

/******************************************************************************
local:
constant:
******************************************************************************/

/******************************************************************************
type:
******************************************************************************/

/******************************************************************************
variable:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: omfCharClone
******************************************************************************/
OmfChar *omfCharClone(OmfChar const * const value)
{
   returnNullIf(!value);

   return memCloneTypeArray(omfCharGetSize(value) + 1, OmfChar, value);
}

/******************************************************************************
func: omfCharCreateFromWchar
******************************************************************************/
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
   ctemp = memCreateTypeArray(count, OmfChar);
   returnNullIf(!ctemp);

   // Convert the string.
   if (!WideCharToMultiByte(CP_UTF8, 0, value, -1, (LPSTR) ctemp, count, NULL, NULL))
   {
      // Something went wrong.
      memDestroy(ctemp);
      return NULL;
   }

   return ctemp;
}

/******************************************************************************
func: omfCharGetSize

Get the byte count of the string.  Not necessarily the character length.
******************************************************************************/
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

/******************************************************************************
func: wcharCreateFromOmfChar
******************************************************************************/
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
   ctemp = memCreateTypeArray(count, wchar_t);
   returnNullIf(!ctemp);

   // Convert the string.
   if (!MultiByteToWideChar(CP_UTF8, 0, (LPCCH) value, -1, ctemp, count))
   {
      memDestroy(ctemp);
      return NULL;
   }
   
   return ctemp;
}
