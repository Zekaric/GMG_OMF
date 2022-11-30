/**************************************************************************************************
file:       OmfGeomSurfTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surf Tri routines
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
func: _OmfGeomSurfTriCreate
**************************************************************************************************/
OmfGeomSurfTri *_OmfGeomSurfTriCreate(void)
{
   OmfGeomSurfTri *geom;

   geom = _OmfMemCreateType(OmfGeomSurfTri);
   returnNullIf(!geom);

   if (!_OmfGeomSurfTriCreateContent(geom))
   {
      omfObjDestroy((OmfObj *) geom);
      return NULL;
   }

   return geom;
}

/**************************************************************************************************
func: _OmfGeomSurfTriCreateContent
**************************************************************************************************/
OmfBool _OmfGeomSurfTriCreateContent(OmfGeomSurfTri * const geom)
{
   _OmfMemClearType(OmfGeomSurfTri, geom);
   geom->typeElem = omfElemTypeSURF_TRI;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfGeomSurfTriDestroyContent
**************************************************************************************************/
void _OmfGeomSurfTriDestroyContent(OmfGeomSurfTri * const geom)
{
   returnVoidIf(!geom);

   omfArrayDestroy(geom->coord);
   omfArrayDestroy(geom->triangle);

   return;
}

/**************************************************************************************************
func: omfGeomSurfTriGetCoord
**************************************************************************************************/
OmfArray *omfGeomSurfTriGetArrayCoord(OmfGeomSurfTri const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->coord;
}

/**************************************************************************************************
func: omfGeomSurfTriGetArrayTriangle
**************************************************************************************************/
OmfArray *omfGeomSurfTriGetArrayTriangle(OmfGeomSurfTri const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->triangle;
}

/**************************************************************************************************
func: omfGeomSurfTriSetCoord
**************************************************************************************************/
OmfBool omfGeomSurfTriSetArrayCoord(OmfGeomSurfTri * const geom, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->coord = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomSurfTriSetArrayTriangle
**************************************************************************************************/
OmfBool omfGeomSurfTriSetArrayTriangle(OmfGeomSurfTri * const geom, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->triangle = value;

   return omfTRUE;
}
