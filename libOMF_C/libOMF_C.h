/******************************************************************************
file:       libOMF_C
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
API for reading and writing OMF files.

Structure of the file.

A file has a project.
   A project has a list of elements.
      
A point set element...
   ... has a point set geometry...
      ... has a coordinate list buffer (compressed blob)
   ... may have a data list
   ... may have a texture list

A line set element...
   ... has a line set geometry...
      ... has a 
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/

/******************************************************************************
constant:
******************************************************************************/
#define libOMF_C_VERSION      1

#define omfArrayTypeINT_TAG   "<i8"
#define omfArrayTypeREAL_TAG  "<f8"

/******************************************************************************
type:

Structures should NEVER be accessed directly.  Use any and all API to access
the contents of the structure.  This
******************************************************************************/
typedef enum
{
   omfFALSE = false,
   omfTRUE  = true
} OmfBool;

typedef enum
{
   omfArrayTypeNONE,
   omfArrayTypeCOLOR,
   omfArrayTypeDATE_TIME,
   omfArrayTypeINT,
   omfArrayTypeINT3,
   omfArrayTypeINT2,
   omfArrayTypeREAL,
   omfArrayTypeREAL2,
   omfArrayTypeREAL3,
   omfArrayTypeSTRING
} OmfArrayType;

typedef enum
{
   // v1
   omfElementTypeNONE,

   omfElementTypeLINE_SET,
   omfElementTypePOINT_SET,
   omfElementTypeSURFACE_GRID,
   omfElementTypeSURFACE_TRI,
   omfElementTypeVOLUME

   // v2
} OmfElementType;

typedef enum
{
   // v1
   omfElementSubTypeNONE,

   omfElementSubTypeLINE_SET_LINE_DEFAULT,
   omfElementSubTypeLINE_SET_BOREHOLE,

   omfElementSubTypePOINT_SET_POINT_DEFAULT,
   omfElementSubTypePOINT_SET_COLLAR,
   omfElementSubTypePOINT_SET_BLASTHOLE,

   omfElementSubTypeSURFACE_GRID_SURFACE_DEFAULT,

   omfElementSubTypeSURFACE_TRI_SURFACE_DEFAULT,

   omfElementSubTypeVOLUME_VOLUME_DEFAULT

   // v2
} OmfElementSubType;

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
   omfItemTypeNONE,

   omfItemTypeSCALAR_DATA,

   omfItemTypeINT2_ARRAY,
   omfItemTypeINT3_ARRAY,
   omfItemTypeSCALAR_ARRAY,
   omfItemTypeSTRING_ARRAY,
   omfItemTypeLEGEND,
   omfItemTypeCOLOR_ARRAY,
   omfItemTypeMAPPED_DATA,
   omfItemTypeVECTOR3_ARRAY,

   omfItemTypePOINT_SET_ELEMENT,
   omfItemTypePOINT_SET_GEOMETRY,
   omfItemTypeLINE_SET_ELEMENT,
   omfItemTypeLINE_SET_GEOMETRY,
   omfItemTypeSURFACE_ELEMENT,
   omfItemTypeSURFACE_GEOMETRY,
   omfItemTypeIMAGE_TEXTURE,
   omfItemTypeBLOCK_MODEL,
   omfItemTypeCOMPOSITE,
   omfItemTypeVOLUME_ELEMENT,
   omfItemTypeVOLUME_GRID_GEOMETRY,
   omfItemTypePROJECT

   // v2
} OmfItemType;

typedef unsigned char                  uchar;

typedef uchar                          OmfChar;
typedef uint32_t                       OmfCount;
typedef struct OmfColor                OmfColor;
typedef uchar                          OmfColorValue;
typedef struct OmfCoord                OmfCoord;
typedef struct OmfArray                OmfArray;
typedef struct OmfData                 OmfData;
typedef struct OmfDataList             OmfDataList;
typedef struct OmfElement              OmfElement;
typedef struct OmfElementLineSet       OmfElementLineSet;
typedef struct OmfElementPointSet      OmfElementPointSet;
typedef struct OmfElementSurfaceGrid   OmfElementSurfaceGrid;
typedef struct OmfElementSurfaceTri    OmfElementSurfaceTri;
typedef struct OmfElementVolume        OmfElementVolume;
typedef struct OmfFile                 OmfFile;
typedef struct OmfFile00_09            OmfFile00_09;
typedef struct OmfFile01_00            OmfFile01_00;
typedef struct OmfFile02_00            OmfFile02_00;
typedef struct OmfGeometry             OmfGeometry;
typedef struct OmfGeometryLineSet      OmfGeometryLineSet;
typedef struct OmfGeometryPointSet     OmfGeometryPointSet;
typedef struct OmfGeometrySurfaceGrid  OmfGeometrySurfaceGrid;
typedef struct OmfGeometrySurfaceTri   OmfGeometrySurfaceTri;
typedef struct OmfGeometryVolume       OmfGeometryVolume;
typedef GUID                           OmfId;
typedef uint32_t                       OmfIndex;
typedef uint64_t                       OmfOffset;
typedef struct OmfProject              OmfProject;
typedef struct OmfTexture              OmfTexture;
typedef struct OmfTextureList          OmfTextureList;
typedef struct OmfTextureUV            OmfTextureUV;
typedef struct OmfVector               OmfVector;


