// Tile.h
#ifndef TILE_H
#define TILE_H

#include <cstddef> // For size_t

namespace MSKMIC017 {

    class Tile {
    public:
        unsigned char* pixelData; // Pointer to the grayscale values array
        int width;                // Width of the tile
        int height;               // Height of the tile

        // Default constructor
        Tile() : width(0), height(0), pixelData(nullptr) {}

        // Constructor with width and height
        Tile(int w, int h);

        // Destructor
        ~Tile();

        // Copy constructor
        Tile(const Tile& other);

        // Copy assignment operator
        Tile& operator=(const Tile& other);

        // Move constructor
        Tile(Tile&& other) noexcept;

        // Move assignment operator
        Tile& operator=(Tile&& other) noexcept;
    };

} // namespace MSKMIC017

#endif // TILE_H
