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

#if !defined(LIB_OMF_C_RDG)
#define      LIB_OMF_C_RDG

/**************************************************************************************************
include:
**************************************************************************************************/
// add headers that you want to pre-compile here
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <assert.h>
#include <guiddef.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// miniz is a smaller (file count) implementation of the compression and zip archive handling
// proj can be found here  https://github.com/richgel999/miniz
// As indicated on usage for that proj, we are just including the source in the proj 
// directly.
// 
// For deflate and inflate
#include "miniz.h"

#include "libJSON_C.h"

/**************************************************************************************************
constant:
**************************************************************************************************/
#define libOMF_C_VERSION      1

#define omfFALSE              false
#define omfTRUE               true

/**************************************************************************************************
type:

Structures should NEVER be accessed directly.  Use any and all API to access
the contents of the structure.  This
**************************************************************************************************/
typedef enum
{
   omfArrayTypeNONE,
   omfArrayTypeCOLOR,
   omfArrayTypeDATE_TIME,
   omfArrayTypeINT,
   omfArrayTypeINT2,
   omfArrayTypeINT3,
   omfArrayTypeREAL,
   omfArrayTypeREAL2,
   omfArrayTypeREAL3,
   omfArrayTypeSTRING
} OmfArrayType;

typedef enum
{
   omfDataTypeNONE,
   omfDataTypeCOLOR,
   omfDataTypeDATE_TIME,
   omfDataTypeDATE_TIME_COLORMAP,
   omfDataTypeLEGEND,
   omfDataTypeMAPPED,
   omfDataTypeSCALAR,
   omfDataTypeSCALAR_COLORMAP,
   omfDataTypeSTRING,
   omfDataTypeVECTOR2,
   omfDataTypeVECTOR3
} OmfDataType;

typedef enum
{
   omfDataLocNONE,
   omfDataLocCELL,
   omfDataLocFACE,
   omfDataLocSEGMENT,
   omfDataLocVERTEX
} OmfDataLoc;

typedef enum
{
   // v1
   omfElemTypeNONE,

   omfElemTypeLINE_SET,
   omfElemTypePNT_SET,
   omfElemTypeSURF_GRID,
   omfElemTypeSURF_TRI,
   omfElemTypeVOL

   // v2
} OmfElemType;

typedef enum
{
   // v1
   omfElemSubTypeNONE,

   omfElemSubTypeLINE_SET_LINE_DEFAULT,
   omfElemSubTypeLINE_SET_BOREHOLE,

   omfElemSubTypePNT_SET_POINT_DEFAULT,
   omfElemSubTypePNT_SET_COLLAR,
   omfElemSubTypePNT_SET_BLASTHOLE,

   omfElemSubTypeSURF_GRID_SURFACE_DEFAULT,

   omfElemSubTypeSURF_TRI_SURFACE_DEFAULT,

   omfElemSubTypeVOL_VOLUME_DEFAULT

   // v2
} OmfElemSubType;

typedef enum
{
   // v1
   omfErrorNONE,
   omfErrorFILE_CREATE_FAILURE,
   omfErrorFILE_NOT_OMF,
   omfErrorFILE_OPEN_FAILURE,
   omfErrorFILE_WRITE_FAILURE,
   omfErrorLIB_NOT_STARTED,
   omfErrorMEM_CREATE_FAILURE,
   omfErrorPARAMETER_BAD

   // v2
} OmfError;

typedef enum
{
   // v1
   omfFileVersionNONE,

   omfFileVersion00_09,
   omfFileVersion01_00,
   omfFileVersion02_00

   // v2
} OmfFileVersion;

typedef enum
{
   // v1
   omfObjTypeNONE,

   omfObjTypeARRAY                     = 0x10000000,
   omfObjTypeARRAY_COLOR,
   omfObjTypeARRAY_DATE_TIME,
   omfObjTypeARRAY_INT,
   omfObjTypeARRAY_INT2,
   omfObjTypeARRAY_INT3,
   omfObjTypeARRAY_REAL,
   omfObjTypeARRAY_REAL2,
   omfObjTypeARRAY_REAL3,
   omfObjTypeARRAY_STRING,

   omfObjTypeDATA                      = 0x20000000,
   omfObjTypeDATA_COLOR,
   omfObjTypeDATA_DATE_TIME,
   omfObjTypeDATA_DATE_TIME_COLORMAP,
   omfObjTypeDATA_LEGEND,
   omfObjTypeDATA_MAPPED,
   omfObjTypeDATA_SCALAR,
   omfObjTypeDATA_SCALAR_COLORMAP,
   omfObjTypeDATA_STRING,
   omfObjTypeDATA_VECTOR2,
   omfObjTypeDATA_VECTOR3,
   
   omfObjTypeELEM                      = 0x40000000,
   omfObjTypeELEM_PNT_SET,
   omfObjTypeELEM_LINE_SET,
   omfObjTypeELEM_SURF_GRID,
   omfObjTypeELEM_SURF_TRI,
   omfObjTypeELEM_VOL,
   
   omfObjTypeGEOM                      = 0x80000000,
   omfObjTypeGEOM_PNT_SET,
   omfObjTypeGEOM_LINE_SET,
   omfObjTypeGEOM_SURF_GRID,
   omfObjTypeGEOM_SURF_TRI,
   omfObjTypeGEOM_VOL,
   
   omfObjTypeMODEL                     = 0x01000000,
   omfObjTypeMODEL_CONTENT,
   omfObjTypeMODEL_ID,
   
   omfObjTypePROJ                      = 0x02000000,
   omfObjTypePROJ_ELEMENT,
   omfObjTypePROJ_ELEMENT_DATA,

   omfObjTypeTEXTURE                   = 0x04000000,

   // v2
} OmfObjType;

typedef unsigned char                  uchar;

