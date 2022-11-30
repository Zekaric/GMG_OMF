/**************************************************************************************************
file:       libJSON_C
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Simple JSON routines.
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

#if !defined(LIB_JSON_RDG)
#define      LIB_JSON_RDG

/**************************************************************************************************
include:
**************************************************************************************************/
#include <assert.h>
#include <locale.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************************
constant:
**************************************************************************************************/
#define jsonTRUE     true
#define jsonFALSE    false

/**************************************************************************************************
type:
**************************************************************************************************/
typedef enum
{
   jsonErrorNONE,

   jsonErrorCANNOT_ARRAY_START,
   jsonErrorCANNOT_ARRAY_STOP,
   jsonErrorCANNOT_OBJECT_START,
   jsonErrorCANNOT_OBJECT_STOP,
   jsonErrorCANNOT_VALUE_OUT,
   jsonErrorFAILED_MEMORY_ALLOC,
   jsonErrorFAILED_SCOPE_POP,
   jsonErrorFAILED_WRITE,
   jsonErrorLIBRARY_NOT_STARTED,
   jsonErrorPARAMETER_BAD,
} JsonError;

typedef enum
{
   jsonObjectPartNONE,

   jsonObjectPartKEY,
   jsonObjectPartVALUE
} JsonObjectPart;

typedef enum
{
   jsonScopeTypeJSON_ROOT,
   jsonScopeTypeOBJECT,
   jsonScopeTypeARRAY
} JsonScopeType;

typedef enum
{
   jsonStateNONE,

   jsonStateVALUE                                     = 0x10000000,
   jsonStateVALUE_OR_ARRAY_STOP,
   jsonStateOBJECT_KEY_OR_OBJECT_STOP                 = 0x20000000,
} JsonState;

typedef enum
{                                   // Starts with...
   jsonTokenNONE,
   
   jsonTokenARRAY_START,            // [
   jsonTokenARRAY_STOP,             // ]
   jsonTokenBOOL_FALSE,             // "false"
   jsonTokenBOOL_TRUE,              // "true"
   jsonTokenCOMMA,                  // ,
   jsonTokenEOF,
   jsonTokenKEY_VALUE_SEPARATOR,    // :
   jsonTokenNULL,                   // "null"
   jsonTokenNUMBER_INTEGER,         // -0123456789
   jsonTokenNUMBER_REAL,            // -0123456789
   jeonTokenOBJECT_START,           // {
   jsonTokenOBJECT_STOP,            // }
   jsonTokenSTRING,                 // "
} JsonToken;

typedef unsigned char          Uft8Char;

typedef bool                   JsonBool;
typedef Uft8Char               JsonChar;
typedef int32_t                JsonCount;
typedef struct JsonScope       JsonScope;
typedef struct Json            Json;

struct Json
{
   JsonBool                    isWriting;
   void                       *input;
   void                       *output;
   JsonBool                  (*funcRead_GetInput)(  void * const input,  JsonChar       * const letter);
   JsonBool                  (*funcRead_SetOutput)( void * const output, JsonToken const token, JsonChar const * const value);
   JsonBool                  (*funcWrite_SetOutput)(void * const output, JsonChar const * const value);
   JsonScope                  *scopeStack;
   JsonCount                   scopeIndex;
   JsonCount                   scopeCount;
   JsonObjectPart              part;
};

struct JsonScope
{
   JsonScopeType               type;
   JsonBool                    isEmpty;
   JsonBool                    isWritingKey;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

JsonError jsonStart(                   void *(*memCreate)(size_t const size), void (*memDestroy)(void * const buffer), void (*memClear)(void * const buffer, size_t const size));
void      jsonStop(                    void);
                                       
Json     *jsonCreateRead(                                 void * const input,  JsonBool (*func_GetInput)( void * const input,  JsonChar       * const letter), void * const output, JsonBool (*func_SetOutput)(void * const output, JsonToken const token, JsonChar const * const value));
JsonBool  jsonCreateContentRead(       Json * const json, void * const input,  JsonBool (*func_GetInput)( void * const input,  JsonChar       * const letter), void * const output, JsonBool (*func_SetOutput)(void * const output, JsonToken const token, JsonChar const * const value));
Json     *jsonCreateWrite(                                void * const output, JsonBool (*func_SetOutput)(void * const output, JsonChar const * const value));
JsonBool  jsonCreateContentWrite(      Json * const json, void * const output, JsonBool (*func_SetOutput)(void * const output, JsonChar const * const value));
                                       
void      jsonDestroy(                 Json * const json);
void      jsonDestroyContent(          Json * const json);

JsonError jsonWriteArrayStart(         Json * const json);
JsonError jsonWriteArrayStop(          Json * const json);
JsonError jsonWriteBoolean(            Json * const json, JsonBool value);
JsonError jsonWriteInteger(            Json * const json, int64_t value);
JsonError jsonWriteNextArrayOrObject(  Json * const json);
JsonError jsonWriteNull(               Json * const json);
JsonError jsonWriteObjectStart(        Json * const json);
JsonError jsonWriteObjectStop(         Json * const json);
JsonError jsonWriteReal(               Json * const json, double value);
JsonError jsonWriteReal4(              Json * const json, double value);
JsonError jsonWriteString(             Json * const json, JsonChar const * const value);

#if defined(__cplusplus)
}
#endif

#endif
