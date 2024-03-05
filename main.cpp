#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <iostream>
#include <string>

using namespace MSKMIC017;

int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cerr << "Usage: " << argv[0] << " -s <size> -i <input.pgm> -n <moves> -x <summary_output.pgm>" << std::endl;
        return 1;
    }

    std::string inputFilename;
    std::string summaryOutputFilename;
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
            summaryOutputFilename = argv[i + 1];
        }
    }

    TileManager tileManager(gridSize);

    if (!tileManager.loadPGMImage(inputFilename)) {
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    // Always use "output" as the base for individual moves
    std::string baseOutputFilename = "output";

    // Save the initial state as output-0.pgm
    tileManager.writePGMImage(baseOutputFilename, 0);

    // Shuffle and save the state after each move
    for (int move = 1; move <= numMoves; move++) {
        tileManager.shuffleTiles();
        tileManager.writePGMImage(baseOutputFilename, move); // Save as output-{move}.pgm
    }

    // Generate and save the summary image using the filename provided by the -x flag
    tileManager.generateSummaryImage(summaryOutputFilename, numMoves);

    std::cout << "Shuffled puzzle states and summary image saved." << std::endl;

    return 0;
}
