/**************************************************************************************************
file:       OmfGeom
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry routines
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
