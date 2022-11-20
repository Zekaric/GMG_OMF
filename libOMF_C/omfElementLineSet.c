/******************************************************************************
file:       OmfElementLineSet
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Line set element 
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
func: _OmfElementLineSetCreate
******************************************************************************/
OmfElementLineSet *_OmfElementLineSetCreate(void)
{
   OmfElementLineSet *omfElementLineSet;

   omfElementLineSet = memCreateType(OmfElementLineSet);
   returnNullIf(!omfElementLineSet);

   if (!_OmfElementLineSetCreateContent(omfElementLineSet))
   {
      memDestroy(omfElementLineSet);
      return NULL;
   }

   return omfElementLineSet;
}

/******************************************************************************
func: _OmfElementLineSetCreateContent
******************************************************************************/
OmfBool _OmfElementLineSetCreateContent(OmfElementLineSet * const omfElementLineSet)
{
   memClearType(OmfElementLineSet, omfElementLineSet);
   omfElementLineSet->type    = omfElementTypeLINE_SET;
   omfElementLineSet->subType = omfElementSubTypeLINE_SET_LINE_DEFAULT;

   return omfTRUE;
}

/******************************************************************************
func: _OmfElementLineSetDestroyContent
******************************************************************************/
void _OmfElementLineSetDestroyContent(OmfElementLineSet * const omfElementLineSet)
{
   returnVoidIf(!omfElementLineSet);

   omfGeometryDestroy((OmfGeometry *) omfElementLineSet->geometry);

   return;
}

/******************************************************************************
func: omfElementLineSetGetGeometry
******************************************************************************/
OmfGeometry *omfElementLineSetGetGeometry(OmfElementLineSet const * const omfElementLineSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementLineSet);

   return (OmfGeometry *) omfElementLineSet->geometry;
}

/******************************************************************************
func: omfElementLineSetSetGeometry
******************************************************************************/
OmfBool omfElementLineSetSetGeometry(OmfElementLineSet * const omfElementLineSet, OmfGeometryLineSet * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementLineSet);

   omfElementLineSet->geometry = value;

   return omfTRUE;
}