struct OmfArray
{
   // Required
   OmfId                       id;
   OmfOffset                   bufferOffset;
   OmfCount                    bufferSize;
   OmfArrayType                bufferType;
   OmfCount                    bufferTypeCount;

   // Optional
   OmfBool                     isDateCreatedSet;
   OmfBool                     isDateModifiedSet;

   OmfChar                    *dateCreated;
   OmfChar                    *dateModified;
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
   OmfId                       id;
   OmfChar                    *name;
} ;

struct OmfDataList
{
   OmfId                       id;
};

struct OmfElement
{
// This is a form of old style object oriented class and sub classing.
// Type casting is used to obtain the proper structure.
#define OMF_ELEMENT_VARS                              \
   OmfElement                 *next;                  \
                                                      \
   OmfElementType              type;                  \
   OmfId                       id;                    \
   OmfColor                    color;                 \
   OmfChar                    *description;           \
   OmfChar                    *name;                  \
   OmfElementSubType           subType;               \
                                                      \
   OmfBool                     isDataListSet;         \
   OmfBool                     isDateCreatedSet;      \
   OmfBool                     isDateModifiedSet;     \
                                                      \
   OmfDataList                *dataList;              \
   OmfChar                    *dateCreated;           \
   OmfChar                    *dateModified;

   OMF_ELEMENT_VARS
};

struct OmfElementLineSet
{
   // Must be first.
   OMF_ELEMENT_VARS

   // Required
   OmfGeometryLineSet         *geometry;

   // Optional
};

struct OmfElementPointSet
{
   // Must be first.
   OMF_ELEMENT_VARS

   // Required
   OmfGeometryPointSet        *geometry;

   // Optional
   OmfBool                     isTextureListSet;

   OmfTextureList             *textureList;
};

struct OmfElementSurfaceGrid
{
   // Must be first.
   OMF_ELEMENT_VARS

   // Required
   OmfGeometrySurfaceGrid     *geometry;

   // Optional
   OmfBool                     isTextureListSet;

   OmfTextureList             *textureList;
};

struct OmfElementSurfaceTri
{
   // Must be first.
   OMF_ELEMENT_VARS

   // Required
   OmfGeometrySurfaceTri      *geometry;

   // Optional
   OmfBool                     isTextureListSet;

   OmfTextureList             *textureList;
};

struct OmfElementVolume
{
   // Must be first.
   OMF_ELEMENT_VARS

   // Required
   OmfGeometryVolume          *geometry;

   // Optional
};

struct OmfProject
{
   // Require
   OmfId                       id;
   OmfChar                    *author;
   OmfChar                    *description;
   OmfChar                    *name;
   OmfCoord                    origin;
   OmfChar                    *revision;
   OmfChar                    *units;

   // Optional
   // Not converting this to a native format.  Leaving that to the user of the library.
   // Date format "YYYY-MM-DDTHH:MM:SSZ" 24 hour time, 0 padded values.  Z = ZULU means 0 offset from GMT.
   OmfBool                     isDateSet;
   OmfBool                     isDateCreatedSet;
   OmfBool                     isDateModifiedSet;

   OmfChar                    *date;
   OmfChar                    *dateCreated;
   OmfChar                    *dateModified;
};

struct OmfFile
{
   OmfBool                     isWriting;
   OmfFileVersion              version;
   OmfProject                  project;

   // v00_09
   FILE                       *file;
   OmfOffset                   offsetTableOfContents;
   OmfId                       idProject;
   OmfChar                    *jsonTableOfContents;

   // v01_00+
   void                       *fileZip;
};

