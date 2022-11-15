/******************************************************************************
file:       OmfProject
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
func: omfProjectCreate
******************************************************************************/
OmfProject *omfProjectCreate(void)
{
   OmfProject *omfProject;

   returnNullIf(!omfIsStarted());

   omfProject = (OmfProject *) memCreateType(OmfProject);
   returnNullIf(!omfProject);

   if (!omfProjectCreateContent(omfProject))
   {
      memDestroy(omfProject);
      return NULL;
   }

   return omfProject;
}

/******************************************************************************
func: omfProjectCreateContent
******************************************************************************/
OmfBool omfProjectCreateContent(OmfProject * const omfProject)
{
   returnFalseIf(!omfIsStarted());

   memClearType(OmfProject, omfProject);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectDestroy
******************************************************************************/
void omfProjectDestroy(OmfProject * const omfProject)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfProject);

   omfProjectDestroyContent(omfProject);
   
   memDestroy(omfProject);

   return;
}

/******************************************************************************
func: omfProjectDestroyContent
******************************************************************************/
void omfProjectDestroyContent(OmfProject * const omfProject)
{
   returnVoidIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->author);
   memDestroy(omfProject->date);
   memDestroy(omfProject->dateCreated);
   memDestroy(omfProject->dateModified);
   memDestroy(omfProject->description);
   memDestroy(omfProject->name);
   memDestroy(omfProject->revision);

   return;
}

/******************************************************************************
func: omfProjectGetAuthor
******************************************************************************/
OmfChar *omfProjectGetAuthor(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->author;
}

/******************************************************************************
func: omfProjectGetDate
******************************************************************************/
OmfChar *omfProjectGetDate(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->date;
}

/******************************************************************************
func: omfProjectGetDateCreated
******************************************************************************/
OmfChar *omfProjectGetDateCreated(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->dateCreated;
}

/******************************************************************************
func: omfProjectGetDateModified
******************************************************************************/
OmfChar *omfProjectGetDateModified(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->dateModified;
}

/******************************************************************************
func: omfProjectGetDescription
******************************************************************************/
OmfChar *omfProjectGetDescription(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->description;
}

/******************************************************************************
func: omfProjectGetId
******************************************************************************/
OmfId omfProjectGetId(OmfProject const * const omfProject)
{
   OmfId id;

   memClearType(OmfId, &id);

   returnIf(
         !omfIsStarted() ||
         !omfProject,
      id);

   return omfProject->id;
}

/******************************************************************************
func: omfProjectGetName
******************************************************************************/
OmfChar *omfProjectGetName(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->name;
}

/******************************************************************************
func: omfProjectGetOrigin
******************************************************************************/
OmfVec3 omfProjectGetOrigin(OmfProject const * const omfProject)
{
   OmfVec3 vec;

   memClearType(OmfVec3, &vec);

   returnIf(
         !omfIsStarted() ||
         !omfProject,
      vec);

   return omfProject->origin;
}

/******************************************************************************
func: omfProjectGetRevision
******************************************************************************/
OmfChar *omfProjectGetRevision(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->revision;
}

/******************************************************************************
func: omfProjectGetUnits
******************************************************************************/
OmfChar *omfProjectGetUnits(OmfProject const * const omfProject)
{
   returnNullIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->units;
}

/******************************************************************************
func: omfProjectSetAuthor
******************************************************************************/
OmfBool omfProjectSetAuthor(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->author);
   omfProject->author = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetDate
******************************************************************************/
OmfBool omfProjectSetDate(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->date);
   omfProject->date = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetDateCreated
******************************************************************************/
OmfBool omfProjectSetDateCreated(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->dateCreated);
   omfProject->dateCreated = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetDateModified
******************************************************************************/
OmfBool omfProjectSetDateModified(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->dateModified);
   omfProject->dateModified = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetDescription
******************************************************************************/
OmfBool omfProjectSetDescription(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->description);
   omfProject->description = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetId
******************************************************************************/
OmfBool omfProjectSetId(OmfProject * const omfProject, OmfId const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   omfProject->id = value;

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetName
******************************************************************************/
OmfBool omfProjectSetName(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->name);
   omfProject->name = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetOrigin
******************************************************************************/
OmfBool omfProjectSetOrigin(OmfProject * const omfProject, OmfVec3 const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   omfProject->origin = value;

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetRevision
******************************************************************************/
OmfBool omfProjectSetRevision(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->revision);
   omfProject->revision = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetUnits
******************************************************************************/
OmfBool omfProjectSetUnits(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   memDestroy(omfProject->units);
   omfProject->units = omfCharClone(value);

   return omfTRUE;
}
