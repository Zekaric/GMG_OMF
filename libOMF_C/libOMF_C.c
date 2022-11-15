/******************************************************************************
file:       libOMF_C
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
API for reading and writing OMF files.
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
static OmfBool _isStarted                                         = omfFALSE;

static void  (*_memClear)(   void * const buf, size_t const size) = NULL;
static void *(*_memCreate)(  size_t const size)                   = NULL;
static void  (*_memDestroy)( void * const buf)                    = NULL;

/******************************************************************************
macro:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
glboal:
function:
******************************************************************************/
/******************************************************************************
func: omfIsStarted
******************************************************************************/
OmfBool omfIsStarted(void)
{
   return _isStarted;
}

/******************************************************************************
func: omfStart

Start up the library routines and initialize whatever needs initializing.
******************************************************************************/
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

/******************************************************************************
func: omfStop

Reset the library.
******************************************************************************/
void omfStop(void)
{
   _memClear   = NULL;
   _memCreate  = NULL;
   _memDestroy = NULL;

   _isStarted  = omfFALSE;
}

/******************************************************************************
lib local:
function:
******************************************************************************/
/******************************************************************************
func: _MemClear
******************************************************************************/
void _MemClear(size_t const size, void * const buf)
{
   _memClear(buf, size);
}

/******************************************************************************
func: _MemCreate
******************************************************************************/
void *_MemCreate(size_t const size)
{
   returnNullIf(!size);

   return _memCreate(size);
}

/******************************************************************************
func: _MemClone
******************************************************************************/
void *_MemClone(size_t const size, void * const buf)
{
   void *dst;

   returnNullIf(!buf || !size);

   dst = _MemCreate(size);
   returnNullIf(!dst);

   memmove(dst, buf, size);

   return dst;
}

/******************************************************************************
func: _MemDestroy
******************************************************************************/
void _MemDestroy(void * const buf)
{
   _memDestroy(buf);
}
