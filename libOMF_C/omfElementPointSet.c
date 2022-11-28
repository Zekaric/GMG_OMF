/**************************************************************************************************
file:       OmfElemPntSet
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Pnt Set routines
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
func: _OmfElemPntSetCreate
**************************************************************************************************/
OmfElemPntSet *_OmfElemPntSetCreate(void)
{
   OmfElemPntSet *elem;

   elem = _OmfMemCreateType(OmfElemPntSet);
   returnNullIf(!elem);

   if (!_OmfElemPntSetCreateContent(elem))
   {
      _OmfMemDestroy(elem);
      return NULL;
   }

   return elem;
}

/**************************************************************************************************
func: _OmfElemPntSetCreateContent
**************************************************************************************************/
OmfBool _OmfElemPntSetCreateContent(OmfElemPntSet * const elem)
{
   _OmfMemClearType(OmfElemPntSet, elem);
   elem->typeElem    = omfElemTypePNT_SET;
   elem->typeElemSub = omfElemSubTypePNT_SET_POINT_DEFAULT;

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfElemPntSetDestroyContent
**************************************************************************************************/
void _OmfElemPntSetDestroyContent(OmfElemPntSet * const elem)
{
   returnVoidIf(!elem);

   omfObjDestroy((OmfObj *) elem->geometry);
   //omfTextureListDestroy(     elem->textureList);
}

/**************************************************************************************************
func: omfElemPntSetGetGeometry
**************************************************************************************************/
OmfGeom *omfElemPntSetGetGeometry(OmfElemPntSet const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return (OmfGeom *) elem->geometry;
}

/**************************************************************************************************
func: omfElemPntSetGetTexture
**************************************************************************************************/
OmfTextureList *omfElemPntSetGetTextureList(OmfElemPntSet const * const elem)
{
   returnNullIf(
      !omfIsStarted() ||
      !elem);

   return elem->textureList;
}

/**************************************************************************************************
func: omfElemPntSetIsTextureListSet
**************************************************************************************************/
OmfBool omfElemPntSetIsTextureListSet(OmfElemPntSet const * const elem)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   return elem->isTextureListSet;
}

/**************************************************************************************************
func: omfElemPntSetSetGeometry
**************************************************************************************************/
OmfBool omfElemPntSetSetGeometry(OmfElemPntSet * const elem, 
   OmfGeomPntSet * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->geometry = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfElemPntSetSetTexture
**************************************************************************************************/
OmfBool omfElemPntSetSetTextureList(OmfElemPntSet * const elem, 
   OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !elem);

   elem->textureList      =  value;
   elem->isTextureListSet = (value != NULL);

   return omfTRUE;
}
