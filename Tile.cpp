// Tile.cpp
#include "Tile.h"
#include <algorithm> // For std::swap
#include <cstring> // For std::memcpy

namespace MSKMIC017 {
 
    Tile::Tile(int w, int h) : width(w), height(h) {        //Constructor
        pixelData = new unsigned char[w * h](); 
    }

    Tile::~Tile() {     //Destructor
        delete[] pixelData;
    }
    //   Copy constructor (Creates a new Tile obj as a copy of another Tile obj)
    Tile::Tile(const Tile& other) : width(other.width), height(other.height), pixelData(new unsigned char[other.width * other.height]) {
        std::memcpy(pixelData, other.pixelData, width * height); //copy data
    }
    //  Copy Assignment operator (Assigns values from one Tile obj to another)
    Tile& Tile::operator=(const Tile& other) {
        if (this != &other) {
            Tile temp(other); // Copy-and-swap.
            *this = std::move(temp);
        }
        return *this;
    }
    // move constructor (moves ownership of resources from one tile to the other)
    Tile::Tile(Tile&& other) noexcept : pixelData(nullptr), width(0), height(0) {
        *this = std::move(other);
    }
    // Move assignment operator that reassigns resources from one Tile to another
    Tile& Tile::operator=(Tile&& other) noexcept {
        if (this != &other) {
            delete[] pixelData; // Free own resources

            pixelData = other.pixelData;
            width = other.width;
            height = other.height;

            other.pixelData = nullptr;
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }

} // namespace MSKMIC017
