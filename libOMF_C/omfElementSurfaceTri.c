/******************************************************************************
file:       OmfElementSurfaceTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Surface Tri element 
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
func: _OmfElementSurfaceTriCreate
******************************************************************************/
OmfElementSurfaceTri *_OmfElementSurfaceTriCreate(void)
{
   OmfElementSurfaceTri *omfElementSurfaceTri;

   omfElementSurfaceTri = memCreateType(OmfElementSurfaceTri);
   returnNullIf(!omfElementSurfaceTri);

   if (!_OmfElementSurfaceTriCreateContent(omfElementSurfaceTri))
   {
      memDestroy(omfElementSurfaceTri);
      return NULL;
   }

   return omfElementSurfaceTri;
}

/******************************************************************************
func: _OmfElementSurfaceTriCreateContent
******************************************************************************/
OmfBool _OmfElementSurfaceTriCreateContent(OmfElementSurfaceTri * const omfElementSurfaceTri)
{
   memClearType(OmfElementSurfaceTri, omfElementSurfaceTri);
   omfElementSurfaceTri->type    = omfElementTypeSURFACE_GRID;
   omfElementSurfaceTri->subType = omfElementSubTypeSURFACE_TRI_SURFACE_DEFAULT;

   return omfTRUE;
}

/******************************************************************************
func: _OmfElementSurfaceTriDestroyContent
******************************************************************************/
void _OmfElementSurfaceTriDestroyContent(OmfElementSurfaceTri * const omfElementSurfaceTri)
{
   returnVoidIf(!omfElementSurfaceTri);

   omfGeometryDestroy((OmfGeometry *) omfElementSurfaceTri->geometry);
   //omfTextureListDestroy(     omfElementSurfaceTri->textureList);

   return;
}

/******************************************************************************
func: omfElementSurfaceTriGetGeometry
******************************************************************************/
OmfGeometry *omfElementSurfaceTriGetGeometry(OmfElementSurfaceTri const * const omfElementSurfaceTri)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementSurfaceTri);

   return (OmfGeometry *) omfElementSurfaceTri->geometry;
}

/******************************************************************************
func: omfElementSurfaceTriGetTexture
******************************************************************************/
OmfTextureList *omfElementSurfaceTriGetTextureList(OmfElementSurfaceTri const * const omfElementSurfaceTri)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementSurfaceTri);

   return omfElementSurfaceTri->textureList;
}

/******************************************************************************
func: omfElementSurfaceTriIsTextureListSet
******************************************************************************/
OmfBool omfElementSurfaceTriIsTextureListSet(OmfElementSurfaceTri const * const omfElementSurfaceTri)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceTri);

   return omfElementSurfaceTri->isTextureListSet;
}

/******************************************************************************
func: omfElementSurfaceTriSetGeometry
******************************************************************************/
OmfBool omfElementSurfaceTriSetGeometry(OmfElementSurfaceTri * const omfElementSurfaceTri, OmfGeometrySurfaceTri * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceTri);

   omfElementSurfaceTri->geometry = value;

   return omfTRUE;
}

/******************************************************************************
func: omfElementSurfaceTriSetTexture
******************************************************************************/
OmfBool omfElementSurfaceTriSetTextureList(OmfElementSurfaceTri * const omfElementSurfaceTri, OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceTri);

   omfElementSurfaceTri->textureList      =  value;
   omfElementSurfaceTri->isTextureListSet = (value != NULL);

   return omfTRUE;
}
