#include "Qite.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Qite qite;

    if (argc > 1) {
        // If a filename is provided as a command line argument, execute from that file
        std::string filename = argv[1];
        qite.executeFromFile(filename);
    } else {
        // Display an error message in bold red text
        std::cerr << "\033[1;31mError: no filename provided\033[0m" << std::endl;
    }

    return 0;
}