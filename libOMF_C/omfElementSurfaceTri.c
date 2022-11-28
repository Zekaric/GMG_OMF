/**************************************************************************************************
file:       OmfElemSurfTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Surf Tri element 
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
func: _OmfElemSurfTriCreate
**************************************************************************************************/
OmfElemSurfTri *_OmfElemSurfTriCreate(void)
{
   OmfElemSurfTri *elem;

   elem = _OmfMemCreateType(OmfElemSurfTri);
   returnNullIf(!elem);

   if (!_OmfElemSurfTriCreateContent(elem))
   {
      _OmfMemDestroy(elem);
      return NULL;
   }

   return elem;
}

/**************************************************************************************************
func: _OmfElemSurfTriCreateContent
**************************************************************************************************/
OmfBool _OmfElemSurfTriCreateContent(OmfElemSurfTri * const elem)
{
   _OmfMemClearType(OmfElemSurfTri, elem);
   elem->typeElem    = omfElemTypeSURF_GRID;
   elem->typeElemSub = omfElemSubTypeSURF_TRI_SURFACE_DEFAULT;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfElemSurfTriDestroyContent
**************************************************************************************************/
void _OmfElemSurfTriDestroyContent(OmfElemSurfTri * const elem)
{
   returnVoidIf(!elem);

   omfObjDestroyObj(elem->geometry);
   //omfTextureListDestroy(     elem->textureList);

   return;
}

/**************************************************************************************************
func: omfElemSurfTriGetGeometry
**************************************************************************************************/
OmfGeom *omfElemSurfTriGetGeometry(OmfElemSurfTri const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return (OmfGeom *) elem->geometry;
}

/**************************************************************************************************
func: omfElemSurfTriGetTexture
**************************************************************************************************/
OmfTextureList *omfElemSurfTriGetTextureList(OmfElemSurfTri const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->textureList;
}

/**************************************************************************************************
func: omfElemSurfTriIsTextureListSet
**************************************************************************************************/
OmfBool omfElemSurfTriIsTextureListSet(OmfElemSurfTri const * const elem)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   return elem->isTextureListSet;
}

/**************************************************************************************************
func: omfElemSurfTriSetGeometry
**************************************************************************************************/
OmfBool omfElemSurfTriSetGeometry(OmfElemSurfTri * const elem, 
   OmfGeomSurfTri * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->geometry = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSurfTriSetTexture
**************************************************************************************************/
OmfBool omfElemSurfTriSetTextureList(OmfElemSurfTri * const elem, 
   OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->textureList      =  value;
   elem->isTextureListSet = (value != NULL);

   return omfTRUE;
}
