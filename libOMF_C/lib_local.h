/******************************************************************************
file:       lib_local.h
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Local to the library only functions and types.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/

/******************************************************************************
constant:
******************************************************************************/
#define omfVERSION00_09_00    "OMF-v0.9.0"

/******************************************************************************
type:
******************************************************************************/

/******************************************************************************
variable:
******************************************************************************/

/******************************************************************************
macro:
******************************************************************************/
// Yes I realize this will give some devs fits.  I use these macroes to reduce 
// tired programmer mistakes.
#define returnIf(     EXP, VAL)                    if (EXP) { return (VAL);    }
#define return0If(    EXP)                         if (EXP) { return 0;        }
#define returnFalseIf(EXP)                         if (EXP) { return omfFALSE; }
#define returnNullIf( EXP)                         if (EXP) { return NULL;     }
#define returnTrueIf( EXP)                         if (EXP) { return omfTRUE;  }
#define returnVoidIf( EXP)                         if (EXP) { return;          }
                                                   
#define breakIf(      EXP)                         if (EXP) { break;           }
#define continueIf(   EXP)                         if (EXP) { continue;        }
#define gotoIf(       EXP, LBL)                    if (EXP) { goto LBL;        }
                                                   
#define forCount(    VAR, COUNT)                   for ((VAR) = 0;         (VAR) < (COUNT); (VAR)++)
#define forCountDown(VAR, COUNT)                   for ((VAR) = COUNT - 1; (VAR) >= 0;      (VAR)--)

#define loop                                       for (;;)

#define memCreateType(            TYPE)            (TYPE *) _MemCreate(            sizeof(TYPE))
#define memCreateTypeArray(COUNT, TYPE)            (TYPE *) _MemCreate(  (COUNT) * sizeof(TYPE))
#define memClearType(             TYPE, BUF)                _MemClear(             sizeof(TYPE), (void *) (BUF))
#define memClearTypeArray( COUNT, TYPE, BUF)                _MemClear(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define memCopyTypeArray(  COUNT, TYPE, SRC, DST)  memmove((DST), (SRC), (COUNT) * sizeof(TYPE))
#define memCloneType(             TYPE, BUF)       (TYPE *) _MemClone(             sizeof(TYPE), (void *) (BUF))
#define memCloneTypeArray( COUNT, TYPE, BUF)       (TYPE *) _MemClone(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define memDestroy(       BUF)                     _MemDestroy((BUF))

#define strIsEqual(SA, SB, LEN)                    (strncmp((SA), (SB), (LEN)) == 0)

/******************************************************************************
prototype:
******************************************************************************/
void            _MemClear(  size_t const size, void * const buf);
void           *_MemCreate( size_t const size);
void           *_MemClone(  size_t const size, void * const buf);
void            _MemDestroy(void * const buf);

// Never to be used by clients.
OmfProject     *omfProjectCreate(         void);
OmfBool         omfProjectCreateContent(  OmfProject       * const omfProject);

void            omfProjectDestroy(        OmfProject       * const omfProject);
void            omfProjectDestroyContent( OmfProject       * const omfProject);

