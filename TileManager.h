// TileManager.h
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <string>
#include <vector>

namespace MSKMIC017 {
    class TileManager {
    private:
        std::vector<std::vector<Tile>> board; // 2D vector to hold tiles
        int gridSize; // The size of the grid (e.g., 3x3, 5x5, etc.)
        int tileWidth, tileHeight; // Dimensions of each tile
        int emptyTileX, emptyTileY; // Position of the empty tile

        // Private methods for internal use
        void swapTiles(int x1, int y1, int x2, int y2); // Swap two tiles' positions

    public:
        TileManager(); // Default constructor
        TileManager(int size, int imageWidth, int imageHeight); // Constructor with grid size and image dimensions
        ~TileManager(); // Destructor

        void loadPGMImage(const std::string& filename); // Load image and initialize tiles
        void shuffleTiles(int numMoves); // Shuffle tiles to create a solvable puzzle
        void writePGMImage(const std::string& filename, int moveNumber); // Write current state to a PGM file
        void makeMove(char direction); // Make a move in the specified direction (L, R, U, D)
        bool isValidMove(char direction); // Check if a move is valid

        // Additional methods as needed for game logic and state management
    };
}

#endif // TILEMANAGER_H
