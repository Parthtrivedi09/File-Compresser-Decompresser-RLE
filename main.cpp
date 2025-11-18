#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "file_utils.h"

const int NUM_THREADS = 4;

int main() {
    std::ifstream in("input.txt", std::ios::binary);
    if (!in) {
        std::cerr << "input.txt missing.\n";
        return 1;
    }

    in.seekg(0, std::ios::end);
    size_t fileSize = in.tellg();
    in.seekg(0);

    size_t chunkSize = fileSize / NUM_THREADS;

    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back([&, i]() {
            size_t start = i * chunkSize;
            size_t end = (i == NUM_THREADS - 1) ? fileSize : (i + 1) * chunkSize;

            size_t size = end - start;
            std::vector<char> buffer(size);

            {
                std::ifstream fin("input.txt", std::ios::binary);
                fin.seekg(start);
                fin.read(buffer.data(), size);
            }

            std::string tempInput = "chunk_" + std::to_string(i) + ".bin";
            std::string tempOutput = "compressed_chunk_" + std::to_string(i) + ".rle";

            {
                std::ofstream fout(tempInput, std::ios::binary);
                fout.write(buffer.data(), size);
            }

            compressRLE(tempInput, tempOutput);
        });
    }

    for (auto &t : threads) t.join();

    std::cout << "Compression complete.\n";
    return 0;
}
