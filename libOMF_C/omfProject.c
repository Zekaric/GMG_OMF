/**************************************************************************************************
file:       OmfProj
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Project routines
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) !!!!YEAR!!!!, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT 
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
func: _OmfProjCreate
**************************************************************************************************/
OmfProj *_OmfProjCreate(void)
{
   OmfProj *project;

   returnNullIf(!omfIsStarted());

   project = _OmfMemCreateType(OmfProj);
   returnNullIf(!project);

   if (!_OmfProjCreateContent(project))
   {
      _OmfMemDestroy(project);
      return NULL;
   }

   return project;
}

/**************************************************************************************************
func: _OmfProjCreateContent
**************************************************************************************************/
OmfBool _OmfProjCreateContent(OmfProj * const project)
{
   returnFalseIf(!omfIsStarted());

   _OmfMemClearType(OmfProj, project);

   return omfTRUE;
}

/**************************************************************************************************
func: _OmfProjDestroyContent
**************************************************************************************************/
void _OmfProjDestroyContent(OmfProj * const project)
{
   returnVoidIf(!project);

   omfCharDestroy(project->author);
   omfCharDestroy(project->date);
   omfCharDestroy(project->description);
   omfCharDestroy(project->name);
   omfCharDestroy(project->revision);

   return;
}

/**************************************************************************************************
func: omfProjGetAuthor
**************************************************************************************************/
OmfChar *omfProjGetAuthor(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->author;
}

/**************************************************************************************************
func: omfProjGetDate
**************************************************************************************************/
OmfChar *omfProjGetDate(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->date;
}

/**************************************************************************************************
func: omfProjGetDescription
**************************************************************************************************/
OmfChar *omfProjGetDescription(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->description;
}

/**************************************************************************************************
func: omfProjGetName
**************************************************************************************************/
OmfChar *omfProjGetName(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->name;
}

/**************************************************************************************************
func: omfProjGetOrigin
**************************************************************************************************/
OmfCoord omfProjGetOrigin(OmfProj const * const project)
{
   OmfCoord vec;

   _OmfMemClearType(OmfCoord, &vec);

   returnIf(
         !omfIsStarted() ||
         !project,
      vec);

   return project->origin;
}

/**************************************************************************************************
func: omfProjGetRevision
**************************************************************************************************/
OmfChar *omfProjGetRevision(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->revision;
}

/**************************************************************************************************
func: omfProjGetUnits
**************************************************************************************************/
OmfChar *omfProjGetUnits(OmfProj const * const project)
{
   returnNullIf(
      !omfIsStarted() ||
      !project);

   return project->units;
}

/**************************************************************************************************
func: omfProjIsDateSet
**************************************************************************************************/
OmfBool omfProjIsDateSet(OmfProj const * const project)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   return project->isDateSet;
}

/**************************************************************************************************
func: omfProjSetAuthor
**************************************************************************************************/
OmfBool omfProjSetAuthor(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->author);
   project->author = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetDate
**************************************************************************************************/
OmfBool omfProjSetDate(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->date);
   project->date      = omfCharClone(value);
   project->isDateSet = (value != NULL);

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetDescription
**************************************************************************************************/
OmfBool omfProjSetDescription(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->description);
   project->description = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetName
**************************************************************************************************/
OmfBool omfProjSetName(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->name);
   project->name = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetOrigin
**************************************************************************************************/
OmfBool omfProjSetOrigin(OmfProj * const project, OmfCoord const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   project->origin = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetRevision
**************************************************************************************************/
OmfBool omfProjSetRevision(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->revision);
   project->revision = omfCharClone(value);

   return omfTRUE;
}

/**************************************************************************************************
func: omfProjSetUnits
**************************************************************************************************/
OmfBool omfProjSetUnits(OmfProj * const project, OmfChar const * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !project);

   omfCharDestroy(project->units);
   project->units = omfCharClone(value);

   return omfTRUE;
}
