// TileManager.h
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <vector>
#include <string>

namespace MSKMIC017 {
    
    class TileManager {
    private:
        int gridSize;
        int tileWidth;
        int tileHeight;
        int emptyTileX;
        int emptyTileY;
        std::vector<std::vector<Tile>> board;
        void swapTiles(int x1, int y1, int x2, int y2);

    public:
        TileManager(int size); // Constructor that only takes the size of the grid
        ~TileManager(); // Destructor to manage resources if necessary
        bool loadPGMImage(const std::string &filename); // Load image and initialize tiles
        void shuffleTiles();
        void writePGMImage(const std::string &filename, int moveNumber);
    };

}

#endif // TILEMANAGER_H