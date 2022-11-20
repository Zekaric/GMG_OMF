/******************************************************************************
file:       OmfElementSurfaceGrid
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Surface Grid element 
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
func: _OmfElementSurfaceGridCreate
******************************************************************************/
OmfElementSurfaceGrid *_OmfElementSurfaceGridCreate(void)
{
   OmfElementSurfaceGrid *omfElementSurfaceGrid;

   omfElementSurfaceGrid = memCreateType(OmfElementSurfaceGrid);
   returnNullIf(!omfElementSurfaceGrid);

   if (!_OmfElementSurfaceGridCreateContent(omfElementSurfaceGrid))
   {
      memDestroy(omfElementSurfaceGrid);
      return NULL;
   }

   return omfElementSurfaceGrid;
}

/******************************************************************************
func: _OmfElementSurfaceGridCreateContent
******************************************************************************/
OmfBool _OmfElementSurfaceGridCreateContent(OmfElementSurfaceGrid * const omfElementSurfaceGrid)
{
   memClearType(OmfElementSurfaceGrid, omfElementSurfaceGrid);
   omfElementSurfaceGrid->type    = omfElementTypeSURFACE_GRID;
   omfElementSurfaceGrid->subType = omfElementSubTypeSURFACE_GRID_SURFACE_DEFAULT;

   return omfTRUE;
}

/******************************************************************************
func: _OmfElementSurfaceGridDestroyContent
******************************************************************************/
void _OmfElementSurfaceGridDestroyContent(OmfElementSurfaceGrid * const omfElementSurfaceGrid)
{
   returnVoidIf(!omfElementSurfaceGrid);

   omfGeometryDestroy((OmfGeometry *) omfElementSurfaceGrid->geometry);
   //omfTextureListDestroy(     omfElementSurfaceGrid->textureList);

   return;
}

/******************************************************************************
func: omfElementSurfaceGridGetGeometry
******************************************************************************/
OmfGeometry *omfElementSurfaceGridGetGeometry(OmfElementSurfaceGrid const * const omfElementSurfaceGrid)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementSurfaceGrid);

   return (OmfGeometry *) omfElementSurfaceGrid->geometry;
}

/******************************************************************************
func: omfElementSurfaceGridGetTexture
******************************************************************************/
OmfTextureList *omfElementSurfaceGridGetTextureList(OmfElementSurfaceGrid const * const omfElementSurfaceGrid)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementSurfaceGrid);

   return omfElementSurfaceGrid->textureList;
}

/******************************************************************************
func: omfElementSurfaceGridIsTextureListSet
******************************************************************************/
OmfBool omfElementSurfaceGridIsTextureListSet(OmfElementSurfaceGrid const * const omfElementSurfaceGrid)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceGrid);

   return omfElementSurfaceGrid->isTextureListSet;
}

/******************************************************************************
func: omfElementSurfaceGridSetGeometry
******************************************************************************/
OmfBool omfElementSurfaceGridSetGeometry(OmfElementSurfaceGrid * const omfElementSurfaceGrid, OmfGeometrySurfaceGrid * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceGrid);

   omfElementSurfaceGrid->geometry = value;

   return omfTRUE;
}

/******************************************************************************
func: omfElementSurfaceGridSetTexture
******************************************************************************/
OmfBool omfElementSurfaceGridSetTextureList(OmfElementSurfaceGrid * const omfElementSurfaceGrid, OmfTextureList * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementSurfaceGrid);

   omfElementSurfaceGrid->textureList      =  value;
   omfElementSurfaceGrid->isTextureListSet = (value != NULL);

   return omfTRUE;
}