typedef bool                           OmfBool;
typedef uchar                          OmfChar;
typedef uint32_t                       OmfCount;
typedef struct OmfColor                OmfColor;
typedef uchar                          OmfColorValue;
typedef struct OmfCoord                OmfCoord;
typedef struct OmfArray                OmfArray;
typedef struct OmfData                 OmfData;
typedef struct OmfDataList             OmfDataList;
typedef struct OmfElem                 OmfElem;
typedef struct OmfElemLineSet          OmfElemLineSet;
typedef struct OmfElemPntSet           OmfElemPntSet;
typedef struct OmfElemSurfGrid         OmfElemSurfGrid;
typedef struct OmfElemSurfTri          OmfElemSurfTri;
typedef struct OmfElemVol              OmfElemVol;
typedef struct OmfFile                 OmfFile;
typedef struct OmfFile00_09            OmfFile00_09;
typedef struct OmfFile01_00            OmfFile01_00;
typedef struct OmfFile02_00            OmfFile02_00;
typedef struct OmfGeom                 OmfGeom;
typedef struct OmfGeomLineSet          OmfGeomLineSet;
typedef struct OmfGeomPntSet           OmfGeomPntSet;
typedef struct OmfGeomSurfGrid         OmfGeomSurfGrid;
typedef struct OmfGeomSurfTri          OmfGeomSurfTri;
typedef struct OmfGeomVol              OmfGeomVol;
typedef GUID                           OmfId;
typedef uint32_t                       OmfIndex;
typedef struct OmfList                 OmfList;
typedef struct OmfListItem             OmfListItem;
typedef struct OmfListIter             OmfListIter;
typedef struct OmfObj                  OmfObj;
typedef uint64_t                       OmfOffset;
typedef struct OmfProj                 OmfProj;
typedef struct OmfTexture              OmfTexture;
typedef struct OmfTextureList          OmfTextureList;
typedef struct OmfTextureUV            OmfTextureUV;
typedef struct OmfVector               OmfVector;

struct OmfObj
{
// This is a form of old style object oriented class and sub classing.
// Type casting is used to obtain the proper structure.
#define OMF_OBJECT_VARS                                                                            \
   OmfObjType                  typeObj;                                                            \
   OmfId                       id;                                                                 \
   OmfChar                    *dateCreated;                                                        \
   OmfChar                    *dateModified;

   OMF_OBJECT_VARS
};

struct OmfList
{
   OmfCount                    count;
   OmfListItem                *head,
                              *tail;
};

struct OmfListItem
{
   OmfListItem                *next;
   OmfObj                     *obj;
};

struct OmfListIter
{
   OmfList const              *list;
   OmfListItem                *curr;
};

struct OmfArray
{
   // Must be first.
   OMF_OBJECT_VARS

   // Required
   OmfOffset                   bufferOffset;
   OmfCount                    bufferSize;
   OmfArrayType                bufferType;
   OmfCount                    bufferTypeCount;
};

struct OmfColor
{
   OmfColorValue               r,
                               g,
                               b;
};

// Going with e)ast, n)orth, and z (elevation) to avoid abiguity.  Often software is using x, y, z to 
// represent this but in some case, because of rendering engines, y is elevation and z is north.
struct OmfCoord
{
   double                      e,
                               n,
                               z;
};

struct OmfVector
{
   double                      e,
                               n,
                               z;
};

struct OmfData
{
#define OMF_DATA_VARS                                                                              \
   OMF_OBJECT_VARS                                                                                 \
                                                                                                   \
   OmfDataType                 typeData;                                                           \
   OmfDataLoc                  location;                                                           \
   OmfArray                   *array;                                                              \
   OmfChar                    *description;                                                        \
   OmfChar                    *name;

   OMF_DATA_VARS
};

struct OmfElem
{
#define OMF_ELEMENT_VARS                                                                           \
   OMF_OBJECT_VARS                                                                                 \
                                                                                                   \
   OmfElemType                 typeElem;                                                           \
   OmfElemSubType              typeElemSub;                                                        \
   OmfColor                    color;                                                              \
   OmfChar                    *description;                                                        \
   OmfChar                    *name;                                                               \
                                                                                                   \
   OmfBool                     isDataListSet;                                                      \
                                                                                                   \
   OmfDataList                *dataList;

   OMF_ELEMENT_VARS
};

struct OmfElemLineSet
{
#define OMF_ELEMENT_LINE_SET_VARS                                                                  \
   OMF_ELEMENT_VARS                                                                                \
                                                                                                   \
   OmfGeomLineSet             *geometry;

   OMF_ELEMENT_LINE_SET_VARS
};

struct OmfElemPntSet
{
#define OMF_ELEMENT_PNT_SET_VARS                                                                   \
   OMF_ELEMENT_VARS                                                                                \
                                                                                                   \
   OmfGeomPntSet              *geometry;                                                           \
                                                                                                   \
   OmfBool                     isTextureListSet;                                                   \
   OmfTextureList             *textureList;

   OMF_ELEMENT_PNT_SET_VARS
};

struct OmfElemSurfGrid
{
#define OMF_ELEMENT_SURF_GRID_VARS                                                                 \
   OMF_ELEMENT_VARS                                                                                \
                                                                                                   \
   OmfGeomSurfGrid            *geometry;                                                           \
                                                                                                   \
   OmfBool                     isTextureListSet;                                                   \
   OmfTextureList             *textureList;

   OMF_ELEMENT_SURF_GRID_VARS
};

struct OmfElemSurfTri
{
#define OMF_ELEMENT_SURF_TRI_VARS                                                                  \
   OMF_ELEMENT_VARS                                                                                \
                                                                                                   \
   OmfGeomSurfTri             *geometry;                                                           \
                                                                                                   \
   OmfBool                     isTextureListSet;                                                   \
   OmfTextureList             *textureList;

   OMF_ELEMENT_SURF_TRI_VARS
};

struct OmfElemVol
{
#define OMF_ELEMENT_VOL_VARS                                                                       \
   OMF_ELEMENT_VARS                                                                                \
                                                                                                   \
   OmfGeomVol                 *geometry;                                                           \

