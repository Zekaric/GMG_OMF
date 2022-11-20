/******************************************************************************
file:       OmfElementPointSet
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
func: _OmfElementPointSetCreate
******************************************************************************/
OmfElementPointSet *_OmfElementPointSetCreate(void)
{
   OmfElementPointSet *omfElementPointSet;

   omfElementPointSet = memCreateType(OmfElementPointSet);
   returnNullIf(!omfElementPointSet);

   if (!_OmfElementPointSetCreateContent(omfElementPointSet))
   {
      memDestroy(omfElementPointSet);
      return NULL;
   }

   return omfElementPointSet;
}

/******************************************************************************
func: _OmfElementPointSetCreateContent
******************************************************************************/
OmfBool _OmfElementPointSetCreateContent(OmfElementPointSet * const omfElementPointSet)
{
   memClearType(OmfElementPointSet, omfElementPointSet);
   omfElementPointSet->type    = omfElementTypePOINT_SET;
   omfElementPointSet->subType = omfElementSubTypePOINT_SET_POINT_DEFAULT;

   return omfTRUE;
}

/******************************************************************************
func: _OmfElementPointSetDestroyContent
******************************************************************************/
void _OmfElementPointSetDestroyContent(OmfElementPointSet * const omfElementPointSet)
{
   returnVoidIf(!omfElementPointSet);

   omfGeometryDestroy((OmfGeometry *) omfElementPointSet->geometry);
   //omfTextureListDestroy(     omfElementPointSet->textureList);
}

/******************************************************************************
func: omfElementPointSetGetGeometry
******************************************************************************/
OmfGeometry *omfElementPointSetGetGeometry(OmfElementPointSet const * const omfElementPointSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementPointSet);

   return (OmfGeometry *) omfElementPointSet->geometry;
}

/******************************************************************************
func: omfElementPointSetGetTexture
******************************************************************************/
OmfTextureList *omfElementPointSetGetTextureList(OmfElementPointSet const * const omfElementPointSet)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementPointSet);

   return omfElementPointSet->textureList;
}

/******************************************************************************
func: omfElementPointSetIsTextureListSet
******************************************************************************/
OmfBool omfElementPointSetIsTextureListSet(OmfElementPointSet const * const omfElementPointSet)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementPointSet);

   return omfElementPointSet->isTextureListSet;
}

/******************************************************************************
func: omfElementPointSetSetGeometry
******************************************************************************/
OmfBool omfElementPointSetSetGeometry(OmfElementPointSet * const omfElementPointSet, OmfGeometryPointSet * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementPointSet);

   omfElementPointSet->geometry = value;

   return omfTRUE;
}

/******************************************************************************
func: omfElementPointSetSetTexture
******************************************************************************/
OmfBool omfElementPointSetSetTextureList(OmfElementPointSet * const omfElementPointSet, OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementPointSet);

   omfElementPointSet->textureList      =  value;
   omfElementPointSet->isTextureListSet = (value != NULL);

   return omfTRUE;
}
