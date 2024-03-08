#include "PGMImageProcessor.h"
#include <fstream>
#include <iostream>
#include <limits>

namespace MSKMIC017
{
    // method to read and store the width, height and pixel info of a PGM image
    bool PGMImageProcessor::readPGM(const std::string &filename, std::vector<unsigned char> &data, int &width, int &height)
    {
        std::ifstream file(filename, std::ios::binary); 
        if (!file)
        {
            std::cerr << "Cannot open file: " << filename <<", please make sure to check the spelling and verify if it's in the right location"<< std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line); // Read the magic number and confirm it is P5
        if (line != "P5")
        {
            std::cerr << "Unsupported file format, only P5 is allowed: " << filename << std::endl;
            return false;
        }

        // Skip comments
        while (file.peek() == '#')
        {
            std::getline(file, line);
        }

        file >> width >> height;
        int maxVal;
        file >> maxVal;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip the newline character after the maxVal

        if (maxVal > 255)
        {
            std::cerr << "Invalid max value {must be <= 255}: " << filename << std::endl;
            return false;
        }

        data.resize(width * height);    //Make data size equal to that of  the image
        file.read(reinterpret_cast<char *>(&data[0]), data.size());

        if (!file)
        {
            std::cerr << "Error reading image data from file: " << filename << std::endl;
            return false;
        }

        return true;
    }
    bool PGMImageProcessor::writePGM(const std::string &filename, const std::vector<unsigned char> &data, int width, int height)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Cannot open file for writing: " << filename << std::endl;
            return false;
        }

        // Write PGM header
        file << "P5\n"
             << width << " " << height << "\n255\n";

        // Write pixel data
        file.write(reinterpret_cast<const char *>(data.data()), data.size());

        if (!file.good())
        {
            std::cerr << "An error occurred while writing to file: " << filename << std::endl;
            return false;
        }

        return true;
    }

}
