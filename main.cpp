#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <iostream>
#include <string>
#include <vector>

using namespace MSKMIC017;

int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cerr << "Usage: " << argv[0] << " -s <size> -i <input.pgm> -n <moves> [-x <output.pgm>]" << std::endl;
        return 1;
    }

    std::string inputFilename;
    std::string outputFilename = "output.pgm"; // Default output file name
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
            i--; // Adjust for optional argument
        }
    }

    // Validate inputs
    if (gridSize <= 0 || numMoves < 0 || inputFilename.empty()) {
        std::cerr << "Invalid input parameters." << std::endl;
        return 1;
    }

    // Load the input image
    std::vector<unsigned char> imageData;
    int width, height;
    if (!PGMImageProcessor::readPGM(inputFilename, imageData, width, height)) {
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    // Initialize the TileManager and the game board
    TileManager manager(gridSize, width, height);
    manager.loadPGMImage(inputFilename); // Assuming this method sets up the tiles correctly

    // Shuffle the tiles to create the initial puzzle state
    manager.shuffleTiles(numMoves);

    // For demonstration, let's write the initial shuffled state to a PGM file
    // You would typically do this in a loop or based on user interaction for each move
    manager.writePGMImage(outputFilename, 0);

    std::cout << "Puzzle initialized and saved to " << outputFilename << std::endl;

    return 0;
}
