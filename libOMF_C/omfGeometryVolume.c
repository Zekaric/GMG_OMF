/******************************************************************************
file:       OmfGeometryVolume
author:     Robbert de Groot
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
func: _OmfGeometryVolumeCreate
******************************************************************************/
OmfGeometryVolume *_OmfGeometryVolumeCreate(void)
{
   OmfGeometryVolume *omfGeometryVolume;

   omfGeometryVolume = memCreateType(OmfGeometryVolume);
   returnNullIf(!omfGeometryVolume);

   if (!_OmfGeometryVolumeCreateContent(omfGeometryVolume))
   {
      omfGeometryDestroy((OmfGeometry *) omfGeometryVolume);
      return NULL;
   }

   return omfGeometryVolume;
}

/******************************************************************************
func: _OmfGeometryVolumeCreateContent
******************************************************************************/
OmfBool _OmfGeometryVolumeCreateContent(OmfGeometryVolume * const omfGeometryVolume)
{
   memClearType(OmfGeometryVolume, omfGeometryVolume);
   omfGeometryVolume->type = omfElementTypeVOLUME;

   return omfTRUE;
}

/******************************************************************************
func: _OmfGeometryVolumeDestroyContent
******************************************************************************/
void _OmfGeometryVolumeDestroyContent(OmfGeometryVolume * const omfGeometryVolume)
{
   returnVoidIf(!omfGeometryVolume);

   omfArrayDestroy(omfGeometryVolume->tensorU);
   omfArrayDestroy(omfGeometryVolume->tensorV);
   omfArrayDestroy(omfGeometryVolume->tensorW);

   return;
}

/******************************************************************************
func: omfGeometryVolumeGetArrayTensorU
******************************************************************************/
OmfArray *omfGeometryVolumeGetArrayTensorU(OmfGeometryVolume const * const omfGeometryVolume)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   return omfGeometryVolume->tensorU;
}

/******************************************************************************
func: omfGeometryVolumeGetArrayTensorV
******************************************************************************/
OmfArray *omfGeometryVolumeGetArrayTensorV(OmfGeometryVolume const * const omfGeometryVolume)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   return omfGeometryVolume->tensorV;
}

/******************************************************************************
func: omfGeometryVolumeGetArrayTensorW
******************************************************************************/
OmfArray *omfGeometryVolumeGetArrayTensorW(OmfGeometryVolume const * const omfGeometryVolume)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   return omfGeometryVolume->tensorW;
}

/******************************************************************************
func: omfGeometryVolumeGetAxisU
******************************************************************************/
OmfVector omfGeometryVolumeGetAxisU(OmfGeometryVolume const * const omfGeometryVolume)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfGeometryVolume,
      vec);

   return omfGeometryVolume->axisU;
}

/******************************************************************************
func: omfGeometryVolumeGetAxisV
******************************************************************************/
OmfVector omfGeometryVolumeGetAxisV(OmfGeometryVolume const * const omfGeometryVolume)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfGeometryVolume,
      vec);

   return omfGeometryVolume->axisV;
}

/******************************************************************************
func: omfGeometryVolumeGetAxisW
******************************************************************************/
OmfVector omfGeometryVolumeGetAxisW(OmfGeometryVolume const * const omfGeometryVolume)
{
   OmfVector vec;

   memClearType(OmfVector, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfGeometryVolume,
      vec);

   return omfGeometryVolume->axisW;
}

/******************************************************************************
func: omfGeometryVolumeSetArrayTensorU
******************************************************************************/
OmfBool omfGeometryVolumeSetArrayTensorU(OmfGeometryVolume * const omfGeometryVolume, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->tensorU = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryVolumeSetArrayTensorV
******************************************************************************/
OmfBool omfGeometryVolumeSetArrayTensorV(OmfGeometryVolume * const omfGeometryVolume, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->tensorV = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryVolumeSetArrayTensorW
******************************************************************************/
OmfBool omfGeometryVolumeSetArrayTensorW(OmfGeometryVolume * const omfGeometryVolume, OmfArray * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->tensorW = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryVolumeSetAxisU
******************************************************************************/
OmfBool omfGeometryVolumeSetAxisU(OmfGeometryVolume * const omfGeometryVolume, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->axisU = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryVolumeSetAxisV
******************************************************************************/
OmfBool omfGeometryVolumeSetAxisV(OmfGeometryVolume * const omfGeometryVolume, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->axisV = value;

   return omfTRUE;
}

/******************************************************************************
func: omfGeometryVolumeSetAxisW
******************************************************************************/
OmfBool omfGeometryVolumeSetAxisW(OmfGeometryVolume * const omfGeometryVolume, OmfVector const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfGeometryVolume);

   omfGeometryVolume->axisW = value;

   return omfTRUE;
}
