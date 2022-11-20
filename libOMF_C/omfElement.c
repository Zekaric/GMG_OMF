/******************************************************************************
file:       OmfElement
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Line set element 
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
func: omfElementCreate
******************************************************************************/
OmfElement *omfElementCreate(OmfElementType const type)
{
   OmfElement *omfElement;

   returnNullIf(type == omfElementTypeNONE);

   omfElement = NULL;

   switch (type)
   {
   // v1
   case omfElementTypeLINE_SET:
      omfElement = (OmfElement *) _OmfElementLineSetCreate();
      break;

   case omfElementTypePOINT_SET:
      omfElement = (OmfElement *) _OmfElementPointSetCreate();
      break;

   case omfElementTypeSURFACE_GRID:
      omfElement = (OmfElement *) _OmfElementSurfaceGridCreate();
      break;

   case omfElementTypeSURFACE_TRI:
      omfElement = (OmfElement *) _OmfElementSurfaceTriCreate();
      break;

   case omfElementTypeVOLUME:
      omfElement = (OmfElement *) _OmfElementVolumeCreate();
      break;

   case omfElementTypeNONE:
   default:
      break;
   }

   return omfElement;
}

/******************************************************************************
func: omfElementDestroy
******************************************************************************/
void omfElementDestroy(OmfElement * const omfElement)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfElement);

   _OmfElementDestroyContent(omfElement);
   
   memDestroy(omfElement);

   return;
}

/******************************************************************************
func: _OmfElementDestroyContent
******************************************************************************/
void _OmfElementDestroyContent(OmfElement * const omfElement)
{
   returnVoidIf(!omfElement);

   switch (omfElement->type)
   {
   // v1
   case omfElementTypeLINE_SET:
      _OmfElementLineSetDestroyContent(    (OmfElementLineSet *)     omfElement);
      break;

   case omfElementTypePOINT_SET:
      _OmfElementPointSetDestroyContent(   (OmfElementPointSet *)    omfElement);
      break;

   case omfElementTypeSURFACE_GRID:
      _OmfElementSurfaceGridDestroyContent((OmfElementSurfaceGrid *) omfElement);
      break;

   case omfElementTypeSURFACE_TRI:
      _OmfElementSurfaceTriDestroyContent( (OmfElementSurfaceTri *)  omfElement);
      break;

   case omfElementTypeVOLUME:
      _OmfElementVolumeDestroyContent(     (OmfElementVolume *)      omfElement);
      break;

   case omfElementTypeNONE:
   default:
      break;
   }

   // TODO omfDataListDestroy(omfElement->dataList);
   omfCharDestroy(omfElement->dateCreated);
   omfCharDestroy(omfElement->dateModified);
   omfCharDestroy(omfElement->description);
   omfCharDestroy(omfElement->name);

   return;
}

/******************************************************************************
func: omfElementGetColor
******************************************************************************/
OmfColor omfElementGetColor(OmfElement const * const omfElement)
{
   OmfColor color;

   memClearType(OmfColor, &color);

   returnIf(
         !omfIsStarted() ||
         !omfElement,
      color);

   return omfElement->color;
}

/******************************************************************************
func: omfElementGetData
******************************************************************************/
OmfDataList *omfElementGetData(OmfElement const * const omfElement)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->dataList;
}

/******************************************************************************
func: omfElementGetDateCreated
******************************************************************************/
OmfChar *omfElementGetDateCreated(OmfElement const * const omfElement)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->dateCreated;
}

/******************************************************************************
func: omfElementGetDateModified
******************************************************************************/
OmfChar *omfElementGetDateModified(OmfElement const * const omfElement)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->dateModified;
}

/******************************************************************************
func: omfElementGetDescription
******************************************************************************/
OmfChar *omfElementGetDescription(OmfElement const * const omfElement)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->description;
}

/******************************************************************************
func: omfElementGetId
******************************************************************************/
OmfId omfElementGetId(OmfElement const * const omfElement)
{
   OmfId id;

   memClearType(OmfId, &id);

   returnIf(
         !omfIsStarted() ||
         !omfElement,
      id);

   return omfElement->id;
}

/******************************************************************************
func: omfElementGetName
******************************************************************************/
OmfChar *omfElementGetName(OmfElement const * const omfElement)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->name;
}

/******************************************************************************
func: omfElementGetType
******************************************************************************/
OmfElementType omfElementGetType(OmfElement const * const omfElement)
{
   returnIf(
         !omfIsStarted() ||
         !omfElement,
      omfArrayTypeNONE);

   return omfElement->type;
}

