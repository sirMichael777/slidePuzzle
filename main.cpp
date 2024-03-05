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

    TileManager tileManager(gridSize); 

    if (!tileManager.loadPGMImage(inputFilename)) { 
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    // Save the initial state as image-0.pgm
    tileManager.writePGMImage(outputFilename, 0);

    // Correctly applying one move at a time and saving the state after each move
    for (int move = 1; move <= numMoves; move++) {
        tileManager.shuffleTiles(); // Adjusted to perform only one shuffle move per call
        tileManager.writePGMImage(outputFilename, move); // Save after each single move
    }

    std::cout << "Shuffled puzzle states saved." << std::endl;

    return 0;
}
