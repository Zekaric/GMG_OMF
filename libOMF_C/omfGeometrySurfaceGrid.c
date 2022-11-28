/**************************************************************************************************
file:       OmfGeomSurfGrid
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surf Grid routines
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
