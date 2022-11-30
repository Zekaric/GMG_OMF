/**************************************************************************************************
file:       Test
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Tests for the library.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
function:
**************************************************************************************************/
/**************************************************************************************************
func: 
**************************************************************************************************/
EXTERN_C static JsonBool _BufferAppendString(void * const buffer, JsonChar const * const str)
{
   Str *s;

   s = (Str *) buffer;

   if (!strAppend(s, (char *) str))
   {
      return jsonFALSE;
   }

   return jsonTRUE;
}

/**************************************************************************************************
func: 
**************************************************************************************************/
EXTERN_C static void *memCreate(size_t const size)
{
   if (size <= 0) 
   { 
      return NULL;
   }

   return malloc(size);
}

/**************************************************************************************************
func: 
**************************************************************************************************/
EXTERN_C static void memDestroy(void * const buffer)
{
   if (!buffer)
   {
      return;
   }

   free(buffer);
}

/**************************************************************************************************
func: 
**************************************************************************************************/
EXTERN_C static void memClear(void * const buffer, size_t const size)
{
   if (!buffer ||
       size <= 0)
   {
      return;
   }

   memset(buffer, 0, size);
}

/**************************************************************************************************
test:
**************************************************************************************************/
/**************************************************************************************************
func: Test
**************************************************************************************************/
TEST(TestStr, Test)
{
   Str *s;

   s = strCreate(0);
   EXPECT_TRUE(s != NULL);

   EXPECT_TRUE(strAppend(s, "Append string 1 to an empty string.\n"));
   EXPECT_TRUE(strAppend(s, 
      "Append string 2 to an existing string.  "
      "Expecting a successful grow operation.\n"));
   EXPECT_TRUE(strAppend(s, "One more append."));
   EXPECT_TRUE(strAppend(s, "1"));
   EXPECT_TRUE(strAppend(s, "2"));
   EXPECT_TRUE(strAppend(s, "3"));
   EXPECT_TRUE(strAppend(s, "4"));
   EXPECT_TRUE(strAppend(s, "5"));
   EXPECT_TRUE(strAppend(s, "6"));
   EXPECT_TRUE(strAppend(s, "7"));
   EXPECT_TRUE(strAppend(s, "8"));
   EXPECT_TRUE(strAppend(s, "9"));
   EXPECT_TRUE(strAppend(s, "0"));
   EXPECT_TRUE(strAppend(s, "A"));
   EXPECT_TRUE(strAppend(s, "B"));
   EXPECT_TRUE(strAppend(s, "C"));
   EXPECT_TRUE(strAppend(s, "D"));
   EXPECT_TRUE(strAppend(s, "E"));
   EXPECT_TRUE(strAppend(s, "F"));
   EXPECT_TRUE(strAppend(s, "G"));
   EXPECT_TRUE(strAppend(s, "H"));
   EXPECT_TRUE(strAppend(s, "I"));
   EXPECT_TRUE(strAppend(s, "J"));
   EXPECT_TRUE(strAppend(s, "K"));
   EXPECT_TRUE(strAppend(s, "L"));
   EXPECT_TRUE(strAppend(s, "M"));
   EXPECT_TRUE(strAppend(s, "N"));
   EXPECT_TRUE(strAppend(s, "O"));
   EXPECT_TRUE(strAppend(s, "P"));
   EXPECT_TRUE(strAppend(s, "Q"));
   EXPECT_TRUE(strAppend(s, "R"));
   EXPECT_TRUE(strAppend(s, "S"));
   EXPECT_TRUE(strAppend(s, "T"));
   EXPECT_TRUE(strAppend(s, "U"));
   EXPECT_TRUE(strAppend(s, "V"));
   EXPECT_TRUE(strAppend(s, "W"));
   EXPECT_TRUE(strAppend(s, "X"));
   EXPECT_TRUE(strAppend(s, "Y"));
   EXPECT_TRUE(strAppend(s, "Z"));

   strDestroy(s);
}

/**************************************************************************************************
func: StartAndStop
**************************************************************************************************/
TEST(TestJSONRoutines, StartAndStop) 
{
  EXPECT_EQ(jsonStart(memCreate, memDestroy, memClear), jsonErrorNONE);
  jsonStop();
}

