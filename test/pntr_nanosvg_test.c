#include <assert.h>
#include <string.h>

#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_NANOSVG_IMPLEMENTATION
#include "pntr_nanosvg.h"

// A 10x10 SVG filled with solid red
static const char* redSquare = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"10\" height=\"10\">"
    "<rect x=\"0\" y=\"0\" width=\"10\" height=\"10\" fill=\"#ff0000\"/></svg>";

// A 10x10 SVG with a red left half and a blue right half
static const char* redBlueHalves = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"10\" height=\"10\">"
    "<rect x=\"0\" y=\"0\" width=\"5\" height=\"10\" fill=\"#ff0000\"/>"
    "<rect x=\"5\" y=\"0\" width=\"5\" height=\"10\" fill=\"#0000ff\"/></svg>";

static int is_blue(pntr_image* image, int x, int y) {
    pntr_color color = pntr_image_get_color(image, x, y);
    return color.rgba.r == 0 && color.rgba.g == 0 && color.rgba.b == 255 && color.rgba.a == 255;
}

static int is_red(pntr_image* image, int x, int y) {
    pntr_color color = pntr_image_get_color(image, x, y);
    return color.rgba.r == 255 && color.rgba.g == 0 && color.rgba.b == 0 && color.rgba.a == 255;
}

static int is_white(pntr_image* image, int x, int y) {
    pntr_color color = pntr_image_get_color(image, x, y);
    return color.rgba.r == 255 && color.rgba.g == 255 && color.rgba.b == 255 && color.rgba.a == 255;
}

