#ifndef TILE_H
#define TILE_H

#include <vector>

namespace MSKMIC017 {

    class Tile {
    public:
        std::vector<unsigned char> pixelData; // Stores the grayscale values
        int width;                            // Width of the tile
        int height;                           // Height of the tile

        // Constructor with width and height
        Tile(int w, int h);

        // Default constructor - if needed based on your overall design
        Tile() = default;

        // Add additional functions or member variables as needed
    };

} // namespace MSKMIC017

#endif // TILE_H
