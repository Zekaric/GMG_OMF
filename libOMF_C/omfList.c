/**************************************************************************************************
file:       OmfList
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
A simple linked list implementation.
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
func: omfListCreate
**************************************************************************************************/
OmfList *omfListCreate(void)
{
   OmfList *list;

   returnNullIf(!omfIsStarted());

   list = _OmfMemCreateType(OmfList);
   returnNullIf(!list);

   if (!omfListCreateContent(list))
   {
      _OmfMemDestroy(list);
      return NULL;
   }

   return list;
}

/**************************************************************************************************
func: omfListCreateContent
**************************************************************************************************/
OmfBool omfListCreateContent(OmfList * const list)
{
   returnFalseIf(!omfIsStarted());

   _OmfMemClearType(OmfList, list);

   return omfTRUE;
}

/**************************************************************************************************
func: omfListDestroy
**************************************************************************************************/
void omfListDestroy(OmfList * const list)
{
   returnVoidIf(
      !omfIsStarted() ||
      !list);

   omfListDestroyContent(list);
   
   _OmfMemDestroy(list);

   return;
}

/**************************************************************************************************
func: omfListDestroyContent
**************************************************************************************************/
void omfListDestroyContent(OmfList * const list)
{
   returnVoidIf(
      !omfIsStarted() ||
      !list);

   return;
}

/**************************************************************************************************
func: omfListAppend
**************************************************************************************************/
void omfListAppend(OmfList * const list, OmfListItem * const item)
{
   returnVoidIf(
      !omfIsStarted() ||
      !list);

   if (list->head == NULL)
   {
      list->head    =
         list->tail = item;
      return;
   }

   // Add the new item to the tail of the list.
   omfListItemSetNext(list->tail, item);

   // Set the new tail.
   list->tail = item;

   // Increment the count.
   list->count++;
}

/**************************************************************************************************
func: omfListGetCount
**************************************************************************************************/
OmfCount omfListGetCount(OmfList const * const list)
{
   returnIf(
         !omfIsStarted() ||
         !list,
      0);

   return list->count;
}

/**************************************************************************************************
func: omfListGetHeadItem
**************************************************************************************************/
OmfListItem *omfListGetHeadItem(OmfList const * const list)
{
   returnNullIf(
      !omfIsStarted() ||
      !list);

   return list->head;
}

/**************************************************************************************************
OmfListItem:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfListItemCreate
**************************************************************************************************/
OmfListItem *omfListItemCreate(void)
{
   OmfListItem *listItem;

   returnNullIf(!omfIsStarted());

   listItem = _OmfMemCreateType(OmfListItem);
   returnNullIf(!listItem);

   if (!omfListItemCreateContent(listItem))
   {
      _OmfMemDestroy(listItem);
      return NULL;
   }

   return listItem;
}

/**************************************************************************************************
func: omfListItemCreateContent
**************************************************************************************************/
OmfBool omfListItemCreateContent(OmfListItem * const listItem)
{
   returnFalseIf(!omfIsStarted());

   _OmfMemClearType(OmfListItem, listItem);

   return omfTRUE;
}

/**************************************************************************************************
func: omfListItemDestroy
**************************************************************************************************/
void omfListItemDestroy(OmfListItem * const listItem)
{
   returnVoidIf(
      !omfIsStarted() ||
      !listItem);

   omfListItemDestroyContent(listItem);
   
   _OmfMemDestroy(listItem);

   return;
}

/**************************************************************************************************
func: omfListItemDestroyContent
**************************************************************************************************/
void omfListItemDestroyContent(OmfListItem * const listItem)
{
   returnVoidIf(
      !omfIsStarted() ||
      !listItem);

   return;
}

/**************************************************************************************************
func: omfListItemGetNext
**************************************************************************************************/
OmfListItem *omfListItemGetNext(OmfListItem const * const listItem)
{
   returnNullIf(
      !omfIsStarted() ||
      !listItem);

   return listItem->next;
}

/**************************************************************************************************
func: omfListItemGetObj
**************************************************************************************************/
OmfObj *omfListItemGetObj(OmfListItem const * const listItem)
{
   returnNullIf(
      !omfIsStarted() ||
      !listItem);

   return listItem->obj;
}

/**************************************************************************************************
func: omfListItemSetNext
**************************************************************************************************/
OmfBool omfListItemSetNext(OmfListItem * const listItem, OmfListItem * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !listItem);

   listItem->next = value;

   return omfTRUE;
}

/**************************************************************************************************
func: omfListItemSetObj
**************************************************************************************************/
OmfBool omfListItemSetObj(OmfListItem * const listItem, OmfObj * const value)
{
   returnFalseIf(
      !omfIsStarted() ||
      !listItem);

   listItem->obj = value;

   return omfTRUE;
}

/**************************************************************************************************
OmfListIter:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfListIterCreate
**************************************************************************************************/
OmfListIter *omfListIterCreate(OmfList const * const list)
{
   OmfListIter *listIter;

   returnNullIf(!omfIsStarted());

   listIter = _OmfMemCreateType(OmfListIter);
   returnNullIf(!listIter);

   if (!omfListIterCreateContent(listIter, list))
   {
      _OmfMemDestroy(listIter);
      return NULL;
   }

   return listIter;
}

/**************************************************************************************************
func: omfListIterCreateContent
**************************************************************************************************/
OmfBool omfListIterCreateContent(OmfListIter * const listIter, OmfList const * const list)
{
   returnFalseIf(!omfIsStarted());

   _OmfMemClearType(OmfListIter, listIter);

   listIter->list = list;
   listIter->curr = list->head;

   return omfTRUE;
}

/**************************************************************************************************
func: omfListIterDestroy
**************************************************************************************************/
void omfListIterDestroy(OmfListIter * const listIter)
{
   returnVoidIf(
      !omfIsStarted() ||
      !listIter);

   omfListIterDestroyContent(listIter);
   
   _OmfMemDestroy(listIter);

   return;
}

/**************************************************************************************************
func: omfListIterDestroyContent
**************************************************************************************************/
void omfListIterDestroyContent(OmfListIter * const listIter)
{
   returnVoidIf(
      !omfIsStarted() ||
      !listIter);

   return;
}

/**************************************************************************************************
func: omfListIterGetItem
**************************************************************************************************/
OmfListItem *omfListIterGetItem(OmfListIter const * const listIter)
{
   returnNullIf(
      !omfIsStarted() ||
      !listIter);

   return listIter->curr;
}

/**************************************************************************************************
func: omfListIterNext
**************************************************************************************************/
OmfBool omfListIterNext(OmfListIter * const listIter)
{
   returnFalseIf(
      !omfIsStarted() ||
      !listIter    ||
      !listIter->curr);

   // Move to the next item in the list.
   listIter->curr = listIter->curr->next;

   // If there is no more items, then we return FALSE.
   returnFalseIf(!listIter->curr);

   // If there is more items, then we return TRUE.
   return omfTRUE;
}