struct OmfGeometry
{
#define OMF_GEOMETRY_VARS                                \
   OmfElementType              type;                     \
   OmfId                       id;                       \
   OmfCoord                    origin;                   \
                                                         \
   OmfBool                     isDateCreatedSet;         \
   OmfBool                     isDateModifiedSet;        \
                                                         \
   OmfChar                    *dateCreated;              \
   OmfChar                    *dateModified;

   OMF_GEOMETRY_VARS
};

struct OmfGeometryLineSet
{
   // Must be first.
   OMF_GEOMETRY_VARS

   // Required
   OmfArray                   *coord;
   OmfArray                   *segment;
};

struct OmfGeometryPointSet
{
   // Must be first.
   OMF_GEOMETRY_VARS

   // Required
   OmfArray                   *coord;
};

struct OmfGeometrySurfaceGrid
{
   // Must be first.
   OMF_GEOMETRY_VARS

   // Required
   OmfVector                   axisU;
   OmfVector                   axisV;
   OmfArray                   *tensorU;
   OmfArray                   *tensorV;

   // Optional
   OmfBool                     isOffsetSet;

   OmfArray                   *offset;
};

struct OmfGeometrySurfaceTri
{
   // Must be first.
   OMF_GEOMETRY_VARS

   // Required
   OmfArray                   *coord;
   OmfArray                   *triangle;
};

struct OmfGeometryVolume
{
   // Must be first.
   OMF_GEOMETRY_VARS

   // Required
   OmfVector                   axisU;
   OmfVector                   axisV;
   OmfVector                   axisW;
   OmfArray                   *tensorU;
   OmfArray                   *tensorV;
   OmfArray                   *tensorW;

   // Optional
};

struct OmfTexture
{
   OmfId                       id;
   OmfChar                    *name;
};

struct OmfTextureList
{
   OmfId                       id;
};

/******************************************************************************
variable:
******************************************************************************/


/******************************************************************************
macro:
******************************************************************************/


/******************************************************************************
prototype:
******************************************************************************/
// Library level routines
OmfBool                     omfIsStarted(                            void);
                           
OmfError                    omfStart(                                void *(*memCreate)(size_t size), void (*memDestroy)(void *buffer), void (*memClear)(void *buffer, size_t size));
void                        omfStop(                                 void);

// Char routines
OmfChar                    *omfCharClone(                            OmfChar const * const value);
OmfChar                    *omfCharCreateFromWchar(                  wchar_t const * const value);

void                        omfCharDestroy(                          OmfChar       * const value);

OmfCount                    omfCharGetSize(                          OmfChar const * const value);

wchar_t                    *wcharCreateFromOmfChar(                  OmfChar const * const value);

// Array buffer routines
OmfArray                   *omfArrayCreate(                          void);
OmfBool                     omfArrayCreateContent(                   OmfArray       * const omfArray);

void                        omfArrayDestroy(                         OmfArray       * const omfArray);
void                        omfArrayDestroyContent(                  OmfArray       * const omfArray);

OmfOffset                   omfArrayGetBufferOffset(                 OmfArray const * const omfArray);
OmfCount                    omfArrayGetBufferSize(                   OmfArray const * const omfArray);
OmfArrayType                omfArrayGetBufferType(                   OmfArray const * const omfArray);
OmfCount                    omfArrayGetBufferTypeCount(              OmfArray const * const omfArray);
OmfError                    omfArrayGetDataCoord(                    OmfFile const * const file, OmfArray const * const omfArray/* , callback to buffer filling */);
OmfError                    omfArrayGetDataIndex(                    OmfFile const * const file, OmfArray const * const omfArray/* , callback to buffer filling */);
OmfChar                    *omfArrayGetDateCreated(                  OmfArray const * const omfArray);
OmfChar                    *omfArrayGetDateModified(                 OmfArray const * const omfArray);
OmfId                       omfArrayGetId(                           OmfArray const * const omfArray);

OmfBool                     omfArrayIsDateCreated(                   OmfArray const * const omfArray);
OmfBool                     omfArrayIsDateModified(                  OmfArray const * const omfArray);

