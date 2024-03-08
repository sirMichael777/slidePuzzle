// TileManager.cpp
#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath> // For sqrt and ceil

namespace MSKMIC017
{

    TileManager::TileManager(int size) : gridSize(size), tileWidth(0), tileHeight(0), board(static_cast<Tile *>(operator new[](size * size * sizeof(Tile))))
    {
        // Memory allocated
    }

    TileManager::~TileManager()
    {
        for (int i = 0; i < gridSize * gridSize; ++i)
        {
            board[i].~Tile(); // call the destructor for each Tile
        }
        operator delete[](board); // Free  memory
    }

    bool TileManager::loadPGMImage(const std::string &filename)
    {
        std::vector<unsigned char> imageData;
        int width, height;
        if (!PGMImageProcessor::readPGM(filename, imageData, width, height))
        {
            std::cerr << "Error reading the provided PGM file." << std::endl;
            return false;
        }

        tileWidth = width / gridSize;
        tileHeight = height / gridSize;

        for (int row = 0; row < gridSize; ++row)
        {
            for (int col = 0; col < gridSize; ++col)
            {
                int index = row * gridSize + col;
                board[index] = Tile(tileWidth, tileHeight); // Construct each Tile

                for (int y = 0; y < tileHeight; ++y)
                {
                    for (int x = 0; x < tileWidth; ++x)
                    {
                        int imageIndex = (row * tileHeight + y) * width + (col * tileWidth + x);
                        board[index].pixelData[y * tileWidth + x] = imageData[imageIndex];
                    }
                }
            }
        }

        // Manually set the bottom right tile to black.
        Tile &bottomRightTile = board[gridSize * gridSize - 1];
        for (int i = 0; i < bottomRightTile.width * bottomRightTile.height; i++)
        {
            bottomRightTile.pixelData[i] = 0;
        }

        return true;
    }
 void TileManager::makeRandomMove()
    {
        // Assume the empty tile is initially at the bottom right
        static int emptyTileX = gridSize - 1;
        static int emptyTileY = gridSize - 1;

        std::vector<std::pair<int, int>> moveOptions; // Each pair is a potential move (dx, dy)

        // Check for valid moves and add them to moveOptions
        if (emptyTileX > 0)
            moveOptions.emplace_back(-1, 0); // Left
        if (emptyTileX < gridSize - 1)
            moveOptions.emplace_back(1, 0); // Right
        if (emptyTileY > 0)
            moveOptions.emplace_back(0, -1); // Up
        if (emptyTileY < gridSize - 1)
            moveOptions.emplace_back(0, 1); // Down

        // Randomly select a move
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, moveOptions.size() - 1);
        int moveIndex = dis(gen);
        auto [dx, dy] = moveOptions[moveIndex];

        // Swap the empty tile with the selected adjacent tile
        swapTiles(emptyTileX, emptyTileY, emptyTileX + dx, emptyTileY + dy);

        // Update the empty tile's position
        emptyTileX += dx;
        emptyTileY += dy;
    }
    // Swaps two tiles in memory by their coordinates
     void TileManager::swapTiles(int x1, int y1, int x2, int y2)
    {
        int index1 = y1 * gridSize + x1;
        int index2 = y2 * gridSize + x2;
        std::swap(board[index1], board[index2]); // Swap Tiles using calculated indices
    }

    
    //For future use 
    // void TileManager::shuffleTiles()
    // {
    //     // Shuffle logic adjusted for dynamically allocated array
    //     std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    //     for (int i = 0; i < gridSize * gridSize; i++)
    //     {
    //         int j = engine() % (gridSize * gridSize);
    //         std::swap(board[i], board[j]); // Swap Tiles
    //     }
    // }

    void TileManager::writePGMImage(const std::string &filename, int moveNumber)
    {
        int imageWidth = gridSize * tileWidth;
        int imageHeight = gridSize * tileHeight;
        std::vector<unsigned char> image(imageWidth * imageHeight, 255); // Initialize image with white pixels

        for (int row = 0; row < gridSize; row++)
        {
            for (int col = 0; col < gridSize; col++)
            {
                Tile &tile = board[row * gridSize + col];
                for (int y = 0; y < tileHeight; y++)
                {
                    for (int x = 0; x < tileWidth; x++)
                    {
                        int destIndex = ((row * tileHeight + y) * imageWidth) + (col * tileWidth + x);
                        int srcIndex = y * tileWidth + x;
                        image[destIndex] = tile.pixelData[srcIndex];
                    }
                }
            }
        }

        std::string outputFilename = filename.substr(0, filename.find_last_of('.')) + "-" + std::to_string(moveNumber) + ".pgm";
        PGMImageProcessor::writePGM(outputFilename, image, imageWidth, imageHeight);
    }

    void TileManager::generateSummaryImage(const std::string &baseFilename, int numMoves)
    {
        int cols = std::ceil(std::sqrt(numMoves + 1));
        int rows = std::ceil((float)(numMoves + 1) / cols);
        int margin = 10;                                                            // Margin between images and around the border
        int summaryWidth = cols * (tileWidth * gridSize + margin) + margin;         // Total width with margins
        int summaryHeight = rows * (tileHeight * gridSize + margin) + margin;       // Total height with margins
        std::vector<unsigned char> summaryImage(summaryWidth * summaryHeight, 255); // Initialize with white pixels

        for (int move = 0; move <= numMoves; move++)
        {
            // Construct filename for current move
            std::string currentFilename = "output-" + std::to_string(move) + ".pgm";

            // Load the image for the current move
            std::vector<unsigned char> imageData;
            int width, height;
            if (!PGMImageProcessor::readPGM(currentFilename, imageData, width, height))
            {
                std::cerr << "Failed to load image: " << currentFilename << std::endl;
                continue; // Skip this file if it fails to load
            }

            int moveRow = move / cols;
            int moveCol = move % cols;
            int startX = margin + moveCol * (tileWidth * gridSize + margin);
            int startY = margin + moveRow * (tileHeight * gridSize + margin);

            // Place each loaded image into the correct position in the summary image
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int srcIndex = y * width + x;
                    int destX = startX + x;
                    int destY = startY + y;
                    int destIndex = destY * summaryWidth + destX;
                    summaryImage[destIndex] = imageData[srcIndex];
                }
            }
        }

        // Write the assembled summary image to the specified base filename
        PGMImageProcessor::writePGM(baseFilename, summaryImage, summaryWidth, summaryHeight);
    }

   

} // namespace MSKMIC017
