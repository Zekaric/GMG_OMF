/**************************************************************************************************
file:       OmfGeomLineSet
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry line set routines
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
func: _OmfGeomLineSetCreate
**************************************************************************************************/
OmfGeomLineSet *_OmfGeomLineSetCreate(void)
{
   OmfGeomLineSet *geom;

   geom = memCreateType(OmfGeomLineSet);
   returnNullIf(!geom);

   if (!_OmfGeomLineSetCreateContent(geom))
   {
      omfObjDestroy((OmfObj *) geom);
      return NULL;
   }

   return geom;
}

/**************************************************************************************************
func: _OmfGeomLineSetCreateContent
**************************************************************************************************/
OmfBool _OmfGeomLineSetCreateContent(OmfGeomLineSet * const geom)
{
   memClearType(OmfGeomLineSet, geom);
   geom->typeElem = omfElemTypeLINE_SET;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfGeomLineSetDestroyContent
**************************************************************************************************/
void _OmfGeomLineSetDestroyContent(OmfGeomLineSet * const geom)
{
   returnVoidIf(!geom);

   omfArrayDestroy(geom->coord);
   omfArrayDestroy(geom->segment);

   return;
}

/**************************************************************************************************
func: omfGeomLineSetGetArrayCoord
**************************************************************************************************/
OmfArray *omfGeomLineSetGetArrayCoord(OmfGeomLineSet const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->coord;
}

/**************************************************************************************************
func: omfGeomLineSetGetArraySegment
**************************************************************************************************/
OmfArray *omfGeomLineSetGetArraySegment(OmfGeomLineSet const * const geom)
{
   returnNullIf(
      !omfIsStarted() ||
      !geom);

   return geom->segment;
}

/**************************************************************************************************
func: omfGeomLineSetSetArrayCoord
**************************************************************************************************/
OmfBool omfGeomLineSetSetArrayCoord(OmfGeomLineSet * const geom, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->coord = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfGeomLineSetSetArraySegment
**************************************************************************************************/
OmfBool omfGeomLineSetSetArraySegment(OmfGeomLineSet * const geom, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !geom);

   geom->segment = value;

   return omfTRUE;
}
