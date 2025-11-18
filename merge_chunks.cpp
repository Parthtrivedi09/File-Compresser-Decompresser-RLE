#include <iostream>
#include <fstream>

const int NUM_THREADS = 4;

int main() {
    std::ofstream out("final_decompressed.txt", std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open final file.\n";
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        std::string chunk = "decompressed_chunk_" + std::to_string(i) + ".bin";
        std::ifstream in(chunk, std::ios::binary);

        if (!in) {
            std::cerr << "Missing: " << chunk << "\n";
            continue;
        }

        out << in.rdbuf();
    }

    std::cout << "Merged successfully.\n";
    return 0;
}