/**************************************************************************************************
func: CreateWrite
**************************************************************************************************/
TEST(TestJSONRoutines, CreateWrite)
{
   Str   *s;
   Json  *json;

   s = strCreate(0);
   
   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateWrite(NULL, NULL);
   EXPECT_TRUE( json == NULL);

   json = jsonCreateWrite(s, NULL);
   EXPECT_TRUE( json == NULL);

   json = jsonCreateWrite(NULL, _BufferAppendString);
   EXPECT_TRUE( json == NULL);

   json = jsonCreateWrite(s, _BufferAppendString);
   EXPECT_FALSE(json == NULL);

   jsonDestroy(json);

   jsonStop();

   strDestroy(s);
}

/**************************************************************************************************
func: write
**************************************************************************************************/
TEST(TestJSONRoutines, Write)
{
   Str   *s;
   Json  *json;

   s = strCreate(0);

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateWrite(s, _BufferAppendString);

   jsonWriteObjectStart(json);
   {
      jsonWriteString( json, (JsonChar *) "ValueTrue");
      jsonWriteBoolean(json, jsonTRUE);

      jsonWriteString( json, (JsonChar *) "ValueFalse");
      jsonWriteBoolean(json, jsonFALSE);

      jsonWriteString( json, (JsonChar *) "ValueNull");
      jsonWriteNull(   json);

      jsonWriteString( json, (JsonChar *) "ValueString");
      jsonWriteString( json, (JsonChar *) "The quick brown fox jumped over the lazy dog.");

      jsonWriteString( json, (JsonChar *) "ValueInteger");
      jsonWriteInteger(json, 42);

      jsonWriteString( json, (JsonChar *) "ValueReal");
      jsonWriteReal(   json, 1.234567890123456789);

      jsonWriteString( json, (JsonChar *) "ValueReal4");
      jsonWriteReal4(  json, 1.234567890123456789);

      jsonWriteString( json, (JsonChar *) "ValueArrayInt");
      jsonWriteArrayStart(json);
      {
         int index;

         for (index = 1; index <= 10; index++)
         {
            jsonWriteInteger(json, index);
         }
      }
      jsonWriteArrayStop(json);

      jsonWriteString( json, (JsonChar *) "ValueObject");
      jsonWriteObjectStart(json);
      {
         jsonWriteString( json, (JsonChar *) "ValueTrue");
         jsonWriteBoolean(json, jsonTRUE);

         jsonWriteString( json, (JsonChar *) "ValueFalse");
         jsonWriteBoolean(json, jsonFALSE);

         jsonWriteString( json, (JsonChar *) "ValueNull");
         jsonWriteNull(   json);

         jsonWriteString( json, (JsonChar *) "ValueString");
         jsonWriteString( json, (JsonChar *) "The quick brown fox jumped over the lazy dog.");

         jsonWriteString( json, (JsonChar *) "ValueInteger");
         jsonWriteInteger(json, 42);

         jsonWriteString( json, (JsonChar *) "ValueReal");
         jsonWriteReal(   json, 1.234567890123456789);

         jsonWriteString( json, (JsonChar *) "ValueReal4");
         jsonWriteReal4(  json, 1.234567890123456789);

         jsonWriteString( json, (JsonChar *) "ValueArrayInt");
         jsonWriteArrayStart(json);
         {
            int index;

            for (index = 1; index <= 10; index++)
            {
               jsonWriteInteger(json, index);
            }
         }
         jsonWriteArrayStop(json);

         jsonWriteString( json, (JsonChar *) "ValueObject");
         jsonWriteObjectStart(json);
         {
            jsonWriteString(json, (JsonChar *) "ValueString");
            jsonWriteString(json, (JsonChar *) "Ok, \r\n\tThat's enough of this silliness.");
         }
         jsonWriteObjectStop(json);
      }
      jsonWriteObjectStop(json);
   }
   jsonWriteObjectStop(json);

   jsonDestroy(json);

   jsonStop();

   strDestroy(s);
}