/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2017 Yuriy Khokhulya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USBD_MAX_NUM_INTERFACES 1
#define USBD_MAX_NUM_CONFIGURATION 1
#define USBD_MAX_STR_DESC_SIZ 0x100
#define USBD_SELF_POWERED 1
#define USBD_DEBUG_LEVEL 2

#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE 0x02
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE 74

#define USBD_malloc malloc
#define USBD_free free
#define USBD_memset memset
#define USBD_memcpy memcpy

#if (USBD_DEBUG_LEVEL > 0)
#define USBD_UsrLog(...) \
    printf(__VA_ARGS__); \
    printf("\n");
#else
#define USBD_UsrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 1)

#define USBD_ErrLog(...) \
    printf("ERROR: ");   \
    printf(__VA_ARGS__); \
    printf("\n");
#else
#define USBD_ErrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 2)
#define USBD_DbgLog(...) \
    printf("DEBUG : ");  \
    printf(__VA_ARGS__); \
    printf("\n");
#else
#define USBD_DbgLog(...)
#endif
