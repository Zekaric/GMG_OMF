/**************************************************************************************************
file:       OmfGeomVol
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
func: _OmfGeomVolCreate
**************************************************************************************************/
OmfGeomVol *_OmfGeomVolCreate(void)
{
   OmfGeomVol *geom;

   geom = memCreateType(OmfGeomVol);
   returnNullIf(!geom);

   if (!_OmfGeomVolCreateContent(geom))
   {
      omfObjDestroy((OmfObj *) geom);
      return NULL;
   }

   return geom;
}

/**************************************************************************************************
func: _OmfGeomVolCreateContent
**************************************************************************************************/
OmfBool _OmfGeomVolCreateContent(OmfGeomVol * const geom)
{
   memClearType(OmfGeomVol, geom);
   geom->typeElem = omfElemTypeVOL;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfGeomVolDestroyContent
**************************************************************************************************/
void _OmfGeomVolDestroyContent(OmfGeomVol * const geom)
{
   returnVoidIf(!geom);

   omfArrayDestroy(geom->tensorU);
   omfArrayDestroy(geom->tensorV);
   omfArrayDestroy(geom->tensorW);

   return;
}

/**************************************************************************************************
func: omfGeomVolGetArrayTensorU
**************************************************************************************************/
OmfArray *omfGeomVolGetArrayTensorU(OmfGeomVol const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->tensorU;
}

/**************************************************************************************************
func: omfGeomVolGetArrayTensorV
**************************************************************************************************/
OmfArray *omfGeomVolGetArrayTensorV(OmfGeomVol const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->tensorV;
}

/**************************************************************************************************
func: omfGeomVolGetArrayTensorW
**************************************************************************************************/
OmfArray *omfGeomVolGetArrayTensorW(OmfGeomVol const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->tensorW;
}

/**************************************************************************************************
func: omfGeomVolGetAxisU
**************************************************************************************************/
OmfVector omfGeomVolGetAxisU(OmfGeomVol const * const geom)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !geom,
      vec);

   return geom->axisU;
}

/**************************************************************************************************
func: omfGeomVolGetAxisV
**************************************************************************************************/
OmfVector omfGeomVolGetAxisV(OmfGeomVol const * const geom)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !geom,
      vec);

   return geom->axisV;
}

/**************************************************************************************************
func: omfGeomVolGetAxisW
**************************************************************************************************/
OmfVector omfGeomVolGetAxisW(OmfGeomVol const * const geom)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !geom,
      vec);

   return geom->axisW;
}

/**************************************************************************************************
func: omfGeomVolSetArrayTensorU
**************************************************************************************************/
OmfBool omfGeomVolSetArrayTensorU(OmfGeomVol * const geom, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->tensorU = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomVolSetArrayTensorV
**************************************************************************************************/
OmfBool omfGeomVolSetArrayTensorV(OmfGeomVol * const geom, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->tensorV = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomVolSetArrayTensorW
**************************************************************************************************/
OmfBool omfGeomVolSetArrayTensorW(OmfGeomVol * const geom, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->tensorW = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomVolSetAxisU
**************************************************************************************************/
OmfBool omfGeomVolSetAxisU(OmfGeomVol * const geom, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->axisU = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomVolSetAxisV
**************************************************************************************************/
OmfBool omfGeomVolSetAxisV(OmfGeomVol * const geom, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->axisV = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomVolSetAxisW
**************************************************************************************************/
OmfBool omfGeomVolSetAxisW(OmfGeomVol * const geom, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->axisW = value;

   return omfTRUE;
}