   OMF_ELEMENT_VOL_VARS
};

struct OmfProj
{
#define OMF_PROJ_VARS                                                                              \
   OMF_OBJECT_VARS                                                                                 \
                                                                                                   \
   OmfChar                    *author;                                                             \
   OmfChar                    *description;                                                        \
   OmfChar                    *name;                                                               \
   OmfCoord                    origin;                                                             \
   OmfChar                    *revision;                                                           \
   OmfChar                    *units;                                                              \
   OmfList                    *elemList;                                                           \
                                                                                                   \
   OmfBool                     isDateSet;                                                          \
   OmfChar                    *date;

   OMF_PROJ_VARS
};

struct OmfFile
{
   OmfBool                     isWriting;
   OmfFileVersion              version;
   OmfProj                    *proj;

   // v00_09
   FILE                       *file;
   OmfOffset                   offsetTableOfContents;
   OmfId                       idProject;
   OmfChar                    *jsonTableOfContents;

   // v01_00+
   void                       *fileZip;
};

struct OmfGeom
{
#define OMF_GEOMETRY_VARS                                                                          \
   OMF_OBJECT_VARS                                                                                 \
                                                                                                   \
   OmfElemType                 typeElem;                                                           \
   OmfCoord                    origin;

   OMF_GEOMETRY_VARS
};

struct OmfGeomLineSet
{
#define OMF_GEOMETRY_LINE_SET_VARS                                                                 \
   OMF_GEOMETRY_VARS                                                                               \
                                                                                                   \
   OmfArray                   *coord;                                                              \
   OmfArray                   *segment;

   OMF_GEOMETRY_LINE_SET_VARS
};

struct OmfGeomPntSet
{
#define OMF_GEOMETRY_PNT_SET_VARS                                                                  \
   OMF_GEOMETRY_VARS                                                                               \
                                                                                                   \
   OmfArray                   *coord;

   OMF_GEOMETRY_PNT_SET_VARS
};

struct OmfGeomSurfGrid
{
#define OMF_GEOMETRY_SURF_GRID_VARS                                                                \
   OMF_GEOMETRY_VARS                                                                               \
                                                                                                   \
   OmfVector                   axisU;                                                              \
   OmfVector                   axisV;                                                              \
   OmfArray                   *tensorU;                                                            \
   OmfArray                   *tensorV;                                                            \
                                                                                                   \
   OmfBool                     isOffsetSet;                                                        \
   OmfArray                   *offset;

   OMF_GEOMETRY_SURF_GRID_VARS
};

struct OmfGeomSurfTri
{
#define OMF_GEOMETRY_SURF_TRI_VARS                                                                 \
   OMF_GEOMETRY_VARS                                                                               \
                                                                                                   \
   OmfArray                   *coord;                                                              \
   OmfArray                   *triangle;

   OMF_GEOMETRY_SURF_TRI_VARS
};

struct OmfGeomVol
{
#define OMF_GEOMETRY_VOL_VARS                                                                      \
   OMF_GEOMETRY_VARS                                                                               \
                                                                                                   \
   OmfVector                   axisU;                                                              \
   OmfVector                   axisV;                                                              \
   OmfVector                   axisW;                                                              \
   OmfArray                   *tensorU;                                                            \
   OmfArray                   *tensorV;                                                            \
   OmfArray                   *tensorW;

   OMF_GEOMETRY_VOL_VARS
};

struct OmfTexture
{
#define OMF_TEXTURE_VARS                                                                           \
   OMF_OBJECT_VARS                                                                                 \
                                                                                                   \
   OmfVector                   axisU;                                                              \
   OmfVector                   axisV;                                                              \
   OmfChar                    *description;                                                        \
   OmfChar                    *pngImage;                                                           \
   OmfChar                    *name;                                                               \
   OmfVector                   origin;

   OMF_TEXTURE_VARS
};

/**************************************************************************************************
variable:
**************************************************************************************************/


/**************************************************************************************************
macro:
**************************************************************************************************/
#define omfObjFromObj(                       OBJ)           ((OmfObj *)          (OBJ))

#define omfArrayFromObj(                     OBJ)           ((OmfArray *)        (((omfObjGetType(OBJ) & omfObjTypeARRAY) == omfObjTypeARRAY)     ? (OBJ) : NULL))
#define omfDataFromObj(                      OBJ)           ((OmfData *)         (((omfObjGetType(OBJ) & omfObjTypeDATA)  == omfObjTypeDATA)      ? (OBJ) : NULL))
#define omfElemFromObj(                      OBJ)           ((OmfElem *)         (((omfObjGetType(OBJ) & omfObjTypeELEM)  == omfObjTypeELEM)      ? (OBJ) : NULL))
#define omfElemLineSetFromObj(               OBJ)           ((OmfElemLineSet *)  ( (omfObjGetType(OBJ) == omfObjTypeLINE_SET)                     ? (OBJ) : NULL))
#define omfElemPntSetFromObj(                OBJ)           ((OmfElemPntSet *)   ( (omfObjGetType(OBJ) == omfObjTypePNT_SET)                      ? (OBJ) : NULL))
#define omfElemSurfGridFromObj(              OBJ)           ((OmfElemSurfGrid *) ( (omfObjGetType(OBJ) == omfObjTypeSURF_GRID)                    ? (OBJ) : NULL))
#define omfElemSurfTriFromObj(               OBJ)           ((OmfElemSurfTri *)  ( (omfObjGetType(OBJ) == omfObjTypeSURF_TRI)                     ? (OBJ) : NULL))
#define omfElemVolFromObj(                   OBJ)           ((OmfElemVol *)      ( (omfObjGetType(OBJ) == omfObjTypeVOL)                          ? (OBJ) : NULL))
#define omfGeomFromObj(                      OBJ)           ((OmfGeom *)         (((omfObjGetType(OBJ) & omfObjTypeGEOM)  == omfObjTypeGEOM)      ? (OBJ) : NULL))
#define omfGeomLineSetFromObj(               OBJ)           ((OmfGeomLineSet  *) ( (omfObjGetType(OBJ) == omfObjTypeLINE_SET)                     ? (OBJ) : NULL))
#define omfGeomPntSetFromObj(                OBJ)           ((OmfGeomPntSet *)   ( (omfObjGetType(OBJ) == omfObjTypePNT_SET)                      ? (OBJ) : NULL))
#define omfGeomSurfGridFromObj(              OBJ)           ((OmfGeomSurfGrid *) ( (omfObjGetType(OBJ) == omfObjTypeSURF_GRID)                    ? (OBJ) : NULL))
#define omfGeomSurfTriFromObj(               OBJ)           ((OmfGeomSurfTri *)  ( (omfObjGetType(OBJ) == omfObjTypeSURF_TRI)                     ? (OBJ) : NULL))
#define omfGeomVolFromObj(                   OBJ)           ((OmfGeomVol *)      ( (omfObjGetType(OBJ) == omfObjTypeVOL)                          ? (OBJ) : NULL))
#define omfProjFromObj(                      OBJ)           ((OmfProj *)         ( (omfObjGetType(OBJ) == omfObjTypePROJ)                         ? (OBJ) : NULL))
#define omfTextureFromObj(                   OBJ)           ((OmfTexture *)      ( (omfObjGetType(OBJ) == omfObjTypeTEXTURE)                      ? (OBJ) : NULL))

