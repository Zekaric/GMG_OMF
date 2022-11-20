/******************************************************************************
file:       OmfGeometry
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
func: omfGeometryCreate
******************************************************************************/
OmfGeometry *omfGeometryCreate(OmfElementType const type)
{
   OmfGeometry *omfGeometry;

   returnNullIf(
      !omfIsStarted() ||
      type == omfElementTypeNONE);

   omfGeometry = NULL;

   switch (type)
   {
   // v1
   case omfElementTypeLINE_SET:
      omfGeometry = (OmfGeometry *) _OmfGeometryLineSetCreate();
      break;

   case omfElementTypePOINT_SET:
      omfGeometry = (OmfGeometry *) _OmfGeometryPointSetCreate();
      break;

   case omfElementTypeSURFACE_GRID:
      omfGeometry = (OmfGeometry *) _OmfGeometrySurfaceGridCreate();
      break;

   case omfElementTypeSURFACE_TRI:
      omfGeometry = (OmfGeometry *) _OmfGeometrySurfaceTriCreate();
      break;

   case omfElementTypeVOLUME:
      omfGeometry = (OmfGeometry *) _OmfGeometryVolumeCreate();
      break;

   case omfElementTypeNONE:
   default:
      break;
   }

   return omfGeometry;
}

/******************************************************************************
func: omfGeometryDestroy
******************************************************************************/
void omfGeometryDestroy(OmfGeometry * const omfGeometry)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfGeometry);

   _OmfGeometryDestroyContent(omfGeometry);
   
   memDestroy(omfGeometry);

   return;
}

/******************************************************************************
func: _OmfGeometryDestroyContent
******************************************************************************/
void _OmfGeometryDestroyContent(OmfGeometry * const omfGeometry)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfGeometry);

   switch (omfGeometry->type)
   {
   // v1
   case omfElementTypeLINE_SET:
      _OmfGeometryLineSetDestroyContent(    (OmfGeometryLineSet *)     omfGeometry);
      break;

   case omfElementTypePOINT_SET:
      _OmfGeometryPointSetDestroyContent(   (OmfGeometryPointSet *)    omfGeometry);
      break;

   case omfElementTypeSURFACE_GRID:
      _OmfGeometrySurfaceGridDestroyContent((OmfGeometrySurfaceGrid *) omfGeometry);
      break;

   case omfElementTypeSURFACE_TRI:
      _OmfGeometrySurfaceTriDestroyContent( (OmfGeometrySurfaceTri *)  omfGeometry);
      break;

   case omfElementTypeVOLUME:
      _OmfGeometryVolumeDestroyContent(     (OmfGeometryVolume *)      omfGeometry);
      break;

   case omfElementTypeNONE:
   default:
      break;
   }

   omfCharDestroy(omfGeometry->dateCreated);
   omfCharDestroy(omfGeometry->dateModified);

   return;
}

/******************************************************************************
func: omfGeometryGetDateCreated
******************************************************************************/
OmfChar *omfGeometryGetDateCreated(OmfGeometry const * const omfGeometry)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometry);

   return omfGeometry->dateCreated;
}

/******************************************************************************
func: omfGeometryGetDateModified
******************************************************************************/
OmfChar *omfGeometryGetDateModified(OmfGeometry const * const omfGeometry)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometry);

   return omfGeometry->dateModified;
}

/******************************************************************************
func: omfGeometryGetId
******************************************************************************/
OmfId omfGeometryGetId(OmfGeometry const * const omfGeometry)
{
   OmfId id;

   memClearType(OmfId, &id);

   returnIf(
         !omfIsStarted() ||
         !omfGeometry,
      id);

   return omfGeometry->id;
}

/******************************************************************************
func: omfGeometryGetOrigin
******************************************************************************/
OmfCoord omfGeometryGetOrigin(OmfGeometry const * const omfGeometry)
{
   OmfCoord coord;

   memClearType(OmfCoord, &coord);

   returnIf(
         !omfIsStarted() ||
         !omfGeometry,
      coord);

   return omfGeometry->origin;
}

/******************************************************************************
func: omfGeometryGetType
******************************************************************************/
OmfElementType omfGeometryGetType(OmfGeometry const * const omfGeometry)
{
   returnIf(
         !omfIsStarted() ||
         !omfGeometry,
      omfElementTypeNONE);

   return omfGeometry->type;
}


/******************************************************************************
func: omfGeometryIsDateCreatedSet
******************************************************************************/
OmfBool omfGeometryIsDateCreatedSet(OmfGeometry const * const omfGeometry)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   return omfGeometry->isDateCreatedSet;
}

/******************************************************************************
func: omfGeometryIsDateModifiedSet
******************************************************************************/
OmfBool omfGeometryIsDateModifiedSet(OmfGeometry const * const omfGeometry)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   return omfGeometry->isDateModifiedSet;
}

/******************************************************************************
func: omfGeometrySetDateCreated
******************************************************************************/
OmfBool omfGeometrySetDateCreated(OmfGeometry * const omfGeometry, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   omfCharDestroy(omfGeometry->dateCreated);
   omfGeometry->dateCreated      = omfCharClone(value);
   omfGeometry->isDateCreatedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySetDateModified
******************************************************************************/
OmfBool omfGeometrySetDateModified(OmfGeometry * const omfGeometry, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   omfCharDestroy(omfGeometry->dateModified);
   omfGeometry->dateModified      = omfCharClone(value);
   omfGeometry->isDateModifiedSet = (value != NULL);

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySetId
******************************************************************************/
OmfBool omfGeometrySetId(OmfGeometry * const omfGeometry, OmfId const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   omfGeometry->id = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySetOrigin
******************************************************************************/
OmfBool omfGeometrySetOrigin(OmfGeometry * const omfGeometry, OmfCoord const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometry);

   omfGeometry->origin = value;

   return omfTRUE;
}
