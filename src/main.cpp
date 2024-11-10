#include "qite.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    Qite engine;

    if (argc > 1) {
        try {
            // Check if file exists
            if (!std::filesystem::exists(argv[1])) {
                std::cerr << "Error: File '" << argv[1] << "' does not exist." << std::endl;
                return 1;
            }

            // Check file extension
            std::string filename(argv[1]);
            if (filename.substr(filename.find_last_of(".") + 1) != "js") {
                std::cerr << "Error: File must have .js extension" << std::endl;
                return 1;
            }

            // Read and execute file
            std::string source = readFile(argv[1]);
            engine.execute(source);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        // Start REPL
        engine.repl();
    }

    return 0;
}