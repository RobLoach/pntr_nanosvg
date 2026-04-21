# pntr_nanosvg

Load and render SVG files for [pntr](https://github.com/robloach/pntr) using [nanosvg](https://github.com/memononen/nanosvg).

## Usage

```c
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_NANOSVG_IMPLEMENTATION
#include "pntr_nanosvg.h"

int main(void) {
    // Load an SVG file
    NSVGimage* svg = pntr_load_nanosvg("image.svg", "px", 96.0f);

    // Render it to a new image at native size (scale 1.0f)
    pntr_image* image = pntr_gen_image_nanosvg(svg, 1.0f);

    // Or draw it onto an existing canvas
    pntr_image* canvas = pntr_gen_image_color(512, 512, PNTR_WHITE);
    pntr_draw_nanosvg(canvas, svg);

    pntr_unload_nanosvg(svg);
    pntr_unload_image(image);
    pntr_unload_image(canvas);
    return 0;
}
```

## API

```c
NSVGimage* pntr_load_nanosvg(const char* fileName, const char* units, float dpi);
NSVGimage* pntr_load_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi);
void pntr_unload_nanosvg(NSVGimage* svg);
pntr_image* pntr_gen_image_nanosvg(NSVGimage* svg, float scale);
void pntr_draw_nanosvg(pntr_image* dst, NSVGimage* svg);
pntr_image* pntr_load_image_nanosvg(const char* fileName, const char* units, float dpi);
pntr_image* pntr_load_image_nanosvg_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* units, float dpi);
```

## Dependencies

- [pntr](https://github.com/robloach/pntr)
- [nanosvg](https://github.com/memononen/nanosvg)

By default the headers `nanosvg.h` and `nanosvgrast.h` are included directly. Override the paths with:

```c
#define PNTR_NANOSVG_NANOSVG_H "path/to/nanosvg.h"
#define PNTR_NANOSVG_NANOSVGRAST_H "path/to/nanosvgrast.h"
```

## Build

```sh
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## License

Unless stated otherwise, all works are:

- Copyright (c) 2026 [Rob Loach](https://robloach.net)

... and licensed under:

- [zlib License](LICENSE)