int main(void) {
    // pntr_load_nanosvg
    {
        NSVGimage* svg = pntr_load_nanosvg("resources/tiger.svg", "px", 96.0f);
        assert(svg != NULL);
        assert(svg->width > 0);
        assert(svg->height > 0);

        // pntr_gen_image_nanosvg
        {
            pntr_image* image = pntr_gen_image_nanosvg(svg, 1.0f);
            assert(image != NULL);
            assert(image->width > 0);
            assert(image->height > 0);
            assert(pntr_save_image(image, "tiger.png"));
            pntr_unload_image(image);
        }

        // pntr_draw_nanosvg
        {
            pntr_image* canvas = pntr_gen_image_color(128, 128, PNTR_WHITE);
            assert(canvas != NULL);
            pntr_draw_nanosvg(canvas, svg);
            pntr_unload_image(canvas);
        }

        pntr_unload_nanosvg(svg);
    }

    // pntr_load_nanosvg with missing file returns NULL
    {
        NSVGimage* svg = pntr_load_nanosvg("resources/missing.svg", "px", 96.0f);
        assert(svg == NULL);
    }

    // pntr_load_nanosvg_from_memory with NULL returns NULL
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory(NULL, 0, "px", 96.0f);
        assert(svg == NULL);
    }

    // pntr_gen_image_nanosvg with NULL returns NULL
    {
        pntr_image* image = pntr_gen_image_nanosvg(NULL, 1.0f);
        assert(image == NULL);
    }

    // pntr_load_image_nanosvg
    {
        pntr_image* image = pntr_load_image_nanosvg("resources/tiger.svg", "px", 96.0f);
        assert(image != NULL);
        assert(image->width > 0);
        assert(image->height > 0);
        pntr_unload_image(image);
    }

    // pntr_load_image_nanosvg with missing file returns NULL
    {
        pntr_image* image = pntr_load_image_nanosvg("resources/missing.svg", "px", 96.0f);
        assert(image == NULL);
    }

    // pntr_load_nanosvg_from_memory
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory((const unsigned char*)redSquare, (unsigned int)strlen(redSquare), "px", 96.0f);
        assert(svg != NULL);
        assert(svg->width == 10.0f);
        assert(svg->height == 10.0f);

        // pntr_gen_image_nanosvg with a scale
        {
            pntr_image* image = pntr_gen_image_nanosvg(svg, 2.0f);
            assert(image != NULL);
            assert(image->width == 20);
            assert(image->height == 20);
            assert(is_red(image, 10, 10));
            pntr_unload_image(image);
        }

        // pntr_gen_image_nanosvg with an invalid scale returns NULL
        {
            assert(pntr_gen_image_nanosvg(svg, 0.0f) == NULL);
            assert(pntr_gen_image_nanosvg(svg, -1.0f) == NULL);
        }

        // pntr_draw_nanosvg fits and centers the SVG
        {
            pntr_image* canvas = pntr_gen_image_color(40, 20, PNTR_WHITE);
            assert(canvas != NULL);
            pntr_draw_nanosvg(canvas, svg);
            assert(is_white(canvas, 2, 10));
            assert(is_red(canvas, 20, 10));
            assert(is_white(canvas, 37, 10));
            pntr_unload_image(canvas);
        }

        // pntr_draw_nanosvg_ex at a position
        {
            pntr_image* canvas = pntr_gen_image_color(20, 20, PNTR_WHITE);
            assert(canvas != NULL);
            pntr_draw_nanosvg_ex(canvas, svg, 5, 5, 1.0f);
            assert(is_white(canvas, 2, 2));
            assert(is_red(canvas, 10, 10));
            assert(is_white(canvas, 17, 17));
            pntr_unload_image(canvas);
        }

        // pntr_draw_nanosvg_ex leaves the destination untouched when fully off it
        {
            pntr_image* canvas = pntr_gen_image_color(20, 20, PNTR_WHITE);
            assert(canvas != NULL);
            pntr_draw_nanosvg_ex(canvas, svg, 100, 100, 1.0f);
            pntr_draw_nanosvg_ex(canvas, svg, -100, -100, 1.0f);
            pntr_draw_nanosvg_ex(canvas, svg, 0, 0, 0.0f);
            pntr_draw_nanosvg_ex(canvas, NULL, 0, 0, 1.0f);
            pntr_draw_nanosvg_ex(NULL, svg, 0, 0, 1.0f);
            for (int y = 0; y < canvas->height; y++) {
                for (int x = 0; x < canvas->width; x++) {
                    assert(is_white(canvas, x, y));
                }
            }
            pntr_unload_image(canvas);
        }

        pntr_unload_nanosvg(svg);
    }

    // pntr_draw_nanosvg_ex clips when partially off the destination
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory((const unsigned char*)redBlueHalves, (unsigned int)strlen(redBlueHalves), "px", 96.0f);
        assert(svg != NULL);
        pntr_image* canvas = pntr_gen_image_color(20, 20, PNTR_WHITE);
        assert(canvas != NULL);

        // Off the left edge, only the blue right half is visible
        pntr_draw_nanosvg_ex(canvas, svg, -5, 0, 1.0f);
        assert(is_blue(canvas, 0, 5));
        assert(is_blue(canvas, 3, 5));
        assert(is_white(canvas, 7, 5));

        // Off the right edge, only the red left half is visible
        pntr_draw_nanosvg_ex(canvas, svg, 15, 10, 1.0f);
        assert(is_red(canvas, 16, 15));
        assert(is_red(canvas, 19, 15));
        assert(is_white(canvas, 12, 15));

        pntr_unload_image(canvas);
        pntr_unload_nanosvg(svg);
    }

    // pntr_load_nanosvg_from_memory with an empty buffer returns NULL
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory((const unsigned char*)redSquare, 0, "px", 96.0f);
        assert(svg == NULL);
    }

    // pntr_load_image_nanosvg_from_memory
    {
        pntr_image* image = pntr_load_image_nanosvg_from_memory((const unsigned char*)redSquare, (unsigned int)strlen(redSquare), "px", 96.0f);
        assert(image != NULL);
        assert(image->width == 10);
        assert(image->height == 10);
        assert(is_red(image, 0, 0));
        assert(is_red(image, 5, 5));
        assert(is_red(image, 9, 9));
        pntr_unload_image(image);
    }

    // pntr_load_image_nanosvg_from_memory with NULL returns NULL
    {
        pntr_image* image = pntr_load_image_nanosvg_from_memory(NULL, 0, "px", 96.0f);
        assert(image == NULL);
    }

    return 0;
}
