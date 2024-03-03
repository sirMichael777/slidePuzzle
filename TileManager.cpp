#include "TileManager.h"
#include "PGMImageProcessor.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

namespace MSKMIC017
{
    // Constructor
    TileManager::TileManager(int size, int imageWidth, int imageHeight) : gridSize(size), emptyTileX(size - 1), emptyTileY(size - 1)
    {
        tileWidth = imageWidth / size;
        tileHeight = imageHeight / size;
        board.resize(size, std::vector<Tile>(size, Tile(tileWidth, tileHeight)));
    }

    // Destructor
    TileManager::~TileManager()
    {
        // If you have dynamically allocated memory within Tiles, manage it here.
        // Given the current design, explicit memory management might not be required.
    }

    void TileManager::loadPGMImage(const std::string &filename)
    {
        std::vector<unsigned char> imageData;
        int imageWidth, imageHeight;
        if (!PGMImageProcessor::readPGM(filename, imageData, imageWidth, imageHeight))
        {
            std::cerr << "Failed to load image: " << filename << std::endl;
            return;
        }

        for (int row = 0; row < gridSize; ++row)
        {
            for (int col = 0; col < gridSize; ++col)
            {
                Tile &tile = board[row][col];
                for (int y = 0; y < tileHeight; ++y)
                {
                    for (int x = 0; x < tileWidth; ++x)
                    {
                        int srcIndex = ((row * tileHeight + y) * imageWidth) + (col * tileWidth + x);
                        int destIndex = y * tileWidth + x;
                        if (srcIndex < imageData.size())
                        {
                            tile.pixelData[destIndex] = imageData[srcIndex];
                        }
                    }
                }
            }
        }
    }

    void TileManager::shuffleTiles(int numMoves)
    {
        std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
        for (int move = 0; move < numMoves; ++move)
        {
            std::vector<char> validMoves;
            if (emptyTileX > 0)
                validMoves.push_back('L'); // Can move left
            if (emptyTileX < gridSize - 1)
                validMoves.push_back('R'); // Can move right
            if (emptyTileY > 0)
                validMoves.push_back('U'); // Can move up
            if (emptyTileY < gridSize - 1)
                validMoves.push_back('D'); // Can move down

            std::shuffle(validMoves.begin(), validMoves.end(), engine);
            makeMove(validMoves.front()); // Make the first valid move
        }
    }

    void TileManager::writePGMImage(const std::string &filename, int moveNumber)
    {
        std::vector<unsigned char> compiledData(tileWidth * gridSize * tileHeight * gridSize, 255); // Initialize with white or another color for empty spaces.

        for (int row = 0; row < gridSize; ++row)
        {
            for (int col = 0; col < gridSize; ++col)
            {
                Tile &tile = board[row][col];
                for (int y = 0; y < tileHeight; ++y)
                {
                    for (int x = 0; x < tileWidth; ++x)
                    {
                        int srcIndex = y * tileWidth + x;
                        int destIndex = ((row * tileHeight + y) * tileWidth * gridSize) + (col * tileWidth + x);
                        compiledData[destIndex] = tile.pixelData[srcIndex];
                    }
                }
            }
        }

        // Adjust filename to include move number
        std::string outputFile = filename.substr(0, filename.size() - 4) + "-" + std::to_string(moveNumber) + ".pgm";
        PGMImageProcessor::writePGM(outputFile, compiledData, tileWidth * gridSize, tileHeight * gridSize);
    }

    void TileManager::makeMove(char direction)
    {
        int newX = emptyTileX, newY = emptyTileY;
        switch (direction)
        {
        case 'L':
            newX -= 1;
            break;
        case 'R':
            newX += 1;
            break;
        case 'U':
            newY -= 1;
            break;
        case 'D':
            newY += 1;
            break;
        }
        if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize)
        {
            swapTiles(emptyTileX, emptyTileY, newX, newY);
            emptyTileX = newX;
            emptyTileY = newY;
        }
    }

    bool TileManager::isValidMove(char direction)
    {
        // Implement logic to check if a move is valid based on the direction and the current position of the empty tile
        return true; // Placeholder
    }

    void TileManager::swapTiles(int x1, int y1, int x2, int y2)
    {
        std::swap(board[y1][x1], board[y2][x2]);
    }
}
