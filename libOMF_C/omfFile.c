/******************************************************************************
file:       omfFile
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
The file routines.
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

/******************************************************************************
macro:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/
static OmfError _TestLoad00_09(     OmfFile       * const file, wchar_t const * const fileName);

static OmfError _WriteHeader00_09(  OmfFile const * const file, OmfOffset const position);

/******************************************************************************
glboal:
function:
******************************************************************************/
/******************************************************************************
func: omfFileCreateRead

Create an OmfFile structure.  Open the omf file for reading.  This function 
will handle the reading of old an new omf file formats.
******************************************************************************/
OmfError omfFileCreateRead(wchar_t const * const fileName, OmfFile ** const file)
{
   OmfError error;
   OmfFile *ftemp;

   returnIf(!omfIsStarted(), omfErrorLIB_NOT_STARTED); 
   returnIf(
         !fileName   ||
         !file,
      omfErrorPARAMETER_BAD);

   *file = NULL;

   // Create the structure.
   ftemp = memCreateType(OmfFile);
   returnIf(!ftemp, omfErrorMEM_CREATE_FAILURE);

   memClearType(OmfFile, ftemp);

   // Set up what needs to be set up for the project.
   _OmfProjectCreateContent(&ftemp->project);

   // Todo read in the file to see if it is a version 0.9.0 or a zip file which
   // will be a version 1.0.0 or larger.
   error = _TestLoad00_09(ftemp, fileName);
   if (error == omfErrorNONE)
   {
      ftemp->version = omfFileVersion00_09;

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

      *file = ftemp;

      return omfErrorNONE;
   }

   return error;
}

/******************************************************************************
func: omfFileCreateWrite

Create an OmfFile sturcture.  Open the omfFile for writing.  This will not over
write the file and fail.  Caller is responsible for destroying the file before
writing.

Provide the version of file you want to write to.
******************************************************************************/
OmfError omfFileCreateWrite(wchar_t const * const fileName, OmfFileVersion const fileVersion, 
   OmfFile ** const file)
{
   OmfError        error;
   OmfFile        *ftemp;

   returnIf(!omfIsStarted(), omfErrorLIB_NOT_STARTED); 
   returnIf(
         !fileName   ||
         !file       ||
         fileVersion == omfFileVersionNONE,
      omfErrorPARAMETER_BAD);

   *file = NULL;

   // Create the structure.
   ftemp = memCreateType(OmfFile);
   returnIf(!ftemp, omfErrorMEM_CREATE_FAILURE);

   memClearType(OmfFile, ftemp);

   // Set up what needs to be set up for the project.
   error = omfErrorMEM_CREATE_FAILURE;
   gotoIf(!_OmfProjectCreateContent(&ftemp->project), omfFileCreateWriteERROR);
   
   // Open the file.
   error = omfErrorFILE_OPEN_FAILURE;
   gotoIf(!_wfopen_s(&ftemp->file, fileName, L"wb"), omfFileCreateWriteERROR);

   error = omfErrorFILE_WRITE_FAILURE;
   gotoIf(!_WriteHeader00_09(ftemp, 0), omfFileCreateWriteERROR);

   ftemp->isWriting  = omfTRUE;
   ftemp->version    = fileVersion;

   *file = ftemp;

   return omfErrorNONE;

omfFileCreateWriteERROR:
   // Clean up.
   fclose(ftemp->file);
   _OmfProjectDestroyContent(&ftemp->project);
   memDestroy(ftemp);

   return error;
}

/******************************************************************************
func: omfFileDestroy

Close the file being read from or written to.  

Clean up the dynamic memory for an omf file.  
******************************************************************************/
void omfFileDestroy(OmfFile * const file)
{
   returnVoidIf(!file);

   // Close the file.
   if (file->version == omfFileVersion00_09)
   {
      // If we are writing, write out the table of contents.
      if (file->isWriting)
      {
         int64_t pos;

         // Find the end of the binary blobs.
         _fseeki64(file->file, 0, SEEK_END);
         pos = _ftelli64(file->file);
          
         // Write the 60 byte header.
         _fseeki64(file->file, 0, SEEK_SET);
         _WriteHeader00_09(file, pos);
          
         // Write the project and other items.
         _fseeki64(file->file, 0, SEEK_END);
         // _WriteTableOfContents00_09(file);
      }

      // Close the file.
      fclose(file->file);
   }
   else
   {
      // Close the zip file.
   }

   // Clean up.
   _OmfProjectDestroyContent(&file->project);

   memDestroy(file->jsonTableOfContents);
   memDestroy(file);
}

