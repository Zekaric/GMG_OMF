/**************************************************************************************************
file:       libOMF_local.h
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

#if !defined(LIBOMF_LOCAL_H_RDG)
#define      LIBOMF_LOCAL_H_RDG

/**************************************************************************************************
include:
**************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define omfVERSION00_09_00    "OMF-v0.9.0"

#define omfArrayTypeINT_TAG   "<i8"
#define omfArrayTypeREAL_TAG  "<f8"

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



#define returnIf(     EXP, VAL)                                if (EXP) { return (VAL);    }
#define return0If(    EXP)                                     if (EXP) { return 0;        }
#define returnFalseIf(EXP)                                     if (EXP) { return omfFALSE; }
#define returnNullIf( EXP)                                     if (EXP) { return NULL;     }
#define returnTrueIf( EXP)                                     if (EXP) { return omfTRUE;  }
#define returnVoidIf( EXP)                                     if (EXP) { return;          }
                                                               
#define breakIf(      EXP)                                     if (EXP) { break;           }
#define continueIf(   EXP)                                     if (EXP) { continue;        }
#define gotoIf(       EXP, LBL)                                if (EXP) { goto LBL;        }
                                                               
#define forCount(    VAR, COUNT)                               for ((VAR) = 0;         (VAR) < (COUNT); (VAR)++)
#define forCountDown(VAR, COUNT)                               for ((VAR) = COUNT - 1; (VAR) >= 0;      (VAR)--)

#define loop                                                   for (;;)

#define _OmfMemCreateType(            TYPE)                    (TYPE *) _OmfMemCreate(            sizeof(TYPE))
#define _OmfMemCreateTypeArray(COUNT, TYPE)                    (TYPE *) _OmfMemCreate(  (COUNT) * sizeof(TYPE))
#define _OmfMemClearType(             TYPE, BUF)                        _OmfMemClear(             sizeof(TYPE), (void *) (BUF))
#define _OmfMemClearTypeArray( COUNT, TYPE, BUF)                        _OmfMemClear(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define _OmfMemCopyTypeArray(  COUNT, TYPE, SRC, DST)          memmove((DST), (SRC),    (COUNT) * sizeof(TYPE))
#define _OmfMemCloneType(             TYPE, BUF)               (TYPE *) _OmfMemClone(             sizeof(TYPE), (void *) (BUF))
#define _OmfMemCloneTypeArray( COUNT, TYPE, BUF)               (TYPE *) _OmfMemClone(   (COUNT) * sizeof(TYPE), (void *) (BUF))
#define _OmfMemGrowTypeArray(  COUNT, TYPE, P_BUF, ADD_COUNT)           _OmfMemGrow(    (COUNT) * sizeof(TYPE), (void **) (P_BUF), ((ADD_COUNT) + (COUNT) * sizeo(TYPE))

#define strIsEqual(SA, SB, LEN)                                (strncmp((SA), (SB), (LEN)) == 0)

/**************************************************************************************************
prototype:
**************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

// Never to be used external to libOMF_C
// Memory functions
void                     _OmfMemClear(                   size_t const size, void * const buf);
void                    *_OmfMemCreate(                  size_t const size);
void                    *_OmfMemClone(                   size_t const size, void * const buf);
void                     _OmfMemDestroy(                 void * const buf);
OmfBool                  _OmfMemGrow(                    size_t const oldSize, void ** const buffer, size_t const newSize);


// Array routines
OmfArray                *_OmfArrayCreate(                                            OmfArrayType const type);
OmfBool                  _OmfArrayCreateContent(         OmfArray * const arrayData, OmfArrayType const type);

void                     _OmfArrayDestroyContent(        OmfArray * const arrayData);


// Data routines
OmfData                 *_OmfDataCreate(                                             OmfDataType const type);
OmfBool                  _OmfDataCreateContent(          OmfData       * const data, OmfDataType const type);

void                     _OmfDataDestroyContent(         OmfData       * const data);


// Element routines
OmfElem                 *_OmfElemCreate(                 OmfElemType type);
                                                                                   
void                     _OmfElemDestroy(                OmfElem       * const elem);
void                     _OmfElemDestroyContent(         OmfElem       * const elem);

// Element Line Set routines
OmfElemLineSet          *_OmfElemLineSetCreate(          void);
OmfBool                  _OmfElemLineSetCreateContent(   OmfElemLineSet * const elem);

void                     _OmfElemLineSetDestroyContent(  OmfElemLineSet * const elem);

// ELement Pnt Set routines
OmfElemPntSet           *_OmfElemPntSetCreate(           void);
OmfBool                  _OmfElemPntSetCreateContent(    OmfElemPntSet * const elem);

void                     _OmfElemPntSetDestroyContent(   OmfElemPntSet * const elem);

// Element Surf Grid routines
OmfElemSurfGrid         *_OmfElemSurfGridCreate(         void);
OmfBool                  _OmfElemSurfGridCreateContent(  OmfElemSurfGrid * const elem);

void                     _OmfElemSurfGridDestroyContent( OmfElemSurfGrid * const elem);

// Element Surf Tri routines
OmfElemSurfTri          *_OmfElemSurfTriCreate(          void);
OmfBool                  _OmfElemSurfTriCreateContent(   OmfElemSurfTri * const elem);

void                     _OmfElemSurfTriDestroyContent(  OmfElemSurfTri * const elem);

// Element Vol routines
OmfElemVol              *_OmfElemVolCreate(              void);
OmfBool                  _OmfElemVolCreateContent(       OmfElemVol * const elem);

void                     _OmfElemVolDestroyContent(      OmfElemVol * const elem);



// Geometry routines
OmfGeom                 *_OmfGeomCreate(                 OmfElemType const type);
                                                                                                     
void                     _OmfGeomDestroy(                OmfGeom       * const geom);
void                     _OmfGeomDestroyContent(         OmfGeom       * const geom);

// Geometry Pnt Set routines
OmfGeomLineSet          *_OmfGeomLineSetCreate(          void);
OmfBool                  _OmfGeomLineSetCreateContent(   OmfGeomLineSet * const geom);

void                     _OmfGeomLineSetDestroyContent(  OmfGeomLineSet * const geom);

// Geometry Pnt Set routines
OmfGeomPntSet           *_OmfGeomPntSetCreate(           void);
OmfBool                  _OmfGeomPntSetCreateContent(    OmfGeomPntSet * const geom);

void                     _OmfGeomPntSetDestroyContent(   OmfGeomPntSet * const geom);

// Geometry Surf Grid routines
OmfGeomSurfGrid         *_OmfGeomSurfGridCreate(         void);
OmfBool                  _OmfGeomSurfGridCreateContent(  OmfGeomSurfGrid * const geom);

void                     _OmfGeomSurfGridDestroyContent( OmfGeomSurfGrid * const geom);

// Geometry Surf Tri routines
OmfGeomSurfTri          *_OmfGeomSurfTriCreate(          void);
OmfBool                  _OmfGeomSurfTriCreateContent(   OmfGeomSurfTri * const geom);

void                     _OmfGeomSurfTriDestroyContent(  OmfGeomSurfTri * const geom);

// Geometry Vol routines
OmfGeomVol              *_OmfGeomVolCreate(              void);
OmfBool                  _OmfGeomVolCreateContent(       OmfGeomVol * const geom);

void                     _OmfGeomVolDestroyContent(      OmfGeomVol * const geom);



// Object routines
void                     _OmfObjDestroyContent(          OmfObj * const object);


// Project routines
OmfProj                 *_OmfProjCreate(                 void);
OmfBool                  _OmfProjCreateContent(          OmfProj * const project);

void                     _OmfProjDestroyContent(         OmfProj * const project);

#if defined(__cplusplus)
}
#endif

#endif
