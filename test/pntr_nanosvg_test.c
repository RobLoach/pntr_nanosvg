#include <assert.h>
#include <string.h>

#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_NANOSVG_IMPLEMENTATION
#include "pntr_nanosvg.h"

static const char* TEST_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"100\">"
    "<rect x=\"10\" y=\"10\" width=\"80\" height=\"80\" fill=\"red\"/>"
    "</svg>";

int main(void) {
    // pntr_load_nanosvg_from_memory
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory(
            (const unsigned char*)TEST_SVG, (unsigned int)strlen(TEST_SVG), "px", 96.0f);
        assert(svg != NULL);
        assert(svg->width > 0);
        assert(svg->height > 0);

        // pntr_gen_image_nanosvg
        {
            pntr_image* image = pntr_gen_image_nanosvg(svg, 64, 64);
            assert(image != NULL);
            assert(image->width == 64);
            assert(image->height == 64);
            assert(pntr_save_image(image, "pntr_nanosvg_test.png"));
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

    // pntr_load_nanosvg_from_memory with NULL returns NULL
    {
        NSVGimage* svg = pntr_load_nanosvg_from_memory(NULL, 0, "px", 96.0f);
        assert(svg == NULL);
    }

    // pntr_gen_image_nanosvg with NULL returns NULL
    {
        pntr_image* image = pntr_gen_image_nanosvg(NULL, 64, 64);
        assert(image == NULL);
    }

    return 0;
}
