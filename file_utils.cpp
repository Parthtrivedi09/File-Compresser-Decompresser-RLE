#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstdint>

bool compressRLE(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open input: " << inputFile << "\n";
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open output: " << outputFile << "\n";
        return false;
    }

    char current;
    if (!in.get(current)) return true;  // empty file

    uint8_t count = 1;
    char next;

    while (in.get(next)) {
        if (next == current && count < 255) {
            count++;
        } else {
            out.write(&current, 1);
            out.write(reinterpret_cast<char*>(&count), 1);
            current = next;
            count = 1;
        }
    }

    out.write(&current, 1);
    out.write(reinterpret_cast<char*>(&count), 1);

    return true;
}

bool decompressRLE(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open input: " << inputFile << "\n";
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open output: " << outputFile << "\n";
        return false;
    }

    char value;
    uint8_t count;

    while (true) {
        if (!in.read(&value, 1)) break;
        if (!in.read(reinterpret_cast<char*>(&count), 1)) break;

        for (uint8_t i = 0; i < count; i++)
            out.write(&value, 1);
    }

    return true;
}
