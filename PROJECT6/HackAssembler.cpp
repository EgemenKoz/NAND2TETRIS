#include "HackAssembler.h"

HackAssembler::HackAssembler() : symbolTable(), code(symbolTable)
{
    // Set the symbol table for the parser to use
    HackParser::SetSymbolTable(&symbolTable);
}

HackAssembler::~HackAssembler()
{
}

void HackAssembler::assemble(const std::string& filename)
{
    //Opens the input file (Prog.asm) and gets ready to process it
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Create output file name (.hack extension)
    std::string outputFilename = filename;
    size_t dotPos = outputFilename.find_last_of('.');
    if (dotPos != std::string::npos) {
        outputFilename = outputFilename.substr(0, dotPos);
    }
    outputFilename += ".hack";
    
    // Open output file
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not create output file " << outputFilename << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> instructions;
    
    // First pass: read all instructions
    while (std::getline(inputFile, line))
    {
        // Remove leading/trailing whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue; // Skip empty lines
        
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);
        
        // Skip comment-only lines
        if (line.substr(0, 2) == "//") continue;
        
        // Remove inline comments
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
            // Trim trailing whitespace after removing comment
            end = line.find_last_not_of(" \t\r\n");
            line = line.substr(0, end + 1);
        }
        
        // Skip if line is empty after removing comments
        if (line.empty()) continue;
        
        instructions.push_back(line);
    }

    // Reset symbol table
    symbolTable = HackSymbolTable();
    
    // Second pass: collect all labels
    int lineNumber = 0;
    for (const std::string& instruction : instructions)
    {
        if (instruction.substr(0, 1) == "(")
        {
            std::string label = instruction.substr(1, instruction.size() - 2);
            symbolTable.addEntry(label, lineNumber);
        }
        else
        {
            // Only increment line number for non-label instructions
            lineNumber++;
        }
    }

    // Third pass: translate instructions to binary and write to output file
    for (const std::string& instruction : instructions)
    {
        if (instruction.substr(0, 1) != "(")
        {
            std::string binaryCode = code.getCode(instruction);
            outputFile << binaryCode << std::endl;
        }
    }
    
    // Close files
    inputFile.close();
    outputFile.close();
    
    std::cout << "Assembly complete. Output written to " << outputFilename << std::endl;
}