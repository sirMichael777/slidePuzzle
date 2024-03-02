// PGMImageProcessor.h
#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H

#include <vector>
#include <string>

namespace MSKMIC017 {
    class PGMImageProcessor {
    public:
        // Reads a PGM image file and fills the passed parameters with image data.
        static bool readPGM(const std::string& filename, std::vector<unsigned char>& data, int& width, int& height);

        // Writes a PGM image file using the provided image data.
        static bool writePGM(const std::string& filename, const std::vector<unsigned char>& data, int width, int height);
    };
}

#endif // PGMIMAGEPROCESSOR_H