OmfBool                     omfArraySetBufferOffset(                 OmfArray       * const omfArray, OmfOffset const value);
OmfBool                     omfArraySetBufferSize(                   OmfArray       * const omfArray, OmfCount const value);
OmfBool                     omfArraySetBufferType(                   OmfArray       * const omfArray, OmfArrayType const value);
OmfBool                     omfArraySetBufferTypeCount(              OmfArray       * const omfArray, OmfCount const value);
OmfError                    omfArraySetDataCoord(                    OmfFile       * const file, OmfArray * const omfArray/* , callback to buffer reading */);
OmfError                    omfArraySetDataIndex(                    OmfFile       * const file, OmfArray * const omfArray/* , callback to buffer reading */);
OmfBool                     omfArraySetDateCreated(                  OmfArray       * const omfArray, OmfChar * const value);
OmfBool                     omfArraySetDateModified(                 OmfArray       * const omfArray, OmfChar * const value);
OmfBool                     omfArraySetId(                           OmfArray       * const omfArray, OmfId const value);

// Element routines
OmfElement                 *omfElementCreate(                        OmfElementType type);
                                                                                      
void                        omfElementDestroy(                       OmfElement       * const omfElement);

OmfColor                    omfElementGetColor(                      OmfElement const * const omfElement);
OmfDataList                *omfElementGetDataList(                   OmfElement const * const omfElement);
OmfChar                    *omfElementGetDateCreated(                OmfElement const * const omfElement);
OmfChar                    *omfElementGetDateModified(               OmfElement const * const omfElement);
OmfChar                    *omfElementGetDescription(                OmfElement const * const omfElement);
OmfId                       omfElementGetId(                         OmfElement const * const omfElement);
OmfChar                    *omfElementGetName(                       OmfElement const * const omfElement);
OmfElementSubType           omfElementGetSubType(                    OmfElement const * const omfElement);
OmfElementType              omfElementGetType(                       OmfElement const * const omfElement);

OmfBool                     omfElementIsDataListSet(                 OmfElement const * const omfElement);
OmfBool                     omfElementIsDateCreatedSet(              OmfElement const * const omfElement);
OmfBool                     omfElementIsDateModifiedSet(             OmfElement const * const omfElement);

OmfBool                     omfElementSetColor(                      OmfElement       * const omfElement, OmfColor const value);
OmfBool                     omfElementSetDataList(                   OmfElement       * const omfElement, OmfDataList * const value);
OmfBool                     omfElementSetDateCreated(                OmfElement       * const omfElement, OmfChar * const value);
OmfBool                     omfElementSetDateModified(               OmfElement       * const omfElement, OmfChar * const value);
OmfBool                     omfElementSetDescription(                OmfElement       * const omfElement, OmfChar * const value);
OmfBool                     omfElementSetId(                         OmfElement       * const omfElement, OmfId const value);
OmfBool                     omfElementSetName(                       OmfElement       * const omfElement, OmfChar * const value);
OmfBool                     omfElementSetSubType(                    OmfElement       * const omfElement, OmfElementSubType const value);

#define omfElementLineSetFromOmfElement(     ELEM)  (OmfElementLineSet *)     ((omfElementGetType(ELEM) == omfElementTypeLINE_SET)     ? (ELEM) : NULL)
#define omfElementPointSetFromOmfElement(    ELEM)  (OmfElementPointSet *)    ((omfElementGetType(ELEM) == omfElementTypePOINT_SET)    ? (ELEM) : NULL)
#define omfElementSurfaceGridFromOmfElement( ELEM)  (OmfElementSurfaceGrid *) ((omfElementGetType(ELEM) == omfElementTypeSURFACE_GRID) ? (ELEM) : NULL)
#define omfElementSurfaceTriFromOmfElement(  ELEM)  (OmfElementSurfaceTri *)  ((omfElementGetType(ELEM) == omfElementTypeSURFACE_TRI)  ? (ELEM) : NULL)

// Element Line Set routines
OmfGeometry                *omfElementLineSetGetGeometry(            OmfElementLineSet const * const omfElementLineSet);
OmfBool                     omfElementLineSetSetGeometry(            OmfElementLineSet       * const omfElementLineSet, OmfGeometryLineSet * const value);

// Element Point Set routines
OmfGeometry                *omfElementPointSetGetGeometry(           OmfElementPointSet const * const omfElementPointSet);
OmfTextureList             *omfElementPointSetGetTextureList(        OmfElementPointSet const * const omfElementPointSet);

OmfBool                     omfElementPointSetIsTextureListSet(      OmfElementPointSet const * const omfElementPointSet);

OmfBool                     omfElementPointSetSetGeometry(           OmfElementPointSet       * const omfElementPointSet, OmfGeometryPointSet * const value);
OmfBool                     omfElementPointSetSetTextureList(        OmfElementPointSet       * const omfElementPointSet, OmfTextureList * const value);

