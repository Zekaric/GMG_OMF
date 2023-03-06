/**************************************************************************************************
file:       libJSON
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Simple JSON routines.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2022, Robbert de Groot

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
#include "libJSON_C.h"
#include "libJSON_local.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
#define jsonStringSEPARATOR            ((JsonChar *) ",")
#define jsonStringARRAY_START          ((JsonChar *) "[")
#define jsonStringARRAY_STOP           ((JsonChar *) "]")
#define jsonStringOBJECT_START         ((JsonChar *) "{")
#define jsonStringOBJECT_STOP          ((JsonChar *) "}")
#define jsonStringKEY_VALUE_SEPARATOR  ((JsonChar *) ":")
#define jsonStringQUOTE                ((JsonChar *) "\"")
#define jsonStringTRUE                 ((JsonChar *) "true")
#define jsonStringFALSE                ((JsonChar *) "false")
#define jsonStringNULL                 ((JsonChar *) "null")

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct 
{
   JsonCount charLen,
             buffLen;
   JsonChar *buff;
} JsonStr;

/**************************************************************************************************
variable:
**************************************************************************************************/
static JsonBool    _isStarted = jsonFALSE;

static void      (*_memClear)(   void * const buf, size_t const size) = NULL;
static void     *(*_memCreate)(  size_t const size)                   = NULL;
static void      (*_memDestroy)( void * const buf)                    = NULL;

static _locale_t   _locale_c;

/**************************************************************************************************
prototype:
**************************************************************************************************/
static JsonChar       _ReadGetNextLetter(       Json       * const json);
static JsonError      _ReadNumber(              Json       * const json, JsonChar letter);
static JsonError      _ReadPredefined(          Json       * const json, JsonChar letter);
static JsonError      _ReadValue(               Json       * const json, JsonBool isStringOnlyAllowed);

static JsonScopeType  _ScopeGetType(            Json const * const json);
static JsonBool       _ScopeIsEmpty(            Json const * const json);
static JsonBool       _ScopeIsWritingKey(       Json const * const json);
static JsonError      _ScopePush(               Json       * const json, JsonScopeType const scope);
static JsonError      _ScopePop(                Json       * const json);
static void           _ScopeSetIsEmpty(         Json       * const json, JsonBool const value);
static void           _ScopeSetIsWritingKey(    Json       * const json, JsonBool const value);
static JsonError      _ScopeStart(              Json       * const json);
static void           _ScopeStop(               Json       * const json);

static JsonState      _StateGet(                Json       * const json);

static JsonBool       _StrAppendLetter(         JsonStr * const str, JsonChar letter);
static JsonStr       *_StrCreate(               void);
static void           _StrDestroy(              JsonStr * const str);

static JsonBool       _WriteStringJson(         Json       * const json, JsonChar const * const value);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: omfStart

