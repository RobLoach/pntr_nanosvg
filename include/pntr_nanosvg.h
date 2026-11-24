/**********************************************************************************************
*
*   pntr_nanosvg - Load SVG for use in pntr.
*
*   Copyright 2026 Rob Loach (@RobLoach)
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

/**
 * @file pntr_nanosvg.h
 * @brief SVG loading and rendering for pntr via nanosvg.
 *
 * Define `PNTR_NANOSVG_IMPLEMENTATION` in exactly one translation unit before
 * including this header to compile the implementation:
 *
 * @code
 * #define PNTR_NANOSVG_IMPLEMENTATION
 * #include "pntr_nanosvg.h"
 * @endcode
 *
 * @defgroup pntr_nanosvg pntr_nanosvg
 * @{
 */

#ifndef PNTR_NANOSVG_H_
#define PNTR_NANOSVG_H_

// Allow overriding the nanosvg header paths
#ifndef PNTR_NANOSVG_NANOSVG_H
#define PNTR_NANOSVG_NANOSVG_H "nanosvg.h"
#endif
#ifndef PNTR_NANOSVG_NANOSVGRAST_H
#define PNTR_NANOSVG_NANOSVGRAST_H "nanosvgrast.h"
#endif

// Compile the nanosvg implementation alongside pntr_nanosvg's, unless opted out
#if defined(PNTR_NANOSVG_IMPLEMENTATION) && !defined(PNTR_NANOSVG_NO_NANOSVG_IMPLEMENTATION)
    #ifndef NANOSVG_IMPLEMENTATION
        #define NANOSVG_IMPLEMENTATION
    #endif
    #ifndef NANOSVGRAST_IMPLEMENTATION
        #define NANOSVGRAST_IMPLEMENTATION
    #endif
#endif

#include PNTR_NANOSVG_NANOSVG_H
#include PNTR_NANOSVG_NANOSVGRAST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PNTR_NANOSVG_API
    #define PNTR_NANOSVG_API PNTR_API
#endif

/**
 * Load an SVG file from disk.
 *
 * @param fileName Path to the SVG file to load.
 * @param units Length units to use when parsing (e.g. "px", "pt", "mm").
 * @param dpi Dots-per-inch used for unit conversion.
 * @return Parsed SVG image, or NULL on failure. Free with pntr_unload_nanosvg().
 */
PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg(const char* fileName, const char* units, float dpi);

/**
 * Load an SVG from a memory buffer.
 *
 * @param fileData Pointer to the raw SVG data.
 * @param dataSize Size of the data buffer in bytes.
 * @param units Length units to use when parsing (e.g. "px", "pt", "mm").
 * @param dpi Dots-per-inch used for unit conversion.
 * @return Parsed SVG image, or NULL on failure. Free with pntr_unload_nanosvg().
 */
PNTR_NANOSVG_API NSVGimage* pntr_load_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi);

/**
 * Unload an SVG image and free its memory.
 *
 * @param svg SVG image to unload. Safe to call with NULL.
 */
PNTR_NANOSVG_API void pntr_unload_nanosvg(NSVGimage* svg);

/**
 * Rasterize an SVG into a new pntr image at the SVG's natural dimensions multiplied by @p scale.
 *
 * @param svg SVG image to rasterize.
 * @param scale Uniform scale factor applied to the SVG's natural size (1.0f = native size).
 * @return New pntr_image on success, or NULL on failure. Free with pntr_unload_image().
 */
PNTR_NANOSVG_API pntr_image* pntr_gen_image_nanosvg(NSVGimage* svg, float scale);

/**
 * Draw an SVG onto an existing pntr image, uniformly scaled to fit the destination.
 *
 * The SVG is scaled uniformly to fit within the destination image dimensions and
 * alpha-blended onto @p dst.
 *
 * @param dst Destination image to draw onto.
 * @param svg SVG image to rasterize and draw.
 */
PNTR_NANOSVG_API void pntr_draw_nanosvg(pntr_image* dst, NSVGimage* svg);

