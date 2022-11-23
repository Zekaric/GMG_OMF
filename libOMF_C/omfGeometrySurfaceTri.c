/**************************************************************************************************
file:       OmfGeomSurfTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surf Tri routines
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

   geom = memCreateType(OmfGeomSurfTri);
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
   memClearType(OmfGeomSurfTri, geom);
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