Start up the library routines and initialize whatever needs initializing.
**************************************************************************************************/
JsonError jsonStart(void *(*memCreate)(size_t const size), void (*memDestroy)(void * const buffer), 
   void (*memClear)(void * const buffer, size_t const size))
{
   if (_isStarted)
   {
      assert(jsonFALSE && "This function should not be called twice.");
      return jsonErrorNONE;
   }

   returnIf(
         !memClear  ||
         !memCreate ||
         !memDestroy,
      jsonErrorPARAMETER_BAD);

   _memClear   = memClear;
   _memCreate  = memCreate;
   _memDestroy = memDestroy;

   _locale_c   = _create_locale(LC_NUMERIC, "C");

   _isStarted  = jsonTRUE;

      return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonStop

Reset the library.
**************************************************************************************************/
void jsonStop(void)
{
   _memClear   = NULL;
   _memCreate  = NULL;
   _memDestroy = NULL;

   _isStarted  = jsonFALSE;
}

/**************************************************************************************************
func: jsonCreateRead

input and output pointers are optional.  The functions are not.
**************************************************************************************************/
Json *jsonCreateRead(void * const input, 
   JsonBool (*func_GetInput)(void * const input, JsonChar * const letter), void * const output, 
   JsonBool (*func_SetOutput)(void * const output, JsonToken const token, JsonChar const * const value))
{
   Json *json;

   returnFalseIf(
      !_isStarted    ||
      !func_GetInput ||
      !func_SetOutput);

   json = _JsonMemCreateType(Json);
   returnNullIf(!json);

   if (!jsonCreateContentRead(json, input, func_GetInput, output, func_SetOutput))
   {
      jsonDestroy(json);
      return NULL;
   }

   return json;
}

/**************************************************************************************************
func: jsonCreateContentRead

input and output pointers are optional.  The functions are not.
**************************************************************************************************/
JsonBool jsonCreateContentRead(Json * const json, void * const input,
   JsonBool (*func_GetInput)(void * const input, JsonChar * const letter), void * const output, 
   JsonBool (*func_SetOutput)(void * const output, JsonToken const token, JsonChar const * const value))
{
   returnFalseIf(
      !_isStarted    ||
      !json          ||
      !func_GetInput ||
      !func_SetOutput);

   _JsonMemClearType(Json, json);

   json->input              = input;
   json->output             = output;
   json->funcRead_GetInput  = func_GetInput;
   json->funcRead_SetOutput = func_SetOutput;

   returnFalseIf(_ScopeStart(json) != jsonErrorNONE);

   return jsonTRUE;
}

/**************************************************************************************************
func: jsonCreateWrite
**************************************************************************************************/
Json *jsonCreateWrite(void * const output, 
   JsonBool (*func_SetOutput)(void * const output, JsonChar const * const value))
{
   Json *json;

   returnFalseIf(
      !_isStarted ||
      !output     ||
      !func_SetOutput);

   json = _JsonMemCreateType(Json);
   returnNullIf(!json);

   if (!jsonCreateContentWrite(json, output, func_SetOutput))
   {
      jsonDestroy(json);
      return NULL;
   }

   return json;
}

/**************************************************************************************************
func: jsonCreateContentWrite
**************************************************************************************************/
JsonBool jsonCreateContentWrite(Json * const json, void * const output, 
   JsonBool (*func_SetOutput)(void * const output, JsonChar const * const value))
{
   returnFalseIf(
      !_isStarted ||
      !json       ||
      !output     ||
      !func_SetOutput);

   _JsonMemClearType(Json, json);

   json->isWriting           = jsonTRUE;
   json->output              = output;
   json->funcWrite_SetOutput = func_SetOutput;

   returnFalseIf(_ScopeStart(json) != jsonErrorNONE);

   return jsonTRUE;
}

/**************************************************************************************************
func: jsonDestroy
**************************************************************************************************/
void jsonDestroy(Json * const json)
{
   returnVoidIf(
      !_isStarted ||
      !json);

   jsonDestroyContent(json);

   _JsonMemDestroy(json);
}

/**************************************************************************************************
func: jsonDestroyContent
**************************************************************************************************/
void jsonDestroyContent(Json * const json)
{
   returnVoidIf(
      !_isStarted ||
      !json);

   // Clean up memory.
   _ScopeStop(json);

   _JsonMemClearType(Json, json);
}

/**************************************************************************************************
func: jsonRead
**************************************************************************************************/
JsonError jsonRead(Json * const json)
{
   JsonError error;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf( json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_READING);

   // Read the one and only value in the json buffer.
   error  = jsonErrorNONE;
   error |= _ReadValue(json, jsonFALSE);

   return error;
}

/**************************************************************************************************
func: jsonWriteArrayStart
**************************************************************************************************/
JsonError jsonWriteArrayStart(Json * const json)
{
   JsonError error;
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can start an array.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_ARRAY_START);

   // Push a new scope onto the scope stack.
   error = _ScopePush(json, jsonScopeTypeARRAY);
   returnIf(error != jsonErrorNONE, error);

   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringARRAY_START), jsonErrorFAILED_WRITE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteArrayStop
**************************************************************************************************/
JsonError jsonWriteArrayStop(Json * const json)
{
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can stop an array.
   state = _StateGet(json);
   returnIf(!(state == jsonStateVALUE_OR_ARRAY_STOP), jsonErrorCANNOT_ARRAY_STOP);
   
   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringARRAY_STOP), jsonErrorFAILED_WRITE);

   // Remove the array scope from the scope stack.
   _ScopePop(json);

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteBoolean
**************************************************************************************************/
JsonError jsonWriteBoolean(Json * const json, JsonBool value)
{
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   if (value)
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringTRUE),  jsonErrorFAILED_WRITE);
   }
   else
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringFALSE), jsonErrorFAILED_WRITE);
   }

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteInteger
**************************************************************************************************/
JsonError jsonWriteInteger(Json * const json, int64_t value)
{
   JsonState state;
   JsonChar  buffer[32];

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   // Convert the integer to a string.
   _i64toa_s(value, (char *) buffer, 32, 10);
   returnIf(!json->funcWrite_SetOutput(json->output, buffer), jsonErrorFAILED_WRITE);

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteNull
**************************************************************************************************/
JsonError jsonWriteNull(Json * const json)
{
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringNULL), jsonErrorFAILED_WRITE);
   
   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteObjectStart
**************************************************************************************************/
JsonError jsonWriteObjectStart(Json * const json)
{
   JsonError error;
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can start an array.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_OBJECT_START);

   // Push a new scope onto the scope stack.
   error = _ScopePush(json, jsonScopeTypeOBJECT);
   returnIf(error != jsonErrorNONE, error);

   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringOBJECT_START), jsonErrorFAILED_WRITE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteObjectStop
**************************************************************************************************/
JsonError jsonWriteObjectStop(Json * const json)
{
   JsonState state;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can stop an array.
   state = _StateGet(json);
   returnIf(!(state == jsonStateOBJECT_KEY_OR_OBJECT_STOP), jsonErrorCANNOT_OBJECT_STOP);
   
   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringOBJECT_STOP), jsonErrorFAILED_WRITE);

   // Remove the array scope from the scope stack.
   _ScopePop(json);

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteReal
**************************************************************************************************/
JsonError jsonWriteReal(Json * const json, double value)
{
   JsonState state;
   JsonChar  buffer[32];

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   // Convert the float to a string.
   _snprintf_s_l((char *) buffer, 32, 32, "%0.15g", _locale_c, value);
   returnIf(!json->funcWrite_SetOutput(json->output, buffer), jsonErrorFAILED_WRITE);

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteReal4

Same as jsonWriteReal but limits the number of significant digits.
**************************************************************************************************/
JsonError jsonWriteReal4(Json * const json, double value)
{
   JsonState state;
   JsonChar  buffer[32];

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(!(state & jsonStateVALUE), jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   // Convert the float to a string.
   _snprintf_s_l((char *) buffer, 32, 32, "%0.7g", _locale_c, value);
   returnIf(!json->funcWrite_SetOutput(json->output, buffer), jsonErrorFAILED_WRITE);

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, jsonTRUE);
   }

   // Indicate that the array has elements in it.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: jsonWriteString
**************************************************************************************************/
JsonError jsonWriteString(Json * const json, JsonChar const * const value)
{
   JsonState       state;
   JsonScopeType   scopeType;

   returnIf(!_isStarted,      jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,            jsonErrorPARAMETER_BAD);
   returnIf(!json->isWriting, jsonErrorSTRUCT_NOT_SETUP_FOR_WRITING);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(
         !(state & jsonStateVALUE ||
           state == jsonStateOBJECT_KEY_OR_OBJECT_STOP),
      jsonErrorCANNOT_VALUE_OUT);

   scopeType = _ScopeGetType(json);

   // Array scope, separate values by a comma.
   if (scopeType == jsonScopeTypeARRAY &&
       !_ScopeIsEmpty(json))
   {
      returnIf(
            !json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), 
         jsonErrorFAILED_WRITE);
   }
   // Object scope, separate key-value pairs by a comma when we are about to write a key.
   if (state == jsonStateOBJECT_KEY_OR_OBJECT_STOP &&
       !_ScopeIsEmpty(json))
   {
      returnIf(
            !json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), 
         jsonErrorFAILED_WRITE);
   }

   // Convert the string to a JSON string.
   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringQUOTE), jsonErrorFAILED_WRITE);
   returnIf(!_WriteStringJson(json, value),                            jsonErrorFAILED_WRITE);
   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringQUOTE), jsonErrorFAILED_WRITE);

   // We just wrote a key of a key-value pair, add the key-value separator.
   if (state == jsonStateOBJECT_KEY_OR_OBJECT_STOP)
   {
      returnIf(
            !json->funcWrite_SetOutput(json->output, jsonStringKEY_VALUE_SEPARATOR), 
         jsonErrorFAILED_WRITE);
   }

   // We are in an object scope, toggle whether we are writing out the key.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Toggle whether we have set the key or not.
      _ScopeSetIsWritingKey(json, !_ScopeIsWritingKey(json));
   }

   // Indicate that the current scope has something.
   _ScopeSetIsEmpty(json, jsonFALSE);

   return jsonErrorNONE;
}

