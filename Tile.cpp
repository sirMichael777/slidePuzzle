// Tile.cpp
#include "Tile.h"

namespace MSKMIC017
{
    // Constructor
    Tile::Tile(int w, int h) : width(w), height(h)
    {
        // Resize the vector to hold the pixel data for the entire tile.
        // The vector holds unsigned char values, which represent the grayscale intensity of each pixel.
        pixelData.resize(width * height, 0); // Initialize all pixel values to 0 (black) for simplicity.
    }
}
