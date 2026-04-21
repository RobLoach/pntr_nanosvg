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

// Allow overriding the nanosvg header paths
#ifndef PNTR_NANOSVG_NANOSVG_H
#define PNTR_NANOSVG_NANOSVG_H "nanosvg.h"
#endif
#ifndef PNTR_NANOSVG_NANOSVGRAST_H
#define PNTR_NANOSVG_NANOSVGRAST_H "nanosvgrast.h"
#endif

#include PNTR_NANOSVG_NANOSVG_H
#include PNTR_NANOSVG_NANOSVGRAST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PNTR_NANOSVG_API
    #define PNTR_NANOSVG_API PNTR_API
#endif

PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg(const char* fileName, const char* units, float dpi);
PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi);
PNTR_NANOSVG_API void pntr_unload_nanosvg(NSVGimage* svg);
PNTR_NANOSVG_API pntr_image* pntr_gen_image_nanosvg(NSVGimage* svg, int width, int height);
PNTR_NANOSVG_API void pntr_draw_nanosvg(pntr_image* dst, NSVGimage* svg);

#ifdef __cplusplus
}
#endif

#endif  // PNTR_NANOSVG_H_

#ifdef PNTR_NANOSVG_IMPLEMENTATION
#ifndef PNTR_NANOSVG_IMPLEMENTATION_ONCE
#define PNTR_NANOSVG_IMPLEMENTATION_ONCE

#ifdef __cplusplus
extern "C" {
#endif

PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg(const char* fileName, const char* units, float dpi) {
    unsigned int bytesRead;
    unsigned char* fileData = pntr_load_file(fileName, &bytesRead);
    if (fileData == NULL) {
        return NULL;
    }
    NSVGimage* svg = pntr_load_nanosvg_from_memory(fileData, bytesRead, units, dpi);
    pntr_unload_file(fileData);
    return svg;
}

PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi) {
    if (fileData == NULL || dataSize == 0) {
        return NULL;
    }

    // nsvgParse modifies its input, so work on a copy
    char* copy = (char*)PNTR_MALLOC(dataSize + 1);
    if (copy == NULL) {
        return NULL;
    }
    PNTR_MEMCPY(copy, fileData, dataSize);
    copy[dataSize] = '\0';

    NSVGimage* svg = nsvgParse(copy, units, dpi);
    PNTR_FREE(copy);
    return svg;
}

PNTR_NANOSVG_API void pntr_unload_nanosvg(NSVGimage* svg) {
    nsvgDelete(svg);
}

PNTR_NANOSVG_API void pntr_draw_nanosvg(pntr_image* dst, NSVGimage* svg) {
    if (dst == NULL || svg == NULL || svg->width <= 0 || svg->height <= 0) {
        return;
    }

    NSVGrasterizer* rast = nsvgCreateRasterizer();
    if (rast == NULL) {
        return;
    }

    int w = dst->width;
    int h = dst->height;
    float scaleX = (float)w / svg->width;
    float scaleY = (float)h / svg->height;
    float scale = scaleX < scaleY ? scaleX : scaleY;

    unsigned char* buf = (unsigned char*)PNTR_MALLOC((size_t)(w * h * 4));
    if (buf == NULL) {
        nsvgDeleteRasterizer(rast);
        return;
    }

    nsvgRasterize(rast, svg, 0, 0, scale, buf, w, h, w * 4);
    nsvgDeleteRasterizer(rast);

    // Blend rasterized RGBA pixels onto dst
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char* p = buf + (y * w + x) * 4;
            pntr_color src = pntr_new_color(p[0], p[1], p[2], p[3]);
            PNTR_PIXEL(dst, x, y) = pntr_color_alpha_blend(PNTR_PIXEL(dst, x, y), src);
        }
    }

    PNTR_FREE(buf);
}

PNTR_NANOSVG_API pntr_image* pntr_gen_image_nanosvg(NSVGimage* svg, int width, int height) {
    if (svg == NULL || width <= 0 || height <= 0) {
        return NULL;
    }

    pntr_image* image = pntr_gen_image_color(width, height, PNTR_BLANK);
    if (image == NULL) {
        return NULL;
    }

    pntr_draw_nanosvg(image, svg);
    return image;
}

#ifdef __cplusplus
}
#endif

#endif  // PNTR_NANOSVG_IMPLEMENTATION_ONCE
#endif  // PNTR_NANOSVG_IMPLEMENTATION