#if 0 // Waiting to see if this is needed.
/**************************************************************************************************
func: jsonWriteStringWchar
**************************************************************************************************/
JsonError jsonWriteStringWchar(Json * const json, wchar_t const * const value)
{
   JsonError error;
   JsonState state;
   JsonChar  buffer[32];

   returnIf(!_isStarted, jsonErrorLIBRARY_NOT_STARTED);
   returnIf(!json,       jsonErrorPARAMETER_BAD);

   // Check if we can write out a value.
   state = _StateGet(json);
   returnIf(
         !(state & jsonStateVALUE ||
           state == jsonStateOBJECT_KEY_OR_OBJECT_STOP),
      jsonErrorCANNOT_VALUE_OUT);

   // We are not in an empty array, add a comma.
   if ( _ScopeGetType(json) == jsonScopeTypeOBJECT &&
       !_ScopeIsEmpty(json))
   {
      returnIf(!json->funcWrite_SetOutput(json->output, jsonStringSEPARATOR), jsonErrorFAILED_WRITE);
   }

   // Convert the integer to a string.
   returnIf(!_WriteStringWchar(json->output, value), jsonErrorFAILED_WRITE);
   returnIf(!json->funcWrite_SetOutput(json->output, jsonStringKEY_VALUE_SEPARATOR), jsonErrorFAILED_WRITE);

   // Indicate that the array has elements in it.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      _ScopeSetIsEmpty(json, jsonFALSE);
   }

   return jsonErrorNONE;
}
#endif

/**************************************************************************************************
lib local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _JsonMemClear
**************************************************************************************************/
void _JsonMemClear(size_t const size, void * const buf)
{
   _memClear(buf, size);
}

/**************************************************************************************************
func: _JsonMemCreate
**************************************************************************************************/
void *_JsonMemCreate(size_t const size)
{
   returnNullIf(!size);

   return _memCreate(size);
}

/**************************************************************************************************
func: _JsonMemClone
**************************************************************************************************/
void *_JsonMemClone(size_t const size, void * const buf)
{
   void *dst;

   returnNullIf(!buf || !size);

   dst = _memCreate(size);
   returnNullIf(!dst);

   memcpy(dst, buf, size);

   return dst;
}

/**************************************************************************************************
func: _JsonMemDestroy
**************************************************************************************************/
void _JsonMemDestroy(void * const buf)
{
   _memDestroy(buf);
}

