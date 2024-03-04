#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace MSKMIC017;

int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cerr << "Usage: " << argv[0] << " -s <size> -i <input.pgm> -n <moves> -x <output.pgm>" << std::endl;
        return 1;
    }

    std::string inputFilename;
    std::string outputFilename;
    int gridSize = 0, numMoves = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i += 2) {
        std::string arg(argv[i]);
        if (arg == "-s") {
            gridSize = std::stoi(argv[i + 1]);
        } else if (arg == "-i") {
            inputFilename = argv[i + 1];
        } else if (arg == "-n") {
            numMoves = std::stoi(argv[i + 1]);
        } else if (arg == "-x") {
            outputFilename = argv[i + 1];
        }
    }

    // Debugging statement to confirm parsed arguments
    std::cout << "Parsed arguments: gridSize=" << gridSize 
              << ", inputFilename=" << inputFilename 
              << ", numMoves=" << numMoves 
              << ", outputFilename=" << outputFilename << std::endl;

    // Initialize TileManager with the image dimensions and grid size
    TileManager tileManager(gridSize); // Grid size is passed to the TileManager constructor

    // Load the input image into the TileManager
    if (!tileManager.loadPGMImage(inputFilename)) { // Load image data into tiles
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    // Shuffle the tiles as specified by numMoves
    tileManager.shuffleTiles(numMoves);

    // Write out the initial state as image-0.pgm
    tileManager.writePGMImage(outputFilename, 0);

    // Perform moves and write each shuffled state to a file
    for (int move = 1; move <= numMoves; move++) {
        // Shuffle the tiles for one move
        tileManager.shuffleTiles(1);
        
        // Write the current shuffled state to a file
        tileManager.writePGMImage(outputFilename, move);
    }

    std::cout << "Shuffled puzzle states saved." << std::endl;

    return 0;
}
