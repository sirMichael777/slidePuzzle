#include "PGMImageProcessor.h"
#include <fstream>
#include <iostream>
#include <limits>

namespace MSKMIC017
{
    bool PGMImageProcessor::readPGM(const std::string &filename, std::vector<unsigned char> &data, int &width, int &height)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line); // Read the magic number
        if (line != "P5")
        {
            std::cerr << "Unsupported file format (must be P5): " << filename << std::endl;
            return false;
        }

        // Skip any comment lines
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
            std::cerr << "Unsupported max value (must be <= 255): " << filename << std::endl;
            return false;
        }

        data.resize(width * height);
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
            std::cerr << "Error occurred while writing to file: " << filename << std::endl;
            return false;
        }

        return true;
    }

}