/******************************************************************************
func: omfFileGetProject
******************************************************************************/
OmfProject *omfFileGetProject(OmfFile * const file)
{
   returnNullIf(
      !omfIsStarted() ||
      !file);

   return &file->project;
}

/******************************************************************************
func: omfFileGetVersion
******************************************************************************/
OmfError omfFileGetVersion(OmfFile const * const file, OmfFileVersion * const value)
{
   returnIf(!omfIsStarted(), omfErrorLIB_NOT_STARTED); 
   returnIf(
         !file ||
         !value,
      omfErrorPARAMETER_BAD);

   *value =  file->version;

   return omfErrorNONE;
}

/******************************************************************************
func: omfFileIsWriting
******************************************************************************/
OmfBool omfFileIsWriting(OmfFile const * const file)
{
   returnFalseIf(
      !omfIsStarted() ||
      !file);

   return file->isWriting;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _TestLoad00_09

Try loading the file as an origianl 0.9.0 OMF file.
******************************************************************************/
static OmfError _TestLoad00_09(OmfFile * const file, wchar_t const * const fileName)
{
   char      magicNumber[4],
             version[32];
   uchar    *jsonTableOfContents;
   size_t    count;
   int64_t   fileSize;

   jsonTableOfContents = NULL;

   // Open the file.
   returnIf(!_wfopen_s(&file->file, fileName, L"rb"), omfErrorFILE_OPEN_FAILURE);

   // Read in the first 60 bytes header for the OMF file.
   count = fread_s(magicNumber, 4, 1, 4, file->file);
   gotoIf(count != 4, LOAD_ERROR);
   gotoIf(
         magicNumber[0] != 0x84 ||
         magicNumber[1] != 0x83 ||
         magicNumber[2] != 0x82 ||
         magicNumber[3] != 0x81,
      LOAD_ERROR);

   // Read in the version.
   count = fread_s(version, 32, 1, 32, file->file);
   gotoIf(count != 32,                                  LOAD_ERROR);
   gotoIf(!strIsEqual(version, omfVERSION00_09_00, 32), LOAD_ERROR);

   // Read in the project uid
   count = fread_s(&file->idProject, 16, 1, 16, file->file);
   gotoIf(count != 16, LOAD_ERROR);
   //TODO we probably have to endian change the GUID 

   // Read in the offset to the json.  Little Endian...  Weird.
   count = fread_s(&file->offsetTableOfContents, 8, 1, 8, file->file);
   gotoIf(count != 8, LOAD_ERROR);
   //TODO on ARM machines (MacOS M1) this value will need endian changes.

   // Jump to the end of the file.
   gotoIf(_fseeki64(file->file, 0, SEEK_END), LOAD_ERROR);
   fileSize = _ftelli64(file->file);

   // Size of the json block, table of contents, at the end of the file.
   count = fileSize - file->offsetTableOfContents;

   // Jump to the start of the json block.
   gotoIf(_fseeki64(file->file, file->offsetTableOfContents, SEEK_SET), LOAD_ERROR);

   // Allocate the buffer for the toc
   file->jsonTableOfContents = memCreateTypeArray(count, uchar);
   gotoIf(!file->jsonTableOfContents, LOAD_ERROR);

   // We got this far then we are dealing with a OMF 0.9.0 file.
   return omfErrorNONE;

LOAD_ERROR:
   // Clean up.
   memDestroy(file->jsonTableOfContents);
   file->jsonTableOfContents = NULL;

   fclose(file->file);
   file->file = NULL;

   file->offsetTableOfContents = 0;
   memClearType(OmfId, &file->idProject);

   return omfErrorFILE_NOT_OMF;
}

/******************************************************************************
func: _WriteHeader00_09
******************************************************************************/
static OmfError _WriteHeader00_09(OmfFile const * const file, OmfOffset const position)
{
   char   magicNumber[4] = { 0x84, 0x83, 0x82, 0x81 };
   char   version[32];
   size_t count;

   // Write out the magic number.
   count = fwrite(magicNumber, 1, 4, file->file);
   gotoIf(count != 4, WRITE_ERROR);

   // Write out the version number.
   memClearTypeArray(32, char,                     version);
   memCopyTypeArray( 10, char, omfVERSION00_09_00, version);
   count = fwrite(version, 1, 32, file->file);
   gotoIf(count != 32, WRITE_ERROR);

   // Write out the project id.
   count = fwrite(&file->project.id, 1, sizeof(OmfId), file->file);
   gotoIf(count != 16, WRITE_ERROR);

   // Write out the offset to the table of contents json.
   count = fwrite(&position, 8, 1, file->file);
   gotoIf(count != 8, WRITE_ERROR);

   return omfErrorNONE;

WRITE_ERROR:
   return omfErrorFILE_WRITE_FAILURE;
}