#define omfObjGetObjType(                    OBJ)           (((OBJ) != NULL) ? (OBJ)->typeObj : omfObjTypeNONE)

#define omfObjDestroyObj(                    OBJ)           omfObjDestroy(                   omfObjFromObj(          OBJ))
#define omfObjGetObjDateCreated(             OBJ)           omfObjGetDateCreated(            omfObjFromObj(          OBJ))
#define omfObjGetObjDateModified(            OBJ)           omfObjGetDateModified(           omfObjFromObj(          OBJ))
#define omfObjGetObjId(                      OBJ)           omfObjGetId(                     omfObjFromObj(          OBJ))
#define omfObjSetObjDateCreated(             OBJ, VAL)      omfObjSetDateCreated(            omfObjFromObj(          OBJ), (VAL))
#define omfObjSetObjDateModified(            OBJ, VAL)      omfObjSetDateModified(           omfObjFromObj(          OBJ), (VAL))
#define omfObjSetObjId(                      OBJ, VAL)      omfObjSetId(                     omfObjFromObj(          OBJ), (VAL))

#define omfObjGetArrayBufferOffset(          OBJ)           omfArrayGetBufferOffset(         omfArrayFromObj(        OBJ))
#define omfObjGetArrayBufferSize(            OBJ)           omfArrayGetBufferSize(           omfArrayFromObj(        OBJ))
#define omfObjGetArrayBufferType(            OBJ)           omfArrayGetBufferType(           omfArrayFromObj(        OBJ))
#define omfObjGetArrayBufferTypeCount(       OBJ)           omfArrayGetBufferTypeCount(      omfArrayFromObj(        OBJ))
#define omfObjSetArrayBufferOffset(          OBJ, VAL)      omfArraySetBufferOffset(         omfArrayFromObj(        OBJ), (VAL))
#define omfObjSetArrayBufferSize(            OBJ, VAL)      omfArraySetBufferSize(           omfArrayFromObj(        OBJ), (VAL))
#define omfObjSetArrayBufferType(            OBJ, VAL)      omfArraySetBufferType(           omfArrayFromObj(        OJB), (VAL))
#define omfObjSetArrayBufferTypeCount(       OBJ, VAL)      omfArraySetBufferTypeCount(      omfArrayFromObj(        OBJ), (VAL))

#define omfObjGetDataArray(                  OBJ)           omfDataGetArray(                 omfDataFromObj(         OBJ))
#define omfObjGetDataDescription(            OBJ)           omfDataGetDescription(           omfDataFromObj(         OBJ))
#define omfObjGetDataLoc(                    OBJ)           omfDataGetLoc(                   omfDataFromObj(         OBJ))
#define omfObjGetDataName(                   OBJ)           omfDataGetName(                  omfDataFromObj(         OBJ))
#define omfObjGetDataType(                   OBJ)           omfDataGetType(                  omfDataFromObj(         OBJ))
#define omfObjSetDataArray(                  OBJ, VAL)      omfDataSetArray(                 omfDataFromObj(         OBJ), (VAL))
#define omfObjSetDataDescription(            OBJ, VAL)      omfDataSetDescription(           omfDataFromObj(         OBJ), (VAL))
#define omfObjSetDataLoc(                    OBJ, VAL)      omfDataSetLoc(                   omfDataFromObj(         OBJ), (VAL))
#define omfObjSetDataName(                   OBJ, VAL)      omfDataSetName(                  omfDataFromObj(         OBJ), (VAL))
#define omfObjSetDataType(                   OBJ, VAL)      omfDataSetType(                  omfDataFromObj(         OBJ), (VAL))

#define omfObjGetElemColor(                  OBJ)           omfElemGetColor(                 omfElemFromObj(         OBJ))
#define omfObjGetElemDataList(               OBJ)           omfElemGetDataList(              omfElemFromObj(         OBJ))
#define omfObjGetElemDescription(            OBJ)           omfElemGetDescription(           omfElemFromObj(         OBJ))
#define omfObjGetElemName(                   OBJ)           omfElemGetName(                  omfElemFromObj(         OBJ))
#define omfObjGetElemType(                   OBJ)           omfElemGetType(                  omfElemFromObj(         OBJ))
#define omfObjGetElemTypeSub(                OBJ)           omfElemGetTypeSub(               omfElemFromObj(         OBJ))
#define omfObjIsElemDataListSet(             OBJ)           omfElemIsDataListSet(            omfElemFromObj(         OBJ))
#define omfObjSetElemColor(                  OBJ, VAL)      omfElemSetColor(                 omfElemFromObj(         OBJ), (VAL))
#define omfObjSetElemDataList(               OBJ, VAL)      omfElemSetDataList(              omfElemFromObj(         OBJ), (VAL))
#define omfObjSetElemDescription(            OBJ, VAL)      omfElemSetDescription(           omfElemFromObj(         OBJ), (VAL))
#define omfObjSetElemName(                   OBJ, VAL)      omfElemSetName(                  omfElemFromObj(         OBJ), (VAL))
#define omfObjSetElemTypeSub(                OBJ, VAL)      omfElemSetTypeSub(               omfElemFromObj(         OBJ), (VAL))

