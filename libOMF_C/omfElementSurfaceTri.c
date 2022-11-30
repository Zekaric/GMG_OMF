/**************************************************************************************************
file:       OmfElemSurfTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Surf Tri element 
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
