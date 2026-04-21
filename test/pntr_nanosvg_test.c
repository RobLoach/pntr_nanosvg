#include <assert.h>

#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_NANOSVG_IMPLEMENTATION
#include "pntr_nanosvg.h"

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

    return 0;
}
