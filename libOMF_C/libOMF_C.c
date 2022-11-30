/**************************************************************************************************
file:       libOMF_C
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
API for reading and writing OMF files.
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
static OmfBool _isStarted                                         = omfFALSE;

static void  (*_memClear)(   void * const buf, size_t const size) = NULL;
static void *(*_memCreate)(  size_t const size)                   = NULL;
static void  (*_memDestroy)( void * const buf)                    = NULL;

/**************************************************************************************************
macro:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
glboal:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfIsStarted
**************************************************************************************************/
OmfBool omfIsStarted(void)
{
   return _isStarted;
}

/**************************************************************************************************
func: omfStart

Start up the library routines and initialize whatever needs initializing.
**************************************************************************************************/
OmfError omfStart(void *(*memCreate)(size_t const size), void (*memDestroy)(void * const buffer), 
   void (*memClear)(void * const buffer, size_t const size))
{
   if (_isStarted)
   {
      assert(omfFALSE && "This function should not be called twice.");
      return omfErrorNONE;
   }

   returnIf(
         !memClear  ||
         !memCreate ||
         !memDestroy,
      omfErrorPARAMETER_BAD);

   _memClear   = memClear;
   _memCreate  = memCreate;
   _memDestroy = memDestroy;

   _isStarted = omfTRUE;

   return omfErrorNONE;
}

/**************************************************************************************************
func: omfStop

Reset the library.
**************************************************************************************************/
void omfStop(void)
{
   _memClear   = NULL;
   _memCreate  = NULL;
   _memDestroy = NULL;

   _isStarted  = omfFALSE;
}

/**************************************************************************************************
lib local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _MemClear
**************************************************************************************************/
void _OmfMemClear(size_t const size, void * const buf)
{
   _memClear(buf, size);
}

/**************************************************************************************************
func: _MemCreate
**************************************************************************************************/
void *_OmfMemCreate(size_t const size)
{
   returnNullIf(!size);

   return _memCreate(size);
}

/**************************************************************************************************
func: _MemClone
**************************************************************************************************/
void *_OmfMemClone(size_t const size, void * const buf)
{
   void *dst;

   returnNullIf(!buf || !size);

   dst = _memCreate(size);
   returnNullIf(!dst);

   memmove(dst, buf, size);

   return dst;
}

/**************************************************************************************************
func: _OmfMemDestroy
**************************************************************************************************/
void _OmfMemDestroy(void * const buf)
{
   _memDestroy(buf);
}

/**************************************************************************************************
func: _OmfMemGrow
**************************************************************************************************/
OmfBool _OmfMemGrow(size_t const oldSize, void ** const buffer, size_t const newSize)
{
   void *vtemp;

   // Create a new buffer.
   vtemp = _memCreate(newSize);
   returnIf(!vtemp, omfFALSE);

   // Copy the data from the source buffer.
   memmove(vtemp, *buffer, oldSize);

   // Clean up the old stack.
   _memDestroy(*buffer);

   // Set to the new stack.
   *buffer = vtemp;

   return omfTRUE;
}