#define omfObjGetElemLineSetGeometry(        OBJ)           omfElemLineSetGetGeometry(       omfElemLineSetFromObj(  OBJ))
#define omfObjSetElemLineSetGeometry(        OBJ, VAL)      omfElemLineSetSetGeometry(       omfElemLineSetFromObj(  OBJ), (VAL))

#define omfObjGetElemPntSetGeometry(         OBJ)           omfElemPntSetGetGeometry(        omfElemPntSetFromObj(   OBJ))
#define omfObjGetElemPntSetTextureList(      OBJ)           omfElemPntSetGetTextureList(     omfElemPntSetFromObj(   OBJ))
#define omfObjIsElemPntSetTextureListSet(    OBJ)           omfElemPntSetIsTextureListSet(   omfElemPntSetFromObj(   OBJ))
#define omfObjSetElemPntSetGeometry(         OBJ, VAL)      omfElemPntSetSetGeometry(        omfElemPntSetFromObj(   OBJ), (VAL))
#define omfObjSetElemPntSetTextureList(      OBJ, VAL)      omfElemPntSetSetTextureList(     omfElemPntSetFromObj(   OBJ), (VAL))

#define omfObjGetElemSurfGridGeometry(       OBJ)           omfElemSurfGridGetGeometry(      omfElemSurfGridFromObj( OBJ))
#define omfObjGetElemSurfGridTextureList(    OBJ)           omfElemSurfGridGetTextureList(   omfElemSurfGridFromObj( OBJ))
#define omfObjIsElemSurfGridTextureListSet(  OBJ)           omfElemSurfGridIsTextureListSet( omfElemSurfGridFromObj( OBJ))
#define omfObjSetElemSurfGridGeometry(       OBJ, VAL)      omfElemSurfGridSetGeometry(      omfElemSurfGridFromObj( OBJ), (VAL))
#define omfObjSetElemSurfGridTextureList(    OBJ, VAL)      omfElemSurfGridSetTextureList(   omfElemSurfGridFromObj( OBJ), (VAL))

#define omfObjGetElemSurfTriGeometry(        OBJ)           omfElemSurfTriGetGeometry(       omfElemSurfTriFromObj(  OBJ))
#define omfObjGetElemSurfTriTextureList(     OBJ)           omfElemSurfTriGetTextureList(    omfElemSurfTriFromObj(  OBJ))
#define omfObjIsElemSurfTriTextureListSet(   OBJ)           omfElemSurfTriIsTextureListSet(  omfElemSurfTriFromObj(  OBJ))
#define omfObjSetElemSurfTriGeometry(        OBJ, VAL)      omfElemSurfTriSetGeometry(       omfElemSurfTriFromObj(  OBJ), (VAL))
#define omfObjSetElemSurfTriTextureList(     OBJ, VAL)      omfElemSurfTriSetTextureList(    omfElemSurfTriFromObj(  OBJ), (VAL))

#define omfObjGetGeomOrigin(                 OBJ)           omfGeomGetOrigin(                omfGeomFromObj(         OBJ))
#define omfObjGetGeomType(                   OBJ)           omfGeomGetType(                  omfGeomFromObj(         OBJ))
#define omfObjSetGeomOrigin(                 OBJ, VAL)      omfGeomSetOrigin(                omfGeomFromObj(         OBJ), (VAL))

#define omfObjGetGeomLineSetArrayCoord(      OBJ)           omfGeomLineSetGetArrayCoord(     omfGeomLineSetFromObj(  OBJ)) 
#define omfObjGetGeomLineSetArraySegment(    OBJ)           omfGeomLineSetGetArraySegment(   omfGeomLineSetFromObj(  OBJ)) 
#define omfObjSetGeomLineSetArrayCoord(      OBJ, VAL)      omfGeomLineSetSetArrayCoord(     omfGeomLineSetFromObj(  OBJ), (VAL))
#define omfObjSetGeomLineSetArraySegment(    OBJ, VAL)      omfGeomLineSetSetArraySegment(   omfGeomLineSetFromObj(  OBJ), (VAL))

#define omfObjGetGeomPntSetArrayCoord(       OBJ)           omfGeomPntSetGetArrayCoord(      omfGeomPntSetFromObj(   OBJ)) 
#define omfObjSetGeomPntSetArrayCoord(       OBJ, VAL)      omfGeomPntSetSetArrayCoord(      omfGeomPntSetFromObj(   OBJ), (VAL))

