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
// Never to be used external to libOMF_C
// Memory functions
void                     _MemClear(                            size_t const size, void * const buf);
void                    *_MemCreate(                           size_t const size);
void                    *_MemClone(                            size_t const size, void * const buf);
void                     _MemDestroy(                          void * const buf);



// Element routines
void                     _OmfElementDestroyContent(            OmfElement       * const omfElement);

// Element Line Set routines
OmfElementLineSet       *_OmfElementLineSetCreate(             void);
OmfBool                  _OmfElementLineSetCreateContent(      OmfElementLineSet * const omfElementLineSet);

void                     _OmfElementLineSetDestroyContent(     OmfElementLineSet * const omfElementLineSet);

// ELement Point Set routines
OmfElementPointSet      *_OmfElementPointSetCreate(            void);
OmfBool                  _OmfElementPointSetCreateContent(     OmfElementPointSet * const omfElementPointSet);

void                     _OmfElementPointSetDestroyContent(    OmfElementPointSet * const omfElementPointSet);

// Element Surface Grid routines
OmfElementSurfaceGrid   *_OmfElementSurfaceGridCreate(         void);
OmfBool                  _OmfElementSurfaceGridCreateContent(  OmfElementSurfaceGrid * const omfElementSurfaceGrid);

void                     _OmfElementSurfaceGridDestroyContent( OmfElementSurfaceGrid * const omfElementSurfaceGrid);

// Element Surface Tri routines
OmfElementSurfaceTri    *_OmfElementSurfaceTriCreate(          void);
OmfBool                  _OmfElementSurfaceTriCreateContent(   OmfElementSurfaceTri * const omfElementSurfaceTri);

void                     _OmfElementSurfaceTriDestroyContent(  OmfElementSurfaceTri * const omfElementSurfaceTri);

// Element Volume routines
OmfElementVolume        *_OmfElementVolumeCreate(              void);
OmfBool                  _OmfElementVolumeCreateContent(       OmfElementVolume * const omfElementVolume);

void                     _OmfElementVolumeDestroyContent(      OmfElementVolume * const omfElementVolume);



// Geometry routines
void                     _OmfGeometryDestroyContent(           OmfGeometry * const omfGeometry);

// Geometry Point Set routines
OmfGeometryLineSet      *_OmfGeometryLineSetCreate(            void);
OmfBool                  _OmfGeometryLineSetCreateContent(     OmfGeometryLineSet * const omfGeometryPointSet  );

void                     _OmfGeometryLineSetDestroyContent(    OmfGeometryLineSet * const omfGeometryPointSet);

// Geometry Point Set routines
OmfGeometryPointSet     *_OmfGeometryPointSetCreate(           void);
OmfBool                  _OmfGeometryPointSetCreateContent(    OmfGeometryPointSet * const omfGeometryPointSet);

void                     _OmfGeometryPointSetDestroyContent(   OmfGeometryPointSet * const omfGeometryPointSet);

// Geometry Surface Grid routines
OmfGeometrySurfaceGrid  *_OmfGeometrySurfaceGridCreate(        void);
OmfBool                  _OmfGeometrySurfaceGridCreateContent( OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid);

void                     _OmfGeometrySurfaceGridDestroyContent(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid);

// Geometry Surface Tri routines
OmfGeometrySurfaceTri   *_OmfGeometrySurfaceTriCreate(         void);
OmfBool                  _OmfGeometrySurfaceTriCreateContent(  OmfGeometrySurfaceTri * const omfGeometrySurfaceTri);

void                     _OmfGeometrySurfaceTriDestroyContent( OmfGeometrySurfaceTri * const omfGeometrySurfaceTri);

// Geometry Volume routines
OmfGeometryVolume       *_OmfGeometryVolumeCreate(             void);
OmfBool                  _OmfGeometryVolumeCreateContent(      OmfGeometryVolume * const omfGeometryVolume);

void                     _OmfGeometryVolumeDestroyContent(     OmfGeometryVolume * const omfGeometryVolume);



// Project routines
OmfBool                  _OmfProjectCreateContent(             OmfProject * const omfProject);

void                     _OmfProjectDestroyContent(            OmfProject * const omfProject);