/******************************************************************************
func: omfElementGetSubType
******************************************************************************/
OmfElementSubType omfElementGetSubType(OmfElement const * const omfElement)
{
   returnIf(
         !omfIsStarted() ||
         !omfElement,
      omfElementSubTypeNONE);

   return omfElement->subType;
}

/******************************************************************************
func: omfElementIsDataListSet
******************************************************************************/
OmfBool omfElementIsDataListSet(OmfElement const * const omfElement)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->isDataListSet;
}

/******************************************************************************
func: omfElementIsDateCreatedSet
******************************************************************************/
OmfBool omfElementIsDateCreatedSet(OmfElement const * const omfElement)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->isDateCreatedSet;
}

/******************************************************************************
func: omfElementIsDateModifiedSet
******************************************************************************/
OmfBool omfElementIsDateModifiedSet(OmfElement const * const omfElement)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   return omfElement->isDateModifiedSet;
}

/******************************************************************************
func: omfElementSetColor
******************************************************************************/
OmfBool omfElementSetColor(OmfElement * const omfElement, OmfColor const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfElement->color = value;

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetData
******************************************************************************/
OmfBool omfElementSetDataList(OmfElement * const omfElement, OmfDataList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfElement->dataList      =  value;
   omfElement->isDataListSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetDateCreated
******************************************************************************/
OmfBool omfElementSetDateCreated(OmfElement * const omfElement, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfCharDestroy(omfElement->dateCreated);
   omfElement->dateCreated      = omfCharClone(value);
   omfElement->isDateCreatedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetDateModified
******************************************************************************/
OmfBool omfElementSetDateModified(OmfElement * const omfElement, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfCharDestroy(omfElement->dateModified);
   omfElement->dateModified      = omfCharClone(value);
   omfElement->isDateModifiedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetDescription
******************************************************************************/
OmfBool omfElementSetDescription(OmfElement * const omfElement, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfCharDestroy(omfElement->description);
   omfElement->description = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetId
******************************************************************************/
OmfBool omfElementSetId(OmfElement * const omfElement, OmfId const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfElement->id = value;

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetName
******************************************************************************/
OmfBool omfElementSetName(OmfElement * const omfElement, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   omfCharDestroy(omfElement->name);
   omfElement->name = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfElementSetSubType
******************************************************************************/
OmfBool omfElementSetSubType(OmfElement * const omfElement, OmfElementSubType const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElement);

   switch (omfElement->type)
   {
   case omfElementTypeLINE_SET:
      switch (value)
      {
      case omfElementSubTypeLINE_SET_LINE_DEFAULT:
      case omfElementSubTypeLINE_SET_BOREHOLE:
         omfElement->subType = value;
         break;

      case omfElementSubTypeNONE:
      case omfElementSubTypePOINT_SET_POINT_DEFAULT:
      case omfElementSubTypePOINT_SET_COLLAR:
      case omfElementSubTypePOINT_SET_BLASTHOLE:
      case omfElementSubTypeSURFACE_GRID_SURFACE_DEFAULT:
      case omfElementSubTypeSURFACE_TRI_SURFACE_DEFAULT:
      case omfElementSubTypeVOLUME_VOLUME_DEFAULT:
      default:
         return omfFALSE;
      }
      break;

   case omfElementTypePOINT_SET:
      switch (value)
      {
      case omfElementSubTypePOINT_SET_POINT_DEFAULT:
      case omfElementSubTypePOINT_SET_BLASTHOLE:
      case omfElementSubTypePOINT_SET_COLLAR:
         omfElement->subType = value;
         break;

      case omfElementSubTypeNONE:
      case omfElementSubTypeLINE_SET_LINE_DEFAULT:
      case omfElementSubTypeLINE_SET_BOREHOLE:
      case omfElementSubTypeSURFACE_GRID_SURFACE_DEFAULT:
      case omfElementSubTypeSURFACE_TRI_SURFACE_DEFAULT:
      case omfElementSubTypeVOLUME_VOLUME_DEFAULT:
      default:
         return omfFALSE;
      }

   case omfElementTypeNONE:
   case omfElementTypeSURFACE_GRID:
   case omfElementTypeSURFACE_TRI:
   case omfElementTypeVOLUME:
   default:
      // only one option, should already be set.
      return omfFALSE;
   }

   return omfTRUE;
}
