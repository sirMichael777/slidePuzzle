// TileManager.h
#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <string>

namespace MSKMIC017 {
    
    class TileManager {
    private:
        int gridSize;
        int tileWidth;
        int tileHeight;
        Tile* board; // Dynamically allocated array of Tiles

    public:
        TileManager(int size);
        ~TileManager();
        bool loadPGMImage(const std::string &filename);
        void shuffleTiles();
        void writePGMImage(const std::string &filename, int moveNumber);
        void generateSummaryImage(const std::string &baseFilename, int numMoves);
        void swapTiles(int x1, int y1, int x2, int y2);
        void makeRandomMove();
    };

} // namespace MSKMIC017

#endif // TILEMANAGER_H
