/**************************************************************************************************
file:       libJSON_local.h
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Local to the library only functions and types.
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

#if !defined(LIBJSON_LOCAL_RDG)
#define      LIBJSON_LOCAL_RDG

/**************************************************************************************************
constant:
**************************************************************************************************/
#define jsonBUFF_SIZE    32

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
macro:
**************************************************************************************************/
// Yes I realize this will give some devs fits.  I use these macroes to reduce 
// tired programmer mistakes.
#define returnIf(     EXP, VAL)                                if (EXP) { return (VAL);     }
#define return0If(    EXP)                                     if (EXP) { return 0;         }
#define returnFalseIf(EXP)                                     if (EXP) { return jsonFALSE; }
#define returnNullIf( EXP)                                     if (EXP) { return NULL;      }
#define returnTrueIf( EXP)                                     if (EXP) { return jsonTRUE;  }
#define returnVoidIf( EXP)                                     if (EXP) { return;           }
                                                               
#define breakIf(      EXP)                                     if (EXP) { break;            }
#define continueIf(   EXP)                                     if (EXP) { continue;         }
#define gotoIf(       EXP, LBL)                                if (EXP) { goto LBL;         }
                                                               
#define forCount(    VAR, COUNT)                               for ((VAR) = 0;         (VAR) < (COUNT); (VAR)++)
#define forCountDown(VAR, COUNT)                               for ((VAR) = COUNT - 1; (VAR) >= 0;      (VAR)--)

#define loop                                                   for (;;)

#define _JsonMemCreateType(            TYPE)                   (TYPE *) _JsonMemCreate(            sizeof(TYPE))
#define _JsonMemCreateTypeArray(COUNT, TYPE)                   (TYPE *) _JsonMemCreate(  (COUNT) * sizeof(TYPE))
#define _JsonMemClearType(             TYPE, BUF)                       _JsonMemClear(             sizeof(TYPE), (void *) (BUF))
#define _JsonMemClearTypeArray( COUNT, TYPE, BUF)                       _JsonMemClear(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define _JsonMemCopyTypeArray(  COUNT, TYPE, SRC, DST)         memmove((DST), (SRC),     (COUNT) * sizeof(TYPE))
#define _JsonMemCloneType(             TYPE, BUF)              (TYPE *) _JsonMemClone(             sizeof(TYPE), (void *) (BUF))
#define _JsonMemCloneTypeArray( COUNT, TYPE, BUF)              (TYPE *) _JsonMemClone(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define _JsonMemGrowTypeArray(  COUNT, TYPE, P_BUF, ADD_COUNT)          _JsonMemGrow(    (COUNT) * sizeof(TYPE), (void **) (P_BUF), ((ADD_COUNT) + (COUNT)) * sizeof(TYPE))

#define strIsEqual(SA, SB, LEN)                                (strncmp((SA), (SB), (LEN)) == 0)

/**************************************************************************************************
prototype:
**************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

   // Never to be used external to libOMF_C
// Memory functions
void      _JsonMemClear(   size_t const size, void * const buf);
void     *_JsonMemCreate(  size_t const size);
void     *_JsonMemClone(   size_t const size, void * const buf);
void      _JsonMemDestroy( void * const buf);
JsonBool  _JsonMemGrow(    size_t const oldSize, void ** const buffer, size_t const newSize);

#if defined(__cplusplus)
}
#endif

#endif
