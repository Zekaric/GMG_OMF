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
static OmfError _TestLoad00_09_00(OmfFile * const file, wchar_t const * const fileName);

/******************************************************************************
glboal:
function:
******************************************************************************/
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
func: omfFileGetVersion
******************************************************************************/
OmfError omfFileGetVersion(OmfFile const * const file, OmfFileVersion * const value)
{
   returnIf(!_isStarted, omfErrorLIB_NOT_STARTED); 
   returnIf(
         !file ||
         !value,
      omfErrorPARAMETER_BAD);

   *value =  file->version;

   return omfErrorNONE;
}

/******************************************************************************
func: omfFileRead
******************************************************************************/
OmfError omfFileRead(wchar_t const * const fileName, OmfFile ** const file)
{
   OmfError error;
   OmfFile *ftemp;

   returnIf(!_isStarted, omfErrorLIB_NOT_STARTED); 
   returnIf(
         !fileName   ||
         !file,
      omfErrorPARAMETER_BAD);

   *file = NULL;

   // Create the structure.
   ftemp = memCreateType(OmfFile);
   returnIf(!ftemp, omfErrorMEM_CREATE_FAILURE);

   memClearType(ftemp, OmfFile);

   // Todo read in the file to see if it is a version 0.9.0 or a zip file which
   // will be a version 1.0.0 or larger.
   error = _TestLoad00_09_00(ftemp, fileName);
   if (error == omfErrorNONE)
   {
      ftemp->version = omfFileVersion00_09_00;

      //ftemp->func    = 

      // Parse the table of contents and prep the internals for client access.
      //error = _DecodeTableOfContents(ftemp);
      
      *file = ftemp;

      return omfErrorNONE;
   }

   // This is a more modern OMF file that uses a zip archive to organize its 
   // data.  Open the zip archive and get some basic data.
   //error = _TestLoadZip(ftemp, fileName);
   if (error == omfErrorNONE)
   {
      // version will have been set by _TestLoadZip() function.
      //ftemp->func = ...

      *file = ftemp;

      return omfErrorNONE;
   }

   return error;
}

/******************************************************************************
func: omfFileWrite
******************************************************************************/
OmfError omfFileWrite(wchar_t const * const fileName, OmfFileVersion const fileVersion, 
   OmfFile ** const file)
{
   OmfFile *ftemp;

   returnIf(!_isStarted, omfErrorLIB_NOT_STARTED); 
   returnIf(
         !fileName   ||
         !file       ||
         fileVersion == omfFileVersionNONE,
      omfErrorPARAMETER_BAD);

   *file = NULL;

   ftemp = memCreateType(OmfFile);
   returnIf(!ftemp, omfErrorMEM_CREATE_FAILURE);

   memClearType(ftemp, OmfFile);

   ftemp->version = fileVersion;

   *file = ftemp;

   return omfErrorNONE;
}

/******************************************************************************
lib local:
function:
******************************************************************************/
/******************************************************************************
func: _MemClear
******************************************************************************/
void _MemClear(void * const buf, size_t const size)
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
func: _MemDestroy
******************************************************************************/
void _MemDestroy(void * const buf)
{
   _memDestroy(buf);
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _TestLoad00_09_00

Try loading the file as an origianl 0.9.0 OMF file.
******************************************************************************/
static OmfError _TestLoad00_09_00(OmfFile * const file, wchar_t const * const fileName)
{
   char      magicNumber[4],
             version[32];
   uchar    *jsonTableOfContents;
   size_t    count;
   int64_t   fileSize;

   jsonTableOfContents = NULL;

   // Open the file.
   returnIf(!_wfopen_s(&file->data.d00_09_00.file, fileName, L"rb"), omfErrorFILE_OPEN_FAILURE);

   // Read in the first 60 bytes header for the OMF file.
   count = fread_s(magicNumber, 4, 1, 4, file->data.d00_09_00.file);
   gotoIf(count != 4, ERROR);
   gotoIf(
         magicNumber[0] != 84 ||
         magicNumber[1] != 83 ||
         magicNumber[2] != 82 ||
         magicNumber[3] != 81,
      ERROR);

   // Read in the version.
   count = fread_s(version, 32, 1, 32, file->data.d00_09_00.file);
   gotoIf(count != 32,                                  ERROR);
   gotoIf(!strIsEqual(version, omfVERSION00_09_00, 32), ERROR);

   // Read in the project uid
   count = fread_s(&file->data.d00_09_00.idProject, 16, 1, 16, file->data.d00_09_00.file);
   gotoIf(count != 16, ERROR);
   //TODO we probably have to endian change the GUID 

   // Read in the offset to the json.  Little Endian...  Weird.
   count = fread_s(&file->data.d00_09_00.offsetTableOfContents, 8, 1, 8, file->data.d00_09_00.file);
   gotoIf(count != 8, ERROR);
   //TODO on ARM machines (MacOS M1) this value will need endian changes.

   // Jump to the end of the file.
   gotoIf(_fseeki64(file->data.d00_09_00.file, 0, SEEK_END), ERROR);
   fileSize = _ftelli64(file->data.d00_09_00.file);

   // Size of the json block, table of contents, at the end of the file.  I am assuming it is 
   // always at the end of the file.  This flies in the face of what I have read somewhere online
   // where this TOC was to be the first block in the file and then binary blobs followed it.
   count = fileSize - file->data.d00_09_00.offsetTableOfContents;

   // Jump to the start of the json block.
   gotoIf(_fseeki64(file->data.d00_09_00.file, file->data.d00_09_00.offsetTableOfContents, SEEK_SET), ERROR);

   // Allocate the buffer for the toc
   file->data.d00_09_00.jsonTableOfContents = memCreateTypeArray(count, uchar);
   gotoIf(!file->data.d00_09_00.jsonTableOfContents, ERROR);

   // We got this far then we are dealing with a OMF 0.9.0 file.
   return omfErrorNONE;

ERROR:
   // Clean up.
   memDestroy(file->data.d00_09_00.jsonTableOfContents);
   file->data.d00_09_00.jsonTableOfContents = NULL;

   fclose(file->data.d00_09_00.file);
   file->data.d00_09_00.file = NULL;

   file->data.d00_09_00.offsetTableOfContents = 0;
   memClearType(&file->data.d00_09_00.idProject, OmfId);

   return omfErrorFILE_NOT_OMF;
}