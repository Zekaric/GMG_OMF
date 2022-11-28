/**************************************************************************************************
file:       OmfGeom
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry routines
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
func: _OmfGeomCreate
**************************************************************************************************/
OmfGeom *_OmfGeomCreate(OmfElemType const type)
{
   OmfGeom *geom;

   returnNullIf(
      !omfIsStarted() ||
      type == omfElemTypeNONE);

   geom = NULL;

   switch (type)
   {
   // v1
   case omfElemTypeLINE_SET:
      geom = (OmfGeom *) _OmfGeomLineSetCreate();
      break;

   case omfElemTypePNT_SET:
      geom = (OmfGeom *) _OmfGeomPntSetCreate();
      break;

   case omfElemTypeSURF_GRID:
      geom = (OmfGeom *) _OmfGeomSurfGridCreate();
      break;

   case omfElemTypeSURF_TRI:
      geom = (OmfGeom *) _OmfGeomSurfTriCreate();
      break;

   case omfElemTypeVOL:
      geom = (OmfGeom *) _OmfGeomVolCreate();
      break;

   case omfElemTypeNONE:
   default:
      break;
   }

   return geom;
}

/**************************************************************************************************
func: _OmfGeomDestroy
**************************************************************************************************/
void _OmfGeomDestroy(OmfGeom * const geom)
{
   returnVoidIf(
      !omfIsStarted() ||
      !geom);

   _OmfGeomDestroyContent(geom);
   
   _OmfMemDestroy(geom);

   return;
}

/**************************************************************************************************
func: _OmfGeomDestroyContent
**************************************************************************************************/
void _OmfGeomDestroyContent(OmfGeom * const geom)
{
   returnVoidIf(
      !omfIsStarted() ||
      !geom);

   switch (geom->typeElem)
   {
   // v1
   case omfElemTypeLINE_SET:
      _OmfGeomLineSetDestroyContent(    (OmfGeomLineSet *)     geom);
      break;

   case omfElemTypePNT_SET:
      _OmfGeomPntSetDestroyContent(   (OmfGeomPntSet *)    geom);
      break;

   case omfElemTypeSURF_GRID:
      _OmfGeomSurfGridDestroyContent((OmfGeomSurfGrid *) geom);
      break;

   case omfElemTypeSURF_TRI:
      _OmfGeomSurfTriDestroyContent( (OmfGeomSurfTri *)  geom);
      break;

   case omfElemTypeVOL:
      _OmfGeomVolDestroyContent(     (OmfGeomVol *)      geom);
      break;

   case omfElemTypeNONE:
   default:
      break;
   }

   omfCharDestroy(geom->dateCreated);
   omfCharDestroy(geom->dateModified);

   return;
}

/**************************************************************************************************
func: omfGeomGetOrigin
**************************************************************************************************/
OmfCoord omfGeomGetOrigin(OmfGeom const * const geom)
{
   OmfCoord coord;

   _OmfMemClearType(OmfCoord, &coord);

   returnIf(
         !omfIsStarted() ||
         !geom,
      coord);

   return geom->origin;
}

/**************************************************************************************************
func: omfGeomGetType
**************************************************************************************************/
OmfElemType omfGeomGetType(OmfGeom const * const geom)
{
   returnIf(
         !omfIsStarted() ||
         !geom,
      omfElemTypeNONE);

   return geom->typeElem;
}


/**************************************************************************************************
func: omfGeomSetOrigin
**************************************************************************************************/
OmfBool omfGeomSetOrigin(OmfGeom * const geom, OmfCoord const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->origin = value;

   return omfTRUE;
}