// Element Surface Grid routines
OmfGeometry                *omfElementSurfaceGridGetGeometry(        OmfElementSurfaceGrid const * const omfElementSurfaceGrid);
OmfTextureList             *omfElementSurfaceGridGetTextureList(     OmfElementSurfaceGrid const * const omfElementSurfaceGrid);

OmfBool                     omfElementSurfaceGridIsTextureListSet(   OmfElementSurfaceGrid const * const omfElementSurfaceGrid);

OmfBool                     omfElementSurfaceGridSetGeometry(        OmfElementSurfaceGrid * const omfElementSurfaceGrid, OmfGeometrySurfaceGrid * const value);
OmfBool                     omfElementSurfaceGridSetTextureList(     OmfElementSurfaceGrid * const omfElementSurfaceGrid, OmfTextureList * const value);

// Element Surface Tri routines
OmfGeometry                *omfElementSurfaceTriGetGeometry(         OmfElementSurfaceTri const * const omfElementSurfaceTri);
OmfTextureList             *omfElementSurfaceTriGetTextureList(      OmfElementSurfaceTri const * const omfElementSurfaceTri);

OmfBool                     omfElementSurfaceTriIsTextureListSet(    OmfElementSurfaceTri const * const omfElementSurfaceTri);

OmfBool                     omfElementSurfaceTriSetGeometry(         OmfElementSurfaceTri * const omfElementSurfaceTri, OmfGeometrySurfaceTri * const value);
OmfBool                     omfElementSurfaceTriSetTextureList(      OmfElementSurfaceTri * const omfElementSurfaceTri, OmfTextureList * const value);

// File routines.
OmfError                    omfFileCreateRead(                       wchar_t const * const fileName,                                   OmfFile ** const file);
OmfError                    omfFileCreateWrite(                      wchar_t const * const fileName, OmfFileVersion const fileVersion, OmfFile ** const file);

void                        omfFileDestroy(                          OmfFile       * const file);

OmfProject                 *omfFileGetProject(                       OmfFile       * const file);
OmfError                    omfFileGetVersion(                       OmfFile const * const file, OmfFileVersion * const value);

OmfBool                     omfFileIsWriting(                        OmfFile const * const file);

// Geometry routines
OmfGeometry                *omfGeometryCreate(                       OmfElementType const type);
                                                                                                       
void                        omfGeometryDestroy(                      OmfGeometry       * const omfGeometry);

OmfChar                    *omfGeometryGetDateCreated(               OmfGeometry const * const omfGeometry);
OmfChar                    *omfGeometryGetDateModified(              OmfGeometry const * const omfGeometry);
OmfId                       omfGeometryGetId(                        OmfGeometry const * const omfGeometry);
OmfCoord                    omfGeometryGetOrigin(                    OmfGeometry const * const omfGeometry);
OmfElementType              omfGeometryGetType(                      OmfGeometry const * const omfGeometry);

OmfBool                     omfGeometryIsDateCreatedSet(             OmfGeometry const * const omfGeometry);
OmfBool                     omfGeometryIsDateModifiedSet(            OmfGeometry const * const omfGeometry);

OmfBool                     omfGeometrySetDateCreated(               OmfGeometry       * const omfGeometry, OmfChar * const value);
OmfBool                     omfGeometrySetDateModified(              OmfGeometry       * const omfGeometry, OmfChar * const value);
OmfBool                     omfGeometrySetId(                        OmfGeometry       * const omfGeometry, OmfId const value);
OmfBool                     omfGeometrySetOrigin(                    OmfGeometry       * const omfGeometry, OmfCoord const value);

#define omfGeometryLineSetFromOmfGeometry(    GEOM)   (OmfGeometryLineSet  *)    ((omfGeometryGetType(GEOM) == omfElementTypeLINE_SET)     ? (GEOM) : NULL)
#define omfGeometryPointSetFromOmfGeometry(   GEOM)   (OmfGeometryPointSet *)    ((omfGeometryGetType(GEOM) == omfElementTypePOINT_SET)    ? (GEOM) : NULL)
#define omfGeometrySurfaceGridFromOmfGeometry(GEOM)   (OmfGeometrySurfaceGrid *) ((omfGeometryGetType(GEOM) == omfElementTypeSURFACE_GRID) ? (GEOM) : NULL)
#define omfGeometrySurfaceTriFromOmfGeometry( GEOM)   (OmfGeometrySurfaceTri *)  ((omfGeometryGetType(GEOM) == omfElementTypeSURFACE_TRI)  ? (GEOM) : NULL)

