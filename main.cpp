#include "TileManager.h"
#include "PGMImageProcessor.h"
#include <iostream>
#include <string>

using namespace MSKMIC017;

int main(int argc, char* argv[]) {
    if (argc < 7) { //Verify if the number of cmd line args has been supplied
        std::cerr << "Usage: " << argv[0] << " -s <size> -i <input.pgm> -n <moves> -x <summary_output.pgm>" << std::endl;
        return 1;
    }

    std::string inputFilename;
    std::string summaryOutputFilename;
    int gridSize = 0, numMoves = 0;

    // Parse cmd line args & set variables  accordingly
    for (int i = 1; i < argc; i += 2) {
        std::string arg(argv[i]);
        if (arg == "-s") {
            gridSize = std::stoi(argv[i + 1]);  //convert "string to integer"
        } else if (arg == "-i") {
            inputFilename = argv[i + 1];
        } else if (arg == "-n") {
            numMoves = std::stoi(argv[i + 1]);
        } else if (arg == "-x") {
            summaryOutputFilename = argv[i + 1];
        }
    }

    TileManager tileManager(gridSize);  //TileManager obj with  given grid size

    if (!tileManager.loadPGMImage(inputFilename)) {
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    std::string baseOutputFilename = "output";
    
    // Save initial image with the black tile at the bottom right corner
    tileManager.writePGMImage(baseOutputFilename, 0);

    // Make a single valid move of the black tile and save the state
    for (int move = 1; move <= numMoves; move++) {
        tileManager.makeRandomMove();
        tileManager.writePGMImage(baseOutputFilename, move); // Save as output-{move}.pgm
    }

    // Generate Summary image and  save it by the -x arg name
    tileManager.generateSummaryImage(summaryOutputFilename, numMoves);

    std::cout << "Puzzle states and summary image saved." << std::endl;

    return 0;
}
