#include "Tile.h"

namespace MSKMIC017 {

    // Constructor implementation
    Tile::Tile(int w, int h) : width(w), height(h) {
        // Initialize pixel data with the size of w*h and default value 0 (black)
        pixelData.resize(w * h, 0);
    }

    // Implement additional functions as needed

} // namespace MSKMIC017
