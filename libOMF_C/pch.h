/******************************************************************************
file:       pch
author:     Robbert de Groot
copyright:  2022, Robbert de Groot

description:
Precompiled header compilation.
******************************************************************************/

#if !defined(PCH_H)
#define      PCH_H

// add headers that you want to pre-compile here
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <guiddef.h>
#include <stdio.h>

#include "libOMF_C.h"
#include "lib_local.h"

// miniz is a smaller (file count) implementation of the compression and zip archive handling
// project can be found here  https://github.com/richgel999/miniz
// As indicated on usage for that project, we are just including the source in the project 
// directly.
// 
// For deflate and inflate
#include "miniz.h"

#endif
