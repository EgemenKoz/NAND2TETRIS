#include <iostream>
#include <string>
#include "HackAssembler.h"

int main(int argc, char* argv[]) {
    // Check if filename is provided as command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.asm>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    
    // Verify the file has .asm extension
    if (filename.length() < 5 || filename.substr(filename.length() - 4) != ".asm") {
        std::cerr << "Error: File must have .asm extension" << std::endl;
        return 1;
    }

    // Create assembler and process the file
    HackAssembler assembler;
    try {
        assembler.assemble(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error during assembly: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error during assembly" << std::endl;
        return 1;
    }

    return 0;
}
