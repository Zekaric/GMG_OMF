/**************************************************************************************************
file:       OmfElemSurfGrid
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Surf Grid element 
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
func: _OmfElemSurfGridCreate
**************************************************************************************************/
OmfElemSurfGrid *_OmfElemSurfGridCreate(void)
{
   OmfElemSurfGrid *elem;

   elem = _OmfMemCreateType(OmfElemSurfGrid);
   returnNullIf(!elem);

   if (!_OmfElemSurfGridCreateContent(elem))
   {
      _OmfMemDestroy(elem);
      return NULL;
   }

   return elem;
}

/**************************************************************************************************
func: _OmfElemSurfGridCreateContent
**************************************************************************************************/
OmfBool _OmfElemSurfGridCreateContent(OmfElemSurfGrid * const elem)
{
   _OmfMemClearType(OmfElemSurfGrid, elem);
   elem->typeElem    = omfElemTypeSURF_GRID;
   elem->typeElemSub = omfElemSubTypeSURF_GRID_SURFACE_DEFAULT;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfElemSurfGridDestroyContent
**************************************************************************************************/
void _OmfElemSurfGridDestroyContent(OmfElemSurfGrid * const elem)
{
   returnVoidIf(!elem);

   omfObjDestroyObj(elem->geometry);
   //omfTextureListDestroy(     elem->textureList);

   return;
}

/**************************************************************************************************
func: omfElemSurfGridGetGeometry
**************************************************************************************************/
OmfGeom *omfElemSurfGridGetGeometry(OmfElemSurfGrid const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return (OmfGeom *) elem->geometry;
}

/**************************************************************************************************
func: omfElemSurfGridGetTexture
**************************************************************************************************/
OmfTextureList *omfElemSurfGridGetTextureList(OmfElemSurfGrid const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->textureList;
}

/**************************************************************************************************
func: omfElemSurfGridIsTextureListSet
**************************************************************************************************/
OmfBool omfElemSurfGridIsTextureListSet(OmfElemSurfGrid const * const elem)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   return elem->isTextureListSet;
}

/**************************************************************************************************
func: omfElemSurfGridSetGeometry
**************************************************************************************************/
OmfBool omfElemSurfGridSetGeometry(OmfElemSurfGrid * const elem, 
   OmfGeomSurfGrid * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->geometry = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemSurfGridSetTexture
**************************************************************************************************/
OmfBool omfElemSurfGridSetTextureList(OmfElemSurfGrid * const elem, 
   OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->textureList      =  value;
   elem->isTextureListSet = (value != NULL);

   return omfTRUE;
}
