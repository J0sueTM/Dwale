/**
 * \file inc/core/core.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 21, 2021
 *
 * \brief Base includes and defines
 * 
 * Copyright (C) Josué Teodoro Moreira
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef __D_CORE_H__
#define __D_CORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <errno.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif /*_WIN32 */

#if defined(__amd64__)  || \
    defined(__amd64)    || \
    defined(_M_AMD64)   || \
    defined(__M_X64)    || \
    defined(__x86_64__) || \
    defined(__x86_64)
#define __D_ARCH64__
#else
#define __D_ARCH32__
#endif /* __amd64__ __amd64 _M_AMD64 __M_X64 __x86_64__ __x86_64 */

#include "core/types.h"
/*
 * TODO(J0sueTM): Add error codes
 * #include "core/errcode.h"
 */

#endif /* __D_CORE_H__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
