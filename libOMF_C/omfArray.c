/******************************************************************************
file:       OmfArray
author:     Robbert de Groot
company:    Robbert de Groot
copyright:  2022, Robbert de Groot

description:

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
prototype:
******************************************************************************/

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: omfArrayCreate
******************************************************************************/
OmfArray *omfArrayCreate(void)
{
   OmfArray *omfArray;

   returnNullIf(!omfIsStarted());

   omfArray = memCreateType(OmfArray);
   returnNullIf(!omfArray);

   if (!omfArrayCreateContent(omfArray))
   {
      memDestroy(omfArray);
      return NULL;
   }

   return omfArray;
}

/******************************************************************************
func: omfArrayCreateContent
******************************************************************************/
OmfBool omfArrayCreateContent(OmfArray * const omfArray)
{
   returnFalseIf(!omfIsStarted());

   memClearType(OmfArray, omfArray);

   return omfTRUE;
}

/******************************************************************************
func: omfArrayDestroy
******************************************************************************/
void omfArrayDestroy(OmfArray * const omfArray)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfArray);

   omfArrayDestroyContent(omfArray);
   
   memDestroy(omfArray);

   return;
}

/******************************************************************************
func: omfArrayDestroyContent
******************************************************************************/
void omfArrayDestroyContent(OmfArray * const omfArray)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfArray);

   omfCharDestroy(omfArray->dateCreated);
   omfCharDestroy(omfArray->dateModified);

   return;
}

/******************************************************************************
func: omfArrayGetBufferOffset
******************************************************************************/
OmfOffset omfArrayGetBufferOffset(OmfArray const * const omfArray)
{
   return0If(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->bufferOffset;
}

/******************************************************************************
func: omfArrayGetBufferSize
******************************************************************************/
OmfCount omfArrayGetBufferSize(OmfArray const * const omfArray)
{
   return0If(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->bufferSize;
}

/******************************************************************************
func: omfArrayGetBufferType
******************************************************************************/
OmfArrayType omfArrayGetBufferType(OmfArray const * const omfArray)
{
   returnIf(
         !omfIsStarted() ||
         !omfArray,
      omfArrayTypeNONE);

   return omfArray->bufferType;
}

/******************************************************************************
func: omfArrayGetBufferTypeCount
******************************************************************************/
OmfCount omfArrayGetBufferTypeCount(OmfArray const * const omfArray)
{
   return0If(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->bufferTypeCount;
}

/******************************************************************************
func: omfArrayGetCoordList
******************************************************************************/
OmfError omfArrayGetCoordList(OmfFile const * const file, OmfArray const * const omfArray/* , callback to buffer filling */)
{
   // If we are writing we should not be calling this function.  This is for reading only.
   returnIf(
         !omfIsStarted()         ||
         !file                   ||
          omfFileIsWriting(file) ||
         !omfArray,
      omfErrorPARAMETER_BAD);

   // TODO reading from the file the compressed buffer.  We don't know at this point in time how
   // many coords we are reading in.  Caller needs to be able to resize their point buffer.

   return omfErrorNONE;
}

/******************************************************************************
func: omfArrayGetDateCreated
******************************************************************************/
OmfChar *omfArrayGetDateCreated(OmfArray const * const omfArray)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->dateCreated;
}

/******************************************************************************
func: omfArrayGetDateModified
******************************************************************************/
OmfChar *omfArrayGetDateModified(OmfArray const * const omfArray)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->dateModified;
}

/******************************************************************************
func: omfArrayGetId
******************************************************************************/
OmfId omfArrayGetId(OmfArray const * const omfArray)
{
   OmfId id;

   memClearType(OmfId, &id);

   returnIf(
         !omfIsStarted() ||
         !omfArray,
      id);

   return omfArray->id;
}

/******************************************************************************
func: omfArrayIsDateCreated
******************************************************************************/
OmfBool omfArrayIsDateCreated(OmfArray const * const omfArray)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->isDateCreatedSet;
}

/******************************************************************************
func: omfArrayIsDateModified
******************************************************************************/
OmfBool omfArrayIsDateModified(OmfArray const * const omfArray)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   return omfArray->isDateModifiedSet;
}

/******************************************************************************
func: omfArraySetBufferOffset
******************************************************************************/
OmfBool omfArraySetBufferOffset(OmfArray * const omfArray, OmfOffset const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfArray->bufferOffset = value;

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetBufferSize
******************************************************************************/
OmfBool omfArraySetBufferSize(OmfArray * const omfArray, OmfCount const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfArray->bufferSize = value;

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetBufferType
******************************************************************************/
OmfBool omfArraySetBufferType(OmfArray * const omfArray, OmfArrayType const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfArray->bufferType = value;

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetBufferTypeCount
******************************************************************************/
OmfBool omfArraySetBufferTypeCount(OmfArray * const omfArray, OmfCount const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfArray->bufferTypeCount = value;

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetCoordList
******************************************************************************/
OmfError omfArraySetCoordList(OmfFile * const file, OmfArray * const omfArray/* , callback to buffer reading */)
{
   // If we are reading, we should not be calling this function.  This is for writing only.
   returnFalseIf(
      !omfIsStarted()         ||
      !file                   ||
      !omfFileIsWriting(file) ||
      !omfArray);

   // TODO, write a new point set coordinate list buffer to the file.

   return omfErrorNONE;
}

/******************************************************************************
func: omfArraySetDateCreated
******************************************************************************/
OmfBool omfArraySetDateCreated(OmfArray * const omfArray, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfCharDestroy(omfArray->dateCreated);
   omfArray->dateCreated      = omfCharClone(value);
   omfArray->isDateCreatedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetDateModified
******************************************************************************/
OmfBool omfArraySetDateModified(OmfArray * const omfArray, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfCharDestroy(omfArray->dateModified);
   omfArray->dateModified      = omfCharClone(value);
   omfArray->isDateModifiedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfArraySetId
******************************************************************************/
OmfBool omfArraySetId(OmfArray * const omfArray, OmfId const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfArray);

   omfArray->id = value;

   return omfTRUE;
}
