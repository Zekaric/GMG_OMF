/**************************************************************************************************
file:       OmfArray
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Array routines, binary blob data
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfArrayCreate
**************************************************************************************************/
OmfArray *_OmfArrayCreate(OmfArrayType const type)
{
   OmfArray *arrayData;

   returnNullIf(!omfIsStarted());

   arrayData = _OmfMemCreateType(OmfArray);
   returnNullIf(!arrayData);

   if (!_OmfArrayCreateContent(arrayData, type))
   {
      _OmfMemDestroy(arrayData);
      return NULL;
   }

   return arrayData;
}

/**************************************************************************************************
func: _OfArrayCreateContent
**************************************************************************************************/
OmfBool _OmfArrayCreateContent(OmfArray * const arrayData, OmfArrayType const type)
{
   returnFalseIf(!omfIsStarted());

   _OmfMemClearType(OmfArray, arrayData);
   arrayData->bufferType = type;

   return omfTRUE;
}

/**************************************************************************************************
func: omfArrayDestroyContent
**************************************************************************************************/
void omfArrayDestroyContent(OmfArray * const arrayData)
{
   returnVoidIf(
      !omfIsStarted() ||
      !arrayData);

   return;
}

/**************************************************************************************************
func: omfArrayGetBufferOffset
**************************************************************************************************/
OmfOffset omfArrayGetBufferOffset(OmfArray const * const arrayData)
{
   return0If(
      !omfIsStarted() ||
      !arrayData);

   return arrayData->bufferOffset;
}

/**************************************************************************************************
func: omfArrayGetBufferSize
**************************************************************************************************/
OmfCount omfArrayGetBufferSize(OmfArray const * const arrayData)
{
   return0If(
      !omfIsStarted() ||
      !arrayData);

   return arrayData->bufferSize;
}

/**************************************************************************************************
func: omfArrayGetBufferType
**************************************************************************************************/
OmfArrayType omfArrayGetBufferType(OmfArray const * const arrayData)
{
   returnIf(
         !omfIsStarted() ||
         !arrayData,
      omfArrayTypeNONE);

   return arrayData->bufferType;
}

/**************************************************************************************************
func: omfArrayGetBufferTypeCount
**************************************************************************************************/
OmfCount omfArrayGetBufferTypeCount(OmfArray const * const arrayData)
{
   return0If(
      !omfIsStarted() ||
      !arrayData);

   return arrayData->bufferTypeCount;
}

/**************************************************************************************************
func: omfArrayGetCoordList
**************************************************************************************************/
OmfError omfArrayGetCoordList(OmfFile const * const file, OmfArray const * const arrayData
   /* , callback to buffer filling */)
{
   // If we are writing we should not be calling this function.  This is for reading only.
   returnIf(
         !omfIsStarted()         ||
         !file                   ||
          omfFileIsWriting(file) ||
         !arrayData,
      omfErrorPARAMETER_BAD);

   // TODO reading from the file the compressed buffer.  We don't know at this point in time how
   // many coords we are reading in.  Caller needs to be able to resize their point buffer.

   return omfErrorNONE;
}

/**************************************************************************************************
func: omfArraySetBufferOffset
**************************************************************************************************/
OmfBool omfArraySetBufferOffset(OmfArray * const arrayData, OmfOffset const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !arrayData);

   arrayData->bufferOffset = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfArraySetBufferSize
**************************************************************************************************/
OmfBool omfArraySetBufferSize(OmfArray * const arrayData, OmfCount const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !arrayData);

   arrayData->bufferSize = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfArraySetBufferType
**************************************************************************************************/
OmfBool omfArraySetBufferType(OmfArray * const arrayData, OmfArrayType const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !arrayData);

   arrayData->bufferType = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfArraySetBufferTypeCount
**************************************************************************************************/
OmfBool omfArraySetBufferTypeCount(OmfArray * const arrayData, OmfCount const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !arrayData);

   arrayData->bufferTypeCount = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfArraySetCoordList
**************************************************************************************************/
OmfError omfArraySetCoordList(OmfFile * const file, OmfArray * const arrayData
   /* , callback to buffer reading */)
{
   // If we are reading, we should not be calling this function.  This is for writing only.
   returnFalseIf(
      !omfIsStarted()         ||
      !file                   ||
      !omfFileIsWriting(file) ||
      !arrayData);

   // TODO, write a new point set coordinate list buffer to the file.

   return omfErrorNONE;
}
