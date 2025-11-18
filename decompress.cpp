#include <iostream>
#include <thread>
#include <vector>
#include "file_utils.h"

const int NUM_THREADS = 4;

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back([i]() {
            std::string src = "compressed_chunk_" + std::to_string(i) + ".rle";
            std::string dst = "decompressed_chunk_" + std::to_string(i) + ".bin";

            if (decompressRLE(src, dst))
                std::cout << "Decompressed chunk " << i << "\n";
            else
                std::cerr << "Failed chunk " << i << "\n";
        });
    }

    for (auto &t : threads) t.join();

    std::cout << "Decompression finished.\n";
    return 0;
}
