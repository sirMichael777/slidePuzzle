// TileManager.cpp
#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

namespace MSKMIC017 {

// Constructor implementation
TileManager::TileManager(int size) : gridSize(size), tileWidth(0), tileHeight(0), emptyTileX(size - 1), emptyTileY(size - 1) {
    // The actual size of tiles will be determined once the image is loaded.
}

// Destructor implementation
TileManager::~TileManager() {
    // If dynamic memory was used, it should be released here.
    // No dynamic memory allocation in this implementation, so empty destructor.
}

// Load PGM image and initialize tiles
bool TileManager::loadPGMImage(const std::string &filename) {
    std::vector<unsigned char> imageData;
    int width, height;

    if (!PGMImageProcessor::readPGM(filename, imageData, width, height)) {
        std::cerr << "Error reading PGM file." << std::endl;
        return false;
    }

    tileWidth = width / gridSize;
    tileHeight = height / gridSize;
    int tileArea = tileWidth * tileHeight;

    board.clear();
    board.reserve(gridSize);
    for (int row = 0; row < gridSize; ++row) {
        std::vector<Tile> tileRow(gridSize, Tile(tileWidth, tileHeight));
        for (int col = 0; col < gridSize; ++col) {
            Tile& tile = tileRow[col];
            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    int originalIndex = (row * tileHeight + y) * width + (col * tileWidth + x);
                    int tileIndex = y * tileWidth + x;
                    tile.pixelData[tileIndex] = imageData[originalIndex];
                }
            }
        }
        board.push_back(tileRow);
    }

    // Set the bottom right tile to black (the empty tile)
    std::fill(board[emptyTileY][emptyTileX].pixelData.begin(), board[emptyTileY][emptyTileX].pixelData.end(), 0);

    return true;
}

// Shuffle tiles to create a solvable puzzle state
void TileManager::shuffleTiles(int numMoves) {
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    for (int move = 0; move < numMoves; ++move) {
        std::vector<std::pair<int, int>> validMoves;

        // Add valid moves (up, down, left, right)
        if (emptyTileX > 0) validMoves.emplace_back(emptyTileX - 1, emptyTileY);
        if (emptyTileX < gridSize - 1) validMoves.emplace_back(emptyTileX + 1, emptyTileY);
        if (emptyTileY > 0) validMoves.emplace_back(emptyTileX, emptyTileY - 1);
        if (emptyTileY < gridSize - 1) validMoves.emplace_back(emptyTileX, emptyTileY + 1);

        // Shuffle the valid moves and choose one
        std::shuffle(validMoves.begin(), validMoves.end(), engine);
        auto [newX, newY] = validMoves.front();

        // Swap the empty tile with the chosen tile
        swapTiles(emptyTileX, emptyTileY, newX, newY);

        // Update empty tile position
        emptyTileX = newX;
        emptyTileY = newY;
    }
}

// Write the current tile arrangement to a PGM image
void TileManager::writePGMImage(const std::string &filename, int moveNumber) {
    int imageWidth = tileWidth * gridSize;
    int imageHeight = tileHeight * gridSize;
    std::vector<unsigned char> image(imageWidth * imageHeight, 255); // Initialize with white background

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            const Tile &tile = board[row][col];
            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    int imageIndex = (row * tileHeight + y) * imageWidth + (col * tileWidth + x);
                    int tileIndex = y * tileWidth + x;
                    image[imageIndex] = tile.pixelData[tileIndex];
                }
            }
        }
    }

    // Construct the filename with the move number
    std::string outputFilename = filename.substr(0, filename.find_last_of('.')) + "-" + std::to_string(moveNumber) + ".pgm";

    // Write the image using PGMImageProcessor
    if (!PGMImageProcessor::writePGM(outputFilename, image, imageWidth, imageHeight)) {
        std::cerr << "Error writing PGM file: " << outputFilename << std::endl;
    }
}

// Swap two tiles in the grid
void TileManager::swapTiles(int x1, int y1, int x2, int y2) {
    std::swap(board[y1][x1], board[y2][x2]);
}

} // namespace MSKMIC017