/**************************************************************************************************
func: _JsonMemGrow
**************************************************************************************************/
JsonBool _JsonMemGrow(size_t const oldSize, void ** const buffer, size_t const newSize)
{
   void *vtemp;

   // Create a new buffer.
   vtemp = _memCreate(newSize);
   returnIf(!vtemp, jsonFALSE);

   // Copy the data from the source buffer.
   memmove(vtemp, *buffer, oldSize);

   // Clean up the old stack.
   _memDestroy(*buffer);

   // Set to the new stack.
   *buffer = vtemp;

   return jsonTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ReadArray
**************************************************************************************************/
static JsonError _ReadArray(Json * const json)
{
   JsonChar  letter;
   JsonError error;

   // Send the token of array start.
   returnIf(
         !json->funcRead_SetOutput(json->output, jsonTokenARRAY_START, NULL),
      jsonErrorFAILED_READ_SET_OUTPUT);

   loop
   {
      error = _ReadValue(json, jsonFALSE);

      // Another value follows.
      if (json->readLastLetter == ',')
      {
         returnIf(
               !json->funcRead_SetOutput(json->output, jsonTokenCOMMA, NULL),
            jsonErrorFAILED_READ_SET_OUTPUT);
         continue;
      }
      // End of the array.
      if (json->readLastLetter == ']')
      {
         break;
      }
      // Called a value that doesn't really read ahead to the next character.
      if (json->readLastLetter == ' ')
      {
         letter = _ReadGetNextLetter(json);
         returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

         if (letter == ',')
         {
            returnIf(
                  !json->funcRead_SetOutput(json->output, jsonTokenCOMMA, NULL),
               jsonErrorFAILED_READ_SET_OUTPUT);
            continue;
         }
         if (letter == ']')
         {
            break;
         }
      }

      // Bad JSON
      return jsonErrorUNEXPECTED_INPUT;
   }

   json->readLastLetter = ' ';

   // Send the token of array stop.
   returnIf(
         !json->funcRead_SetOutput(json->output, jsonTokenARRAY_STOP, NULL),
      jsonErrorFAILED_READ_SET_OUTPUT);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ReadGetNextLetter
**************************************************************************************************/
static JsonChar _ReadGetNextLetter(Json * const json)
{
   JsonBool result;
   JsonChar letter;

   loop
   {
      result = json->funcRead_GetInput(json->input, &letter);
      
      // Bad input or 
      // End of file.
      returnIf(
            result == jsonFALSE ||
            letter == 0, 
         0);

      // Whitespace
      if (letter == (JsonChar) ' '  ||
          letter == (JsonChar) '\t' ||
          letter == (JsonChar) '\n' ||
          letter == (JsonChar) '\r')
      {
         // Skip white space.
         continue;
      }

      break;
   }

   // regular letter.
   return letter;
}

/**************************************************************************************************
func: _ReadNumber
**************************************************************************************************/
static JsonError _ReadNumber(Json * const json, JsonChar letterStart)
{
   JsonStr  *stemp;
   JsonChar  letter;
   JsonBool  isReal;

   isReal = jsonFALSE;
   stemp  = _StrCreate();
   returnIf(!stemp, jsonErrorFAILED_MEMORY_ALLOC);

   _StrAppendLetter(stemp, letterStart);

   // Get the integer portion
   loop
   {
      letter = _ReadGetNextLetter(json);
      returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

      breakIf(!('0' <= letter && letter <= '9'));

      returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);
   }

   // Get the fractional.
   if (letter == '.')
   {
      isReal = jsonTRUE;

      returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);

      loop
      {
         letter = _ReadGetNextLetter(json);
         returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

         breakIf(!('0' <= letter && letter <= '9'));

         returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);
      }
   }

   // Get the exponent.
   if (letter == 'e' || letter == 'E')
   {
      isReal = jsonTRUE;

      returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);

      letter = _ReadGetNextLetter(json);
      returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

      // + and - can only appear at the start of the exponent
      returnIf(
            !(letter == '+' || 
              letter == '-' ||
              ('0' <= letter && letter <= '9')),
         jsonErrorUNEXPECTED_INPUT);

      returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);

      loop
      {
         letter = _ReadGetNextLetter(json);
         returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

         breakIf(!('0' <= letter && letter <= '9'));

         returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);
      }
   }

   // Send out the token.
   if (isReal)
   {
      returnIf(
            !json->funcRead_SetOutput(json->output, jsonTokenNUMBER_REAL, stemp->buff),
         jsonErrorFAILED_READ_SET_OUTPUT);
   }
   else
   {
      returnIf(
            !json->funcRead_SetOutput(json->output, jsonTokenNUMBER_INTEGER, stemp->buff),
         jsonErrorFAILED_READ_SET_OUTPUT);
   }

   // Clean up.
   _StrDestroy(stemp);

   // Set the last letter read.
   json->readLastLetter = letter;

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ReadObject
**************************************************************************************************/
static JsonError _ReadObject(Json * const json)
{
   JsonChar  letter;
   JsonError error;

   // Send the token of array start.
   returnIf(
         !json->funcRead_SetOutput(json->output, jsonTokenOBJECT_START, NULL),
      jsonErrorFAILED_READ_SET_OUTPUT);

   loop
   {
      // Get the key
      error = _ReadValue(json, jsonTRUE);

      // May not be an error.  Could just be a }
      if (error != jsonErrorNONE)
      {
         letter = json->readLastLetter;
         if (letter == '}')
         {
            break;
         }
      }


      // Get the next letter to see what to do.
      letter = _ReadGetNextLetter(json);
      returnIf(!letter, jsonErrorUNEXPECTED_INPUT);

      // Key value splitter.  
      if (letter == ':')
      {
         returnIf(
               !json->funcRead_SetOutput(json->output, jsonTokenKEY_VALUE_SEPARATOR, NULL),
            jsonErrorFAILED_READ_SET_OUTPUT);
      }
      // Not allowed here.
      if (letter == '}')
      {
         return jsonErrorUNEXPECTED_INPUT;
      }

      // Get the value
      error = _ReadValue(json, jsonFALSE);

      // Get the next letter to see what to do.
      letter               = json->readLastLetter;
      json->readLastLetter = ' ';
      if (letter == ' ')
      {
         letter = _ReadGetNextLetter(json);
         returnIf(!letter, jsonErrorUNEXPECTED_INPUT);
      }

      // Another value follows.
      if (letter == ',')
      {
         returnIf(
               !json->funcRead_SetOutput(json->output, jsonTokenCOMMA, NULL),
            jsonErrorFAILED_READ_SET_OUTPUT);
         continue;
      }
      // End of the array.
      if (letter == '}')
      {
         break;
      }

      // Bad JSON
      return jsonErrorUNEXPECTED_INPUT;
   }

   // Send the token of array stop.
   returnIf(
         !json->funcRead_SetOutput(json->output, jsonTokenOBJECT_STOP, NULL),
      jsonErrorFAILED_READ_SET_OUTPUT);

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ReadPredefined
**************************************************************************************************/
static JsonError _ReadPredefined(Json * const json, JsonChar letter)
{
   char ltemp[5];

   // Reading in "false"
   if (letter == 'f')
   {
      ltemp[0] = _ReadGetNextLetter(json);
      ltemp[1] = _ReadGetNextLetter(json);
      ltemp[2] = _ReadGetNextLetter(json);
      ltemp[3] = _ReadGetNextLetter(json);
      
      returnIf(
            !(ltemp[0] == 'a' &&
              ltemp[1] == 'l' &&
              ltemp[2] == 's' &&
              ltemp[3] == 'e'),
         jsonErrorUNEXPECTED_INPUT);

      returnIf(
            !json->funcRead_SetOutput(json->output, jsonTokenBOOL_FALSE, NULL),
         jsonErrorFAILED_READ_SET_OUTPUT);
   }
   
   // Reading in "true"
   if (letter == 't')
   {
      ltemp[0] = _ReadGetNextLetter(json);
      ltemp[1] = _ReadGetNextLetter(json);
      ltemp[2] = _ReadGetNextLetter(json);

      returnIf(
            !(ltemp[0] == 'r' &&
              ltemp[1] == 'u' &&
              ltemp[2] == 'e'),
         jsonErrorUNEXPECTED_INPUT);

      returnIf(
            !json->funcRead_SetOutput(json->output, jsonTokenBOOL_TRUE, NULL),
         jsonErrorFAILED_READ_SET_OUTPUT);
   }

   // Reading in "null"
   if (letter == 'n')
   {
      ltemp[0] = _ReadGetNextLetter(json);
      ltemp[1] = _ReadGetNextLetter(json);
      ltemp[2] = _ReadGetNextLetter(json);

      returnIf(
            !(ltemp[0] == 'u' &&
              ltemp[1] == 'l' &&
              ltemp[2] == 'l'),
         jsonErrorUNEXPECTED_INPUT);

      returnIf(
            !json->funcRead_SetOutput(json->output, jsonTokenNULL, NULL),
         jsonErrorFAILED_READ_SET_OUTPUT);
   }

   // Set the last letter read to a space.
   json->readLastLetter = ' ';

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ReadString
**************************************************************************************************/
static JsonError _ReadString(Json * const json)
{
   JsonStr  *stemp;
   JsonChar  letter;

   stemp = _StrCreate();
   returnIf(!stemp, jsonErrorFAILED_MEMORY_ALLOC);

   loop
   {
      letter = _ReadGetNextLetter(json);
      returnIf(!letter, jsonErrorUNEXPECTED_INPUT);
      
      // And unescaped quote terminates the string.
      breakIf(letter == '\"');
   
      returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);

      // Escaped letter
      if (letter == '\\')
      {
         letter = _ReadGetNextLetter(json);
         returnIf(!letter, jsonErrorUNEXPECTED_INPUT);
         
         returnIf(!_StrAppendLetter(stemp, letter), jsonErrorFAILED_MEMORY_ALLOC);
      }
   }

   // Send the string to the output.
   returnIf(
         !json->funcRead_SetOutput(json->output, jsonTokenSTRING, stemp->buff),
      jsonErrorFAILED_READ_SET_OUTPUT);

   // Destroy the string.  
   _StrDestroy(stemp);

   // Set the last letter read to a space.
   json->readLastLetter = ' ';

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ReadValue
**************************************************************************************************/
static JsonError _ReadValue(Json * const json, JsonBool isStringOnlyAllowed)
{
   JsonChar  letter;
   JsonError error;

   letter = _ReadGetNextLetter(json);

   // Premature EOF
   returnIf(letter == 0, jsonErrorUNEXPECTED_EOF);

   // Start of an object.
   if (letter == '{')
   {
      _ScopePush(json, jsonScopeTypeOBJECT);
      
      returnIf(isStringOnlyAllowed, jsonErrorUNEXPECTED_INPUT);
      error = _ReadObject(json);

      _ScopePop(json);

      return error;
   }

   // Start of an array.
   if (letter == '[')
   {
      _ScopePush(json, jsonScopeTypeARRAY);

      returnIf(isStringOnlyAllowed, jsonErrorUNEXPECTED_INPUT);
      error = _ReadArray(json);

      _ScopePop(json);

      return error;
   }

   // Start of a string.
   if (letter == '\"')
   {
      return _ReadString(json);
   }

   // Start of true, false, or null
   if (letter == 't' ||
       letter == 'f' ||
       letter == 'n')
   {
      returnIf(isStringOnlyAllowed, jsonErrorUNEXPECTED_INPUT);
      return _ReadPredefined(json, letter);
   }

   // Start of a number.
   if (letter == '-' ||
       ('0' <= letter && letter <= '9'))
   {
      returnIf(isStringOnlyAllowed, jsonErrorUNEXPECTED_INPUT);
      return _ReadNumber(json, letter);
   }

   if (letter == ']')
   {
      json->readLastLetter = letter;
      returnIf(_ScopeGetType(json) == jsonScopeTypeARRAY, jsonErrorNONE);
   }

   if (letter == '}')
   {
      json->readLastLetter = letter;
      returnIf(_ScopeGetType(json) == jsonScopeTypeOBJECT, jsonErrorNONE);
   }

   // Bad JSON
   return jsonErrorUNEXPECTED_INPUT;
}

/**************************************************************************************************
func: _ScopeGet
**************************************************************************************************/
static JsonScopeType _ScopeGetType(Json const * const json)
{
   return json->scopeStack[json->scopeIndex].type;
}

/**************************************************************************************************
func: _ScopeIsEmpty
**************************************************************************************************/
static JsonBool _ScopeIsEmpty(Json const * const json)
{
   return json->scopeStack[json->scopeIndex].isEmpty;
}

/**************************************************************************************************
func: _ScopeIsWritingKey
**************************************************************************************************/
static JsonBool _ScopeIsWritingKey(Json const * const json)
{
   return json->scopeStack[json->scopeIndex].isWritingKey;
}

/**************************************************************************************************
func: _ScopePush
**************************************************************************************************/
static JsonError _ScopePush(Json * const json, JsonScopeType const scopeType)
{
   JsonScope *scope;

   // Resize the scope stack.
   if (json->scopeIndex == json->scopeCount - 1)
   {
      returnIf(
            !_JsonMemGrowTypeArray(json->scopeCount, JsonScope, &(json->scopeStack), jsonBUFF_SIZE), 
         jsonErrorFAILED_MEMORY_ALLOC);
   }

   // Move to the nest stack scope.
   json->scopeIndex++;

   // Get the scope structure
   scope = &json->scopeStack[json->scopeIndex];

   // Initialize it.
   scope->type         = scopeType;
   scope->isEmpty      = jsonTRUE;
   scope->isWritingKey = jsonTRUE;

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ScopePop
**************************************************************************************************/
static JsonError _ScopePop(Json * const json)
{
   returnIf(json->scopeIndex == 0, jsonErrorFAILED_SCOPE_POP);
   
   json->scopeIndex--;

   return jsonErrorNONE;
}

/**************************************************************************************************
func: _ScopeSetIsEmpty
**************************************************************************************************/
static void _ScopeSetIsEmpty(Json * const json, JsonBool const value)
{
   json->scopeStack[json->scopeIndex].isEmpty = value;
}

/**************************************************************************************************
func: _ScopeSetIsWritingKey
**************************************************************************************************/
static void _ScopeSetIsWritingKey(Json * const json, JsonBool const value)
{
   json->scopeStack[json->scopeIndex].isWritingKey = value;
}

/**************************************************************************************************
func: _ScopeStart
**************************************************************************************************/
static JsonError _ScopeStart(Json * const json)
{
   json->scopeCount = jsonBUFF_SIZE;
   json->scopeIndex = -1;
   json->scopeStack = _JsonMemCreateTypeArray(json->scopeCount, JsonScope);
   returnIf(!json->scopeStack, jsonErrorFAILED_MEMORY_ALLOC);

   return _ScopePush(json, jsonScopeTypeJSON_ROOT);
}

/**************************************************************************************************
func: _ScopeStop
**************************************************************************************************/
static void _ScopeStop(Json * const json)
{
   _JsonMemDestroy(json->scopeStack);
   json->scopeStack = NULL;
}

/**************************************************************************************************
func: _StateGet
**************************************************************************************************/
static JsonState _StateGet(Json * const json)
{
   // Array scope.
   if (_ScopeGetType(json) == jsonScopeTypeARRAY)
   {
      // Just a list of values until close.
      return jsonStateVALUE_OR_ARRAY_STOP;
   }
   
   // Object scope.
   if (_ScopeGetType(json) == jsonScopeTypeOBJECT)
   {
      // Key value pair.  We are expecting a key or close.
      if (_ScopeIsWritingKey(json))
      {
         return jsonStateOBJECT_KEY_OR_OBJECT_STOP;
      }

      // Key value pair.  We are expecting a value.
      return jsonStateVALUE;
   }

   // Root json element.
   // If nothing is set yet then we expect a value.
   // object, array, string, number, "true", "false", or "null"
   if (_ScopeIsEmpty(json))
   {
      return jsonStateVALUE;
   }

   // We have written the one and only thing that makes up a JSON file.
   return jsonStateNONE;
}

/**************************************************************************************************
func: _StrAppendLetter
**************************************************************************************************/
static JsonBool _StrAppendLetter(JsonStr * const str, JsonChar letter)
{
   // Grow the buffer
   if (str->charLen == str->buffLen - 1)
   {
      returnFalseIf(!_JsonMemGrowTypeArray(str->buffLen, JsonChar, &str->buff, jsonBUFF_SIZE));
      str->buffLen += jsonBUFF_SIZE;
   }

   // Set the letter
   str->buff[str->charLen++] = letter;
   str->buff[str->charLen]   = 0; // Always null terminate.

   return jsonTRUE;
}

/**************************************************************************************************
func: _StrCreate
**************************************************************************************************/
static JsonStr *_StrCreate(void)
{
   JsonStr *str;

   str = _JsonMemCreateType(JsonStr);

   str->charLen = 0;
   str->buffLen = jsonBUFF_SIZE;
   str->buff    = _JsonMemCreateTypeArray(str->buffLen, JsonChar);
   if (!str->buff)
   {
      _JsonMemDestroy(str);
      return NULL;
   }

   str->buff[0] = 0;

   return str;
}

/**************************************************************************************************
func: _StrDestroy
**************************************************************************************************/
static void _StrDestroy(JsonStr * const str)
{
   _JsonMemDestroy(str->buff);
   _JsonMemDestroy(str);
}

/**************************************************************************************************
func: _WriteStringJson

Write out a string.  Escaping the characters that need escaping as we do.
Yes not very efficient but will do for now.  I don't want to allocate memory when I don't 
absolutely need to.
**************************************************************************************************/
static JsonBool _WriteStringJson(Json * const json, JsonChar const * const value)
{
   JsonChar const *letter;
   JsonChar        letterString[2];
   JsonBool        result;

   letterString[1] = 0;

   // For all letters in the null terminated string.
   for (letter = value; *letter != 0; letter++)
   {
      // Write out the escaped letter or the letter itself.
      // Not escaping unicode letters, they should already be properly encoded in the UTF-8 string.
      switch (*letter)
      {
      // Characters to escape.
      case '\"': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\"");  break;
      case '\\': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\");  break;
      case '/':  result = json->funcWrite_SetOutput(json->output, (JsonChar *) "/");   break;
      case '\b': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\b"); break;
      case '\f': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\f"); break;
      case '\n': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\n"); break;
      case '\r': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\r"); break;
      case '\t': result = json->funcWrite_SetOutput(json->output, (JsonChar *) "\\t"); break;

      // No excapting.
      default:   letterString[0] = *letter;
                 result = json->funcWrite_SetOutput(json->output, letterString);       break;
      }

      // There was a problem writing to the output.
      returnFalseIf(!result);
   }

   return jsonTRUE;
}