/**
 * Load an SVG file from disk and rasterize it into a new pntr image.
 *
 * A convenience wrapper around pntr_load_nanosvg() and pntr_gen_image_nanosvg().
 * The output image uses the SVG's natural pixel dimensions.
 *
 * @param fileName Path to the SVG file to load.
 * @param units Length units to use when parsing (e.g. "px", "pt", "mm").
 * @param dpi Dots-per-inch used for unit conversion.
 * @return New pntr_image on success, or NULL on failure. Free with pntr_unload_image().
 */
PNTR_NANOSVG_API pntr_image* pntr_load_image_nanosvg(const char* fileName, const char* units, float dpi);

/**
 * Load an SVG from a memory buffer and rasterize it into a new pntr image.
 *
 * A convenience wrapper around pntr_load_nanosvg_from_memory() and pntr_gen_image_nanosvg().
 * The output image uses the SVG's natural pixel dimensions.
 *
 * @param fileData Pointer to the raw SVG data.
 * @param dataSize Size of the data buffer in bytes.
 * @param units Length units to use when parsing (e.g. "px", "pt", "mm").
 * @param dpi Dots-per-inch used for unit conversion.
 * @return New pntr_image on success, or NULL on failure. Free with pntr_unload_image().
 */
PNTR_NANOSVG_API pntr_image* pntr_load_image_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi);

#ifdef __cplusplus
}
#endif

/** @} */

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
    if (svg != NULL) {
        nsvgDelete(svg);
    }
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
    float tx = ((float)w - svg->width * scale) / 2.0f;
    float ty = ((float)h - svg->height * scale) / 2.0f;

    unsigned char* buf = (unsigned char*)PNTR_MALLOC((size_t)w * (size_t)h * 4);
    if (buf == NULL) {
        nsvgDeleteRasterizer(rast);
        return;
    }

    nsvgRasterize(rast, svg, tx, ty, scale, buf, w, h, w * 4);
    nsvgDeleteRasterizer(rast);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char* p = buf + ((size_t)y * (size_t)w + (size_t)x) * 4;
            pntr_color src = pntr_new_color(p[0], p[1], p[2], p[3]);
            PNTR_PIXEL(dst, x, y) = pntr_color_alpha_blend(PNTR_PIXEL(dst, x, y), src);
        }
    }

    PNTR_FREE(buf);
}

PNTR_NANOSVG_API pntr_image* pntr_gen_image_nanosvg(NSVGimage* svg, float scale) {
    if (svg == NULL || scale <= 0.0f) {
        return NULL;
    }

    int w = (int)(svg->width * scale);
    int h = (int)(svg->height * scale);
    if (w <= 0 || h <= 0) {
        return NULL;
    }

    pntr_image* image = pntr_gen_image_color(w, h, PNTR_BLANK);
    if (image == NULL) {
        return NULL;
    }

    pntr_draw_nanosvg(image, svg);
    return image;
}

PNTR_NANOSVG_API pntr_image* pntr_load_image_nanosvg(const char* fileName, const char* units, float dpi) {
    NSVGimage* svg = pntr_load_nanosvg(fileName, units, dpi);
    if (svg == NULL) {
        return NULL;
    }

    pntr_image* image = pntr_gen_image_nanosvg(svg, 1.0f);
    pntr_unload_nanosvg(svg);
    return image;
}

PNTR_NANOSVG_API pntr_image* pntr_load_image_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi) {
    NSVGimage* svg = pntr_load_nanosvg_from_memory(fileData, dataSize, units, dpi);
    if (svg == NULL) {
        return NULL;
    }

    pntr_image* image = pntr_gen_image_nanosvg(svg, 1.0f);
    pntr_unload_nanosvg(svg);
    return image;
}

#ifdef __cplusplus
}
#endif

#endif  // PNTR_NANOSVG_IMPLEMENTATION_ONCE
#endif  // PNTR_NANOSVG_IMPLEMENTATION
