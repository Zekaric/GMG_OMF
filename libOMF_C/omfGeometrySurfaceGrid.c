/**************************************************************************************************
file:       OmfGeomSurfGrid
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surf Grid routines
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
func: _OmfGeomSurfGridCreate
**************************************************************************************************/
OmfGeomSurfGrid *_OmfGeomSurfGridCreate(void)
{
   OmfGeomSurfGrid *geom;

   geom = _OmfMemCreateType(OmfGeomSurfGrid);
   returnNullIf(!geom);

   if (!_OmfGeomSurfGridCreateContent(geom))
   {
      omfObjDestroy((OmfObj *) geom);
      return NULL;
   }

   return geom;
}

/**************************************************************************************************
func: _OmfGeomSurfGridCreateContent
**************************************************************************************************/
OmfBool _OmfGeomSurfGridCreateContent(OmfGeomSurfGrid * const geom)
{
   _OmfMemClearType(OmfGeomSurfGrid, geom);
   geom->typeElem = omfElemTypeSURF_GRID;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfGeomSurfGridDestroyContent
**************************************************************************************************/
void _OmfGeomSurfGridDestroyContent(OmfGeomSurfGrid * const geom)
{
   returnVoidIf(!geom);

   omfArrayDestroy(geom->offset);
   omfArrayDestroy(geom->tensorU);
   omfArrayDestroy(geom->tensorV);

   return;
}

/**************************************************************************************************
func: omfGeomSurfGridGetArrayOffset
**************************************************************************************************/
OmfArray *omfGeomSurfGridGetArrayOffset(OmfGeomSurfGrid const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->offset;
}

/**************************************************************************************************
func: omfGeomSurfGridGetArrayTensorU
**************************************************************************************************/
OmfArray *omfGeomSurfGridGetArrayTensorU(OmfGeomSurfGrid const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->tensorU;
}

/**************************************************************************************************
func: omfGeomSurfGridGetArrayTensorV
**************************************************************************************************/
OmfArray *omfGeomSurfGridGetArrayTensorV(OmfGeomSurfGrid const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->tensorV;
}

/**************************************************************************************************
func: omfGeomSurfGridGetAxisU
**************************************************************************************************/
OmfVector omfGeomSurfGridGetAxisU(OmfGeomSurfGrid const * const geom)
{
   OmfVector vec;

   _OmfMemClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !geom,
      vec);

   return geom->axisU;
}

/**************************************************************************************************
func: omfGeomSurfGridGetAxisV
**************************************************************************************************/
OmfVector omfGeomSurfGridGetAxisV(OmfGeomSurfGrid const * const geom)
{
   OmfVector vec;

   _OmfMemClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !geom,
      vec);

   return geom->axisV;
}

/**************************************************************************************************
func: omfGeomSurfGridIsArrayOffsetSet
**************************************************************************************************/
OmfBool omfGeomSurfGridIsArrayOffsetSet(OmfGeomSurfGrid const * const geom)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   return geom->isOffsetSet;
}

/**************************************************************************************************
func: omfGeomSurfGridSetArrayOffset
**************************************************************************************************/
OmfBool omfGeomSurfGridSetArrayOffset(OmfGeomSurfGrid * const geom, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->offset = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomSurfGridSetArrayTensorU
**************************************************************************************************/
OmfBool omfGeomSurfGridSetArrayTensorU(OmfGeomSurfGrid * const geom, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->tensorU = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomSurfGridSetArrayTensorV
**************************************************************************************************/
OmfBool omfGeomSurfGridSetArrayTensorV(OmfGeomSurfGrid * const geom, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->tensorV = value;

   return omfTRUE;
}
/**************************************************************************************************
func: omfGeomSurfGridSetAxisU
**************************************************************************************************/
OmfBool omfGeomSurfGridSetAxisU(OmfGeomSurfGrid * const geom, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->axisU = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomSurfGridSetAxisV
**************************************************************************************************/
OmfBool omfGeomSurfGridSetAxisV(OmfGeomSurfGrid * const geom, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->axisV = value;

   return omfTRUE;
}
