/**************************************************************************************************
file:       libJSON
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Simple JSON routines.
**************************************************************************************************/

#if !defined(LIB_JSON_ROBBERT_DE_GROOT)
#define      LIB_JSON_ROBBERT_DE_GROOT

/**************************************************************************************************
include:
**************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef enum
{
   jsonFALSE,
   jsonTRUE
} JsonBool;

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
JsonError jsonWriteString(             Json * const json, JsonChar const * const value);

#endif
