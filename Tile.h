// Tile.h
#ifndef TILE_H
#define TILE_H

#include <vector>

namespace MSKMIC017 {
    class Tile {
    public:
        std::vector<unsigned char> pixelData;
        int width, height;

        Tile(int w, int h);
    };
}

#endif
