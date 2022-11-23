/**************************************************************************************************
file:       OmfObj
author:     Robbert de Groot
copyright:  2022: Robbert de Groot

description:
Data routines
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
func: omfObjCreate
**************************************************************************************************/
OmfObj *omfObjCreate(OmfObjType const type)
{
   OmfObj *obj;

   returnNullIf(!omfIsStarted());

   obj = NULL;

   switch (type)
   {
   default:
   case omfObjTypeNONE:
   case omfObjTypeARRAY:
   case omfObjTypeDATA:
   case omfObjTypeELEM:
   case omfObjTypeGEOM:
   case omfObjTypeMODEL:
      break;

   case omfObjTypeARRAY_COLOR:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeCOLOR);
      break;

   case omfObjTypeARRAY_DATE_TIME:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeDATE_TIME);
      break;

   case omfObjTypeARRAY_INT:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeINT);
      break;

   case omfObjTypeARRAY_INT2:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeINT2);
      break;

   case omfObjTypeARRAY_INT3:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeINT3);
      break;

   case omfObjTypeARRAY_REAL:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeREAL);
      break;

   case omfObjTypeARRAY_REAL2:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeREAL2);
      break;

   case omfObjTypeARRAY_REAL3:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeREAL3);
      break;

   case omfObjTypeARRAY_STRING:
      obj = (OmfObj *) _OmfArrayCreate(omfArrayTypeSTRING);
      break;


   case omfObjTypeDATA_COLOR:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeCOLOR);
      break;

   case omfObjTypeDATA_DATE_TIME:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeDATE_TIME);
      break;

   case omfObjTypeDATA_DATE_TIME_COLORMAP:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeDATE_TIME_COLORMAP);
      break;

   case omfObjTypeDATA_LEGEND:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeLEGEND);
      break;

   case omfObjTypeDATA_MAPPED:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeMAPPED);
      break;

   case omfObjTypeDATA_SCALAR:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeSCALAR);
      break;

   case omfObjTypeDATA_SCALAR_COLORMAP:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeSCALAR_COLORMAP);
      break;

   case omfObjTypeDATA_STRING:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeSTRING);
      break;

   case omfObjTypeDATA_VECTOR2:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeVECTOR2);
      break;

   case omfObjTypeDATA_VECTOR3:
      obj = (OmfObj *) _OmfDataCreate(omfDataTypeVECTOR3);
      break;

   
   case omfObjTypeELEM_LINE_SET:
      obj = (OmfObj *) _OmfElemCreate(omfElemTypeLINE_SET);
      break;

   case omfObjTypeELEM_PNT_SET:
      obj = (OmfObj *) _OmfElemCreate(omfElemTypePNT_SET);
      break;

   case omfObjTypeELEM_SURF_GRID:
      obj = (OmfObj *) _OmfElemCreate(omfElemTypeSURF_GRID);
      break;

   case omfObjTypeELEM_SURF_TRI:
      obj = (OmfObj *) _OmfElemCreate(omfElemTypeSURF_TRI);
      break;

   case omfObjTypeELEM_VOL:
      obj = (OmfObj *) _OmfElemCreate(omfElemTypeVOL);
      break;
   

   case omfObjTypeGEOM_LINE_SET:
      obj = (OmfObj *) _OmfGeomCreate(omfElemTypeLINE_SET);
      break;

   case omfObjTypeGEOM_PNT_SET:
      obj = (OmfObj *) _OmfGeomCreate(omfElemTypePNT_SET);
      break;

   case omfObjTypeGEOM_SURF_GRID:
      obj = (OmfObj *) _OmfGeomCreate(omfElemTypeSURF_GRID);
      break;

   case omfObjTypeGEOM_SURF_TRI:
      obj = (OmfObj *) _OmfGeomCreate(omfElemTypeSURF_TRI);
      break;

   case omfObjTypeGEOM_VOL:
      obj = (OmfObj *) _OmfGeomCreate(omfElemTypeVOL);
      break;

   
   case omfObjTypeMODEL_CONTENT:
      //TODO obj = (OmfObj *) _OmfModelCreateContent();
      break;

   case omfObjTypeMODEL_ID:
      //TODO obj = (OmfObj *) _OmfModelCreateId();
      break;

   
   case omfObjTypePROJ:
      obj = (OmfObj *) _OmfProjCreate();
      break;

   case omfObjTypePROJ_ELEMENT:
      //TODO obj = (OmfObj *) _OmfProjElementCreate();
      break;

   case omfObjTypePROJ_ELEMENT_DATA:
      //TODO obj = (OmfObj *) _OmfProjElementDataCreate();
      break;


   case omfObjTypeTEXTURE:
      //TODO obj = (OmfObj *) _OmfTextureCreate();
      break;
   }

   //TODO
   //obj->dateCreated  = omfDateTimeGetNow();
   //obj->dateModified = omfCharClone(obj->dateCreated);
   //obj->id           = omfIdGetNew();

   return obj;
}

