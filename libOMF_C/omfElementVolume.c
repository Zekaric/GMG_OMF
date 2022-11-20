/******************************************************************************
file:       OmfElementVolume
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Volume element 
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
func: _OmfElementVolumeCreate
******************************************************************************/
OmfElementVolume *_OmfElementVolumeCreate(void)
{
   OmfElementVolume *omfElementVolume;

   omfElementVolume = memCreateType(OmfElementVolume);
   returnNullIf(!omfElementVolume);

   if (!_OmfElementVolumeCreateContent(omfElementVolume))
   {
      memDestroy(omfElementVolume);
      return NULL;
   }

   return omfElementVolume;
}

/******************************************************************************
func: _OmfElementVolumeCreateContent
******************************************************************************/
OmfBool _OmfElementVolumeCreateContent(OmfElementVolume * const omfElementVolume)
{
   memClearType(OmfElementVolume, omfElementVolume);
   omfElementVolume->type    = omfElementTypeVOLUME;
   omfElementVolume->subType = omfElementSubTypeVOLUME_VOLUME_DEFAULT;

   return omfTRUE;
}

/******************************************************************************
func: _OmfElementVolumeDestroyContent
******************************************************************************/
void _OmfElementVolumeDestroyContent(OmfElementVolume * const omfElementVolume)
{
   returnVoidIf(!omfElementVolume);

   omfGeometryDestroy((OmfGeometry *) omfElementVolume->geometry);

   return;
}

/******************************************************************************
func: omfElementVolumeGetGeometry
******************************************************************************/
OmfGeometry *omfElementVolumeGetGeometry(OmfElementVolume const * const omfElementVolume)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfElementVolume);

   return (OmfGeometry *) omfElementVolume->geometry;
}

/******************************************************************************
func: omfElementVolumeSetGeometry
******************************************************************************/
OmfBool omfElementVolumeSetGeometry(OmfElementVolume * const omfElementVolume, OmfGeometryVolume * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfElementVolume);

   omfElementVolume->geometry = value;

   return omfTRUE;
}
