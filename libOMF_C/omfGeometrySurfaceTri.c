/******************************************************************************
file:       OmfGeometrySurfaceTri
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surface Tri routines
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
func: _OmfGeometrySurfaceTriCreate
******************************************************************************/
OmfGeometrySurfaceTri *_OmfGeometrySurfaceTriCreate(void)
{
   OmfGeometrySurfaceTri *omfGeometrySurfaceTri;

   omfGeometrySurfaceTri = memCreateType(OmfGeometrySurfaceTri);
   returnNullIf(!omfGeometrySurfaceTri);

   if (!_OmfGeometrySurfaceTriCreateContent(omfGeometrySurfaceTri))
   {
      omfGeometryDestroy((OmfGeometry *) omfGeometrySurfaceTri);
      return NULL;
   }

   return omfGeometrySurfaceTri;
}

/******************************************************************************
func: _OmfGeometrySurfaceTriCreateContent
******************************************************************************/
OmfBool _OmfGeometrySurfaceTriCreateContent(OmfGeometrySurfaceTri * const omfGeometrySurfaceTri)
{
   memClearType(OmfGeometrySurfaceTri, omfGeometrySurfaceTri);
   omfGeometrySurfaceTri->type = omfElementTypeSURFACE_TRI;

   return omfTRUE;
}

/******************************************************************************
func: _OmfGeometrySurfaceTriDestroyContent
******************************************************************************/
void _OmfGeometrySurfaceTriDestroyContent(OmfGeometrySurfaceTri * const omfGeometrySurfaceTri)
{
   returnVoidIf(!omfGeometrySurfaceTri);

   omfArrayDestroy(omfGeometrySurfaceTri->coord);
   omfArrayDestroy(omfGeometrySurfaceTri->triangle);

   return;
}

/******************************************************************************
func: omfGeometrySurfaceTriGetCoord
******************************************************************************/
OmfArray *omfGeometrySurfaceTriGetArrayCoord(OmfGeometrySurfaceTri const * const omfGeometrySurfaceTri)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceTri);

   return omfGeometrySurfaceTri->coord;
}

/******************************************************************************
func: omfGeometrySurfaceTriGetArrayTriangle
******************************************************************************/
OmfArray *omfGeometrySurfaceTriGetArrayTriangle(OmfGeometrySurfaceTri const * const omfGeometrySurfaceTri)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceTri);

   return omfGeometrySurfaceTri->triangle;
}

/******************************************************************************
func: omfGeometrySurfaceTriSetCoord
******************************************************************************/
OmfBool omfGeometrySurfaceTriSetArrayCoord(OmfGeometrySurfaceTri * const omfGeometrySurfaceTri, 
   OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceTri);

   omfGeometrySurfaceTri->coord = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySurfaceTriSetArrayTriangle
******************************************************************************/
OmfBool omfGeometrySurfaceTriSetArrayTriangle(OmfGeometrySurfaceTri * const omfGeometrySurfaceTri, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceTri);

   omfGeometrySurfaceTri->triangle = value;

   return omfTRUE;
}
