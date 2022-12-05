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

// This should get around the compiler error about no binary |=, |, & operator found for JsonError.
inline JsonError operator |(JsonError a, JsonError b)
{
    return static_cast<JsonError>(static_cast<int>(a) | static_cast<int>(b));
}

inline JsonError operator &(JsonError a, JsonError b)
{
    return static_cast<JsonError>(static_cast<int>(a) & static_cast<int>(b));
}

inline JsonError& operator |=(JsonError& a, JsonError b)
{
    return a= a |b;
}

/**************************************************************************************************
variable: 
**************************************************************************************************/
static char *omfJson = 
   "{\n"
   "   \"aa6fec60-fefe-4e5f-b742-e581ec73b769\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 60,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 99\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"a8b06d1e-bbac-4746-bb90-888f9b1f8f6e\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         \"WP001\", \"WP002\", \"WP003\", \"WP004\", \"WP005\", \"WP006\", \"WP007\", \"WP008\", \"WP009\", \"WP010\",\n"
   "         \"WP011\", \"WP012\", \"WP013\", \"WP014\", \"WP015\", \"WP016\", \"WP017\", \"WP018\", \"WP019\", \"WP020\",\n"
   "         \"WP021\", \"WP022\", \"WP023\",          \"WP025\", \"WP026\", \"WP027\", \"WP028\", \"WP029\", \"WP030\",\n"
   "         \"WP031\", \"WP032\", \"WP033\", \"WP034\", \"WP035\", \"WP036\", \"WP037\", \"WP038\", \"WP039\", \"WP040\",\n"
   "         \"WP041\",          \"WP043\", \"WP044\", \"WP045\", \"WP046\", \"WP047\", \"WP048\", \"WP049\", \"WP050\",\n"
   "                  \"WP052\", \"WP053\", \"WP054\", \"WP055\", \"WP056\", \"WP057\", \"WP058\"\n"
   "      ],\n"
   "      \"__class__\": \"StringArray\"\n"
   "   },\n"
   "   \"78ba26b7-1c9a-4880-8580-d574b49e6ecc\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"a8b06d1e-bbac-4746-bb90-888f9b1f8f6e\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"95c44ffa-965b-4f32-af97-3a53768303ba\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         [ 61, 255, 61 ],\n"
   "         [ 255, 255, 96 ],\n"
   "         [ 255, 25, 25 ],\n"
   "         [ 255, 132, 193 ], \n"
   "         [ 158, 255, 61 ],\n"
   "         [ 255, 175, 96 ],\n"
   "         [ 255, 168, 168 ],\n"
   "         [ 96, 96, 255 ],\n"
   "         [ 61, 61, 255 ], \n"
   "         [ 255, 193, 132 ],\n"
   "         [ 255, 96, 255 ],\n"
   "         [ 132, 255, 193 ],\n"
   "         [ 96, 255, 255 ],\n"
   "         [ 193, 132, 255 ], \n"
   "         [ 25, 255, 140 ],\n"
   "         [ 255, 96, 175 ],\n"
   "         [ 175, 255, 96 ],\n"
   "         [ 168, 211, 255 ],\n"
   "         [ 25, 255, 25 ], \n"
   "         [ 168, 255, 255 ],\n"
   "         [ 25, 255, 255 ],\n"
   "         [ 255, 132, 132 ],\n"
   "         [ 168, 255, 211 ],\n"
   "         [ 175, 96, 255 ], \n"
   "         [ 140, 25, 255 ],\n"
   "         [ 255, 25, 255 ],\n"
   "         [ 255, 61, 158 ],\n"
   "         [ 61, 158, 255 ],\n"
   "         [ 132, 255, 132 ],\n"
   "         [ 193, 255, 132 ],\n"
   "         [ 255, 255, 61 ],\n"
   "         [ 132, 193, 255 ], \n"
   "         [ 255, 255, 132 ],\n"
   "         [ 25, 140, 255 ],\n"
   "         [ 61, 255, 158 ],\n"
   "         [ 255, 140, 25 ],\n"
   "         [ 168, 255, 168 ],\n"
   "         [ 132, 255, 255 ],\n"
   "         [ 140, 255, 25 ], \n"
   "         [ 158, 61, 255 ],\n"
   "         [ 255, 132, 255 ],\n"
   "         [ 255, 255, 168 ],\n"
   "         [ 255, 158, 61 ],\n"
   "         [ 211, 255, 168 ],\n"
   "         [ 255, 61, 61 ],\n"
   "         [ 132, 132, 255 ], \n"
   "         [ 96, 255, 96 ],\n"
   "         [ 61, 255, 255 ],\n"
   "         [ 255, 211, 168 ],\n"
   "         [ 255, 25, 140 ],\n"
   "         [ 25, 25, 255 ],\n"
   "         [ 255, 255, 25 ], \n"
   "         [ 255, 96, 96 ],\n"
   "         [ 96, 255, 175 ], \n"
   "         [ 96, 175, 255 ]\n"
   "      ],\n"
   "      \"__class__\": \"ColorArray\"\n"
   "   },\n"
   "   \"7e6febf4-ca5c-4480-beae-3404212d8e48\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"95c44ffa-965b-4f32-af97-3a53768303ba\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"43a206d8-1beb-4d35-a528-4f422f34a92d\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"vertices\",\n"
   "      \"array\": \"aa6fec60-fefe-4e5f-b742-e581ec73b769\",\n"
   "      \"legends\": [\n"
   "         \"78ba26b7-1c9a-4880-8580-d574b49e6ecc\",\n"
   "         \"7e6febf4-ca5c-4480-beae-3404212d8e48\"\n"
   "      ],\n"
   "      \"__class__\": \"MappedData\"\n"
   "   },\n"
   "   \"24b86b64-90c9-448b-b0de-2dab6feae213\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 159,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 892\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"fbd1ec9c-ccd6-4dfd-ab3e-e8d17ea2fcb1\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"origin\": [\n"
   "         0,\n"
   "         0,\n"
   "         0\n"
   "      ],\n"
   "      \"vertices\": \"24b86b64-90c9-448b-b0de-2dab6feae213\",\n"
   "      \"__class__\": \"PntSetGeometry\"\n"
   "   },\n"
   "   \"538089c7-d2f0-4260-ba91-7ae674b9bdea\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"collar\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [\n"
   "         \"43a206d8-1beb-4d35-a528-4f422f34a92d\"\n"
   "      ],\n"
   "      \"color\": [\n"
   "         174,\n"
   "         199,\n"
   "         232\n"
   "      ],\n"
   "      \"geometry\": \"fbd1ec9c-ccd6-4dfd-ab3e-e8d17ea2fcb1\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"point\",\n"
   "      \"__class__\": \"PntSetElement\"\n"
   "   },\n"
   "   \"91bf26c2-c955-4480-98f5-4d9d14f14601\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 1051,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 14533\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"6468dbdb-cb35-4c0d-bbbd-1faa49150ca3\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"CU_pct\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"91bf26c2-c955-4480-98f5-4d9d14f14601\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"85b5d4e0-06f5-4d9f-a895-f12d0ef81190\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 15584,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 9964\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"79c34d45-d198-4b4a-b066-542c96878bc9\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"DENSITY\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"85b5d4e0-06f5-4d9f-a895-f12d0ef81190\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"7ccf8ee0-b037-44fd-a124-ad279b57d038\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 25548,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 14252\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"e864aa11-44dc-4bb6-a312-08ec569f76a5\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"AG_gpt\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"7ccf8ee0-b037-44fd-a124-ad279b57d038\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"a6e5c2cc-acdf-4596-9d31-9b9e39bbef2e\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 39800,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 15347\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"bc057cef-0eb6-4a13-a213-c388ee81fc0a\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"AU_gpt\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"a6e5c2cc-acdf-4596-9d31-9b9e39bbef2e\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"3b515c11-1bb8-4ce4-8f54-289254d2fa1c\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 55147,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 3301\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"3afe4e07-807a-42e9-b5ba-09157f90c058\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"RECOV\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"3b515c11-1bb8-4ce4-8f54-289254d2fa1c\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"6dee20aa-c143-42bb-9d40-4ebcbc661548\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 58448,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 6566\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"292ff592-4a81-4802-bf09-de72fe5e64a0\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"S_pct\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"6dee20aa-c143-42bb-9d40-4ebcbc661548\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"dfa36d76-db43-4e9f-8d3d-85893d7c44fa\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 65014,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 18729\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"0ed882e1-5d33-422a-9576-bcea91c7b63b\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"MO_ppm\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"dfa36d76-db43-4e9f-8d3d-85893d7c44fa\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"1f85d8eb-de71-4892-b7b4-25cd00abf55e\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 83743,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 16338\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"2880f5a6-a025-4cc0-a82e-0ef1f2452ee4\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"AS_ppm\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"1f85d8eb-de71-4892-b7b4-25cd00abf55e\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"982c6aea-fcbe-410f-aac1-f14503dc55b5\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 100081,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 1152\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"c03946c3-8472-4f07-8ac0-d35b9ff1c945\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         \"Ignored\",\n"
   "         \"Ore\",\n"
   "         \"waste\"\n"
   "      ],\n"
   "      \"__class__\": \"StringArray\"\n"
   "   },\n"
   "   \"89a190db-1348-431b-9557-2f597d44f953\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"Final_cut\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"c03946c3-8472-4f07-8ac0-d35b9ff1c945\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"1d725801-a4ee-45a8-bb86-3c7a0ce1c0c9\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         [116,55,240],\n"
   "         [87,148,108],\n"
   "         [198,250,190]\n"
   "      ],\n"
   "      \"__class__\": \"ColorArray\"\n"
   "   },\n"
   "   \"3849d694-04a4-44cb-9f57-15622d033c38\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"Final_cut\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"1d725801-a4ee-45a8-bb86-3c7a0ce1c0c9\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"a61d96a0-b5cf-478a-b612-bad21007142e\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"Final_cut\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"982c6aea-fcbe-410f-aac1-f14503dc55b5\",\n"
   "      \"legends\": [\n"
   "         \"89a190db-1348-431b-9557-2f597d44f953\",\n"
   "         \"3849d694-04a4-44cb-9f57-15622d033c38\"\n"
   "      ],\n"
   "      \"__class__\": \"MappedData\"\n"
   "   },\n"
   "   \"a445cefe-024f-477f-98fb-183e5dd4f9de\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 101233,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 261\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"1c6dbdb1-df1c-4484-9462-ac04ec6cd016\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         \"WP001\",\"WP002\",\"WP003\",\"WP004\",\"WP005\",\n"
   "         \"WP006\",\"WP007\",\"WP008\",\"WP009\",\"WP010\",\n"
   "         \"WP011\",\"WP012\",\"WP013\",\"WP014\",\"WP015\",\n"
   "         \"WP016\",\"WP017\",\"WP018\",\"WP019\",\"WP020\",\n"
   "         \"WP021\",\"WP022\",\"WP023\",\"WP025\",\"WP026\",\n"
   "         \"WP027\",\"WP028\",\"WP029\",\"WP030\",\"WP031\",\n"
   "         \"WP032\",\"WP033\",\"WP034\",\"WP035\",\"WP036\",\n"
   "         \"WP037\",\"WP038\",\"WP039\",\"WP040\",\"WP041\",\n"
   "         \"WP043\",\"WP044\",\"WP045\",\"WP046\",\"WP047\",\n"
   "         \"WP048\",\"WP049\",\"WP050\",\"WP052\",\"WP053\",\n"
   "         \"WP054\",\"WP055\",\"WP056\",\"WP057\",\"WP058\"\n"
   "      ],\n"
   "      \"__class__\": \"StringArray\"\n"
   "   },\n"
   "   \"c38e23f2-1e87-4f1c-be4c-6bff2d30aa0f\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"1c6dbdb1-df1c-4484-9462-ac04ec6cd016\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"30fff2d0-084f-45cd-ae41-1731ca049a76\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": [\n"
   "         [61,255,255],\n"
   "         [255,61,158],\n"
   "         [255,61,61],\n"
   "         [211,255,168],\n"
   "         [255,255,61],\n"
   "         [255,61,61],\n"
   "         [25,255,255],\n"
   "         [61,61,255],\n"
   "         [255,175,96],\n"
   "         [132,255,255],\n"
   "         [193,255,132],\n"
   "         [255,132,255],\n"
   "         [255,96,175],\n"
   "         [61,255,158],\n"
   "         [96,175,255],\n"
   "         [61,255,158],\n"
   "         [255,255,168],\n"
   "         [132,255,132],\n"
   "         [96,255,255],\n"
   "         [175,255,96],\n"
   "         [175,96,255],\n"
   "         [255,25,25],\n"
   "         [132,255,193],\n"
   "         [255,25,255],\n"
   "         [168,255,168],\n"
   "         [158,61,255],\n"
   "         [25,25,255],\n"
   "         [96,255,96],\n"
   "         [255,255,132],\n"
   "         [255,168,168],\n"
   "         [132,193,255],\n"
   "         [140,255,25],\n"
   "         [255,255,96],\n"
   "         [61,255,61],\n"
   "         [255,255,25],\n"
   "         [255,140,25],\n"
   "         [96,96,255],\n"
   "         [255,132,193],\n"
   "         [25,255,25],\n"
   "         [255,211,168],\n"
   "         [96,255,175],\n"
   "         [25,255,140],\n"
   "         [255,61,255],\n"
   "         [255,193,132],\n"
   "         [140,25,255],\n"
   "         [255,158,61],\n"
   "         [255,25,140],\n"
   "         [255,96,96],\n"
   "         [255,96,255],\n"
   "         [158,255,61],\n"
   "         [61,158,255],\n"
   "         [193,132,255],\n"
   "         [255,132,132],\n"
   "         [25,140,255],\n"
   "         [132,132,255]\n"
   "      ],\n"
   "      \"__class__\": \"ColorArray\"\n"
   "   },\n"
   "   \"6d06967e-de74-4dc8-857b-c8da9538fdc7\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"values\": \"30fff2d0-084f-45cd-ae41-1731ca049a76\",\n"
   "      \"__class__\": \"Legend\"\n"
   "   },\n"
   "   \"351d1919-f577-426d-95bd-dab287b4b545\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"name\": \"holeid\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"segments\",\n"
   "      \"array\": \"a445cefe-024f-477f-98fb-183e5dd4f9de\",\n"
   "      \"legends\": [\n"
   "         \"c38e23f2-1e87-4f1c-be4c-6bff2d30aa0f\",\n"
   "         \"6d06967e-de74-4dc8-857b-c8da9538fdc7\"\n"
   "      ],\n"
   "      \"__class__\": \"MappedData\"\n"
   "   },\n"
   "   \"357241d5-00c1-4689-9320-4443e1c5de9b\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 101494,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 160194\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"0bb3fe9d-e0ae-4ad7-8117-8b83058bd3ef\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 261688,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 14294\n"
   "      },\n"
   "      \"__class__\": \"Int2Array\"\n"
   "   },\n"
   "   \"8e30c134-6371-431d-a12b-f99b33901b70\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:31Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"357241d5-00c1-4689-9320-4443e1c5de9b\",\n"
   "      \"segments\": \"0bb3fe9d-e0ae-4ad7-8117-8b83058bd3ef\",\n"
   "      \"__class__\": \"LineSetGeometry\"\n"
   "   },\n"
   "   \"39daee76-e38d-44a6-b1ad-5fb16796ce9a\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:22Z\",\n"
   "      \"name\": \"wolfpass_WP_assay\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [\n"
   "         \"6468dbdb-cb35-4c0d-bbbd-1faa49150ca3\",\n"
   "         \"79c34d45-d198-4b4a-b066-542c96878bc9\",\n"
   "         \"e864aa11-44dc-4bb6-a312-08ec569f76a5\",\n"
   "         \"bc057cef-0eb6-4a13-a213-c388ee81fc0a\",\n"
   "         \"3afe4e07-807a-42e9-b5ba-09157f90c058\",\n"
   "         \"292ff592-4a81-4802-bf09-de72fe5e64a0\",\n"
   "         \"0ed882e1-5d33-422a-9576-bcea91c7b63b\",\n"
   "         \"2880f5a6-a025-4cc0-a82e-0ef1f2452ee4\",\n"
   "         \"a61d96a0-b5cf-478a-b612-bad21007142e\",\n"
   "         \"351d1919-f577-426d-95bd-dab287b4b545\"\n"
   "      ],\n"
   "      \"color\": [199,199,199],\n"
   "      \"geometry\": \"8e30c134-6371-431d-a12b-f99b33901b70\",\n"
   "      \"subtype\": \"line\",\n"
   "      \"__class__\": \"LineSetElement\"\n"
   "   },\n"
   "   \"baff1938-18a5-45dd-a13b-88c602e427db\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 275982,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 245367\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"a7edab72-587a-40c9-8040-5b2b4842fa37\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"name\": \"Elevation\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"vertices\",\n"
   "      \"array\": \"baff1938-18a5-45dd-a13b-88c602e427db\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"ab6f9cc5-e48b-4d87-8575-201302d193b6\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 521349,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 671393\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"caf5db70-1237-46e4-8f38-adc66a6f0434\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 1192742,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 267390\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"c766d7f3-d872-4d22-afec-54790eefbf1c\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"ab6f9cc5-e48b-4d87-8575-201302d193b6\",\n"
   "      \"triangles\": \"caf5db70-1237-46e4-8f38-adc66a6f0434\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"697f7955-9d48-46c4-addf-34d2e3fba525\": {\n"
   "      \"date_created\": \"2017-08-29T18:25:30Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:30Z\",\n"
   "      \"name\": \"\",\n"
   "      \"description\": \"\",\n"
   "      \"origin\": [443200,491750,0],\n"
   "      \"axis_u\": [4425,0,0],\n"
   "      \"axis_v\": [0,3690,0],\n"
   "      \"image\": {\n"
   "         \"start\": 1460132,\n"
   "         \"dtype\": \"image/png\",\n"
   "         \"length\": 872539\n"
   "      },\n"
   "      \"__class__\": \"ImageTexture\"\n"
   "   },\n"
   "   \"91f54905-5051-49e2-8de6-25c97f23a8e2\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:30Z\",\n"
   "      \"name\": \"Topography\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [\n"
   "         \"a7edab72-587a-40c9-8040-5b2b4842fa37\"\n"
   "      ],\n"
   "      \"color\": [152,223,138],\n"
   "      \"geometry\": \"c766d7f3-d872-4d22-afec-54790eefbf1c\",\n"
   "      \"textures\": [\n"
   "         \"697f7955-9d48-46c4-addf-34d2e3fba525\"\n"
   "      ],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"9a430ccb-ee89-44a0-b978-d2b25d623af2\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:32Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:32Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 2332671,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 812893\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"2c74bb64-9711-4150-aa32-7c36c54c8c15\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:32Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:32Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 3145564,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 366411\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"7e1820b7-69b3-4239-8671-b6962daf4690\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:32Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:32Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"9a430ccb-ee89-44a0-b978-d2b25d623af2\",\n"
   "      \"triangles\": \"2c74bb64-9711-4150-aa32-7c36c54c8c15\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"12380ba7-6864-49e3-b873-7793c034b84d\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:32Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"Basement\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [],\n"
   "      \"color\": [214,39,40],\n"
   "      \"geometry\": \"7e1820b7-69b3-4239-8671-b6962daf4690\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"b8eee73f-04d9-47b4-b159-ca05b8b386dc\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 3511975,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 764944\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"e5d88471-5d05-413a-851c-cdb0633f14bd\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 4276919,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 341809\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"28a10326-3506-4b5c-8570-f8640e61ebb9\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"b8eee73f-04d9-47b4-b159-ca05b8b386dc\",\n"
   "      \"triangles\": \"e5d88471-5d05-413a-851c-cdb0633f14bd\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"74d84d14-3a3b-40aa-83f0-08a0795c1842\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"Early Diorite\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [],\n"
   "      \"color\": [227,119,194],\n"
   "      \"geometry\": \"28a10326-3506-4b5c-8570-f8640e61ebb9\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"69aa4d7a-e909-4615-b3d9-3c4c62520b23\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 4618728,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 1020471\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"d1a810a4-820f-4481-99e9-76ddaa637069\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 5639199,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 476545\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"564bffc6-4d68-480b-997e-347835c284e5\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"69aa4d7a-e909-4615-b3d9-3c4c62520b23\",\n"
   "      \"triangles\": \"d1a810a4-820f-4481-99e9-76ddaa637069\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"3ecc6939-241e-422e-ada0-99b2f656b806\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"Intermineral diorite\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [],\n"
   "      \"color\": [247,182,210],\n"
   "      \"geometry\": \"564bffc6-4d68-480b-997e-347835c284e5\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"6d76b1c7-e35b-47a7-a6ab-6bb80017ec9b\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 6115744,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 364716\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"71eb4fec-d9af-401e-91f5-e468fc17cd78\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 6480460,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 179363\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"6dc4014b-4322-4772-ab77-0c264bd4dcb0\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"6d76b1c7-e35b-47a7-a6ab-6bb80017ec9b\",\n"
   "      \"triangles\": \"71eb4fec-d9af-401e-91f5-e468fc17cd78\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"726b37cb-ad38-44a0-bb4c-6ad3ea4ab3f1\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"Dacite\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [],\n"
   "      \"color\": [152,223,138],\n"
   "      \"geometry\": \"6dc4014b-4322-4772-ab77-0c264bd4dcb0\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"42b5a211-6fee-4fe2-942b-65e17efec5e3\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 6659823,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 1014649\n"
   "      },\n"
   "      \"__class__\": \"Vector3Array\"\n"
   "   },\n"
   "   \"0e9f73b1-e90f-4b28-bb32-50258ea14b1e\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 7674472,\n"
   "         \"dtype\": \"<i8\",\n"
   "         \"length\": 419838\n"
   "      },\n"
   "      \"__class__\": \"Int3Array\"\n"
   "   },\n"
   "   \"1354e6da-04f6-41f5-ab97-e33d055b295a\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:27Z\",\n"
   "      \"origin\": [0,0,0],\n"
   "      \"vertices\": \"42b5a211-6fee-4fe2-942b-65e17efec5e3\",\n"
   "      \"triangles\": \"0e9f73b1-e90f-4b28-bb32-50258ea14b1e\",\n"
   "      \"__class__\": \"SurfGeometry\"\n"
   "   },\n"
   "   \"de99b692-3bc7-429e-a229-1254e69495d9\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:27Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:14Z\",\n"
   "      \"name\": \"Cover\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [],\n"
   "      \"color\": [197,176,213],\n"
   "      \"geometry\": \"1354e6da-04f6-41f5-ab97-e33d055b295a\",\n"
   "      \"textures\": [],\n"
   "      \"subtype\": \"surface\",\n"
   "      \"__class__\": \"SurfElement\"\n"
   "   },\n"
   "   \"a8619a26-7495-4083-9438-a611ab915f2a\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"array\": {\n"
   "         \"start\": 8094310,\n"
   "         \"dtype\": \"<f8\",\n"
   "         \"length\": 12739166\n"
   "      },\n"
   "      \"__class__\": \"ScalarArray\"\n"
   "   },\n"
   "   \"c6a68c40-7a23-432b-a04a-31f6e855a785\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"name\": \"CU_pct\",\n"
   "      \"description\": \"\",\n"
   "      \"location\": \"cells\",\n"
   "      \"array\": \"a8619a26-7495-4083-9438-a611ab915f2a\",\n"
   "      \"__class__\": \"ScalarData\"\n"
   "   },\n"
   "   \"0ccfc3df-bf7d-4c99-8aaa-cc4bece06f15\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:28Z\",\n"
   "      \"date_modified\": \"2017-02-27T00:21:28Z\",\n"
   "      \"origin\": [444700,492800,2330],\n"
   "      \"tensor_u\": [\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10\n"
   "      ],\n"
   "      \"tensor_v\": [\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10\n"
   "      ],\n"
   "      \"tensor_w\": [\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,\n"
   "         10,10,10,10,10,10\n"
   "      ],\n"
   "      \"axis_u\": [1,0,0],\n"
   "      \"axis_v\": [0,1,0],\n"
   "      \"axis_w\": [0,0,1],\n"
   "      \"__class__\": \"VolGridGeometry\"\n"
   "   },\n"
   "   \"e6cc3e55-d6b3-4b26-bbac-4c490c1b465a\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:31Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:23Z\",\n"
   "      \"name\": \"Block Model\",\n"
   "      \"description\": \"\",\n"
   "      \"data\": [\n"
   "         \"c6a68c40-7a23-432b-a04a-31f6e855a785\"\n"
   "      ],\n"
   "      \"color\": [219,219,141],\n"
   "      \"geometry\": \"0ccfc3df-bf7d-4c99-8aaa-cc4bece06f15\",\n"
   "      \"subtype\": \"volume\",\n"
   "      \"__class__\": \"VolElement\"\n"
   "   },\n"
   "   \"b3a1eb11-d893-4e15-9b4d-6b7fdd4b35da\": {\n"
   "      \"date_created\": \"2017-02-27T00:21:32Z\",\n"
   "      \"date_modified\": \"2017-08-29T18:25:47Z\",\n"
   "      \"name\": \"Wolfpass\",\n"
   "      \"description\": \"OMF Wolfpass model\",\n"
   "      \"author\": \"\",\n"
   "      \"revision\": \"\",\n"
   "      \"units\": \"\",\n"
   "      \"elements\": [\n"
   "         \"538089c7-d2f0-4260-ba91-7ae674b9bdea\",\n"
   "         \"39daee76-e38d-44a6-b1ad-5fb16796ce9a\",\n"
   "         \"91f54905-5051-49e2-8de6-25c97f23a8e2\",\n"
   "         \"12380ba7-6864-49e3-b873-7793c034b84d\",\n"
   "         \"74d84d14-3a3b-40aa-83f0-08a0795c1842\",\n"
   "         \"3ecc6939-241e-422e-ada0-99b2f656b806\",\n"
   "         \"726b37cb-ad38-44a0-bb4c-6ad3ea4ab3f1\",\n"
   "         \"de99b692-3bc7-429e-a229-1254e69495d9\",\n"
   "         \"e6cc3e55-d6b3-4b26-bbac-4c490c1b465a\"\n"
   "      ],\n"
   "      \"origin\": [0,0,0],\n"
   "      \"__class__\": \"Project\"\n"
   "   }\n"
   "}\n";

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
func: _ReadGetInput
**************************************************************************************************/
JsonBool _ReadGetInput(void * const input, JsonChar * const letter)
{
   Str *s = (Str *) input;

   // Get the letter being pointed to.
   *letter = (JsonChar) strPosGetLetter(s);

   // Increment the index of the next letter.
   strPosNext(s);

   if (*letter == 0)
   {
      return jsonFALSE;
   }

   return jsonTRUE;
}

/**************************************************************************************************
func: _ReadSetOutput
**************************************************************************************************/
JsonBool _ReadSetOutput(void * const output, JsonToken const token, JsonChar const * const value)
{
   switch (token)
   {
   case jsonTokenARRAY_START:         printf("[\n");                         break;
   case jsonTokenARRAY_STOP:          printf("]\n");                         break;
   case jsonTokenBOOL_FALSE:          printf("false\n");                     break;
   case jsonTokenBOOL_TRUE:           printf("true\n");                      break;
   case jsonTokenCOMMA:               printf(",\n");                         break;
   case jsonTokenEOF:                 printf("EOF\n");                       break;
   case jsonTokenKEY_VALUE_SEPARATOR: printf(":\n");                         break;
   case jsonTokenNULL:                printf("null\n");                      break;
   case jsonTokenNUMBER_INTEGER:      printf("INT : %s\n", (char *) value);  break;
   case jsonTokenNUMBER_REAL:         printf("REAL: %s\n", (char *) value);  break;
   case jsonTokenOBJECT_START:        printf("{\n");                         break;
   case jsonTokenOBJECT_STOP:         printf("}\n");                         break;
   case jsonTokenSTRING:              printf("STR : %s\n", (char *) value);  break;
   }

   return jsonTRUE;
}

/**************************************************************************************************
func: memCreate
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
func: memDestroy
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
func: memClear
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
   Str         *s;
   Json        *json;
   JsonError    error;
   char         result[] = 
      "{"
         "\"ValueTrue\":true,"
         "\"ValueFalse\":false,"
         "\"ValueNull\":null,"
         "\"ValueString\":\"The quick brown fox jumped over the lazy dog.\","
         "\"ValueInteger\":42,"
         "\"ValueReal\":1.23456789012346,"
         "\"ValueReal4\":1.234568,"
         "\"ValueArrayInt\":[1,2,3,4,5,6,7,8,9,10],"
         "\"ValueObject\":{"
            "\"ValueTrue\":true,"
            "\"ValueFalse\":false,"
            "\"ValueNull\":null,"
            "\"ValueString\":\"The quick brown fox jumped over the lazy dog.\","
            "\"ValueInteger\":42,"
            "\"ValueReal\":1.23456789012346,"
            "\"ValueReal4\":1.234568,"
            "\"ValueArrayInt\":[1,2,3,4,5,6,7,8,9,10],"
            "\"ValueObject\":{"
               "\"ValueString\":\"Ok, \\r\\n\\tThat's enough of this silliness.\""
            "}"
         "}"
      "}";

   s = strCreate(0);

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateWrite(s, _BufferAppendString);

   error  = jsonErrorNONE;
   error |= jsonWriteObjectStart(json); 
   {
      error |= jsonWriteString( json, (JsonChar *) "ValueTrue");  
      error |= jsonWriteBoolean(json, jsonTRUE);

      error |= jsonWriteString( json, (JsonChar *) "ValueFalse");
      error |= jsonWriteBoolean(json, jsonFALSE);

      error |= jsonWriteString( json, (JsonChar *) "ValueNull");
      error |= jsonWriteNull(   json);

      error |= jsonWriteString( json, (JsonChar *) "ValueString");
      error |= jsonWriteString( json, (JsonChar *) "The quick brown fox jumped over the lazy dog.");

      error |= jsonWriteString( json, (JsonChar *) "ValueInteger");
      error |= jsonWriteInteger(json, 42);
      
      error |= jsonWriteString( json, (JsonChar *) "ValueReal");
      error |= jsonWriteReal(   json, 1.234567890123456789);
      
      error |= jsonWriteString( json, (JsonChar *) "ValueReal4");
      error |= jsonWriteReal4(  json, 1.234567890123456789);
      
      error |= jsonWriteString( json, (JsonChar *) "ValueArrayInt");
      error |= jsonWriteArrayStart(json);
      {
         int index;

         for (index = 1; index <= 10; index++)
         {
            error |= jsonWriteInteger(json, index);
         }
      }
      error |= jsonWriteArrayStop(json);
      
      error |= jsonWriteString( json, (JsonChar *) "ValueObject");
      error |= jsonWriteObjectStart(json);
      {
         error |= jsonWriteString( json, (JsonChar *) "ValueTrue");
         error |= jsonWriteBoolean(json, jsonTRUE);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueFalse");
         error |= jsonWriteBoolean(json, jsonFALSE);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueNull");
         error |= jsonWriteNull(   json);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueString");
         error |= jsonWriteString( json, (JsonChar *) "The quick brown fox jumped over the lazy dog.");
      
         error |= jsonWriteString( json, (JsonChar *) "ValueInteger");
         error |= jsonWriteInteger(json, 42);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueReal");
         error |= jsonWriteReal(   json, 1.234567890123456789);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueReal4");
         error |= jsonWriteReal4(  json, 1.234567890123456789);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueArrayInt");
         error |= jsonWriteArrayStart(json);
         {
            int index;

            for (index = 1; index <= 10; index++)
            {
               error |= jsonWriteInteger(json, index);
            }
         }
         error |= jsonWriteArrayStop(json);
      
         error |= jsonWriteString( json, (JsonChar *) "ValueObject");
         error |= jsonWriteObjectStart(json);
         {
            error |= jsonWriteString(json, (JsonChar *) "ValueString");
            error |= jsonWriteString(json, (JsonChar *) "Ok, \r\n\tThat's enough of this silliness.");
         }
         error |= jsonWriteObjectStop(json);
      }
      error |= jsonWriteObjectStop(json);
   }
   error |= jsonWriteObjectStop(json);

   EXPECT_TRUE(error == jsonErrorNONE);

   jsonDestroy(json);

   jsonStop();

   EXPECT_TRUE(strcmp(s->buffer, result) == 0);

   strDestroy(s);
}

/**************************************************************************************************
func: write errors
**************************************************************************************************/
TEST(TestJSONRoutines, WriteError1)
{
   Str         *s;
   Json        *json;
   JsonError    error;

   s = strCreate(0);

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateWrite(s, _BufferAppendString);

   error  = jsonErrorNONE;
   error |= jsonWriteString(json, (JsonChar *) "value");
   EXPECT_TRUE(error == jsonErrorNONE);

   error |= jsonWriteString(json, (JsonChar *) "2nd value should be error.");
   EXPECT_FALSE(error == jsonErrorNONE);

   jsonDestroy(json);

   jsonStop();

   strDestroy(s);
}

/**************************************************************************************************
func: write errors
**************************************************************************************************/
TEST(TestJSONRoutines, WriteError2)
{
   Str         *s;
   Json        *json;
   JsonError    error;

   s = strCreate(0);

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateWrite(s, _BufferAppendString);

   error  = jsonErrorNONE;
   error |= jsonWriteObjectStart(json);
   {
      // Key is expected.  This is not a stirng/key.
      error |= jsonWriteInteger(json, 42);
      EXPECT_FALSE(error == jsonErrorNONE);

      error  = jsonErrorNONE;
      error |= jsonWriteString(json, (JsonChar *) "key");
   }
   // Value for a key is expected.  Can't close yet.
   error |= jsonWriteObjectStop(json);
   EXPECT_FALSE(error == jsonErrorNONE);

   jsonDestroy(json);

   jsonStop();

   strDestroy(s);
}

/**************************************************************************************************
func: CreateRead
**************************************************************************************************/
TEST(TestJSONRoutines, CreateRead)
{
   Json *json;

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateRead(NULL, _ReadGetInput, NULL, _ReadSetOutput);
   EXPECT_TRUE(json != NULL);

   jsonDestroy(json);

   jsonStop();
}

/**************************************************************************************************
func: 
**************************************************************************************************/
TEST(TestJSONRoutines, Read)
{
   Str      *s;
   Json     *json;
   JsonError error;

   s = strCreate(0);
   strAppend(s, omfJson);

   jsonStart(memCreate, memDestroy, memClear);

   json = jsonCreateRead(s, _ReadGetInput, NULL, _ReadSetOutput);
   EXPECT_TRUE(json != NULL);

   // Perform the read of the json.
   error = jsonRead(json);

   jsonDestroy(json);

   jsonStop();

   strDestroy(s);
}