#define omfObjGetGeomSurfGridArrayOffset(    OBJ)           omfGeomSurfGridGetArrayOffset(   omfGeomSurfGridFromObj( OBJ)) 
#define omfObjGetGeomSurfGridArrayTensorU(   OBJ)           omfGeomSurfGridGetArrayTensorU(  omfGeomSurfGridFromObj( OBJ)) 
#define omfObjGetGeomSurfGridArrayTensorV(   OBJ)           omfGeomSurfGridGetArrayTensorV(  omfGeomSurfGridFromObj( OBJ)) 
#define omfObjGetGeomSurfGridAxisU(          OBJ)           omfGeomSurfGridGetAxisU(         omfGeomSurfGridFromObj( OBJ)) 
#define omfObjGetGeomSurfGridAxisV(          OBJ)           omfGeomSurfGridGetAxisV(         omfGeomSurfGridFromObj( OBJ)) 
#define omfObjIsGeomSurfGridArrayOffsetSet(  OBJ)           omfGeomSurfGridIsArrayOffsetSet( omfGeomSurfGridFromObj( OBJ)) 
#define omfObjSetGeomSurfGridArrayOffset(    OBJ, VAL)      omfGeomSurfGridSetArrayOffset(   omfGeomSurfGridFromObj( OBJ), (VAL))
#define omfObjSetGeomSurfGridArrayTensorU(   OBJ, VAL)      omfGeomSurfGridSetArrayTensorU(  omfGeomSurfGridFromObj( OBJ), (VAL))
#define omfObjSetGeomSurfGridArrayTensorV(   OBJ, VAL)      omfGeomSurfGridSetArrayTensorV(  omfGeomSurfGridFromObj( OBJ), (VAL))
#define omfObjSetGeomSurfGridAxisU(          OBJ, VAL)      omfGeomSurfGridSetAxisU(         omfGeomSurfGridFromObj( OBJ), (VAL))
#define omfObjSetGeomSurfGridAxisV(          OBJ, VAL)      omfGeomSurfGridSetAxisV(         omfGeomSurfGridFromObj( OBJ), (VAL))

#define omfObjGetGeomSurfTriArrayCoord(      OBJ)           omfGeomSurfTriGetArrayCoord(     omfGeomSurfTriFromObj(  OBJ)) 
#define omfObjGetGeomSurfTriArrayTriangle(   OBJ)           omfGeomSurfTriGetArrayTriangle(  omfGeomSurfTriFromObj(  OBJ)) 
#define omfObjSetGeomSurfTriArrayCoord(      OBJ, VAL)      omfGeomSurfTriSetArrayCoord(     omfGeomSurfTriFromObj(  OBJ), (VAL))
#define omfObjSetGeomSurfTriArrayTriangle(   OBJ, VAL)      omfGeomSurfTriSetArrayTriangle(  omfGeomSurfTriFromObj(  OBJ), (VAL))

#define omfObjAddProjElem(                   OBJ, ELEM)     omfProjAddElem(                  omfProjFromObj(         OBJ), (ELEM))
#define omfObjGetProjAuthor(                 OBJ)           omfProjGetAuthor(                omfProjFromObj(         OBJ)) 
#define omfObjGetProjDate(                   OBJ)           omfProjGetDate(                  omfProjFromObj(         OBJ)) 
#define omfObjGetProjDescription(            OBJ)           omfProjGetDescription(           omfProjFromObj(         OBJ)) 
#define omfObjGetProjName(                   OBJ)           omfProjGetName(                  omfProjFromObj(         OBJ)) 
#define omfObjGetProjOrigin(                 OBJ)           omfProjGetOrigin(                omfProjFromObj(         OBJ)) 
#define omfObjGetProjRevision(               OBJ)           omfProjGetRevision(              omfProjFromObj(         OBJ)) 
#define omfObjGetProjUnits(                  OBJ)           omfProjGetUnits(                 omfProjFromObj(         OBJ)) 
#define omfObjSetProjAuthor(                 OBJ, VAL)      omfProjSetAuthor(                omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjDate(                   OBJ, VAL)      omfProjSetDate(                  omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjDescription(            OBJ, VAL)      omfProjSetDescription(           omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjName(                   OBJ, VAL)      omfProjSetName(                  omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjOrigin(                 OBJ, VAL)      omfProjSetOrigin(                omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjRevision(               OBJ, VAL)      omfProjSetRevision(              omfProjFromObj(         OBJ), (VAL))
#define omfObjSetProjUnits(                  OBJ, VAL)      omfProjSetUnits(                 omfProjFromObj(         OBJ), (VAL))

/**************************************************************************************************
prototype:
**************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

// Library level routines
OmfBool                     omfIsStarted(                            void);
                           
OmfError                    omfStart(                                void *(*memCreate)(size_t size), void (*memDestroy)(void *buffer), void (*memClear)(void *buffer, size_t size));
void                        omfStop(                                 void);

// Object routines
OmfObj                     *omfObjCreate(                            OmfObjType const type);
void                        omfObjDestroy(                           OmfObj * const object);

OmfChar                    *omfObjGetDateCreated(                    OmfObj const * const obj);
OmfChar                    *omfObjGetDateModified(                   OmfObj const * const obj);
OmfId                       omfObjGetId(                             OmfObj const * const obj);
OmfObjType                  omfObjGetType(                           OmfObj const * const obj);

OmfBool                     omfObjSetDateCreated(                    OmfObj       * const obj, OmfChar * const value);
OmfBool                     omfObjSetDateModified(                   OmfObj       * const obj, OmfChar * const value);
OmfBool                     omfObjSetId(                             OmfObj       * const obj, OmfId const value);

// Char routines
OmfChar                    *omfCharClone(                            OmfChar const * const value);
OmfChar                    *omfCharCreateFromWchar(                  wchar_t const * const value);

void                        omfCharDestroy(                          OmfChar       * const value);

OmfCount                    omfCharGetSize(                          OmfChar const * const value);

wchar_t                    *wcharCreateFromOmfChar(                  OmfChar const * const value);

// OmfList functions
OmfList                    *omfListCreate(                           void);
OmfBool                     omfListCreateContent(                    OmfList       * const list);

void                        omfListDestroy(                          OmfList       * const list);
void                        omfListDestroyContent(                   OmfList       * const list);

void                        omfListAppend(                           OmfList       * const list, OmfListItem * const item);

OmfCount                    omfListGetCount(                         OmfList const * const list);
OmfListItem                *omfListGetHeadItem(                      OmfList const * const list);

// OmfListItem functions
OmfListItem                *omfListItemCreate(                       void);
OmfBool                     omfListItemCreateContent(                OmfListItem       * const listItem);

void                        omfListItemDestroy(                      OmfListItem       * const listItem);
void                        omfListItemDestroyContent(               OmfListItem       * const listItem);

OmfListItem                *omfListItemGetNext(                      OmfListItem const * const listItem);
OmfObj                     *omfListItemGetObj(                       OmfListItem const * const listItem);

OmfBool                     omfListItemSetNext(                      OmfListItem       * const listItem, OmfListItem * const value);
OmfBool                     omfListItemSetObj(                       OmfListItem       * const listItem, OmfObj * const value);

// OmfListIter function
OmfListIter                *omfListIterCreate(                       OmfList const * const list);
OmfBool                     omfListIterCreateContent(                OmfListIter       * const listIter, OmfList const * const list);

void                        omfListIterDestroy(                      OmfListIter       * const listIter);
void                        omfListIterDestroyContent(               OmfListIter       * const listIter);

OmfListItem                *omfListIterGetItem(                      OmfListIter const * const listIter);

OmfBool                     omfListIterNext(                         OmfListIter       * const listIter);

// Array buffer routines
OmfArray                   *omfArrayCreate(                          void);
OmfBool                     omfArrayCreateContent(                   OmfArray       * const arrayData);

void                        omfArrayDestroy(                         OmfArray       * const arrayData);
void                        omfArrayDestroyContent(                  OmfArray       * const arrayData);

OmfOffset                   omfArrayGetBufferOffset(                 OmfArray const * const arrayData);
OmfCount                    omfArrayGetBufferSize(                   OmfArray const * const arrayData);
OmfArrayType                omfArrayGetBufferType(                   OmfArray const * const arrayData);
OmfCount                    omfArrayGetBufferTypeCount(              OmfArray const * const arrayData);
OmfError                    omfArrayGetDataCoord(                    OmfFile const * const file, OmfArray const * const arrayData/* , callback to buffer filling */);
OmfError                    omfArrayGetDataIndex(                    OmfFile const * const file, OmfArray const * const arrayData/* , callback to buffer filling */);