/**************************************************************************************************
func: omfObjDestroy
**************************************************************************************************/
void omfObjDestroy(OmfObj * const obj)
{
   returnVoidIf(
      !omfIsStarted() ||
      !obj);

   _OmfObjDestroyContent(obj);
   
   memDestroy(obj);

   return;
}

/**************************************************************************************************
func: omfObjDestroyContent
**************************************************************************************************/
void _OmfObjDestroyContent(OmfObj * const obj)
{
   returnVoidIf(
      !omfIsStarted() ||
      !obj);

   switch (obj->typeObj)
   {
   default:
   case omfObjTypeNONE:
   case omfObjTypeARRAY:
   case omfObjTypeDATA:
   case omfObjTypeELEM:
   case omfObjTypeGEOM:
   case omfObjTypeMODEL:
      break;

   case omfObjTypeARRAY_COLOR:
   case omfObjTypeARRAY_DATE_TIME:
   case omfObjTypeARRAY_INT:
   case omfObjTypeARRAY_INT2:
   case omfObjTypeARRAY_INT3:
   case omfObjTypeARRAY_REAL:
   case omfObjTypeARRAY_REAL2:
   case omfObjTypeARRAY_REAL3:
   case omfObjTypeARRAY_STRING:
      _OmfArrayDestroyContent((OmfArray *) obj);
      break;

   case omfObjTypeDATA_COLOR:
   case omfObjTypeDATA_DATE_TIME:
   case omfObjTypeDATA_DATE_TIME_COLORMAP:
   case omfObjTypeDATA_LEGEND:
   case omfObjTypeDATA_MAPPED:
   case omfObjTypeDATA_SCALAR:
   case omfObjTypeDATA_SCALAR_COLORMAP:
   case omfObjTypeDATA_STRING:
   case omfObjTypeDATA_VECTOR2:
   case omfObjTypeDATA_VECTOR3:
      _OmfDataDestroyContent((OmfData *) obj);
      break;
   
   case omfObjTypeELEM_LINE_SET:
   case omfObjTypeELEM_PNT_SET:
   case omfObjTypeELEM_SURF_GRID:
   case omfObjTypeELEM_SURF_TRI:
   case omfObjTypeELEM_VOL:
      _OmfElemDestroyContent((OmfElem *) obj);
      break;
   
   case omfObjTypeGEOM_LINE_SET:
   case omfObjTypeGEOM_PNT_SET:
   case omfObjTypeGEOM_SURF_GRID:
   case omfObjTypeGEOM_SURF_TRI:
   case omfObjTypeGEOM_VOL:
      _OmfGeomDestroyContent((OmfGeom *) obj);
      break;
   
   case omfObjTypeMODEL_CONTENT:
   case omfObjTypeMODEL_ID:
      //TODO
      break;
   
   case omfObjTypePROJ:
      _OmfProjDestroyContent((OmfProj *) obj);
      break;

   case omfObjTypePROJ_ELEMENT:
   case omfObjTypePROJ_ELEMENT_DATA:
      //TODO
      break;

   case omfObjTypeTEXTURE:
      //TODO
      break;
   }

   omfCharDestroy(obj->dateCreated);
   omfCharDestroy(obj->dateModified);

   return;
}

/**************************************************************************************************
func: omfObjGetDateCreated
**************************************************************************************************/
OmfChar *omfObjGetDateCreated(OmfObj const * const obj)
{
   returnNullIf(
      !omfIsStarted() ||
      !obj);

   return obj->dateCreated;
}

/**************************************************************************************************
func: omfObjGetDateModified
**************************************************************************************************/
OmfChar *omfObjGetDateModified(OmfObj const * const obj)
{
   returnNullIf(
      !omfIsStarted() ||
      !obj);

   return obj->dateModified;
}

/**************************************************************************************************
func: omfObjGetId
**************************************************************************************************/
OmfId omfObjGetId(OmfObj const * const obj)
{
   OmfId id;

   memClearType(OmfId, &id);

   returnIf(
         !omfIsStarted() ||
         !obj,
      id);

   return obj->id;
}

/**************************************************************************************************
func: omfObjGetType
**************************************************************************************************/
OmfObjType omfObjGetType(OmfObj const * const obj)
{
   returnIf(
         !omfIsStarted() ||
         !obj,
      omfObjTypeNONE);

   return obj->typeObj;
}

/**************************************************************************************************
func: omfObjSetDateCreated
**************************************************************************************************/
OmfBool omfObjSetDateCreated(OmfObj * const obj, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !obj);

   omfCharDestroy(obj->dateCreated);
   obj->dateCreated = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfObjSetDateModified
**************************************************************************************************/
OmfBool omfObjSetDateModified(OmfObj * const obj, OmfChar * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !obj);

   omfCharDestroy(obj->dateModified);
   obj->dateModified = omfCharClone(value);;

   return omfTRUE;
}

/**************************************************************************************************
func: omfObjSetId
**************************************************************************************************/
OmfBool omfObjSetId(OmfObj * const obj, OmfId const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !obj);

   obj->id = value;

   return omfTRUE;
}
