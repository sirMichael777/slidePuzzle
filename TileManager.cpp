// TileManager.cpp
#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cmath> // For sqrt and ceil

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

    board.resize(gridSize, std::vector<Tile>(gridSize, Tile(tileWidth, tileHeight)));
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            Tile& tile = board[row][col];
            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    int index = (row * tileHeight + y) * width + (col * tileWidth + x);
                    tile.pixelData[y * tileWidth + x] = imageData[index];
                }
            }
        }
    }

    // Set the bottom right tile to black
    std::fill(board[gridSize-1][gridSize-1].pixelData.begin(), board[gridSize-1][gridSize-1].pixelData.end(), 0);

    return true;
}

void TileManager::generateSummaryImage(const std::string &summaryOutputFilename, int numMoves) {
    int margin = 10; // Margin size between images and for the outer border
    int cols = std::ceil(std::sqrt(numMoves + 1));
    int rows = std::ceil(static_cast<float>(numMoves + 1) / cols);

    // Adjust the summary image dimensions to include the margins plus an extra margin on all sides for the border
    int summaryWidth = cols * tileWidth * gridSize + (cols - 1) * margin + 2 * margin;
    int summaryHeight = rows * tileHeight * gridSize + (rows - 1) * margin + 2 * margin;
    std::vector<unsigned char> summaryImage(summaryWidth * summaryHeight, 255); // Initialize with white pixels for the border

    for (int move = 0; move <= numMoves; ++move) {
        // Filename construction remains the same
        std::string filename = "output-" + std::to_string(move) + ".pgm";
        std::vector<unsigned char> moveImageData;
        int width, height;
        if (!PGMImageProcessor::readPGM(filename, moveImageData, width, height)) {
            std::cerr << "Error reading image file: " << filename << std::endl;
            continue; // Skip this file if there's an error
        }

        int moveRow = move / cols;
        int moveCol = move % cols;
        // Start position now includes the border margin as well
        int startX = margin + moveCol * (width + margin);
        int startY = margin + moveRow * (height + margin);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int destIndex = ((startY + y) * summaryWidth) + (startX + x);
                summaryImage[destIndex] = moveImageData[y * width + x];
            }
        }
    }

    // Write the summary image to file
    PGMImageProcessor::writePGM(summaryOutputFilename, summaryImage, summaryWidth, summaryHeight);
}




// Shuffle tiles to create a solvable puzzle state
void MSKMIC017::TileManager::shuffleTiles() {
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<std::pair<int, int>> validMoves;

    if (emptyTileX > 0) validMoves.emplace_back(emptyTileX - 1, emptyTileY);
    if (emptyTileX < gridSize - 1) validMoves.emplace_back(emptyTileX + 1, emptyTileY);
    if (emptyTileY > 0) validMoves.emplace_back(emptyTileX, emptyTileY - 1);
    if (emptyTileY < gridSize - 1) validMoves.emplace_back(emptyTileX, emptyTileY + 1);

    if (!validMoves.empty()) {
        std::shuffle(validMoves.begin(), validMoves.end(), engine);
        auto [newX, newY] = validMoves.front();
        swapTiles(emptyTileX, emptyTileY, newX, newY);
        emptyTileX = newX;
        emptyTileY = newY;
    }
}




// Write the current tile arrangement to a PGM image
void MSKMIC017::TileManager::writePGMImage(const std::string &baseFilename, int moveNumber) {
    std::string outputFilename = baseFilename.substr(0, baseFilename.find_last_of('.')) + "-" + std::to_string(moveNumber) + ".pgm";
    int imageWidth = gridSize * tileWidth;
    int imageHeight = gridSize * tileHeight;
    std::vector<unsigned char> image(imageWidth * imageHeight, 255);

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            const Tile& tile = board[row][col];
            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    image[(row * tileHeight + y) * imageWidth + (col * tileWidth + x)] = tile.pixelData[y * tileWidth + x];
                }
            }
        }
    }

    if (!PGMImageProcessor::writePGM(outputFilename, image, imageWidth, imageHeight)) {
        std::cerr << "Failed to write output image: " << outputFilename << std::endl;
    }
}


// Swap two tiles in the grid
void TileManager::swapTiles(int x1, int y1, int x2, int y2) {
    std::swap(board[y1][x1], board[y2][x2]);
}

} // namespace MSKMIC017