OmfBool                     omfArraySetBufferOffset(                 OmfArray       * const arrayData, OmfOffset const value);
OmfBool                     omfArraySetBufferSize(                   OmfArray       * const arrayData, OmfCount const value);
OmfBool                     omfArraySetBufferType(                   OmfArray       * const arrayData, OmfArrayType const value);
OmfBool                     omfArraySetBufferTypeCount(              OmfArray       * const arrayData, OmfCount const value);
OmfError                    omfArraySetDataCoord(                    OmfFile       * const file, OmfArray * const arrayData/* , callback to buffer reading */);
OmfError                    omfArraySetDataIndex(                    OmfFile       * const file, OmfArray * const arrayData/* , callback to buffer reading */);

// Data routines
OmfArray                   *omfDataGetArray(                         OmfData const * const data);
OmfChar                    *omfDataGetDescription(                   OmfData const * const data);
OmfDataLoc                  omfDataGetLoc(                           OmfData const * const data);
OmfChar                    *omfDataGetName(                          OmfData const * const data);
OmfDataType                 omfDataGetType(                          OmfData const * const data);

OmfBool                     omfDataSetArray(                         OmfData       * const data, OmfArray * const value);
OmfBool                     omfDataSetDescription(                   OmfData       * const data, OmfChar * const value);
OmfBool                     omfDataSetLoc(                           OmfData       * const data, OmfDataLoc const value);
OmfBool                     omfDataSetName(                          OmfData       * const data, OmfChar * const value);
OmfBool                     omfDataSetType(                          OmfData       * const data, OmfDataType const value);

// Element routines
OmfColor                    omfElemGetColor(                         OmfElem const * const elem);
OmfDataList                *omfElemGetDataList(                      OmfElem const * const elem);
OmfChar                    *omfElemGetDescription(                   OmfElem const * const elem);
OmfChar                    *omfElemGetName(                          OmfElem const * const elem);
OmfElemType                 omfElemGetType(                          OmfElem const * const elem);
OmfElemSubType              omfElemGetTypeSub(                       OmfElem const * const elem);

OmfBool                     omfElemIsDataListSet(                    OmfElem const * const elem);

OmfBool                     omfElemSetColor(                         OmfElem       * const elem, OmfColor const value);
OmfBool                     omfElemSetDataList(                      OmfElem       * const elem, OmfDataList * const value);
OmfBool                     omfElemSetDescription(                   OmfElem       * const elem, OmfChar * const value);
OmfBool                     omfElemSetName(                          OmfElem       * const elem, OmfChar * const value);
OmfBool                     omfElemSetTypeSub(                       OmfElem       * const elem, OmfElemSubType const value);

// Element Line Set routines
OmfGeom                    *omfElemLineSetGetGeometry(               OmfElemLineSet const * const elem);

OmfBool                     omfElemLineSetSetGeometry(               OmfElemLineSet       * const elem, OmfGeomLineSet * const value);

// Element Pnt Set routines
OmfGeom                    *omfElemPntSetGetGeometry(                OmfElemPntSet const * const elem);
OmfTextureList             *omfElemPntSetGetTextureList(             OmfElemPntSet const * const elem);

OmfBool                     omfElemPntSetIsTextureListSet(           OmfElemPntSet const * const elem);

OmfBool                     omfElemPntSetSetGeometry(                OmfElemPntSet       * const elem, OmfGeomPntSet * const value);
OmfBool                     omfElemPntSetSetTextureList(             OmfElemPntSet       * const elem, OmfTextureList * const value);

// Element Surf Grid routines
OmfGeom                    *omfElemSurfGridGetGeometry(              OmfElemSurfGrid const * const elem);
OmfTextureList             *omfElemSurfGridGetTextureList(           OmfElemSurfGrid const * const elem);

OmfBool                     omfElemSurfGridIsTextureListSet(         OmfElemSurfGrid const * const elem);

