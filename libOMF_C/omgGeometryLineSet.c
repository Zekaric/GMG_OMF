/******************************************************************************
file:       OmfGeometryLineSet
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry line set routines
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
func: _OmfGeometryLineSetCreate
******************************************************************************/
OmfGeometryLineSet *_OmfGeometryLineSetCreate(void)
{
   OmfGeometryLineSet *omfGeometryLineSet;

   omfGeometryLineSet = memCreateType(OmfGeometryLineSet);
   returnNullIf(!omfGeometryLineSet);

   if (!_OmfGeometryLineSetCreateContent(omfGeometryLineSet))
   {
      omfGeometryDestroy((OmfGeometry *) omfGeometryLineSet);
      return NULL;
   }

   return omfGeometryLineSet;
}

/******************************************************************************
func: _OmfGeometryLineSetCreateContent
******************************************************************************/
OmfBool _OmfGeometryLineSetCreateContent(OmfGeometryLineSet * const omfGeometryLineSet)
{
   memClearType(OmfGeometryLineSet, omfGeometryLineSet);
   omfGeometryLineSet->type = omfElementTypeLINE_SET;

   return omfTRUE;
}

/******************************************************************************
func: _OmfGeometryLineSetDestroyContent
******************************************************************************/
void _OmfGeometryLineSetDestroyContent(OmfGeometryLineSet * const omfGeometryLineSet)
{
   returnVoidIf(!omfGeometryLineSet);

   omfArrayDestroy(omfGeometryLineSet->coord);
   omfArrayDestroy(omfGeometryLineSet->segment);

   return;
}

/******************************************************************************
func: omfGeometryLineSetGetArrayCoord
******************************************************************************/
OmfArray *omfGeometryLineSetGetArrayCoord(OmfGeometryLineSet const * const omfGeometryLineSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryLineSet);

   return omfGeometryLineSet->coord;
}

/******************************************************************************
func: omfGeometryLineSetGetArraySegment
******************************************************************************/
OmfArray *omfGeometryLineSetGetArraySegment(OmfGeometryLineSet const * const omfGeometryLineSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryLineSet);

   return omfGeometryLineSet->segment;
}

/******************************************************************************
func: omfGeometryLineSetSetArrayCoord
******************************************************************************/
OmfBool omfGeometryLineSetSetArrayCoord(OmfGeometryLineSet * const omfGeometryLineSet, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryLineSet);

   omfGeometryLineSet->coord = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryLineSetSetArraySegment
******************************************************************************/
OmfBool omfGeometryLineSetSetArraySegment(OmfGeometryLineSet * const omfGeometryLineSet, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryLineSet);

   omfGeometryLineSet->segment = value;

   return omfTRUE;
}
