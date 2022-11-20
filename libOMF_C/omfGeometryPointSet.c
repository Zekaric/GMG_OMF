/******************************************************************************
file:       OmfGeometryPointSet
author:     Robbert de Groot
company:    Robbert de Groot
copyright:  2022, Robbert de Groot

description:

******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pch.h"

/******************************************************************************
local:
constant:
******************************************************************************/

/******************************************************************************
type:
******************************************************************************/

/******************************************************************************
variable:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: _OmfGeometryPointSetCreate
******************************************************************************/
OmfGeometryPointSet *_OmfGeometryPointSetCreate(void)
{
   OmfGeometryPointSet *omfGeometryPointSet;

   omfGeometryPointSet = memCreateType(OmfGeometryPointSet);
   returnNullIf(!omfGeometryPointSet);

   if (!_OmfGeometryPointSetCreateContent(omfGeometryPointSet))
   {
      omfGeometryDestroy((OmfGeometry *) omfGeometryPointSet);
      return NULL;
   }

   return omfGeometryPointSet;
}

/******************************************************************************
func: _OmfGeometryPointSetCreateContent
******************************************************************************/
OmfBool _OmfGeometryPointSetCreateContent(OmfGeometryPointSet * const omfGeometryPointSet)
{
   memClearType(OmfGeometryPointSet, omfGeometryPointSet);
   omfGeometryPointSet->type = omfElementTypePOINT_SET;

   return omfTRUE;
}

/******************************************************************************
func: _OmfGeometryPointSetDestroyContent
******************************************************************************/
void _OmfGeometryPointSetDestroyContent(OmfGeometryPointSet * const omfGeometryPointSet)
{
   returnVoidIf(!omfGeometryPointSet);

   omfArrayDestroy(omfGeometryPointSet->coord);

   return;
}

/******************************************************************************
func: omfGeometryPointSetGetCoord
******************************************************************************/
OmfArray *omfGeometryPointSetGetArrayCoord(OmfGeometryPointSet const * const omfGeometryPointSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryPointSet);

   return omfGeometryPointSet->coord;
}

/******************************************************************************
func: omfGeometryPointSetSetCoord
******************************************************************************/
OmfBool omfGeometryPointSetSetArrayCoord(OmfGeometryPointSet * const omfGeometryPointSet, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryPointSet);

   omfGeometryPointSet->coord = value;

   return omfTRUE;
}