// Geometry Line Set routines
OmfArray                   *omfGeometryLineSetGetArrayCoord(         OmfGeometryLineSet const * const omfGeometryLineSet);
OmfArray                   *omfGeometryLineSetGetArraySegment(       OmfGeometryLineSet const * const omfGeometryLineSet);

OmfBool                     omfGeometryLineSetSetArrayCoord(         OmfGeometryLineSet * const omfGeometryLineSet, OmfArray * const value);;
OmfBool                     omfGeometryLineSetSetArraySegment(       OmfGeometryLineSet * const omfGeometryLineSet, OmfArray * const value);

// Geometry Point Set routines
OmfArray                   *omfGeometryPointSetGetArrayCoord(        OmfGeometryPointSet const * const omfGeometry);

OmfBool                     omfGeometryPointSetSetArrayCoord(        OmfGeometryPointSet       * const omfGeometry, OmfArray * const value);

// Geometry Surface Grid routines
OmfArray                   *omfGeometrySurfaceGridGetArrayOffset(    OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);
OmfArray                   *omfGeometrySurfaceGridGetArrayTensorU(   OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);
OmfArray                   *omfGeometrySurfaceGridGetArrayTensorV(   OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);
OmfVector                   omfGeometrySurfaceGridGetAxisU(          OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);
OmfVector                   omfGeometrySurfaceGridGetAxisV(          OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);

OmfBool                     omfGeometrySurfaceGridIsArrayOffsetSet(  OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid);

OmfBool                     omfGeometrySurfaceGridSetArrayOffset(    OmfGeometrySurfaceGrid       * const omfGeometrySurfaceGrid, OmfArray * const value);
OmfBool                     omfGeometrySurfaceGridSetArrayTensorU(   OmfGeometrySurfaceGrid       * const omfGeometrySurfaceGrid, OmfArray * const value);
OmfBool                     omfGeometrySurfaceGridSetArrayTensorV(   OmfGeometrySurfaceGrid       * const omfGeometrySurfaceGrid, OmfArray * const value);
OmfBool                     omfGeometrySurfaceGridSetAxisU(          OmfGeometrySurfaceGrid       * const omfGeometrySurfaceGrid, OmfVector const value);
OmfBool                     omfGeometrySurfaceGridSetAxisV(          OmfGeometrySurfaceGrid       * const omfGeometrySurfaceGrid, OmfVector const value);

// Geometry Surface Tri routines
OmfArray                   *omfGeometrySurfaceTriGetArrayCoord(      OmfGeometrySurfaceTri const * const omfGeometrySurfaceTri);
OmfArray                   *omfGeometrySurfaceTriGetArrayTriangle(   OmfGeometrySurfaceTri const * const omfGeometrySurfaceTri);

OmfBool                     omfGeometrySurfaceTriSetArrayCoord(      OmfGeometrySurfaceTri * const omfGeometrySurfaceTri, OmfArray * const value);
OmfBool                     omfGeometrySurfaceTriSetArrayTriangle(   OmfGeometrySurfaceTri * const omfGeometrySurfaceTri, OmfArray * const value);

// Project routines
OmfChar                    *omfProjectGetAuthor(                     OmfProject const * const omfProject);
OmfChar                    *omfProjectGetDate(                       OmfProject const * const omfProject);
OmfChar                    *omfProjectGetDateCreated(                OmfProject const * const omfProject);
OmfChar                    *omfProjectGetDateModified(               OmfProject const * const omfProject);
OmfChar                    *omfProjectGetDescription(                OmfProject const * const omfProject);
OmfId                       omfProjectGetId(                         OmfProject const * const omfProject);
OmfChar                    *omfProjectGetName(                       OmfProject const * const omfProject);
OmfCoord                    omfProjectGetOrigin(                     OmfProject const * const omfProject);
OmfChar                    *omfProjectGetRevision(                   OmfProject const * const omfProject);
OmfChar                    *omfProjectGetUnits(                      OmfProject const * const omfProject);

OmfBool                     omfProjectSetAuthor(                     OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetDate(                       OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetDateCreated(                OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetDateModified(               OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetDescription(                OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetId(                         OmfProject       * const omfProject, OmfId const value);
OmfBool                     omfProjectSetName(                       OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetOrigin(                     OmfProject       * const omfProject, OmfCoord const value);
OmfBool                     omfProjectSetRevision(                   OmfProject       * const omfProject, OmfChar const * const value);
OmfBool                     omfProjectSetUnits(                      OmfProject       * const omfProject, OmfChar const * const value);
