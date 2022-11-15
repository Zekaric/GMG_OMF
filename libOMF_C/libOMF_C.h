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

/******************************************************************************
constant:
******************************************************************************/
#define libOMF_C_VERSION 1

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

typedef unsigned char   uchar;
typedef uint64_t        OmfOffset;
typedef GUID            OmfId;
typedef uchar           OmfChar;
typedef uint32_t        OmfCount;
typedef uint32_t        OmfIndex;

// Going with e)ast, n)orth, and z (elevation) to avoid abiguity.  Often software is using x, y, z to 
// represent this but in some case, because of rendering engines, y is elevation and z is north.
typedef struct
{
   double               e,
                        n,
                        z;
} OmfVec3;

typedef struct
{
   // Require
   OmfId                 id;
   OmfChar              *author;
   OmfChar              *description;
   OmfChar              *name;
   OmfChar              *revision;
   OmfChar              *units;
   OmfVec3               origin;

   // Optional
   // Not converting this to a native format.  Leaving that to the user of the library.
   // Date format "YYYY-MM-DDTHH:MM:SSZ" 24 hour time, 0 padded values.  Z = ZULU means 0 offset from GMT.
   OmfChar              *date;
   OmfChar              *dateCreated;
   OmfChar              *dateModified;
} OmfProject;

typedef struct
{
   FILE                 *file;
   OmfOffset             offsetTableOfContents;
   OmfId                 idProject;
   OmfChar              *jsonTableOfContents;
} OmfFileData00_09;

typedef struct
{
   void                 *file;
} OmfFileData01_00;

typedef struct
{
   void                 *file;
} OmfFileData02_00;

typedef union
{
   OmfFileData00_09      d00_09;
   OmfFileData01_00      d01_00;
   OmfFileData02_00      d02_00;
} OmfFileData;

typedef struct
{
   OmfBool               isWriting;
   OmfFileVersion        version;
   OmfFileData           data;
   OmfProject            project;
} OmfFile;

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
OmfBool         omfIsStarted(             void);

OmfError        omfStart(                 void *(*memCreate)(size_t size), void (*memDestroy)(void *buffer), void (*memClear)(void *buffer, size_t size));
void            omfStop(                  void);

// Char routines
OmfChar        *omfCharClone(             OmfChar const * const value);
OmfChar        *omfCharCreateFromWchar(   wchar_t const * const value);

OmfCount        omfCharGetSize(           OmfChar const * const value);

wchar_t        *wcharCreateFromOmfChar(   OmfChar const * const value);

// File routines.
OmfError        omfFileCreateRead(        wchar_t const * const fileName,                                   OmfFile ** const file);
OmfError        omfFileCreateWrite(       wchar_t const * const fileName, OmfFileVersion const fileVersion, OmfFile ** const file);

void            omfFileDestroy(           OmfFile       * const file);

OmfProject     *omfFileGetProject(        OmfFile       * const file);
OmfError        omfFileGetVersion(        OmfFile const * const file, OmfFileVersion * const value);

// Project routines
OmfChar        *omfProjectGetAuthor(      OmfProject const * const omfProject);
OmfChar        *omfProjectGetDate(        OmfProject const * const omfProject);
OmfChar        *omfProjectGetDateCreated( OmfProject const * const omfProject);
OmfChar        *omfProjectGetDateModified(OmfProject const * const omfProject);
OmfChar        *omfProjectGetDescription( OmfProject const * const omfProject);
OmfId           omfProjectGetId(          OmfProject const * const omfProject);
OmfChar        *omfProjectGetName(        OmfProject const * const omfProject);
OmfVec3         omfProjectGetOrigin(      OmfProject const * const omfProject);
OmfChar        *omfProjectGetRevision(    OmfProject const * const omfProject);
OmfChar        *omfProjectGetUnits(       OmfProject const * const omfProject);

OmfBool         omfProjectSetAuthor(      OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetDate(        OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetDateCreated( OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetDateModified(OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetDescription( OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetId(          OmfProject       * const omfProject, OmfId const value);
OmfBool         omfProjectSetName(        OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetOrigin(      OmfProject       * const omfProject, OmfVec3 const value);
OmfBool         omfProjectSetRevision(    OmfProject       * const omfProject, OmfChar const * const value);
OmfBool         omfProjectSetUnits(       OmfProject       * const omfProject, OmfChar const * const value);
