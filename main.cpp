#include "PGMImageProcessor.h"
#include <iostream>
#include <vector>
#include <string>

using namespace MSKMIC017;

int main(int argc, char *argv[])
{
    if (argc < 7)
    {
        std::cerr << "Usage: " << argv[0] << " -s <size> -i <input.pgm> -n <moves> -x <output.pgm>" << std::endl;
        return 1;
    }

    std::string inputFilename;
    std::string outputFilename;
    int gridSize = 0, numMoves = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i += 2)
    {
        std::string arg(argv[i]);
        if (arg == "-s")
        {
            gridSize = std::stoi(argv[i + 1]);
        }
        else if (arg == "-i")
        {
            inputFilename = argv[i + 1];
        }
        else if (arg == "-n")
        {
            numMoves = std::stoi(argv[i + 1]);
        }
        else if (arg == "-x")
        {
            outputFilename = argv[i + 1];
        }
    }

    // Debugging statement to confirm parsed arguments
    std::cout << "Parsed arguments: gridSize=" << gridSize
              << ", inputFilename=" << inputFilename
              << ", numMoves=" << numMoves
              << ", outputFilename=" << outputFilename << std::endl;

    // Read the input image
    std::vector<unsigned char> imageData;
    int width, height;
    if (!PGMImageProcessor::readPGM(inputFilename, imageData, width, height))
    {
        std::cerr << "Failed to load image: " << inputFilename << std::endl;
        return 1;
    }

    std::cout << "Image loaded successfully: " << inputFilename
              << " with dimensions " << width << "x" << height << std::endl;

    // Example manipulation: Let's just reverse the image data for demonstration
    std::reverse(imageData.begin(), imageData.end());

    // Write the output image
    if (!PGMImageProcessor::writePGM(outputFilename, imageData, width, height))
    {
        std::cerr << "Failed to write image data to file: " << outputFilename << std::endl;
        return 1;
    }

    std::cout << "Shuffled puzzle state saved to: " << outputFilename << std::endl;

    return 0;
}
