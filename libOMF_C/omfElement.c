/**************************************************************************************************
file:       OmfElem
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Line set element 
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
func: omfElemCreate
**************************************************************************************************/
OmfElem *omfElemCreate(OmfElemType const type)
{
   OmfElem *elem;

   returnNullIf(type == omfElemTypeNONE);

   elem = NULL;

   switch (type)
   {
   // v1
   case omfElemTypeLINE_SET:
      elem = (OmfElem *) _OmfElemLineSetCreate();
      break;

   case omfElemTypePNT_SET:
      elem = (OmfElem *) _OmfElemPntSetCreate();
      break;

   case omfElemTypeSURF_GRID:
      elem = (OmfElem *) _OmfElemSurfGridCreate();
      break;

   case omfElemTypeSURF_TRI:
      elem = (OmfElem *) _OmfElemSurfTriCreate();
      break;

   case omfElemTypeVOL:
      elem = (OmfElem *) _OmfElemVolCreate();
      break;

   case omfElemTypeNONE:
   default:
      break;
   }

   return elem;
}

/**************************************************************************************************
func: omfElemDestroy
**************************************************************************************************/
void omfElemDestroy(OmfElem * const elem)
{
   returnVoidIf(
      !omfIsStarted() ||
      !elem);

   _OmfElemDestroyContent(elem);
   
   _OmfMemDestroy(elem);

   return;
}

/**************************************************************************************************
func: _OmfElemDestroyContent
**************************************************************************************************/
void _OmfElemDestroyContent(OmfElem * const elem)
{
   returnVoidIf(!elem);

   switch (elem->typeElem)
   {
   // v1
   case omfElemTypeLINE_SET:
      _OmfElemLineSetDestroyContent(    (OmfElemLineSet *)     elem);
      break;

   case omfElemTypePNT_SET:
      _OmfElemPntSetDestroyContent(   (OmfElemPntSet *)    elem);
      break;

   case omfElemTypeSURF_GRID:
      _OmfElemSurfGridDestroyContent((OmfElemSurfGrid *) elem);
      break;

   case omfElemTypeSURF_TRI:
      _OmfElemSurfTriDestroyContent( (OmfElemSurfTri *)  elem);
      break;

   case omfElemTypeVOL:
      _OmfElemVolDestroyContent(     (OmfElemVol *)      elem);
      break;

   case omfElemTypeNONE:
   default:
      break;
   }

   // TODO omfDataListDestroy(elem->dataList);
   omfCharDestroy(elem->dateCreated);
   omfCharDestroy(elem->dateModified);
   omfCharDestroy(elem->description);
   omfCharDestroy(elem->name);

   return;
}

/**************************************************************************************************
func: omfElemGetColor
**************************************************************************************************/
OmfColor omfElemGetColor(OmfElem const * const elem)
{
   OmfColor color;

   _OmfMemClearType(OmfColor, &color);

   returnIf(
         !omfIsStarted() ||
         !elem,
      color);

   return elem->color;
}

/**************************************************************************************************
func: omfElemGetData
**************************************************************************************************/
OmfDataList *omfElemGetData(OmfElem const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->dataList;
}

/**************************************************************************************************
func: omfElemGetDescription
**************************************************************************************************/
OmfChar *omfElemGetDescription(OmfElem const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->description;
}

/**************************************************************************************************
func: omfElemGetName
**************************************************************************************************/
OmfChar *omfElemGetName(OmfElem const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->name;
}

/**************************************************************************************************
func: omfElemGetType
**************************************************************************************************/
OmfElemType omfElemGetType(OmfElem const * const elem)
{
   returnIf(
         !omfIsStarted() ||
         !elem,
      omfArrayTypeNONE);

   return elem->typeElem;
}

/**************************************************************************************************
func: omfElemGetTypeSub
**************************************************************************************************/
OmfElemSubType omfElemGetTypeSub(OmfElem const * const elem)
{
   returnIf(
         !omfIsStarted() ||
         !elem,
      omfElemSubTypeNONE);

   return elem->typeElemSub;
}

/**************************************************************************************************
func: omfElemIsDataListSet
**************************************************************************************************/
OmfBool omfElemIsDataListSet(OmfElem const * const elem)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   return elem->isDataListSet;
}

/**************************************************************************************************
func: omfElemSetColor
**************************************************************************************************/
OmfBool omfElemSetColor(OmfElem * const elem, OmfColor const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->color = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSetData
**************************************************************************************************/
OmfBool omfElemSetDataList(OmfElem * const elem, OmfDataList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->dataList      =  value;
   elem->isDataListSet = (value != NULL);

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSetDescription
**************************************************************************************************/
OmfBool omfElemSetDescription(OmfElem * const elem, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   omfCharDestroy(elem->description);
   elem->description = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSetName
**************************************************************************************************/
OmfBool omfElemSetName(OmfElem * const elem, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   omfCharDestroy(elem->name);
   elem->name = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSetTypeSub
**************************************************************************************************/
OmfBool omfElemSetTypeSub(OmfElem * const elem, OmfElemSubType const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   switch (elem->typeElem)
   {
   case omfElemTypeLINE_SET:
      switch (value)
      {
      case omfElemSubTypeLINE_SET_LINE_DEFAULT:
      case omfElemSubTypeLINE_SET_BOREHOLE:
         elem->typeElemSub = value;
         break;

      case omfElemSubTypeNONE:
      case omfElemSubTypePNT_SET_POINT_DEFAULT:
      case omfElemSubTypePNT_SET_COLLAR:
      case omfElemSubTypePNT_SET_BLASTHOLE:
      case omfElemSubTypeSURF_GRID_SURFACE_DEFAULT:
      case omfElemSubTypeSURF_TRI_SURFACE_DEFAULT:
      case omfElemSubTypeVOL_VOLUME_DEFAULT:
      default:
         return omfFALSE;
      }
      break;

   case omfElemTypePNT_SET:
      switch (value)
      {
      case omfElemSubTypePNT_SET_POINT_DEFAULT:
      case omfElemSubTypePNT_SET_BLASTHOLE:
      case omfElemSubTypePNT_SET_COLLAR:
         elem->typeElemSub = value;
         break;

      case omfElemSubTypeNONE:
      case omfElemSubTypeLINE_SET_LINE_DEFAULT:
      case omfElemSubTypeLINE_SET_BOREHOLE:
      case omfElemSubTypeSURF_GRID_SURFACE_DEFAULT:
      case omfElemSubTypeSURF_TRI_SURFACE_DEFAULT:
      case omfElemSubTypeVOL_VOLUME_DEFAULT:
      default:
         return omfFALSE;
      }

   case omfElemTypeNONE:
   case omfElemTypeSURF_GRID:
   case omfElemTypeSURF_TRI:
   case omfElemTypeVOL:
   default:
      // only one option, should already be set.
      return omfFALSE;
   }

   return omfTRUE;
}
