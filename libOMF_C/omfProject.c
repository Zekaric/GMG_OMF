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
func: _OmfProjectCreateContent
******************************************************************************/
OmfBool _OmfProjectCreateContent(OmfProject * const omfProject)
{
   memClearType(OmfProject, omfProject);

   return omfTRUE;
}

/******************************************************************************
func: _OmfProjectDestroyContent
******************************************************************************/
void _OmfProjectDestroyContent(OmfProject * const omfProject)
{
   returnVoidIf(!omfProject);

   omfCharDestroy(omfProject->author);
   omfCharDestroy(omfProject->date);
   omfCharDestroy(omfProject->dateCreated);
   omfCharDestroy(omfProject->dateModified);
   omfCharDestroy(omfProject->description);
   omfCharDestroy(omfProject->name);
   omfCharDestroy(omfProject->revision);

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
OmfCoord omfProjectGetOrigin(OmfProject const * const omfProject)
{
   OmfCoord vec;

   memClearType(OmfCoord, &vec);

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
func: omfProjectIsDateSet
******************************************************************************/
OmfBool omfProjectIsDateSet(OmfProject const * const omfProject)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->isDateSet;
}

/******************************************************************************
func: omfProjectIsDateCreatedSet
******************************************************************************/
OmfBool omfProjectIsDateCreatedSet(OmfProject const * const omfProject)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->isDateCreatedSet;
}

/******************************************************************************
func: omfProjectIsDateModifiesSet
******************************************************************************/
OmfBool omfProjectIsDateModifiesSet(OmfProject const * const omfProject)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   return omfProject->isDateModifiedSet;
}

/******************************************************************************
func: omfProjectSetAuthor
******************************************************************************/
OmfBool omfProjectSetAuthor(OmfProject * const omfProject, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !omfProject);

   omfCharDestroy(omfProject->author);
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

   omfCharDestroy(omfProject->date);
   omfProject->date      = omfCharClone(value);
   omfProject->isDateSet = (value != NULL);

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

   omfCharDestroy(omfProject->dateCreated);
   omfProject->dateCreated      = omfCharClone(value);
   omfProject->isDateCreatedSet = (value != NULL);

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

   omfCharDestroy(omfProject->dateModified);
   omfProject->dateModified      = omfCharClone(value);
   omfProject->isDateModifiedSet = (value != NULL);

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

   omfCharDestroy(omfProject->description);
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

   omfCharDestroy(omfProject->name);
   omfProject->name = omfCharClone(value);

   return omfTRUE;
}

/******************************************************************************
func: omfProjectSetOrigin
******************************************************************************/
OmfBool omfProjectSetOrigin(OmfProject * const omfProject, OmfCoord const value)
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

   omfCharDestroy(omfProject->revision);
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

   omfCharDestroy(omfProject->units);
   omfProject->units = omfCharClone(value);

   return omfTRUE;
}
