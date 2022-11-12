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
   omfErrorNONE,
   omfErrorFILE_CREATE_FAILUE,
   omfErrorFILE_NOT_OMF,
   omfErrorFILE_OPEN_FAILURE,
   omfErrorLIB_NOT_STARTED,
   omfErrorMEM_CREATE_FAILURE,
   omfErrorPARAMETER_BAD,
   
   omfErrorCOUNT
} OmfError;

typedef enum
{
   omfFileVersionNONE,

   omfFileVersion00_09_00,
   omfFileVersion01_00_00,
   omfFileVersion02_00_00,

   omfFileVersionCOUNT
} OmfFileVersion;

typedef unsigned char   uchar;

typedef uint64_t        OmfOffset;

typedef GUID            OmfId;

typedef uchar           OmfChar;

typedef enum
{
   
} OmfFuncV00_09_00;

typedef enum
{
   
} OmfFuncV01_00_00;

typedef enum
{
   
} OmfFuncV02_00_00;

typedef union
{
   OmfFuncV00_09_00      f00_09_00;
   OmfFuncV01_00_00      f01_00_00;
   OmfFuncV02_00_00      f02_00_00;
} OmfFunc;

typedef struct
{
   FILE                 *file;
   OmfOffset             offsetTableOfContents;
   OmfId                 idProject;
   OmfChar              *jsonTableOfContents;
} OmfFileData00_09_00;

typedef struct
{
   void                 *file;
} OmfFileData01_00_00;

typedef struct
{
   void                 *file;
} OmfFileData02_00_00;

typedef union
{
   OmfFileData00_09_00   d00_09_00;
   OmfFileData01_00_00   d01_00_00;
   OmfFileData02_00_00   d02_00_00;
} OmfFileData;

typedef struct
{
   OmfFileVersion        version;
   OmfFunc               func;
   OmfFileData           data;
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
OmfError        omfStart(           void *(*memCreate)(size_t size), void (*memDestroy)(void *buffer), void (*memClear)(void *buffer, size_t size));
void            omfStop(            void);

OmfError        omfFileGetVersion(  OmfFile const * const file, OmfFileVersion * const value);
OmfError        omfFileRead(        wchar_t const * const fileName,                                   OmfFile ** const file);
OmfError        omfFileWrite(       wchar_t const * const fileName, OmfFileVersion const fileVersion, OmfFile ** const file);

