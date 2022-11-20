/******************************************************************************
file:       OmfGeometrySurfaceGrid
author:     Robbert de Groot
company:    Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Geometry Surface Grid routines
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
func: _OmfGeometrySurfaceGridCreate
******************************************************************************/
OmfGeometrySurfaceGrid *_OmfGeometrySurfaceGridCreate(void)
{
   OmfGeometrySurfaceGrid *omfGeometrySurfaceGrid;

   omfGeometrySurfaceGrid = memCreateType(OmfGeometrySurfaceGrid);
   returnNullIf(!omfGeometrySurfaceGrid);

   if (!_OmfGeometrySurfaceGridCreateContent(omfGeometrySurfaceGrid))
   {
      omfGeometryDestroy((OmfGeometry *) omfGeometrySurfaceGrid);
      return NULL;
   }

   return omfGeometrySurfaceGrid;
}

/******************************************************************************
func: _OmfGeometrySurfaceGridCreateContent
******************************************************************************/
OmfBool _OmfGeometrySurfaceGridCreateContent(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid)
{
   memClearType(OmfGeometrySurfaceGrid, omfGeometrySurfaceGrid);
   omfGeometrySurfaceGrid->type = omfElementTypeSURFACE_GRID;

   return omfTRUE;
}

/******************************************************************************
func: _OmfGeometrySurfaceGridDestroyContent
******************************************************************************/
void _OmfGeometrySurfaceGridDestroyContent(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid)
{
   returnVoidIf(!omfGeometrySurfaceGrid);

   omfArrayDestroy(omfGeometrySurfaceGrid->offset);
   omfArrayDestroy(omfGeometrySurfaceGrid->tensorU);
   omfArrayDestroy(omfGeometrySurfaceGrid->tensorV);

   return;
}

/******************************************************************************
func: omfGeometrySurfaceGridGetArrayOffset
******************************************************************************/
OmfArray *omfGeometrySurfaceGridGetArrayOffset(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   return omfGeometrySurfaceGrid->offset;
}

/******************************************************************************
func: omfGeometrySurfaceGridGetArrayTensorU
******************************************************************************/
OmfArray *omfGeometrySurfaceGridGetArrayTensorU(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   return omfGeometrySurfaceGrid->tensorU;
}

/******************************************************************************
func: omfGeometrySurfaceGridGetArrayTensorV
******************************************************************************/
OmfArray *omfGeometrySurfaceGridGetArrayTensorV(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   return omfGeometrySurfaceGrid->tensorV;
}

/******************************************************************************
func: omfGeometrySurfaceGridGetAxisU
******************************************************************************/
OmfVector omfGeometrySurfaceGridGetAxisU(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfGeometrySurfaceGrid,
      vec);

   return omfGeometrySurfaceGrid->axisU;
}

/******************************************************************************
func: omfGeometrySurfaceGridGetAxisV
******************************************************************************/
OmfVector omfGeometrySurfaceGridGetAxisV(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfGeometrySurfaceGrid,
      vec);

   return omfGeometrySurfaceGrid->axisV;
}

/******************************************************************************
func: omfGeometrySurfaceGridIsArrayOffsetSet
******************************************************************************/
OmfBool omfGeometrySurfaceGridIsArrayOffsetSet(OmfGeometrySurfaceGrid const * const omfGeometrySurfaceGrid)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   return omfGeometrySurfaceGrid->isOffsetSet;
}

/******************************************************************************
func: omfGeometrySurfaceGridSetArrayOffset
******************************************************************************/
OmfBool omfGeometrySurfaceGridSetArrayOffset(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   omfGeometrySurfaceGrid->offset = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySurfaceGridSetArrayTensorU
******************************************************************************/
OmfBool omfGeometrySurfaceGridSetArrayTensorU(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   omfGeometrySurfaceGrid->tensorU = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySurfaceGridSetArrayTensorV
******************************************************************************/
OmfBool omfGeometrySurfaceGridSetArrayTensorV(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   omfGeometrySurfaceGrid->tensorV = value;

   return omfTRUE;
}
/******************************************************************************
func: omfGeometrySurfaceGridSetAxisU
******************************************************************************/
OmfBool omfGeometrySurfaceGridSetAxisU(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   omfGeometrySurfaceGrid->axisU = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometrySurfaceGridSetAxisV
******************************************************************************/
OmfBool omfGeometrySurfaceGridSetAxisV(OmfGeometrySurfaceGrid * const omfGeometrySurfaceGrid, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometrySurfaceGrid);

   omfGeometrySurfaceGrid->axisV = value;

   return omfTRUE;
}