OmfBool                     omfElemSurfGridSetGeometry(              OmfElemSurfGrid       * const elem, OmfGeomSurfGrid * const value);
OmfBool                     omfElemSurfGridSetTextureList(           OmfElemSurfGrid       * const elem, OmfTextureList * const value);

// Element Surf Tri routines
OmfGeom                    *omfElemSurfTriGetGeometry(               OmfElemSurfTri const * const elem);
OmfTextureList             *omfElemSurfTriGetTextureList(            OmfElemSurfTri const * const elem);

OmfBool                     omfElemSurfTriIsTextureListSet(          OmfElemSurfTri const * const elem);

OmfBool                     omfElemSurfTriSetGeometry(               OmfElemSurfTri       * const elem, OmfGeomSurfTri * const value);
OmfBool                     omfElemSurfTriSetTextureList(            OmfElemSurfTri       * const elem, OmfTextureList * const value);

// File routines.
OmfError                    omfFileCreateRead(                       wchar_t const * const fileName,                                   OmfFile ** const file);
OmfError                    omfFileCreateWrite(                      wchar_t const * const fileName, OmfFileVersion const fileVersion, OmfFile ** const file);

void                        omfFileDestroy(                          OmfFile       * const file);

OmfProj                    *omfFileGetProject(                       OmfFile       * const file);
OmfError                    omfFileGetVersion(                       OmfFile const * const file, OmfFileVersion * const value);

OmfBool                     omfFileIsWriting(                        OmfFile const * const file);

// Geometry routines
OmfCoord                    omfGeomGetOrigin(                        OmfGeom const * const geom);
OmfElemType                 omfGeomGetType(                          OmfGeom const * const geom);

OmfBool                     omfGeomSetOrigin(                        OmfGeom       * const geom, OmfCoord const value);

// Geometry Line Set routines
OmfArray                   *omfGeomLineSetGetArrayCoord(             OmfGeomLineSet const * const geom);
OmfArray                   *omfGeomLineSetGetArraySegment(           OmfGeomLineSet const * const geom);

OmfBool                     omfGeomLineSetSetArrayCoord(             OmfGeomLineSet       * const geom, OmfArray * const value);
OmfBool                     omfGeomLineSetSetArraySegment(           OmfGeomLineSet       * const geom, OmfArray * const value);

// Geometry Pnt Set routines
OmfArray                   *omfGeomPntSetGetArrayCoord(              OmfGeomPntSet const * const geom);

OmfBool                     omfGeomPntSetSetArrayCoord(              OmfGeomPntSet       * const geom, OmfArray * const value);

// Geometry Surf Grid routines
OmfArray                   *omfGeomSurfGridGetArrayOffset(           OmfGeomSurfGrid const * const geom);
OmfArray                   *omfGeomSurfGridGetArrayTensorU(          OmfGeomSurfGrid const * const geom);
OmfArray                   *omfGeomSurfGridGetArrayTensorV(          OmfGeomSurfGrid const * const geom);
OmfVector                   omfGeomSurfGridGetAxisU(                 OmfGeomSurfGrid const * const geom);
OmfVector                   omfGeomSurfGridGetAxisV(                 OmfGeomSurfGrid const * const geom);

OmfBool                     omfGeomSurfGridIsArrayOffsetSet(         OmfGeomSurfGrid const * const geom);

OmfBool                     omfGeomSurfGridSetArrayOffset(           OmfGeomSurfGrid       * const geom, OmfArray * const value);
OmfBool                     omfGeomSurfGridSetArrayTensorU(          OmfGeomSurfGrid       * const geom, OmfArray * const value);
OmfBool                     omfGeomSurfGridSetArrayTensorV(          OmfGeomSurfGrid       * const geom, OmfArray * const value);
OmfBool                     omfGeomSurfGridSetAxisU(                 OmfGeomSurfGrid       * const geom, OmfVector const value);
OmfBool                     omfGeomSurfGridSetAxisV(                 OmfGeomSurfGrid       * const geom, OmfVector const value);

// Geometry Surf Tri routines
OmfArray                   *omfGeomSurfTriGetArrayCoord(             OmfGeomSurfTri const * const geom);
OmfArray                   *omfGeomSurfTriGetArrayTriangle(          OmfGeomSurfTri const * const geom);

OmfBool                     omfGeomSurfTriSetArrayCoord(             OmfGeomSurfTri       * const geom, OmfArray * const value);
OmfBool                     omfGeomSurfTriSetArrayTriangle(          OmfGeomSurfTri       * const geom, OmfArray * const value);

// Project routines
OmfBool                     omfProjAddElem(                       OmfProj       * const proj, OmfElem * const elem);

OmfChar                    *omfProjGetAuthor(                     OmfProj const * const proj);
OmfChar                    *omfProjGetDate(                       OmfProj const * const proj);
OmfChar                    *omfProjGetDescription(                OmfProj const * const proj);
OmfChar                    *omfProjGetName(                       OmfProj const * const proj);
OmfCoord                    omfProjGetOrigin(                     OmfProj const * const proj);
OmfChar                    *omfProjGetRevision(                   OmfProj const * const proj);
OmfChar                    *omfProjGetUnits(                      OmfProj const * const proj);

OmfBool                     omfProjSetAuthor(                     OmfProj       * const proj, OmfChar const * const value);
OmfBool                     omfProjSetDate(                       OmfProj       * const proj, OmfChar const * const value);
OmfBool                     omfProjSetDescription(                OmfProj       * const proj, OmfChar const * const value);
OmfBool                     omfProjSetName(                       OmfProj       * const proj, OmfChar const * const value);
OmfBool                     omfProjSetOrigin(                     OmfProj       * const proj, OmfCoord const value);
OmfBool                     omfProjSetRevision(                   OmfProj       * const proj, OmfChar const * const value);
OmfBool                     omfProjSetUnits(                      OmfProj       * const proj, OmfChar const * const value);

#if defined(__cplusplus)
}
#endif

#endif
