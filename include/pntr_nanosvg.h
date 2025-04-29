/**********************************************************************************************
*
*   pntr_nanosvg - Load SVG for use in pntr.
*
*   Copyright 2025 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       pntr https://github.com/robloach/pntr
*       nanosvg https://github.com/memononen/nanosvg
*
*   LICENSE: zlib/libpng
*
*   pntr_nanosvg is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef PNTR_NANOSVG_H_
#define PNTR_NANOSVG_H_

// cute_tiled
#ifndef PNTR_NANOSVG_NANOSVG_H
#define PNTR_NANOSVG_NANOSVG_H "nanosvg.h"
#endif
#include PNTR_NANOSVG_NANOSVG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PNTR_NANOSVG_API
    #define PNTR_NANOSVG_API PNTR_API
#endif

PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg(const char* fileName, const char* units, float dpi);
PNTR_NANOSVG_API NSVGimage* dpntr_load_nanosvg_from_memory(void* file, const char* units, float dpi);
PNTR_NANOSVG_API void pntr_draw_nanosvg(pntr_image* dst, NSVGimage* svg);

#ifdef __cplusplus
}
#endif

#endif  // PNTR_NANOSVG_H_

#ifdef PNTR_NANOSVG_IMPLEMENTATION
#ifndef PNTR_NANOSVG_IMPLEMENTATION_ONCE
#define PNTR_NANOSVG_IMPLEMENTATION_ONCE

// nanosvg
#define NANOSVG_IMPLEMENTATION
#include PNTR_NANOSVG_NANOSVG_H

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif  // PNTR_NANOSVG_IMPLEMENTATION_ONCE
#endif  // PNTR_NANOSVG_IMPLEMENTATION
